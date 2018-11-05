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
volatile unsigned int old_time;

/* 割り込みハンドラのプロトタイプ宣言 */
void int_imia0(void);

int main(void)
{
  ROMEMU(); /* ROMエミュレーションをON (割り込み使用時必須) */
  lcd_init();

  /* 時間を格納する変数の初期化 */
  sys_time = 0;
  sec_time = 0;
  old_time = 0;

  int force_print = 0;

  int h = 0;
  int m = 0;
  int s = 0;
  int sD100 = 0;

  unsigned char cf;
	int i = 0;
	int j = 0;
	int weight[12] = {};
	int pushed[12] = {};
	int keycode = 12;
	int keycode_old = 12;

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

  while (1) {
    /* 割り込み動作以外はこの無限ループを実行している */

		keycode_old = keycode;
		keycode = 0;

    PADR = 0x07; // PA3 = L
    cf = P6DR;   // データ入力
    cf = ~cf;    // cfの反転
    cf &= 0x07;  // P60,1,2のみ見る
    switch(cf) {
    case 1 : keycode = 1; break;
    case 2 : keycode = 2; break;
    case 4 : keycode = 3; break;
	}  
      
    //key 4,5,6
    PADR = 0x0b;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : keycode = 4; break;
    case 2 : keycode = 5; break;
    case 4 : keycode = 6; break;
    }  
      
    //key 7,8,9
    PADR = 0x0d;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : keycode = 7; break;
    case 2 : keycode = 8; break;
    case 4 : keycode = 9; break;
    }  
    PADR = 0x0e;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : keycode = 10; break;
    case 2 : keycode = 0; break;
    case 4 : keycode = 11; break;
    }
	if(keycode == keycode_old){
		weight[keycode]++;
		//lcd_cursor(0,1);
		//printnum(weight[1]);
	}else{
		for(j = 0; j < 12; j++){
			pushed[j] = 0;
			weight[j] = 0;
		}
	}

	for(i = 0; i < 12 ; i++){
		if(pushed[i] == 0 && weight[i] > 500){
			for(j = 0; j < 12; j++){
				pushed[j] = 0;
				weight[j] = 0;
			}
			pushed[i] = 1;
			weight[i] = 0;
			if(i == 1 && h < 24) h++;
			if(i == 4 && h > 0) h--;
			if(i == 2 && m < 60) m++;
			if(i == 5 && m > 0) m--;
			if(i == 3 && s < 60) s++;
			if(i == 6 && s > 0) s--;
			force_print = 1;
		}else if(pushed[i] == 1 && weight[i] > 500){
			weight[i] = 0;
			pushed[i] = 0;
		}
	}

	if (old_time != sec_time){
		s++;
		if(s > 59) m += 1;
			s %= 60;
		if(m > 59) h += 1;
			m %= 60;
		if(h > 23) h = 0;

  		lcd_cursor(0,0);
		lcd_printch(h / 10 + '0');
		lcd_printch(h % 10 + '0');
		lcd_printch(':');
		lcd_printch(m / 10 + '0');
		lcd_printch(m % 10 + '0');
		lcd_printch(':');
		lcd_printch(s / 10 + '0');
		lcd_printch(s % 10 + '0');
		old_time = sec_time;
	}
	if (force_print){
		force_print = 0;
  		lcd_cursor(0,0);
		lcd_printch(h / 10 + '0');
		lcd_printch(h % 10 + '0');
		lcd_printch(':');
		lcd_printch(m / 10 + '0');
		lcd_printch(m % 10 + '0');
		lcd_printch(':');
		lcd_printch(s / 10 + '0');
		lcd_printch(s % 10 + '0');
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
  
  /* 再びタイマ割り込みを使用するために必要な操作      */
  /*   タイマ0の割り込みフラグをクリアしないといけない */
  timer_intflag_reset(0);

  ENINT();       /* CPUを割り込み許可状態に */
}
