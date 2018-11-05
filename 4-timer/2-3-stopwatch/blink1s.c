#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"
#include "lcd.h"

/* 割り込みの周期 1000us */
#define INT1MS 1000

/* 割り込み処理に必要な変数は大域変数にとる */
/* volatile はプログラムの流れとは無関係に変化する変数に必ずつける */
volatile unsigned int sys_time;
volatile unsigned int sec_time; /* 1秒毎に +1 される変数を確保 */
volatile unsigned int secD100_time; /* 0.1秒毎に +1 される変数を確保 */
volatile unsigned int oldD100_time;

/* 割り込みハンドラのプロトタイプ宣言 */
void int_imia0(void);

int main(void)
{
  ROMEMU(); /* ROMエミュレーションをON (割り込み使用時必須) */
  lcd_init();

  /* 時間を格納する変数の初期化 */
  sys_time = 0;
  sec_time = 0;
  secD100_time = 0;
  oldD100_time = 0;

  int h = 23;
  int m = 59;
  int s = 55;
  int sD100 = 0;

  int run = 0;

  unsigned char cf, key_data, key_data_old;
	int i = 0;
	int j = 0;
	int weight[12] = {};
	int pushed[12] = {};
	int keycode = 12;

  P9DDR = 0x30;  /* ポート9の初期化(P95-P94を出力に設定) */

  P6DDR &= ~0x07;  /* P60,1,2   入力 */
  PADDR |= 0x0f;   /* PA0,1,2,3 出力 */

  timer_init();        /* タイマを使用前に初期化する */
  timer_set(0,INT1MS); /* タイマ0を1ms間隔で動作設定 */
  timer_start(0);      /* タイマ(チャネル0)スタート  */

  ENINT();             /* CPU割り込み許可 */

  		lcd_cursor(0,0);
		lcd_printch(h / 10 + '0');
		lcd_printch(h % 10 + '0');
		lcd_printch(':');
		lcd_printch(m / 10 + '0');
		lcd_printch(m % 10 + '0');
		lcd_printch(':');
		lcd_printch(s / 10 + '0');
		lcd_printch(s % 10 + '0');
		lcd_printch('.');
		lcd_printch(sD100 / 10 + '0');
		lcd_printch(sD100 % 10 + '0');

  while (1) {
    /* 割り込み動作以外はこの無限ループを実行している */

		key_data_old = key_data;
		key_data = 0;

    PADR = 0x0e;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : keycode = 10; break;
    case 2 : keycode = 0; break;
    case 4 : keycode = 11; break;
    }
		if(key_data == key_data_old){
			weight[keycode]++;
		}

		for(i = 0; i < 12 ; i++){
			if(pushed[i] == 0 && weight[i] > 100){
				for(j = 0; j < 12; j++){
					pushed[j] = 0;
					weight[j] = 0;
				}
				pushed[i] = 1;
				weight[i] = 0;
				if(i == 10){
					run = 1;
				}else if(i == 11){
					run = 0;
				}else if(i == 0){
					run = 0;
					sD100 = 0;
					s = 0;
					m = 0;
					h = 0;
					lcd_cursor(0,0);
					lcd_printch(h / 10 + '0');
					lcd_printch(h % 10 + '0');
					lcd_printch(':');
					lcd_printch(m / 10 + '0');
					lcd_printch(m % 10 + '0');
					lcd_printch(':');
					lcd_printch(s / 10 + '0');
					lcd_printch(s % 10 + '0');
					lcd_printch('.');
					lcd_printch(sD100 / 10 + '0');
					lcd_printch(sD100 % 10 + '0');
				}
			}
		}

	if (run == 1 && oldD100_time != secD100_time){
		sD100++;
		if(sD100 > 99) s += 1;
			sD100 %= 100;
		if(s > 59) m += 1;
			s %= 60;
		if(m > 59) h += 1;
			m %= 60;
		if(h > 23){
			run = 0;
			h = 23;
			m = 59;
			s = 59;
			sD100 = 99;
		}

  		lcd_cursor(0,0);
		lcd_printch(h / 10 + '0');
		lcd_printch(h % 10 + '0');
		lcd_printch(':');
		lcd_printch(m / 10 + '0');
		lcd_printch(m % 10 + '0');
		lcd_printch(':');
		lcd_printch(s / 10 + '0');
		lcd_printch(s % 10 + '0');
		lcd_printch('.');
		lcd_printch(sD100 / 10 + '0');
		lcd_printch(sD100 % 10 + '0');
		oldD100_time = secD100_time;
	}

  }
  return 1; /* mainからの戻り値はエラーレベルを表す 0:正常終了 */
            /* 永久ループの外なので,戻ったら何かおかしい       */
}

void printnum(unsigned int num){
	if (num != 0){
		printnum(num/10);
	}else{
		return;
	}

	lcd_printch((num % 10) + '0');
}

#pragma interrupt
void int_imia0(void)
     /*
      *  タイマ0の割り込みハンドラ
      *    タイマ0 から割り込み要求がくると，この関数が呼び出される．
      *  タイマ0 の割り込みの場合は，この関数の名前（int_imia0）と
      *  決まっている．
      *    関数の直前に割り込みハンドラ指定の #pragma interrupt が必要．
      */
{
  /* 割り込みハンドラの処理が軽くなるように配慮すること */
  /* 外でできる処理はここには書かない */

  /* sys_time の更新 ( +1 する) をここに書く */
	sys_time++;

  
  /* ここに sec_time の更新 ( +1 する) を書く */
	if (sys_time % 1000 == 0){
		sec_time++;
	}
	if (sys_time % 10 == 0){
		secD100_time++;
	}
  
  /* 再びタイマ割り込みを使用するために必要な操作      */
  /*   タイマ0の割り込みフラグをクリアしないといけない */
  timer_intflag_reset(0);

  ENINT();       /* CPUを割り込み許可状態に */
}
