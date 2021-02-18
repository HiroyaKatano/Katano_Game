//=========================================================================================================================
//
// フェードヘッダー [fade.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define FADE_COLOR_R (0.0f)														// 背景色(赤)
#define FADE_COLOR_G (0.0f)														// 背景色(緑)
#define FADE_COLOR_B (0.0f)														// 背景色(青)
#define FADE_COLOR_A (1.0f)														// 背景色(透明度)

//=========================================================================================================================
// 構造体の定義
//=========================================================================================================================
typedef enum
{
	FADE_NONE = 0,	// 何もしていない
	FADE_IN,		// フェードイン
	FADE_OUT,		// フェードアウト
	FADE_MAX
}FADE;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitFade(MODE modeNext);												// フェードの初期化処理
void UninitFade(void);															// フェードの終了処理
void UpdateFade(void);															// フェードの更新処理
void DrawFade(void);															// フェードの描画処理
void SetFade(FADE fade, MODE modeNext);											//
FADE GetFade(void);

#endif