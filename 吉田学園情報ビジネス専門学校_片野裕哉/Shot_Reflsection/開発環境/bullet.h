//=========================================================================================================================
//
// バレットヘッダー [bullet.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "Score.h"


//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_MODE_BULLET (6)
#define MAX_BULLET (1024)
#define MOVE_PLAYER_BULLET (5.0f)
#define MOVE_ENEMY_BULLET (10.0f)
#define LIFE_BULLET (250)
#define BULLET_NORMAL_SIZE_X (10)
#define BULLET_NORMAL_SIZE_Y (10)
#define BULLET_LASER_SIZE_X (10)
#define BULLET_LASER_SIZE_Y (10)
#define BULLET_WAVE_SIZE_X (50)
#define BULLET_WAVE_SIZE_Y (10)
#define BULLET_BOMBER_SIZE_X (20)
#define BULLET_BOMBER_SIZE_Y (20)
#define BULLET_CIRCLE_SIZE_X (20)
#define BULLET_CIRCLE_SIZE_Y (20)

#define BULLET_NORMAL_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// 通常弾の色

#define LASER_COLOR (D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.40f))	// レーザーの色

//=========================================================================================================================
// 弾の種類
//=========================================================================================================================
typedef enum
{
	BULLETTYPE_PLAYER = 0,	// 自機
	BULLETTYPE_ENEMY,		// 敵
	BULLETTYPE_MAX
}BULLETTYPE;

typedef enum
{
	BULLET_NORMAL = 0,		// 通常弾
	BULLET_LASER,			// レーザー
	BULLET_WAVE,			// ウェーブ弾
	BULLET_BOMBER,			// 爆発弾
	BULLET_CIRCLE,			// 円形弾
	BULLET_MAX
}BULLETMODE;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	int nLife;			// 寿命
	D3DXCOLOR col;		// 色
	bool bUse;			// 使用しているかどうか
	BULLETTYPE type;	// 弾の種類
	BULLETMODE mode;	// 弾の性質
	int nAttack;		// 攻撃力
}BULLET;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitBullet(void);															// ポリゴンの初期化処理
void UninitBullet(void);															// ポリゴンの終了処理
void UpdateBullet(void);															// ポリゴンの更新処理
void DrawBullet(void);																// ポリゴンの描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type, BULLETMODE mode, int nAttack);		// 
void SetVertexBullet(int nIdx);
BULLET *GetBullet(void);

#endif