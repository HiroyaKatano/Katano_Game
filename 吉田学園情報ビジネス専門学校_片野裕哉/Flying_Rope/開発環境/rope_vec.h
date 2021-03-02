//
//
//
//
//
//
#ifndef _ROPE_VEC_H_
#define _ROPE_VEC_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_ROPE_VEC (8)
#define ROPE_VEC_SIZE_VERTEX_X (8.4f)
#define ROPE_VEC_SIZE_VERTEX_Y (15.0f)
#define ROPE_VEC_MAX_SIZE_Y (120.0f)

#define ROPE_VEC_NEUTORAL_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f))
#define ROPE_VEC_NOT_NEUTORAL_COLOR (D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f))

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 前回の位置
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	D3DXVECTOR3 rot;	// 矢印の回転角
	float fLength;	// 矢印の対角線の長さ
	float fAngle;	// 矢印の対角線の角度
} ROPE_VEC;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;	// 矢印の回転角
} AXIS_ROT;

//
// プロトタイプ宣言
//
HRESULT InitRopeVec(void);
void UninitRopeVec(void);
void UpdateRopeVec(void);
void DrawRopeVec(void);
void SetRopeVec(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRopeVecWigth, float fRopeVecHeight);
void SetVertexRopeVec(int nIdx);
ROPE_VEC *GetRopeVec(void);

#endif 
