////
////
//// モデルヘッダー [model.h]
////
////
////
//#ifndef _MODEL_H_
//#define _MODEL_H_
//#include "main.h"
//
////
//// 構造体
////
//typedef struct
//{
//	D3DXVECTOR3 pos;			// 位置
//	D3DXVECTOR3 move;			// 移動量
//	D3DXVECTOR3 rot;			// 向き
//	D3DXVECTOR3 rotDest;		// 目的の向き
//	D3DXMATRIX mtxWorld;		// ワールドマトリックス
//} PLAYER;
//
//typedef struct
//{
//	D3DXVECTOR3 pos;			// 位置
//	D3DXVECTOR3 move;			// 移動量
//	D3DXVECTOR3 rot;			// 向き
//	D3DXVECTOR3 rotDest;		// 目的の向き
//	D3DXVECTOR3 vtxMinModel;	// モデルの最小値
//	D3DXVECTOR3 vtxMaxModel;	// モデルの最大値
//	D3DXMATRIX mtxWorld;		// ワールドマトリックス
//
//	LPD3DXMESH pMeshModel = NULL;		// メッシュ(頂点情報)へのポインタ
//	LPD3DXBUFFER pBuffMatModel = NULL;	// マテリアル(材質情報)へのポインタ
//	DWORD nNumMatModel = NULL;			// マテリアルの数
//} MODEL;
//
////
//// プロトタイプ宣言
////
//void InitModel(void);
//void UninitModel(void);
//void UpdateModel(void);
//void DrawModel(void);
//MODEL *GetModel(void);
//
//#endif