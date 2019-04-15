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

int number_to_string(int number,char string[]){
	int index;
	if( number == 0 ){
		return 0;
	}else{
		index = number_to_string(number/10,string);
		string[index] = '0' + number % 10;
		return index+1;
	}
}


int main(void)
{
  lcd_init();

	enum Calc { ADD, SUB, MUL, DIV};

	char str[20];
	char str2[20];
	int i,j,k;
	int a = 1000;
	int b = 1000;
	enum Calc calc0 = DIV;

	switch(calc0){
		case ADD: a += b; break;
		case SUB: a -= b; break;
		case MUL: a *= b; break;
		case DIV: a /= b; break;
	}

	if(a == 0){
	    print(0,0,"0");
	}else{
	    str[number_to_string(a,str)] = '\0';
	}

	for(i=0; str[i] != '\0' ; i++);
	k = i % 3;
	for(j=0,i=0; str[i] != '\0' ; i++,j++){
		if( (i+3-k)%3 == 0 && j!=0){
			str2[j] = ',';
			j++;
		}
		str2[j] = str[i];
	}
	str2[j] = '\0';
	print(0,0,str2);

  return 0;
}
