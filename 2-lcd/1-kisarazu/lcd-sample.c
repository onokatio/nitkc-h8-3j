#include "h8-3052-iodef.h"
#include "lcd.h"

int main(void)
{
  lcd_init();

  lcd_cursor(0,0);
  lcd_printch('K');

  lcd_cursor(1,0);
  lcd_printch('i');

  lcd_cursor(2,0);
  lcd_printch('s');

  lcd_cursor(3,0);
  lcd_printch('a');

  lcd_cursor(4,0);
  lcd_printch('r');

  lcd_cursor(5,0);
  lcd_printch('a');

  lcd_cursor(6,0);
  lcd_printch('z');

  lcd_cursor(7,0);
  lcd_printch('u');

  return 0;
}
