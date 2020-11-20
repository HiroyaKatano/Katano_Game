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
#define SCORE_LEFT_X			(1380.0f)											// 左X座標
#define SCORE_RIGHT_X			(1440.0f)											// 右X座標
#define SCORE_HIGH_Y			(350.0f)											// 上Y座標
#define SCORE_LOW_Y				(430.0f)											// 下Y座標
#define SCORE_WIDTH_X			(60.0f)											// スコアの幅

#define MAX_SCORE_PATTERN     (10)									// アニメーションパターンNo.の最大数
#define SCORE_TEXTURE_X		(10)										// アニメーションパターンNo.の横の最大数
#define SCORE_TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数

#define SCORE_PLAY_ANIM       ((1.0f / SCORE_TEXTURE_X) * pScore->nPatternAnim)   // テクスチャの動作
#define SCORE_UV_U			(1.0f / SCORE_TEXTURE_X + SCORE_PLAY_ANIM)			// Uの値
#define SCORE_UV_V			(1.0f / SCORE_TEXTURE_Y)						// Vの値

#define SCORE_COLOR_R (255)														// 背景色(赤)
#define SCORE_COLOR_G (255)														// 背景色(緑)
#define SCORE_COLOR_B (0)														// 背景色(青)
#define SCORE_COLOR_A (255)														// 背景色(透明度)

#define RIHGT_BG_COLOR_R (255)														// 背景色(赤)
#define RIHGT_BG_COLOR_G (255)														// 背景色(緑)
#define RIHGT_BG_COLOR_B (255)														// 背景色(青)
#define RIHGT_BG_COLOR_A (255)														// 背景色(透明度)

#define LEFT_BG_COLOR_R (255)														// 背景色(赤)
#define LEFT_BG_COLOR_G (255)														// 背景色(緑)
#define LEFT_BG_COLOR_B (255)														// 背景色(青)
#define LEFT_BG_COLOR_A (255)														// 背景色(透明度)

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

#endif
