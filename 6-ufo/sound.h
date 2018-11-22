// sound.c を利用するために必要なヘッダファイル
// 外から参照される関数のみを宣言

extern void sound_init(void);
     /* 音を鳴らすための初期化               */
     /* D/A変換用の初期化とスピーカの切り替え */

extern void sound_beep(int hz,int msec,int vol);
     /* タイマ0の割り込みを使って単音を一定の長さだけ鳴らすための関数  */
     /* 引数は、音程:hz, 音長:msec, 音量:vol                        */
