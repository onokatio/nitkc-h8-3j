#include "h8-3052-iodef.h"
#define MILLISEC 14280


void sleep(int max){
	int i,j,k,c;

	for(c=0; c < max;c++)
		for(i=0; i < MILLISEC ;i++);
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

		b4_old = b4_new;
		b5_old = b5_new;

		b4_new = ~(b5_old ^ b4_old) & 0x01;
		b5_new = (~b5_old)         & 0x01;

		dout = b4_new << 4 | b5_new << 5;
		P9DR = dout;

		sleep(1000);
  }
}
