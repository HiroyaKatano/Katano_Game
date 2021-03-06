//========================================================================================================================
//
// スコアヘッダー [Score.h]
// Author:Hiroya Katano
//
//========================================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "input.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_SCORE (8)	// スコアの最大桁数
#define SCORE_WIDTH_X			(30.0f)											// スコアの幅
#define SCORE_LEFT_X			((SCREEN_WIDTH_L + 270) - (MAX_SCORE + 1) * SCORE_WIDTH_X)	// 左X座標
#define SCORE_RIGHT_X			((SCREEN_WIDTH_L + 270) - MAX_SCORE * SCORE_WIDTH_X)	// 右X座標
#define SCORE_HIGH_Y			(3.75f)											// 上Y座標
#define SCORE_LOW_Y				(60.0f)											// 下Y座標

#define MAX_SCORE_PATTERN     (10)									// アニメーションパターンNo.の最大数
#define SCORE_TEXTURE_X		(10)										// アニメーションパターンNo.の横の最大数
#define SCORE_TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数

#define SCORE_PLAY_ANIM       ((1.0f / SCORE_TEXTURE_X) * pScore->nPatternAnim)   // テクスチャの動作
#define SCORE_UV_U			(1.0f / SCORE_TEXTURE_X + SCORE_PLAY_ANIM)			// Uの値
#define SCORE_UV_V			(1.0f / SCORE_TEXTURE_Y)						// Vの値

#define SCORE_COLOR_R (255)														// 背景色(赤)
#define SCORE_COLOR_G (255)														// 背景色(緑)
#define SCORE_COLOR_B (255)														// 背景色(青)
#define SCORE_COLOR_A (255)														// 背景色(透明度)

#define RIHGT_BG_COLOR_R (255)														// 背景色(赤)
#define RIHGT_BG_COLOR_G (255)														// 背景色(緑)
#define RIHGT_BG_COLOR_B (255)														// 背景色(青)
#define RIHGT_BG_COLOR_A (255)														// 背景色(透明度)

#define LEFT_BG_COLOR_R (255)														// 背景色(赤)
#define LEFT_BG_COLOR_G (255)														// 背景色(緑)
#define LEFT_BG_COLOR_B (255)														// 背景色(青)
#define LEFT_BG_COLOR_A (255)														// 背景色(透明度)

#define BIGIN_SCORE (200000)				// 初期スコア

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

#endif
