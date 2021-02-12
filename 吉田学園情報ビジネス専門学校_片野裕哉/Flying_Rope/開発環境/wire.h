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
// �}�N����`
//
#define MAX_WIRE (1)
#define WIRE_SIZE_VERTEX_X (1.5f)
#define WIRE_SIZE_Y (0.0f)
#define WIRE_MAX_SIZE_Y (120.0f)
#define WIRE_EXTEND_SPD (10.0f)
#define WIRE_ROLL_SPD (0.1f)

#define WIRE_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

//
// �\���̂̒�`
//
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �O��̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	float fContactHeight;	// �ڒn���̃��C���[�̒���
	bool bUse;				// �g�p����Ă��邩�ǂ���
	bool bContact;			// �u���b�N�ɐG�ꂽ���ǂ���
	bool bExtend;			// ���C���[���L�тĂ��邩�ǂ���
	D3DXVECTOR3 rotWire;	// ���C���[�̉�]�p
	float fLengthWire;		// ���C���[�̑Ίp���̒���
	float fAngleWire;		// ���C���[�̑Ίp���̊p�x
} WIRE;

//
// �v���g�^�C�v�錾
//
HRESULT InitWire(void);
void UninitWire(void);
void UpdateWire(void);
void DrawWire(void);
void SetWire(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWireWigth, float fWireHeight);
void SetVertexWire(int nIdx);
WIRE *GetWire(void);

#endif 
