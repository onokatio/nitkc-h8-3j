// da.c を利用するために必要なヘッダファイル
// 外から参照される関数や定数のみを宣言

#define MIC     0
#define SPEAKER 1

extern void da_init();
     /* D/A 変換とスピーカ切替えの初期化をする関数 */

extern void da_out(unsigned char ch, unsigned char val);
     /* D/A変換を出力するための関数                      */
     /*   ch: チャネル指定(0, 1)  val: 出力値(8ビット長) */
     /*   出力すると共用している端子は D/A しか使えない   */

extern void da_stop(unsigned char ch);
     /* D/A変換を停止するための関数                    */
     /*   停止すると共用している端子を他の用途に使用可  */

extern void speaker_switch(int mode);
     /* スピーカの機能を選択するための関数 */
     /*   mode: SPEAKER, MIC             */
