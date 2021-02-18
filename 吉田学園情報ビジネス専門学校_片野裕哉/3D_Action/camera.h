//
//
// カメラヘッダー [camera.h]
//
//
//
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//
// 構造体
//
typedef struct
{
	D3DXVECTOR3 posV;			// 現在の視点
	D3DXVECTOR3 posVDest;		// 目的の視点
	D3DXVECTOR3 posR;			// 現在の注視点
	D3DXVECTOR3 posRDest;		// 目的の注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXVECTOR3 rot;			// 現在の向き
	D3DXVECTOR3 rotObjective;	// 目的の向き
	D3DXVECTOR3 move;			// 移動量
	D3DXMATRIX  mtxPrjection;	// プロジェクションマトリックス
	D3DXMATRIX  mtxView;		// ビューマトリックス
	float fDistance;			// 視点と注視点の距離
	bool bFollow;				// 追従のON/OFF
	D3DVIEWPORT9 viewport;		// ビューポート
} Camera;

//
// プロトタイプ宣言
//
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
Camera *GetCamera(void);

#endif
