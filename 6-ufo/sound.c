#include "h8-3052-iodef.h"
#include "timer.h"
#include "da.h"
#include "h8-3052-int.h"

// 単音を一定時間鳴らすための関数群。
// タイマ0を使って音高の1/2周期で割り込みを起こす。
// 音の長さは割り込み回数をカウントして測る。

void int_imia0(void);

/* sound.cの中だけで閉じている大域変数、割り込みハンドラ用 */
unsigned int timer0_count, play_count;
unsigned char da_amp;

void sound_init(void)
     /* 音を鳴らすための初期化               */
     /* D/A変換用の初期化とスピーカの切り替え */
{
  da_init();               /* DAの初期化 */
  speaker_switch(SPEAKER); /* スピーカとして使用 */
}

void sound_beep(int hz,int msec,int vol)
     /* タイマ0の割り込みを使って単音を一定の長さだけ鳴らすための関数  */
     /* 引数は、hz:音高, msec:音長, vol:音量                        */
     /* timer0_count, play_cont, da_amp は割り込みハンドラで使用    */
{
    unsigned int int_time;

    timer0_count = 0;      /* 割り込み回数用カウンタの初期化 */

  /* ここで割り込み周期(単位は[μs])を求めて int_time に入れる */
  /* 割り込み周期は音高周期の半分 */
	int_time = (1000/hz)/2;

  /* ここで指定音長となる割り込み回数を求めて play_count に入れる */
  /* 単位に注意して音長が割り込み何回分かを求める */
	play_count = int_time

  /* ここで指定音量になるように da_amp にセットする */
  /* 割り込みハンドラに渡すために大域変数に入れる */

    timer_set(0,int_time);  /* 音高用割り込み周期のセット */
    timer_start(0);         /* タイマ0スタート */
}

#pragma interrupt
void int_imia0(void)
     /* 音高を出すための割り込みハンドラ */
     /* 使用する大域変数と役割は以下の通り */
     /*   timer0_count は割り込み回数を数えるカウンタ */
     /*   play_cont は指定音長になるときの割り込み回数 */
     /*   da_amp はD/Aの出力上限値  */
{
  /* ここで、割り込み回数をインクリメントする */

  /* ここで、割り込みがかかる度にD/Aの出力を上限値か下限値に切替える */

  /* ここで、タイマカウントが音長カウントに達したらタイマストップする */
  /* タイマストップしたら割り込みはかからなくなる */

  /* 再びタイマ割り込みを使用するために必要な操作      */
    timer_intflag_reset(0);  /* タイマ0の割り込みフラグをクリア */
    ENINT();                 /* CPUを割り込み許可状態に */
}
