//=========================================================================================================================
//
// TIMER [timer.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_TYPE_TIMER (2)
#define TIMER_COLOR_R (1.0f)
#define TIMER_COLOR_G (1.0f)
#define TIMER_COLOR_B (1.0f)
#define TIMER_COLOR_A (1.0f)

#define TIMER_WIDTH (30.0f)
#define TIMER_HEIGHT (56.25f)
#define TIMER_POS_X (SCREEN_WIDTH_R / 2 - TIMER_WIDTH / 2)
#define TIMER_POS_Y (SCREEN_HEIGHT_T)


#define NUMBER_X (45.0f)
#define NUMBER_Y (60.0f)
#define MAX_SCORE_PATTERN     (10)									// アニメーションパターンNo.の最大数
#define NUMBER_TEXTURE_X		(10)										// アニメーションパターンNo.の横の最大数
#define NUMBER_TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数
#define NUMBER_PLAY_ANIM       ((1.0f / NUMBER_TEXTURE_X) * pNumber->nPatternAnim)   // テクスチャの動作
#define NUMBER_UV_U			(1.0f / NUMBER_TEXTURE_X + NUMBER_PLAY_ANIM)			// Uの値
#define NUMBER_UV_V			(1.0f / NUMBER_TEXTURE_Y)						// Vの値


//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitTimer(void);															// ポリゴンの初期化処理
void UninitTimer(void);															// ポリゴンの終了処理
void UpdateTimer(void);															// ポリゴンの更新処理
void DrawTimer(void);																// ポリゴンの描画処理


#endif
