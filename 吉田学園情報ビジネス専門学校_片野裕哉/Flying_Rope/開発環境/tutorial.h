//=========================================================================================================================
//
// チュートリアル [tutorial.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define TUTORIAL_POS_LEFT_X (SCREEN_WIDTH_L)
#define TUTORIAL_POS_RIGHT_X (SCREEN_WIDTH_R)
#define TUTORIAL_POS_TOP_Y (SCREEN_HEIGHT_T)
#define TUTORIAL_POS_UNDER_Y (SCREEN_HEIGHT_U)
#define TUTORIAL_COLOR_R (255)														// 背景色(赤)
#define TUTORIAL_COLOR_G (255)														// 背景色(緑)
#define TUTORIAL_COLOR_B (255)														// 背景色(青)
#define TUTORIAL_COLOR_A (255)														// 背景色(透明度)
#define MAX_TUTORIAL_TYPE (1)
#define MOVE_FIRST_TUTORIAL_U (0.0001f)

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitTutorial(void);															// ポリゴンの初期化処理
void UninitTutorial(void);															// ポリゴンの終了処理
void UpdateTutorial(void);															// ポリゴンの更新処理
void DrawTutorial(void);															// ポリゴンの描画処理

#endif
