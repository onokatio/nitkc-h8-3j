#include "h8-3052-iodef.h"

#define MIC     0
#define SPEAKER 1

void da_init();
void da_out(unsigned char ch, unsigned char val);
void da_stop(unsigned char ch);
void speaker_switch(int mode);

void da_init()
     /* D/A 変換とスピーカ切替えの初期化をする関数 */
{
  P9DR = P9DR | 0x10;   
  P9DDR = P9DDR | 0x10; /* フォトMOS制御用のポート P94 を出力設定 */
  DACR = 0x1f;          /* D/A変換出力禁止                        */ 
}

void da_out(unsigned char ch, unsigned char val)
     /* D/A変換を出力するための関数                      */
     /*   ch: チャネル指定(0, 1)  val: 出力値(8ビット長) */
     /*   出力すると共用している端子は D/A しか使えない  */
     /*   DA0: P76, AN6  DA1: P77, AN7 とそれぞれ共用    */
{
  if (ch == 0){
    DADR0 = val;
    DACR = DACR | 0x40;
  } else {
    DADR1 = val;
    DACR = DACR | 0x80;
  }
}

void da_stop(unsigned char ch)
     /* D/A変換を停止するための関数                    */
     /*   停止すると共用している端子を他の用途に使用可 */
     /*   DA0: P76, AN6  DA1: P77, AN7 とそれぞれ共用  */
{
  if (ch == 0) DACR = DACR & 0xbf;       /* DA0 の停止 */
  else DACR = DACR & 0x7f;               /* DA1 の停止 */
}

void speaker_switch(int mode)
     /* スピーカの機能を選択するための関数 */
     /*   mode: SPEAKER, MIC               */
{
  if (mode == SPEAKER) P9DR = P9DR & 0xef; /* フォトMOSをON (D/A 0 を接続) */
  else P9DR = P9DR | 0x10;                 /* フォトMOSをOFF               */
}
