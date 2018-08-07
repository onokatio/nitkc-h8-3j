#ifndef H8_3052_IODEF
#define H8_3052_IODEF

/* h8-3052-iodef.h */
/* H8300Hシリーズ3052の各レジスタ群の定義 */

/*   定義されているレジスタ名をあたかも変数のように使用できる */
/*     例：P1DDR = a; a = P1DR; のように使える */ 

/*   設定の詳細はPDFマニュアル(rjj09b0335_3052bhm.pdf)参照のこと */
/*   作成2008年4月1日 和崎 */

/* SCIについてはレジスタ名の後にチャネル番号を付加してある */
/*   例：BRR0 (但しSCMRだけはチャネル0固有のため付加せず) */

/* モードコントロールレジスタ */
#define MDCR (*(volatile unsigned char *)0xfffff1)
/* システムコントロールレジスタ */
#define SYSCR (*(volatile unsigned char *)0xfffff2)

/* 内蔵ROM関連 */
/* フラッシュメモリコントロールレジスタ1 */
#define FLMCR1 (*(volatile unsigned char *)0xffff40)
/* フラッシュメモリコントロールレジスタ2 */
#define FLMCR2 (*(volatile unsigned char *)0xffff41)
/* 消去ブロック指定レジスタ1 */
#define EBR1 (*(volatile unsigned char *)0xffff42)
/* 消去ブロック指定レジスタ2 */
#define EBR2 (*(volatile unsigned char *)0xffff43)
/* RAMコントロールレジスタ */
#define RAMCR (*(volatile unsigned char *)0xffff47)

/* 低消費電力状態関連 */
/* システムコントロールレジスタ */
/* #define SYSCR (*(volatile unsigned char *)0xfffff1 */
/* モジュールスタンバイコントロールレジスタ */
#define MSTCR (*(volatile unsigned char *)0xffff5e)

/* クロック発振器関連 */
/* 分周器(CPUクロックφを生成するための分周器) */
/* 分周比コントロールレジスタ */
#define DIVCR (*(volatile unsigned char *)0xffff5d)

/* IRQ関連 */
/* IRQセンスコントロールレジスタ */
#define ISCR (*(volatile unsigned char *)0xfffff4)
/* IRQイネーブルレジスタ */
#define IER (*(volatile unsigned char *)0xfffff5)
/* IRQステータスレジスタ */
#define ISR (*(volatile unsigned char *)0xfffff6)
/* インタラプト・プライオリティレジスタA */
#define IPRA (*(volatile unsigned char *)0xfffff8)
/* インタラプト・プライオリティレジスタB */
#define IPRB (*(volatile unsigned char *)0xfffff9)

/* バスコントロール関連 */
/* バス幅コントロールレジスタ */
#define ABWCR (*(volatile unsigned char *)0xffffec)
/* アクセスステートコントロールレジスタ */
#define ASTCR (*(volatile unsigned char *)0xffffed)
/* ウェイトコントロールレジスタ */
#define WCR (*(volatile unsigned char *)0xffffee)
/* ウェイトステートコントローライネーブルレジスタ */
#define WCER (*(volatile unsigned char *)0xffffef)
/* バスリリースコントロールレジスタ */
#define BRCR (*(volatile unsigned char *)0xfffff3)
/* チップセレクトコントロールレジスタ */
#define CSCR (*(volatile unsigned char *)0xffff5f)

/* リフレッシュコントローラ(D-RAM制御) */
/* リフレッシュコントロールレジスタ */
#define RFSHCR (*(volatile unsigned char *)0xffffac)
/* リフレッシュタイマコントロール・ステータスレジスタ */
#define RTMCSR (*(volatile unsigned char *)0xffffad)
/* リフレッシュタイマカウンタ */
#define RTCNT (*(volatile unsigned char *)0xffffae)
/* リフレッシュタイムコンスタントレジスタ */
#define RTCOR (*(volatile unsigned char *)0xffffaf)

/* DMAコントローラ関連 */
/* チャネル 0A */
/* メモリアドレスレジスタ0AR */
#define MAR0AR (*(volatile unsigned char *)0xffff20)
/* メモリアドレスレジスタ0AE */
#define MAR0AE (*(volatile unsigned char *)0xffff21)
/* メモリアドレスレジスタ0AH */
#define MAR0AH (*(volatile unsigned char *)0xffff22)
/* メモリアドレスレジスタ0AL */
#define MAR0AL (*(volatile unsigned char *)0xffff23)
/* 転送カウントレジスタ0AH */
#define ETCR0AH (*(volatile unsigned char *)0xffff24)
/* 転送カウントレジスタ0AL */
#define ETCR0AL (*(volatile unsigned char *)0xffff25)
/* I/Oアドレスレジスタ0A */
#define IOAR0A (*(volatile unsigned char *)0xffff26)
/* データ転送制御レジスタ0A */
#define DTCR0A (*(volatile unsigned char *)0xffff27)
/* チャネル 0B */
/* メモリアドレスレジスタ0BR */
#define MAR0BR (*(volatile unsigned char *)0xffff28)
/* メモリアドレスレジスタ0BE */
#define MAR0BE (*(volatile unsigned char *)0xffff29)
/* メモリアドレスレジスタ0BH */
#define MAR0BH (*(volatile unsigned char *)0xffff2a)
/* メモリアドレスレジスタ0BL */
#define MAR0BL (*(volatile unsigned char *)0xffff2b)
/* 転送カウントレジスタ0BH */
#define ETCR0BH (*(volatile unsigned char *)0xffff2c)
/* 転送カウントレジスタ0BL */
#define ETCR0BL (*(volatile unsigned char *)0xffff2d)
/* I/Oアドレスレジスタ0B */
#define IOAR0B (*(volatile unsigned char *)0xffff2e)
/* データ転送制御レジスタ0B */
#define DTCR0B (*(volatile unsigned char *)0xffff2f)
/* チャネル 1A */
/* メモリアドレスレジスタ1AR */
#define MAR1AR (*(volatile unsigned char *)0xffff30)
/* メモリアドレスレジスタ1AE */
#define MAR1AE (*(volatile unsigned char *)0xffff31)
/* メモリアドレスレジスタ1AH */
#define MAR1AH (*(volatile unsigned char *)0xffff32)
/* メモリアドレスレジスタ1AL */
#define MAR1AL (*(volatile unsigned char *)0xffff33)
/* 転送カウントレジスタ1AH */
#define ETCR1AH (*(volatile unsigned char *)0xffff34)
/* 転送カウントレジスタ1AL */
#define ETCR1AL (*(volatile unsigned char *)0xffff35)
/* I/Oアドレスレジスタ1A */
#define IOAR1A (*(volatile unsigned char *)0xffff36)
/* データ転送制御レジスタ1A */
#define DTCR1A (*(volatile unsigned char *)0xffff37)
/* チャネル 1B */
/* メモリアドレスレジスタ1BR */
#define MAR1BR (*(volatile unsigned char *)0xffff38)
/* メモリアドレスレジスタ1BE */
#define MAR1BE (*(volatile unsigned char *)0xffff39)
/* メモリアドレスレジスタ1BH */
#define MAR1BH (*(volatile unsigned char *)0xffff3a)
/* メモリアドレスレジスタ1BL */
#define MAR1BL (*(volatile unsigned char *)0xffff3b)
/* 転送カウントレジスタ1BH */
#define ETCR1BH (*(volatile unsigned char *)0xffff3c)
/* 転送カウントレジスタ1BL */
#define ETCR1BL (*(volatile unsigned char *)0xffff3d)
/* I/Oアドレスレジスタ1B */
#define IOAR1B (*(volatile unsigned char *)0xffff3e)
/* データ転送制御レジスタ1B */
#define DTCR1B (*(volatile unsigned char *)0xffff3f)

/* IOポート関連 */
/* ポート１データディレクションレジスタ */
#define P1DDR (*(volatile unsigned char *)0xffffc0)
/* ポート１データレジスタ */
#define P1DR (*(volatile unsigned char *)0xffffc2)
/* ポート２データディレクションレジスタ */
#define P2DDR (*(volatile unsigned char *)0xffffc1)
/* ポート２データレジスタ */
#define P2DR (*(volatile unsigned char *)0xffffc3)
/* ポート２入力プルアップMOSコントロールレジスタ */
#define P2PCR (*(volatile unsigned char *)0xffffd8)
/* ポート３データディレクションレジスタ */
#define P3DDR (*(volatile unsigned char *)0xffffc4)
/* ポート３データレジスタ */
#define P3DR (*(volatile unsigned char *)0xffffc6)
/* ポート４データディレクションレジスタ */
#define P4DDR (*(volatile unsigned char *)0xffffc5)
/* ポート４データレジスタ */
#define P4DR (*(volatile unsigned char *)0xffffc7)
/* ポート４入力プルアップMOSコントロールレジスタ */
#define P4PCR (*(volatile unsigned char *)0xffffda)
/* ポート５データディレクションレジスタ */
#define P5DDR (*(volatile unsigned char *)0xffffc8)
/* ポート５データレジスタ */
#define P5DR (*(volatile unsigned char *)0xffffca)
/* ポート５入力プルアップMOSコントロールレジスタ */
#define P5PCR (*(volatile unsigned char *)0xffffdb)
/* ポート６データディレクションレジスタ */
#define P6DDR (*(volatile unsigned char *)0xffffc9)
/* ポート６データレジスタ */
#define P6DR (*(volatile unsigned char *)0xffffcb)
/* ポート７データレジスタ（入力のみ） */
#define P7DR (*(volatile unsigned char *)0xffffce)
/* ポート８データディレクションレジスタ */
#define P8DDR (*(volatile unsigned char *)0xffffcd)
/* ポート８データレジスタ（５ビット） */
#define P8DR (*(volatile unsigned char *)0xffffcf)
/* ポート９データディレクションレジスタ */
#define P9DDR (*(volatile unsigned char *)0xffffd0)
/* ポート９データレジスタ（６ビット） */
#define P9DR (*(volatile unsigned char *)0xffffd2)
/* ポートAデータディレクションレジスタ */
#define PADDR (*(volatile unsigned char *)0xffffd1)
/* ポートAデータレジスタ */
#define PADR (*(volatile unsigned char *)0xffffd3)
/* ポートBデータディレクションレジスタ */
#define PBDDR (*(volatile unsigned char *)0xffffd4)
/* ポートBデータレジスタ */
#define PBDR (*(volatile unsigned char *)0xffffd6)

/* ITU (16ビットタイマ) */
/* チャネル共通 */
/* タイマスタートレジスタ */
#define TSTR (*(volatile unsigned char *)0xffff60)
/* タイマシンクロレジスタ */
#define TSNC (*(volatile unsigned char *)0xffff61)
/* タイマモードレジスタ */
#define TMDR (*(volatile unsigned char *)0xffff62)
/* タイマファンクションコントロールレジスタ */
#define TFCR (*(volatile unsigned char *)0xffff63)
/* タイマアウトプットマスタイネーブルレジスタ */
#define TOER (*(volatile unsigned char *)0xffff90)
/* タイマアウトプットコントロールレジスタ */
#define TOCR (*(volatile unsigned char *)0xffff91)
/* チャネル0 */
/* タイマコントロールレジスタ0 */
#define TCR0 (*(volatile unsigned char *)0xffff64)
/* タイマI/Oコントロールレジスタ0 */
#define TIOR0 (*(volatile unsigned char *)0xffff65)
/* タイマインタラプトイネーブルレジスタ0 */
#define TIER0 (*(volatile unsigned char *)0xffff66)
/* タイマステータスレジスタ0 */
#define TSR0 (*(volatile unsigned char *)0xffff67)
/* タイマカウンタ0H */
#define TCNT0H (*(volatile unsigned char *)0xffff68)
/* タイマカウンタ0L */
#define TCNT0L (*(volatile unsigned char *)0xffff69)
/* ジェネラルレジスタA0H */
#define GRA0H (*(volatile unsigned char *)0xffff6a)
/* ジェネラルレジスタA0L */
#define GRA0L (*(volatile unsigned char *)0xffff6b)
/* ジェネラルレジスタB0H */
#define GRB0H (*(volatile unsigned char *)0xffff6c)
/* ジェネラルレジスタB0L */
#define GRB0L (*(volatile unsigned char *)0xffff6d)
/* チャネル1 */
/* タイマコントロールレジスタ1 */
#define TCR1 (*(volatile unsigned char *)0xffff6e)
/* タイマI/Oコントロールレジスタ１ */
#define TIOR1 (*(volatile unsigned char *)0xffff6f)
/* タイマインタラプトイネーブルレジスタ1 */
#define TIER1 (*(volatile unsigned char *)0xffff70)
/* タイマステータスレジスタ1 */
#define TSR1 (*(volatile unsigned char *)0xffff71)
/* タイマカウンタ１H */
#define TCNT1H (*(volatile unsigned char *)0xffff72)
/* タイマカウンタ１L */
#define TCNT1L (*(volatile unsigned char *)0xffff73)
/* ジェネラルレジスタA1H */
#define GRA1H (*(volatile unsigned char *)0xffff74)
/* ジェネラルレジスタA1L */
#define GRA1L (*(volatile unsigned char *)0xffff75)
/* ジェネラルレジスタB1H */
#define GRB1H (*(volatile unsigned char *)0xffff76)
/* ジェネラルレジスタB1L */
#define GRB1L (*(volatile unsigned char *)0xffff77)
/* チャネル2 */
/* タイマコントロールレジスタ2 */
#define TCR2 (*(volatile unsigned char *)0xffff78)
/* タイマI/Oコントロールレジスタ2 */
#define TIOR2 (*(volatile unsigned char *)0xffff79)
/* タイマインタラプトイネーブルレジスタ2 */
#define TIER2 (*(volatile unsigned char *)0xffff7a)
/* タイマステータスレジスタ2 */
#define TSR2 (*(volatile unsigned char *)0xffff7b)
/* タイマカウンタ2H */
#define TCNT2H (*(volatile unsigned char *)0xffff7c)
/* タイマカウンタ2L */
#define TCNT2L (*(volatile unsigned char *)0xffff7d)
/* ジェネラルレジスタA2H */
#define GRA2H (*(volatile unsigned char *)0xffff7e)
/* ジェネラルレジスタA2L */
#define GRA2L (*(volatile unsigned char *)0xffff7f)
/* ジェネラルレジスタB2H */
#define GRB2H (*(volatile unsigned char *)0xffff80)
/* ジェネラルレジスタB2L */
#define GRB2L (*(volatile unsigned char *)0xffff81)
/* チャネル3 */
/* タイマコントロールレジスタ3 */
#define TCR3 (*(volatile unsigned char *)0xffff82)
/* タイマI/Oコントロールレジスタ3 */
#define TIOR3 (*(volatile unsigned char *)0xffff83)
/* タイマインタラプトイネーブルレジスタ3 */
#define TIER3 (*(volatile unsigned char *)0xffff84)
/* タイマステータスレジスタ3 */
#define TSR3 (*(volatile unsigned char *)0xffff85)
/* タイマカウンタ3H */
#define TCNT3H (*(volatile unsigned char *)0xffff86)
/* タイマカウンタ3L */
#define TCNT3L (*(volatile unsigned char *)0xffff87)
/* ジェネラルレジスタA3H */
#define GRA3H (*(volatile unsigned char *)0xffff88)
/* ジェネラルレジスタA3L */
#define GRA3L (*(volatile unsigned char *)0xffff89)
/* ジェネラルレジスタB3H */
#define GRB3H (*(volatile unsigned char *)0xffff8a)
/* ジェネラルレジスタB3L */
#define GRB3L (*(volatile unsigned char *)0xffff8b)
/* バッファレジスタA3H */
#define BRA3H (*(volatile unsigned char *)0xffff8c)
/* バッファレジスタA3L */
#define BRA3L (*(volatile unsigned char *)0xffff8d)
/* バッファレジスタB3H */
#define BRB3H (*(volatile unsigned char *)0xffff8e)
/* バッファレジスタB3L */
#define BRB3L (*(volatile unsigned char *)0xffff8f)
/* チャネル4 */
/* タイマコントロールレジスタ4 */
#define TCR4 (*(volatile unsigned char *)0xffff92)
/* タイマI/Oコントロールレジスタ4 */
#define TIOR4 (*(volatile unsigned char *)0xffff93)
/* タイマインタラプトイネーブルレジスタ4 */
#define TIER4 (*(volatile unsigned char *)0xffff94)
/* タイマステータスレジスタ4 */
#define TSR4 (*(volatile unsigned char *)0xffff95)
/* タイマカウンタ4H */
#define TCNT4H (*(volatile unsigned char *)0xffff96)
/* タイマカウンタ4L */
#define TCNT4L (*(volatile unsigned char *)0xffff97)
/* ジェネラルレジスタA4H */
#define GRA4H (*(volatile unsigned char *)0xffff98)
/* ジェネラルレジスタA4L */
#define GRA4L (*(volatile unsigned char *)0xffff99)
/* ジェネラルレジスタB4H */
#define GRB4H (*(volatile unsigned char *)0xffff9a)
/* ジェネラルレジスタB4L */
#define GRB4L (*(volatile unsigned char *)0xffff9b)
/* バッファレジスタA4H */
#define BRA4H (*(volatile unsigned char *)0xffff9c)
/* バッファレジスタA4L */
#define BRA4L (*(volatile unsigned char *)0xffff9d)
/* バッファレジスタB4H */
#define BRB4H (*(volatile unsigned char *)0xffff9e)
/* バッファレジスタB4L */
#define BRB4L (*(volatile unsigned char *)0xffff9f)

/* プログラマブルタイミングパターンコントローラ関連 */
/* ポートAデータディレクションレジスタ */
/* #define PADDR (*(volatile unsigned char *)0xffffd1) */
/* ポートAデータレジスタ */
/* #define PADR (*(volatile unsigned char *)0xffffd3) */
/* ポートBデータディレクションレジスタ */
/* #define PBDDR (*(volatile unsigned char *)0xffffd4) */
/* ポートBデータレジスタ */
/* #define PBDR (*(volatile unsigned char *)0xffffd6) */
/* TPC出力モードレジスタ */
#define TPMR (*(volatile unsigned char *)0xffffa0)
/* TPC出力コントロールレジスタ */
#define TPCR (*(volatile unsigned char *)0xffffa1)
/* ネクストデータイネーブルレジスタB */
#define NDERB (*(volatile unsigned char *)0xffffa2)
/* ネクストデータイネーブルレジスタA */
#define NDERA (*(volatile unsigned char *)0xffffa3)
/* ネクストデータレジスタA(出力トリガが同一のとき) */
#define NDRA (*(volatile unsigned char *)0xffffa5)
/* ネクストデータレジスタA1(出力トリガが異なるときグループ1) */
#define NDRA1 (*(volatile unsigned char *)0xffffa5)
/* ネクストデータレジスタA0(出力トリガが異なるときグループ0) */
#define NDRA0 (*(volatile unsigned char *)0xffffa7)
/* ネクストデータレジスタB(出力トリガが同一のとき) */
#define NDRB (*(volatile unsigned char *)0xffffa4)
/* ネクストデータレジスタB1(出力トリガが異なるときグループ3) */
#define NDRB3 (*(volatile unsigned char *)0xffffa4)
/* ネクストデータレジスタB0(出力トリガが異なるときグループ2) */
#define NDRB2 (*(volatile unsigned char *)0xffffa6)

/* ウォッチドッグタイマ(WDT)関連 */
/* タイマコントロール/ステータスレジスタ */
#define TCSR (*(volatile unsigned char *)0xffffa8)
/* タイマカウンタ */
#define TCNT (*(volatile unsigned char *)0xffffa9)
/* リセットコントロール/ステータスレジスタ */
#define RSTCSR (*(volatile unsigned char *)0xffffab)

/* シリアルコミュニケーションインターフェース(SCI) */
/* 及び スマートカードインターフェース関連 */
/* チャネル0 (USB変換器接続チャネル) */
/* シリアルモードレジスタ */
#define SMR0 (*(volatile unsigned char *)0xffffb0)
/* ビットレートレジスタ */
#define BRR0 (*(volatile unsigned char *)0xffffb1)
/* シリアルコントロールレジスタ */
#define SCR0 (*(volatile unsigned char *)0xffffb2)
/* トランスミットデータレジスタ */
#define TDR0 (*(volatile unsigned char *)0xffffb3)
/* シリアルステータスレジスタ */
#define SSR0 (*(volatile unsigned char *)0xffffb4)
/* レシーブデータレジスタ */
#define RDR0 (*(volatile unsigned char *)0xffffb5)
/* スマートカードモードレジスタ */
#define SCMR (*(volatile unsigned char *)0xffffb6)
/* チャネル1 (ROM書き込みチャネル)*/
/* シリアルモードレジスタ */
#define SMR1 (*(volatile unsigned char *)0xffffb8)
/* ビットレートレジスタ */
#define BRR1 (*(volatile unsigned char *)0xffffb9)
/* シリアルコントロールレジスタ */
#define SCR1 (*(volatile unsigned char *)0xffffba)
/* トランスミットデータレジスタ */
#define TDR1 (*(volatile unsigned char *)0xffffbb)
/* シリアルステータスレジスタ */
#define SSR1 (*(volatile unsigned char *)0xffffbc)
/* レシーブデータレジスタ */
#define RDR1 (*(volatile unsigned char *)0xffffbd)

/* A/D変換器関連 */
/* A/DデータレジスタAH */
#define ADDRAH (*(volatile unsigned char *)0xffffe0)
/* A/DデータレジスタAL */
#define ADDRAL (*(volatile unsigned char *)0xffffe1)
/* A/DデータレジスタBH */
#define ADDRBH (*(volatile unsigned char *)0xffffe2)
/* A/DデータレジスタBL */
#define ADDRBL (*(volatile unsigned char *)0xffffe3)
/* A/DデータレジスタCH */
#define ADDRCH (*(volatile unsigned char *)0xffffe4)
/* A/DデータレジスタCL */
#define ADDRCL (*(volatile unsigned char *)0xffffe5)
/* A/DデータレジスタDH */
#define ADDRDH (*(volatile unsigned char *)0xffffe6)
/* A/DデータレジスタDL */
#define ADDRDL (*(volatile unsigned char *)0xffffe7)
/* A/Dコントロール/ステータスレジスタ */
#define ADCSR (*(volatile unsigned char *)0xffffe8)
/* A/Dコントロールレジスタ */
#define ADCR (*(volatile unsigned char *)0xffffe9)

/* D/A変換器関連 */
/* D/Aデータレジスタ0 */
#define DADR0 (*(volatile unsigned char *)0xffffdc)
/* D/Aデータレジスタ1 */
#define DADR1 (*(volatile unsigned char *)0xffffdd)
/* D/Aコントロールレジスタ */
#define DACR (*(volatile unsigned char *)0xffffde)
/* D/Aスタンバイコントロールレジスタ */
#define DASTCR (*(volatile unsigned char *)0xffff5c)

#endif
