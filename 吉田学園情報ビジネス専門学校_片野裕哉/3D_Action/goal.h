//
//
// ゴールヘッダー [goal.h]
//
//
//
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_MODEL_G (1)		// モデル(パーツ)の最大数(総数)

//
// 構造体
//
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;		// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;	// マテリアル(材質情報)へのポインタ
	DWORD nNumMatModel = NULL;			// マテリアルの数
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 move;					// 移動量
	D3DXVECTOR3 rot;					// 向き
	D3DXVECTOR3 rotDest;				// 目的の向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	int nIdxModelParent;				// 親のインデックス
	D3DXVECTOR3 vtxMinModel;			// モデルの最小値
	D3DXVECTOR3 vtxMaxModel;			// モデルの最大値

} MODEL_G;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 rotDest;		// 目的の向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	MODEL_G aModel[MAX_MODEL_G];	// モデル(パーツ)
	int nNumModel;				// モデル(パーツ)の数
} GOAL;

typedef enum
{
	MODEL_G_LABEL_GOAL = 0,	// 立方体
	MODEL_G_LABEL_MAX
} MODEL_G_LABEL;

//
// プロトタイプ宣言
//
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
GOAL *GetGoal(void);

#endif