//=========================================================================================================================
//
// ポーズ画面 [pause.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define PAUSE_BG_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))			// 背景色
#define PAUSE_BG_SIZE_X (1920.0f)
#define PAUSE_BG_SIZE_Y (1080.0f)

#define PAUSE_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f))			// 色
#define PAUSE_SIZE_X (550.0f)
#define PAUSE_SIZE_Y (650.0f)

#define PAUSE_LOGO_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))		// 色
#define PAUSE_LOGO_SIZE_X (215.0f)
#define PAUSE_LOGO_SIZE_Y (55.0f)

#define CONTINUE_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))			// 色
#define CONTINUE_SIZE_X (420.0f)
#define CONTINUE_SIZE_Y (69.0f)

#define RETRY_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))			// 色0.3f, 0.3f, 0.3f, 1.0f
#define RETRY_SIZE_X (265.0f)
#define RETRY_SIZE_Y (80.0f)

#define QUIT_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))				// 色
#define QUIT_SIZE_X (210.0f)
#define QUIT_SIZE_Y (80.0f)

#define NOT_SELECT_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))		// 非選択時の色
#define SELECT_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))			// 選択時の色

#define MAX_PAUSE_TYPE (6)

//=========================================================================================================================
// 構造体の定義
//=========================================================================================================================
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// コンティニュー
	PAUSE_MENU_RETRY,			// リトライ
	PAUSE_MENU_QUIT,			// 終了
	PAUSE_MENU_MAX
}PAUSE_MENU;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitPause(void);															// ポリゴンの初期化処理
void UninitPause(void);															// ポリゴンの終了処理
void UpdatePause(void);															// ポリゴンの更新処理
void DrawPause(void);																// ポリゴンの描画処理

#endif
