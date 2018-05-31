#include "h8-3052-iodef.h"
#define MILLISEC 14280


void sleep(int max){
	int i,j,k,c;

	for(c=0; c < max;c++)
		for(i=0; i < MILLISEC ;i++); //ミリ秒分空ループする
}

int main(void)
{
	char b4_old;
	char b5_old;
	char b4_new = 0;
	char b5_new = 0;
	char dout = 0;
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */
	P9DR = 0xff;


  while(1)
  {

		b4_old = b4_new; //前回の状態を保存
		b5_old = b5_new; 

		b4_new = ~(b5_old ^ b4_old) & 0x01; //前回の2つのLEDをxor
		b5_new = (~b5_old)          & 0x01; //前回のb5ポートを反転

		dout = ( b4_new << 4 | b5_new << 5 ) | ( dout & 0xCF ); //任意のビットのみ変更
		P9DR = dout;

		sleep(1000); //　1秒スリープ
  }
}
