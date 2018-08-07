#include "h8-3052-iodef.h"
#include "lcd.h"
#include "stdio.h"

int main(void)
{
  unsigned char cf, key_data, key_data_old;
	char str[32] = {};
	int i = 0;
	int j = 0;
	int weight[12] = {};
	int pushed[12] = {};
	int keycode = 12;
	//int temp;

  P9DDR = 0x30;  /* ポート9の初期化(P95-P94を出力に設定) */

  P6DDR &= ~0x07;  /* P60,1,2   入力 */
  PADDR |= 0x0f;   /* PA0,1,2,3 出力 */

  P9DR = 0x30;  /* D1(赤)消灯, D2(緑)消灯 */

	lcd_init();

  while(1) {

		key_data_old = key_data;
		key_data = 0;

    //key 1,2,3
    PADR = 0x07; // PA3 = L
    cf = P6DR;   // データ入力
    cf = ~cf;    // cfの反転
    cf &= 0x07;  // P60,1,2のみ見る
    switch(cf) {
    case 1 : key_data = '1'; break;
    case 2 : key_data = '2'; break;
    case 4 : key_data = '3'; break;
		}  
      
    //key 4,5,6
    PADR = 0x0b;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : key_data = '4'; break;
    case 2 : key_data = '5'; break;
    case 4 : key_data = '6'; break;
    }  
      
    //key 7,8,9
    PADR = 0x0d;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : key_data = '7'; break;
    case 2 : key_data = '8'; break;
    case 4 : key_data = '9'; break;
    }  
      
    //key *,0,#
    PADR = 0x0e;
    cf = P6DR;
    cf = ~cf;
    cf &= 0x07;
    switch(cf) {
    case 1 : key_data = '*'; break;
    case 2 : key_data = '0'; break;
    case 4 : key_data = '#'; break;
    }  
    
		if(key_data - '0' >= 0 && key_data - '0' <= 9){
			keycode = key_data - '0';
		}else if(key_data == '*'){
			keycode = 10;
		}else if(key_data == '#'){
			keycode = 11;
		}else{
			keycode = 12;
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
					lcd_printch('*');
				}else if(i == 11){
					lcd_printch('*');
				}else{
					lcd_printch('0' + i);
				}
			}
		}

  }

}
