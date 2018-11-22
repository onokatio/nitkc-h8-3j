#include "h8-3052-iodef.h"
#include "h8-3052-int.h"

#include "lcd.h"
#include "random.h"
#include "timer.h"
#include "key.h"
#include "da.h"
#include "sound.h"

/* フラグ定数 */
#define TRUE  1
#define FALSE 0

/* 表示に関する定数 */
  /* LCDの横方向桁数 */
#define MAXDIGITNUM 16
  /* ゲームに使う表示桁数 */
#define MAXINVNUM   16

/* 敵の進行スピードに関する定数（単位はms） */
  /* 進行時間間隔 */
#define INITSPEED   2000
  /* スピード上昇定数 */
#define SPEEDUP     10

/* 効果音に関する定数 */
  /* TONE_XXX は音程（単位はHz） */
  /* LONG_XXX は音長（単位はms） */
#define TONE_TARGET 83
#define LONG_TARGET 100
#define TONE_MISS   50
#define LONG_MISS   300
#define TONE_HIT    250
#define LONG_HIT    200
#define TONE_DEF    63
#define LONG_DEF    200

/* 得点表示の長さの定数（単位はms） */
#define WAITFEWSEC  5000

/* 割り込みハンドラで処理する変数 */
volatile unsigned long n_time, speed_count, speed;
volatile int shift_flag;

int main(void);
char *ntos(unsigned int n, char *s);
int game_start(void);
void effect(char c);
void int_imia0(void);
void int_imia1(void);

int main(void)
     /* UFOゲーム(電卓ゲーム風) */
{
  unsigned int score, high_score;
  char score_s[MAXDIGITNUM+1];

  /* 初期化 */
  ROMEMU();           /* ROMエミュレーションをON */
  USE_UI();           /* 多重割り込み制御のためにUIビットを使用 */
  timer_pri_set(0,1); /* タイマ0の割り込みをプライオリティ1(優先)に設定 */
  random_init();      /* 乱数発生の初期化 */
  lcd_init();         /* LCD表示器の初期化 */
  key_init();         /* キースキャンの初期化 */
  timer_init();       /* タイマの初期化 */
  sound_init();       /* 効果音の初期化 */
  timer_set(1,1000);  /* タイマ1は音長/キーセンス/速度調整/時間待ち用 */
  timer_start(1);     /* タイマ1スタート */
  ENINT();            /* 全割り込み受付可 */
  /* LCD にメニュー表示 */
  lcd_cursor(0,0);
  lcd_printstr(" 0:Game Start   ");
  lcd_cursor(0,1);
  lcd_printstr(" *:High Score   ");
  high_score = 0;
  while(1){
    if (key_check(10) == KEYON){     /* *キー:ハイスコア表示 */
      lcd_cursor(0,0);                   /* LCD にハイスコア表示 */
      lcd_printstr(" High Score is  ");
      lcd_cursor(0,1);
      lcd_printstr("                ");
      lcd_cursor(0,1);
      lcd_printstr(ntos(high_score,score_s));
    }
    if (key_check(10) == KEYOFF){     /* *キーを離したらメニュー表示 */
      lcd_cursor(0,0);                     /* LCD にメッセージ表示 */
      lcd_printstr(" 0:Game Start   ");
      lcd_cursor(0,1);
      lcd_printstr(" *:High Score   ");
    }
    if (key_check(11) == KEYON){      /* 0キー:ゲームスタート */
      lcd_cursor(0,0);                   /* LCD に操作方法表示 */
      lcd_printstr("*:Sight  0:Trig.");
      score = game_start();              /* ゲームスタート */
      lcd_cursor(0,1);                   /* 得点表示欄のクリア */
      lcd_printstr("                ");
      if (score > high_score){           /* ハイスコアのとき */
	high_score = score;                /* ハイスコア登録 */
	lcd_cursor(0,0);                   /* ハイスコア表示 */
	lcd_printstr(" High Score !!! ");
	lcd_cursor(0,1);
	lcd_printstr(ntos(high_score,score_s));
      } else {                           /* ハイスコアでないとき*/
	lcd_cursor(0,0);                   /* スコアを表示 */
	lcd_printstr(" Your Score ... ");
	lcd_cursor(0,1);
	lcd_printstr(ntos(score,score_s));
      }
      n_time = 0;
      while (n_time < WAITFEWSEC);       /* 得点表示後にちょっと待つ */
      lcd_cursor(0,0);                     /* LCD にメッセージ表示 */
      lcd_printstr(" 0:Game Start   ");
      lcd_cursor(0,1);
      lcd_printstr(" *:High Score   ");
    }
  }
}

char *ntos(unsigned int n, char *s)
     /* 数値を文字列に変換する関数 */
     /* 引数は、整数値(>0)：n, 変換文字列が入る文字列変数ポインタ：s */
     /* 戻り値は、文字列変数ポインタ */
{
  int count, i;
  char st[MAXDIGITNUM+1];
  char d;

  count = 0;
  do {
    d = n % 10;
    n = (n - d) / 10;
    st[count] = d + '0';
    count++;
  } while (n > 0);
  for (i = 0; i < count; i++) 
    s[i] = st[count - 1 - i];
  s[count] = '\0';
  return s;
}

int game_start(void)
     /* UFOゲームの本体                                      */
     /* 戻り値: ゲームスコア                                 */
     /* 処理の高速化のためになるべく関数化しないで書いてある    */
     /* 関数を呼び出すと多くのレジスタを退避するし,            */
     /* 外部メモリのアクセスは8ビット幅でかつ遅い              */
     /* 但し, きれいに関数化しても差障りはないかもしれない      */
{
  int target, score, gameover, hit, i, j;
  int prev_key10, prev_key11, key10, key11;
  unsigned int ds;
  char t, nc;
  char disp[MAXINVNUM+1]; /* [0: 1234567890n] のような画面イメージ */
                          /*  照準,区切り,インベーダとUFO */
  target = 0; t = '0'; score = 0;     /* 照準とスコアの初期化 */
  speed_count = 0; speed = INITSPEED; /* プレイ速度の初期化 */
  shift_flag = FALSE;                 /* 敵の前進フラグの初期化 */
  disp[0] = '0'; disp[1] = ':';       /* 表示フィールドの初期化 */
  for (i = 2; i < MAXINVNUM; i++) disp[i] = ' ';
  disp[MAXINVNUM] = '\0';
  gameover = FALSE;       /* ゲーム終了フラグの初期化 */
  key10 = key_check(10);  /* キーバッファ(照準キー)の初期化 */
  prev_key10 = KEYOFF;
  key11 = key_check(11);  /* キーバッファ(発射キー)の初期化 */
  prev_key11 = KEYOFF;
  lcd_cursor(0,1);        /* 初期画面の表示 */
  lcd_printstr(disp);
  while (gameover == FALSE){ /* ゲームオーバでなければループ */
    /* キーの立上りを検出するための前回チェック時のキー状態を記憶 */
    /* キーバッファ(照準キー)処理 */
    if (key10 != KEYTRANS) prev_key10 = key10; /* 遷移中は前々回の値そのまま */
    key10 = key_check(10);
    /* キーバッファ(発射キー)処理 */
    if (key11 != KEYTRANS) prev_key11 = key11; /* 遷移中は前々回の値そのまま */
    key11 = key_check(11);
    if ((prev_key10 == KEYOFF) && (key10 == KEYON)){
      /* 照準キーが押されたときの処理 */
      /* 照準は 0->1->...->8->9->n->0->... と順に変化する */
      target++;                           /* 照準 +1 */
      if (target > 10) target = 0;        /* UFOの次は0 */
      if (target < 10) t = '0' + target;  /* 照準がUFOでないときのキャラ */
      else t = 'n';                       /* 照準がUFOのときのキャラ */
      disp[0] = t;                        /* 照準値を表示にセット */
      effect('t');                        /* 効果音を鳴らす */
      /* フィールドの表示 */
      lcd_cursor(0,1);
      lcd_printstr(disp);
    }
    if ((prev_key11 == KEYOFF) && (key11 == KEYON)){
      /* 発射キーが押されたときの処理 */
      hit = FALSE;  /* ヒット判定フラグの初期化 */
      i = 2;        /* 最も左の敵表示位置 */
      while ((i < MAXINVNUM) && (hit != TRUE)){ /* 列の左から命中を探す */
	if (disp[i] == t){    /* 照準と一致するキャラか? */
	  hit = TRUE;           /*   ヒット判定 */
	  ds = MAXINVNUM - i;   /*   基本得点の計算(砲台に近い程大) */
	  score = score + ds;   /*   得点追加 */
	  if (target > 9) score = score + ds * 2;  /* UFOなら3倍の得点 */
	  for (j = i; j > 2; j--) disp[j] = disp[j-1];  /* 命中左側を右寄せ */
	  disp[2] = ' ';        /* 最も左は常に空白を詰める */
	  /* フィールドの表示 */
	  lcd_cursor(0,1);
	  lcd_printstr(disp);
	}
	i++;  /* 探索位置を +1 */
      } /* ヒット判定があるか右端まで調べたら, 探索終了 */
      if (hit == TRUE) effect('s'); /* 命中時の効果音 */
      else effect('m');             /* 失敗時の効果音 */
    }
    /* 敵が前進するタイミングのときの処理 */
    if (shift_flag == TRUE){          /* 前進フラグが立っているなら */
      if (disp[2] != ' ') disp[1] = disp[2]; /* 侵略時のみ区切りに侵入 */
      for (i = 2; i < MAXINVNUM; i++)   /* 敵全体を左に1つシフト */
	disp[i] = disp[i + 1];
      if (score % 10 == 1) nc = 'n';    /* スコアの最下位が1ならUFO出現 */
      else nc = (random() % 10) + '0';  /* それ以外はランダムな数字 */
      disp[MAXINVNUM - 1] = nc;         /* 右端に新キャラを入れる */
      shift_flag = FALSE;               /* 前進フラグの消去 */
      lcd_cursor(0,1);                  /* フィールドの表示 */
      lcd_printstr(disp);
    }
    if (disp[1] != ':') gameover = TRUE; /* 侵略されたらゲームオーバ */
  }
  return score; /* 得点を返す */
}

void effect(char c)
     /* 効果音を発生するための関数 */
     /* 引数: c 効果音の種類を指定 */
{
  unsigned int t;
  unsigned long p;

  switch (c) {       /* 種類によって音程と音長を変えられる */
  case 't':            /* 照準を動かしたとき */
    t = TONE_TARGET;
    p = LONG_TARGET;
    break;
  case 'm':            /* ミスしたとき */
    t = TONE_MISS;
    p = LONG_MISS;
    break;
  case 's':            /* ヒットしたとき */
    t = TONE_HIT;
    p = LONG_HIT;
    break;
  default:             /* その他のとき*/
    t = TONE_DEF;
    p = LONG_DEF;
  }
  sound_beep(t,p,32);
}

#pragma interrupt
void int_imia1(void)
     /* キーセンス・速度調整・時間待ち用のタイマ1割り込みハンドラ */
{
  ENINT1();        /* 音程用の割り込み処理を優先させる */
  key_sense();     /* キーセンス */
  n_time++;        /* 時間待ち用のカウンタ +1 */
  speed_count++;                 /* スピード調整用カウンタ +1 */
  if (speed_count >= speed){     /* 設定値になったら */
    speed_count = 0;             /*   カウンタ初期化 */
    speed = speed - SPEEDUP;     /*   スピードアップ */
    shift_flag = TRUE;           /*   前進フラグ ON */
  }

  /* 再びタイマ割り込みを使用するために必要な操作      */
  /*   タイマ1の割り込みフラグをクリアしないといけない */
  timer_intflag_reset(1);

  ENINT();         /* CPUを割り込み許可状態に */
}
