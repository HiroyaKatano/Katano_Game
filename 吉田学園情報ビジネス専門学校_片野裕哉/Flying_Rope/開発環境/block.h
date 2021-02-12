//
//
//
//
//
//
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_BLOCK (256)
#define BLOCK_SIZE_X (100)
#define BLOCK_SIZE_Y (50)
#define BLOCK_MOVE_X (10)

#define BLOCK_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	D3DXCOLOR col;		// 色
	float fWidth;		// 幅
	float fHeight;		// 高さ
	bool bUse;			// 使用されているかどうか
} BLOCK;

//
// プロトタイプ宣言
//
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fBlockWigth, float fBlockHeight);
void SetVertexBlock(int nIdx);
BLOCK *GetBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,	// ブロックの当たり判定
	D3DXVECTOR3 *pMove, float fWidth, float fHeight);			// (現在の位置, 前回の位置, 移動量, 幅, 高さ)

#endif 
