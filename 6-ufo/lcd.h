// lcd.c を利用するために必要なヘッダファイル
// 外から参照される関数を宣言

extern void lcd_init(void);
     /* LCD 表示器を使うための初期化関数             */
     /* 一部, キーセンスとの兼ね合いがあるが対策済み */
     /* LCD 表示器の初期化には時間がかかるので注意   */

extern void lcd_cursor(int x, int y);
     /* 表示位置を変更する関数 */
     /* 表示器左上が (0,0) となる */

extern void lcd_clear(void);
     /* 表示器の全画面をクリアするための関数 */

extern void lcd_printstr(unsigned char *str);
     /* 表示器に文字列を表示する関数 */
     /* 文字コードは ASCII コードの範囲なら問題ない */

extern void lcd_printch(unsigned char ch);
     /* 表示器に1文字だけ表示する関数 */
     /* 文字コードは ASCII コードの範囲なら問題ない */

extern void wait1ms(int ms);
     /* ms = 1 のとき, 約1msだけムダなループで待つ関数       */
     /* LCDの動作を保証するために必要な時間を確保するのが目的 */
