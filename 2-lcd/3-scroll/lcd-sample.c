#include "h8-3052-iodef.h"
#include "lcd.h"

#define WIDTH 16
#define HEIGHT 2
#define MILLISEC 14280

void sleep(int max){
	int i,j,k,c;

	for(c=0; c < max;c++)
		for(i=0; i < MILLISEC ;i++); //ミリ秒分空ループする
}
void clear(){
	int x;
	int y;

	for(y=0; y<HEIGHT; y++){
		for(x=0; x<WIDTH; x++){
			lcd_cursor( x , y );		
			lcd_printch(' ');
		}
	}
}

void print(int startx,int starty, char str[]){
	int roop;
	int x = 0;
	int y = 0;
	
	for(roop = 0; (str[roop] != '\0' && roop < WIDTH * HEIGHT); roop++){

		lcd_cursor( (startx + x)%WIDTH ,(starty + y)%HEIGHT );
		lcd_printch(str[roop]);

		if( (startx + x+1)%WIDTH == 0)	y++;
		x++;
	}

}

void scroll(int startx, int starty, int revert, char str[]){
	int roop;
	int x = 0;
	int y = 0;

	for(roop = 0; 1 ; roop++){

		clear();
		if(revert){
			print(WIDTH - x%WIDTH + startx, HEIGHT - y%HEIGHT + starty,str);
		}else{
			print((startx + x)%WIDTH, (starty + y)%HEIGHT,str);
		}
		sleep(1000);

		if(revert){
			if( WIDTH - (x-1)%WIDTH + startx == WIDTH - 1)	y++;
		}else{
			if( (startx + x+1)%WIDTH == 0)	y++;
		}

		x++;
	}
}

int abs(int i){
	return i<0 ? -i : i;
}

int main(void)
{
  lcd_init();

	scroll(1,5,1,"abcdefghijklmnopqrstuvwxyz");

  return 0;
}
