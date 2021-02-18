//
//
// バレットヘッダー [bullet.h]
//
//
//
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//
// 構造体
//
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	bool bUse;					// 使用しているかどうか
} BULLET;

//
// プロトタイプ宣言
//
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void SetVertexBullet(int nIdx);

#endif