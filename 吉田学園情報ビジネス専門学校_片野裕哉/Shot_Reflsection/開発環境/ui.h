//=========================================================================================================================
//
// UI [ui.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_TYPE_UI (9)
#define UI_COLOR_R (1.0f)
#define UI_COLOR_G (1.0f)
#define UI_COLOR_B (1.0f)
#define UI_COLOR_A (1.0f)
//#define RIHGT_BG_COLOR_R (255)														// 背景色(赤)
//#define RIHGT_BG_COLOR_G (255)														// 背景色(緑)
//#define RIHGT_BG_COLOR_B (255)														// 背景色(青)
//#define RIHGT_BG_COLOR_A (255)														// 背景色(透明度)
//
//#define LEFT_BG_COLOR_R (255)														// 背景色(赤)
//#define LEFT_BG_COLOR_G (255)														// 背景色(緑)
//#define LEFT_BG_COLOR_B (255)														// 背景色(青)
//#define LEFT_BG_COLOR_A (255)														// 背景色(透明度)

#define MINI_PLAYER_X (64.5f)
#define MINI_PLAYER_Y (64.5f)

#define ADD_UP_X (30.0f)
#define ADD_UP_Y (30.0f)

#define NUMBER_X (45.0f)
#define NUMBER_Y (60.0f)
#define MAX_SCORE_PATTERN     (10)									// アニメーションパターンNo.の最大数
#define NUMBER_TEXTURE_X		(10)										// アニメーションパターンNo.の横の最大数
#define NUMBER_TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数
#define NUMBER_PLAY_ANIM       ((1.0f / NUMBER_TEXTURE_X) * pNumber->nPatternAnim)   // テクスチャの動作
#define NUMBER_UV_U			(1.0f / NUMBER_TEXTURE_X + NUMBER_PLAY_ANIM)			// Uの値
#define NUMBER_UV_V			(1.0f / NUMBER_TEXTURE_Y)						// Vの値


#define GAUGE_BG_X (330.0f)
#define GAUGE_BG_Y (26.6f)
#define GAUGE_X (300.0f)
#define GAUGE_Y (25.0f)
#define GAUGE_FLAME_X (330.0f)
#define GAUGE_FLAME_Y (26.6f)

#define OPERATION_X (400.0f)
#define OPERATION_Y (368.0f)


//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitUi(void);															// ポリゴンの初期化処理
void UninitUi(void);															// ポリゴンの終了処理
void UpdateUi(void);															// ポリゴンの更新処理
void DrawUi(void);																// ポリゴンの描画処理
void ManageMachine(void);
void ManageGauge(void);

#endif
