//
//
// パーティクルヘッダー [particle.h]
//
//
//
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
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
	int nLife;					// 寿命
	bool bUse;					// 使用しているかどうか
} PARTICLE;

//
// プロトタイプ宣言
//
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void SetVertexParticle(int nIdx);

#endif