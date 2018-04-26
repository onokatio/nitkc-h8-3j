#include "h8-3052-iodef.h"
#define MILLISEC 14280


void sleep(int max){
	int i,j,k,c;

	for(c=0; c < max;c++)
		for(i=0; i < MILLISEC ;i++);
}

int main(void)
{
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */


  while(1)
  {
		P9DR = 0xff;  /* 出力データをセット */
		sleep(1000);
		P9DR &= ~0x10;  /* 出力データをセット */
		sleep(1000);
		P9DR &= ~0x20;  /* 出力データをセット */
		sleep(1000);
		P9DR &= 0x00;  /* 出力データをセット */
		sleep(1000);
  }
}
