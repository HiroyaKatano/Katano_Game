//=========================================================================================================================
//
// タイトルヘッダー [title.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TITLE_H_
#define _TIELE_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define TITLE_BG_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			// 背景色(赤, 緑, 青, 透明度)

#define TITLE_LOGOSHADOW_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	// ロゴ影色(赤, 緑, 青, 透明度)

#define TITLE_LOGO_COLOR (D3DXCOLOR(0.0f, 0.66f, 1.0f, 1.0f))		// ロゴ色(赤, 緑, 青, 透明度)

#define ENTER_SIGN_COLOR_OFF (D3DXCOLOR(0.15f, 1.0f, 1.0f, 0.0f))		// エンターサインOFF色(赤, 緑, 青, 透明度)
#define ENTER_SIGN_COLOR_ON (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// エンターサインON色(赤, 緑, 青, 透明度)

#define MAX_TYPE_TITLE (4)
#define TITLE_BG_SIZE_X (SCREEN_WIDTH_R * 4)
#define TITLE_BG_SIZE_Y (SCREEN_HEIGHT_U)
#define TITLE_LOGOB_SIZE_X (936.0f)
#define TITLE_LOGOB_SIZE_Y (116.0f)
#define TITLE_LOGOF_SIZE_X (550.0f)
#define TITLE_LOGOF_SIZE_Y (274.0f)
#define FLASHING_ENTER_SIZE_X (381.0f)
#define FLASHING_ENTER_SIZE_Y (55.0f)

#define MOVE_BG_U (0.00017f)
#define MOVE_TITLE_BG_V (0.00075f)

//=========================================================================================================================
// 構造体の定義
//=========================================================================================================================
typedef enum
{
	ENTERSTATE_WAIT = 0,	// 待機状態
	ENTERSTATE_ACTIVE,		// 開始
	ENTERSTATE_MAX
} ENTERSTATE;				// 

typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	int nType;			// 種類
} TITLELOGO;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitTitle(void);															// ゲームの初期化処理
void UninitTitle(void);															// ゲームの終了処理
void UpdateTitle(void);															// ゲームの更新処理
void DrawTitle(void);															// ゲームの描画処理

#endif