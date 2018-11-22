#include "h8-3052-iodef.h"

void ad_init();
void ad_start(unsigned char ch, unsigned char int_sw);

void ad_init()
     /* A/D 変換器を使うための初期化関数 */
     /* 単一スキャンのみ対応             */
{
  unsigned char dmy;

  ADCR = 0x7e;  /* 外部トリガ変換開始の禁止 */
  dmy = ADCSR;  /* 変換終了フラグクリアのためのダミーリード */
  ADCSR = 0x08; /* 単一スキャン, 割り込み禁止, A/D変換停止, */
                /* 134ステート変換時間, チャネル 0 選択     */
}

void ad_start(unsigned char ch, unsigned char int_sw)
     /* A/D変換をスタートさせる関数                                */
     /* ch:入力チャネル番号(0-7), int_sw:変換終了割り込み許可(0,1) */
     /* 割り込み許可の場合, 別途割り込みハンドラが必要             */
     /* また, CPUを割り込み許可状態にしないと割り込みは発生しない  */
     /* 割り込み処理には数usの時間がかかることを考慮すること       */
{
  if (int_sw != 0) int_sw = 0x40;
  else int_sw = 0;
  ADCSR = (ADCSR & 0xd8) | (ch & 0x07);   /* 変換停止, チャネルの書き換え */
  ADCSR = (ADCSR & 0x1f) | 0x20 | int_sw; /* エンドフラグクリア, 変換開始 */
}
