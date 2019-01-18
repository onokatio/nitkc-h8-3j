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

int main(void)
{
  lcd_init();

	enum Calc { ADD, SUB, MUL, DIV};

	char str[20];
	char str2[20];
	int i,j,k;
	int a = 10000000;
	int b = 20;
	enum Calc calc0 = MUL;

	switch(calc0){
		case ADD: a += b; break;
		case SUB: a -= b; break;
		case MUL: a *= b; break;
		case DIV: a /= b; break;
	}

	//sprintf(str,"%d",a);
	for(i=0;a != 0;i++){
		str2[i] = a%10;
		a = a/10;
	}
	for(;i>0;i--){
		str[i]=str[]
	}
	for(i=0; str[i] != '\0' ; i++);
	k = i % 3;
	for(j=0,i=0; str[i] != '\0' ; i++,j++){
		if( (i+3-k)%3 == 0 ){
			str2[j] = ',';
			j++;
		}
		str2[j] = str[i];
	}
	str2[j] = '\0';
	if(str2[0] == ','){
		//(&str) = (&str) + 1;
	}
	print(0,0,str2);

  return 0;
}
