//
//
//
//
//
//
#ifndef _WIRE_H_
#define _WIRE_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_WIRE (1)
#define WIRE_SIZE_VERTEX_X (1.5f)
#define WIRE_SIZE_Y (0.0f)
#define WIRE_MAX_SIZE_Y (120.0f)
#define WIRE_EXTEND_SPD (10.0f)
#define WIRE_ROLL_SPD (0.1f)

#define WIRE_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 前回の位置
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	float fContactHeight;	// 接地時のワイヤーの長さ
	bool bUse;				// 使用されているかどうか
	bool bContact;			// ブロックに触れたかどうか
	bool bExtend;			// ワイヤーが伸びているかどうか
	D3DXVECTOR3 rotWire;	// ワイヤーの回転角
	float fLengthWire;		// ワイヤーの対角線の長さ
	float fAngleWire;		// ワイヤーの対角線の角度
} WIRE;

//
// プロトタイプ宣言
//
HRESULT InitWire(void);
void UninitWire(void);
void UpdateWire(void);
void DrawWire(void);
void SetWire(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWireWigth, float fWireHeight);
void SetVertexWire(int nIdx);
WIRE *GetWire(void);

#endif 
