// key.c を利用するために必要なヘッダファイル
// 外から参照される関数や定数を宣言

#define KEYMINNUM  1   /* キー番号の最小値 */
#define KEYMAXNUM 12   /* キー番号の最大値 */
#define KEYNONE   -1   /* 指定したキーがない */
#define KEYOFF     0   /* 指定したキーはずっと離されている状態 */
#define KEYON      1   /* 指定したキーはずっと押されている状態 */
#define KEYTRANS   2   /* 指定したキーは遷移状態 */

// キースキャンを行って、状態を調べる関数群
// 一定時間（数ms程度）毎に keysense() を呼び出すことが前提
// 任意のキー状態を読み出すには key_check() を呼び出す

extern void key_init(void);
     /* キーを読み出すために必要な初期化を行う関数 */

extern void key_sense(void);
     /* キースキャンしてキーバッファに入れる関数          */
     /*   数ms 程度に一度, タイマ割り込み等で呼び出すこと */

extern int key_check(int keynum);
     /* キー番号を引数で与えると, キーの状態を調べて返す関数                 */
     /* キー番号(keynum)は 1-12 で指定(回路図の sw1-sw12 に対応)            */
     /* 基板上の 1-9 のキーは sw1-sw9 に対応している                        */
     /* 基板上の *,0,# のキーは sw10,sw11,sw12 にそれぞれ対応している       */
     /* 戻り値は, KEYOFF, KEYON, KEYTRANS, KEYNONE のいずれか              */
     /* チェック中の割り込みによるバッファ書き換え対策はバッファの大きさで対応 */
