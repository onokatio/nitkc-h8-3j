#include "h8-3052-iodef.h"
#include "lcd.h"

#define W 16
#define H 2

void print(int startx,int starty, char str[]){
	int roop;
	int x = 0;
	int y = 0;
	char vram[16][2];
	
	for(roop = 0; (str[roop] != '\0' && roop < 32); roop++){

		lcd_cursor( (startx + x)%16 ,(starty + y)%2 );		
		lcd_printch(str[roop]);

		if( (startx + x+1)%16 == 0)	y++;
		x++;
	}
	for(y=0; y<2 ; y++){
		for(x=0; x<16 ; x++){
			//lcd_cursor(x,y);		
		//lcd_cursor(x%16 ,y%2 );		
		//lcd_printch(vram[x][y]);
		}
	}

}

int main(void)
{
  lcd_init();

	print(10,0,"abcdefghijklmnopqrstuvwxyz");

  return 0;
}
