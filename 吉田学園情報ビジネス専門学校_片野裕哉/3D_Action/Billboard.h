//
//
// ビルボードヘッダー [Billboard.h]
//
//
//
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"

//
// 構造体
//
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
} BILLBOARD;

//
// プロトタイプ宣言
//
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

#endif