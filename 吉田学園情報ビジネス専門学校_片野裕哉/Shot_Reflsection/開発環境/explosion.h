//=========================================================================================================================
//
// エクスプロージョンヘッダー [explosion.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"


//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_EXPLOSION (256)
#define EXPLOSION_SIZE (50)

#define MAX_EXPLOSION_PATTERN     (8)									// アニメーションパターンNo.の最大数
#define EXPLOSION_TEXTURE_X		(8)										// アニメーションパターンNo.の横の最大数
#define EXPLOSION_TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数

#define EXPLOSION_PLAY_ANIM       ((1.0f / EXPLOSION_TEXTURE_X) * pExplosion->nPatternAnim)   // テクスチャの動作
#define EXPLOSION_UV_U			(1.0f / EXPLOSION_TEXTURE_X + EXPLOSION_PLAY_ANIM)			// Uの値
#define EXPLOSION_UV_V			(1.0f / EXPLOSION_TEXTURE_Y)						// Vの値

#define EXPLOSION_COLOR_R (160)														// 背景色(赤)
#define EXPLOSION_COLOR_G (150)														// 背景色(緑)
#define EXPLOSION_COLOR_B (150)														// 背景色(青)
#define EXPLOSION_COLOR_A (255)														// 背景色(透明度)

//========================================================================================================================
// 構造体の定義
//========================================================================================================================
typedef enum
{
	EXPLOSION_ENEMY = 0,
	EXPLOSION_BOMBER,
	EXPLOSION_MAX
}EXPLOSIONTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNo.
	bool bUse;				// 使用しているかどうか
	EXPLOSIONTYPE type;
	int nAttack;
}EXPLOSION;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitExplosion(void);															// ポリゴンの初期化処理
void UninitExplosion(void);															// ポリゴンの終了処理
void UpdateExplosion(void);															// ポリゴンの更新処理
void DrawExplosion(void);																// ポリゴンの描画処理
void SetExplosion(D3DXVECTOR3 pos, EXPLOSIONTYPE type);		// 
void SetVertexExplosion(int nIdx);
EXPLOSION *GetExplosion(void);

#endif
