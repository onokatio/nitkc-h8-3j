#include "h8-3052-iodef.h"

/* 内部クロックφのときの1usあたりのGRA値 */
#define TCONST1us 25
#define CLKDIV1MAX 2621
#define CLKDIV2MAX 5242
#define CLKDIV4MAX 10485
#define CLKDIV8MAX 20971

int timer_set(int ch, unsigned int time_us);
void timer_start(int ch);
void timer_stop(int ch);
void timer_init(void);
void timer_intflag_reset(int ch);

int timer_set(int ch, unsigned int time_us)
     /* 指定チャネルのタイマを指定時間間隔で割り込み設定する関数 */
     /* ch:0-4, time_us:1-20971 の範囲でないと正常動作しない     */
     /* φ=25MHz のとき, φ/1 : 2621.4 us   φ/2 : 5242.8 us     */
     /* 最大の指定周期は φ/4 : 10485.6 us  φ/8 : 20971.2 us    */
     /* ch = x (x = 0-4) のとき int_imiax() に制御が移る         */
     /* CPU自体の割り込み許可を出さなければ動かない              */
     /* 戻り値: 指定が適正なときは1、適正でないときは -1         */
     /* 注意: 指定したタイマは停止するので別途スタートさせること */
{
  unsigned long tcr_addr,tsr_addr,tior_addr,tier_addr;
  unsigned long grah_addr,gral_addr,tcnth_addr,tcntl_addr;
  unsigned int gra,rf;
  unsigned char dmy,clk_div,chmask;

  switch (ch){
  case 1:
    tcr_addr = 0xffff6e;   tior_addr = 0xffff6f;
    tsr_addr = 0xffff71;   tier_addr = 0xffff70;
    tcnth_addr = 0xffff72; tcntl_addr = 0xffff73;
    grah_addr = 0xffff74;  gral_addr = 0xffff75;
    break;
  case 2:
    tcr_addr = 0xffff78;   tior_addr = 0xffff79;
    tsr_addr = 0xffff7b;   tier_addr = 0xffff7a;
    tcnth_addr = 0xffff7c; tcntl_addr = 0xffff7d;
    grah_addr = 0xffff7e;  gral_addr = 0xffff7f;
    break;
  case 3:
    tcr_addr = 0xffff82;   tior_addr = 0xffff83;
    tsr_addr = 0xffff85;   tier_addr = 0xffff84;
    tcnth_addr = 0xffff86; tcntl_addr = 0xffff87;
    grah_addr = 0xffff88;  gral_addr = 0xffff89;
    break;
  case 4:
    tcr_addr = 0xffff92;   tior_addr = 0xffff93;
    tsr_addr = 0xffff95;   tier_addr = 0xffff94;
    tcnth_addr = 0xffff96; tcntl_addr = 0xffff97;
    grah_addr = 0xffff98;  gral_addr = 0xffff99;
    break;
  case 0:
  default:
    ch = 0;
    tcr_addr = 0xffff64;   tior_addr = 0xffff65;
    tsr_addr = 0xffff67;   tier_addr = 0xffff66;
    tcnth_addr = 0xffff68; tcntl_addr = 0xffff69;
    grah_addr = 0xffff6a;  gral_addr = 0xffff6b;
    break;
  }
  clk_div = 0;
  if (time_us > 0) rf = 1;
  else rf = -1;
  if (time_us > CLKDIV1MAX) clk_div = 1; /* Φ = φ/2 */
  if (time_us > CLKDIV2MAX) clk_div = 2; /* Φ = φ/4 */
  if (time_us > CLKDIV4MAX) clk_div = 3; /* Φ = φ/8 */
  if (time_us > CLKDIV8MAX) rf = -1;
  /* 設定するタイマの動作を止める */
  chmask = 1;
  chmask = ~(chmask << ch);
  TSTR = TSTR & chmask;
  /* TCNT(カウンタ)を 0 にリセット */
  *((volatile unsigned char *)tcnth_addr) = 0;
  *((volatile unsigned char *)tcntl_addr) = 0;
  /* GRAコンペアマッチクリア, 内部クロックΦ(自動選択) */
  *((volatile unsigned char *)tcr_addr) = 0xa0 | (clk_div & 0x02);
  /* GRAはアウトプットコンペアレジスタ */
  *((volatile unsigned char *)tior_addr)
    = (*((volatile unsigned char *)tior_addr) & 0xf0) | 0x08;
  /* TSRのフラグをリセット */
  dmy = *((volatile unsigned char *)tsr_addr);
  *((volatile unsigned char *)tsr_addr) = 0xf8;
  /* GRA=TCNTのときの割り込み許可 */
  *((volatile unsigned char *)tier_addr) = 0xf9;
  /* 指定された時間間隔になるようにGRAをセット */
  gra = (unsigned int)(time_us * TCONST1us / (1 << clk_div));
  *((volatile unsigned char *)gral_addr) = gra & 0xff;
  *((volatile unsigned char *)grah_addr) = (gra >> 8) & 0xff;
  return rf;
}

void timer_start(int ch)
     /* 指定チャネルのタイマ動作を開始する関数                    */
     /* 指定チャネルの範囲 ch: 0-4                                */
     /* CPUの割り込み許可を行わないと割り込みは発生しないので注意 */
{
  unsigned char chmask;

  if ((ch < 0) || (ch > 4)) ch = 0;
  chmask = 1;
  chmask = chmask << ch;
  TSTR = TSTR | chmask;
}

void timer_stop(int ch)
     /* 指定チャネルのタイマ動作を停止する関数                    */
     /* 指定チャネルの範囲 ch: 0-4                                */
{
  unsigned char chmask;

  if ((ch < 0) || (ch > 4)) ch = 0;
  chmask = 1;
  chmask = ~(chmask << ch);
  TSTR = TSTR & chmask;
}

void timer_init(void)
     /* 16ビットタイマの初期化を行う関数                 */
     /* タイマを使用するときには, 最初に必ず呼び出すこと */
{
  TSNC = 0xe0; /* チャネル0-4 全て独立動作 */
  TMDR = 0x80; /* チャネル0-4 全て通常動作モード */
  TFCR = 0xc0; /* チャネル3,4 は通常動作 */
  TOER = 0xc0; /* チャネル3,4 の端子出力を禁止 */
  TOCR = 0xff; /* 通常動作では設定意味なし、初期値に設定 */
}

void timer_intflag_reset(int ch)
     /* 指定チャネルのタイマの割り込みフラグのリセットを行う関数   */
     /* 指定チャネルの範囲 ch: 0-4                                 */
     /* 割り込みハンドラ内の割り込みを許可する前に必ず呼び出すこと */
{
  unsigned char dmy;

  switch (ch){
  case  1: dmy = TSR1; TSR1 = 0xf8; break; /* タイマ1の処理 */
  case  2: dmy = TSR2; TSR2 = 0xf8; break; /* タイマ2の処理 */
  case  3: dmy = TSR3; TSR3 = 0xf8; break; /* タイマ3の処理 */
  case  4: dmy = TSR4; TSR4 = 0xf8; break; /* タイマ4の処理 */
  case  0:
  default: dmy = TSR0; TSR0 = 0xf8;        /* タイマ0の処理 */
  }
}
