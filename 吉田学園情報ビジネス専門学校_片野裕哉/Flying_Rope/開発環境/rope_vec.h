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
// �}�N����`
//
#define MAX_ROPE_VEC (8)
#define ROPE_VEC_SIZE_VERTEX_X (8.4f)
#define ROPE_VEC_SIZE_VERTEX_Y (15.0f)
#define ROPE_VEC_MAX_SIZE_Y (120.0f)

#define ROPE_VEC_NEUTORAL_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f))
#define ROPE_VEC_NOT_NEUTORAL_COLOR (D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f))

//
// �\���̂̒�`
//
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �O��̈ʒu
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	D3DXVECTOR3 rot;	// ���̉�]�p
	float fLength;	// ���̑Ίp���̒���
	float fAngle;	// ���̑Ίp���̊p�x
} ROPE_VEC;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;	// ���̉�]�p
} AXIS_ROT;

//
// �v���g�^�C�v�錾
//
HRESULT InitRopeVec(void);
void UninitRopeVec(void);
void UpdateRopeVec(void);
void DrawRopeVec(void);
void SetRopeVec(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRopeVecWigth, float fRopeVecHeight);
void SetVertexRopeVec(int nIdx);
ROPE_VEC *GetRopeVec(void);

#endif 
