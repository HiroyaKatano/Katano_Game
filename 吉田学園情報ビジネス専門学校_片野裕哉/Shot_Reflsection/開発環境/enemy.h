//========================================================================================================================
//
// エネミーヘッダー [enemy.h]
// Author:Hiroya Katano
//
//========================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "input.h"

//========================================================================================================================
// マクロ定義
//========================================================================================================================
#define MAX_TYPE_ENEMY (4)	// 敵の種類数
#define MAX_ENEMY (256)	// 敵の最大数
#define ENEMY_SIZE_X (25)	// 敵のサイズ
#define ENEMY_SIZE_Y (25)	// 敵のサイズ

#define BOSS_SIZE_X (200)	// ボスのサイズ
#define BOSS_SIZE_Y (200)	// ボスのサイズ

#define ENEMY_VERTEX_X			(600.0f)

#define MAX_ENEMY_PATTERN     (1)											// アニメーションパターンNo.の最大数
#define ENEMY_TEXTURE_X		(1)											// アニメーションパターンNo.の横の最大数
#define ENEMY_TEXTURE_Y		(1)											// アニメーションパターンNo.の縦の最大数

#define MOVE_ENEMY		(4.0f)										// 敵の移動量

#define PLAY_ENEMY_ANIM       ((1.0f / ENEMY_TEXTURE_X) * g_nPatternEnemyAnim)		// テクスチャの動作
#define ENEMY_UV_U			(1.0f / ENEMY_TEXTURE_X + PLAY_ENEMY_ANIM)				// Uの値
#define ENEMY_UV_V			(1.0f / ENEMY_TEXTURE_Y)							// Vの値

#define ENEMY_COLOR_R (255)														// 背景色(赤)
#define ENEMY_COLOR_G (255)														// 背景色(緑)
#define ENEMY_COLOR_B (255)														// 背景色(青)
#define ENEMY_COLOR_A (255)														// 背景色(透明度)

#define MAX_COUNT		(500)										// カウント

#define MAX_LINE (3)

//========================================================================================================================
// 構造体の定義
//========================================================================================================================
typedef enum
{
	FHASE_0 = 0,
	FHASE_1,
	FHASE_2,
	FHASE_3,
	FHASE_BOSS
}FHASE;

typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTASE_MAX
}ENEMYSTATE;					// 敵の状態

typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	int nType;			// 種類
	bool bUse;			// 使用しているかどうか
	ENEMYSTATE state;	// 状態
	int nCounterState;	// 状態カウンター
	int nLife;			// 体力
	int nCounterEnemy;
	int nCounterBullet;
	FHASE fhase;
} ENEMY;

//========================================================================================================================
// プロトタイプ宣言
//========================================================================================================================
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void SetVertexEnemy(int nIdx);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);
void Fhase1st(void);
void Fhase2nd(void);
void Fhase3rd(void);
void Fhase4th(void);
void FhaseBoss(void);

#endif
