//
//
// ウォールヘッダー [wall.h]
//
//
//
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_WALL (256)			// 壁の最大数

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;			// 中心座標
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	bool bUse;					// 使用しているかどうか
}Wall;

//
// プロトタイプ宣言
//
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetVertexWall(int nIdx);
Wall *GetWall(void);

#endif