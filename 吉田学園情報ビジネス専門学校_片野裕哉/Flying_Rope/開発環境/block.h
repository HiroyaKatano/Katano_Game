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
// �}�N����`
//
#define MAX_BLOCK (256)
#define BLOCK_SIZE_X (100)
#define BLOCK_SIZE_Y (50)
#define BLOCK_MOVE_X (10)

#define BLOCK_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

//
// �\���̂̒�`
//
typedef enum
{
	BLOCKTYPE_BLOCK = 0,
	BLOCKTYPE_GOAL,
	BLOCKTYPE_MAX,
} BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXCOLOR col;		// �F
	float fWidth;		// ��
	float fHeight;		// ����
	BLOCKTYPE BlockType;
	bool bUse;			// �g�p����Ă��邩�ǂ���
} BLOCK;

//
// �v���g�^�C�v�錾
//
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockMove, float fBlockWigth, float fBlockHeight, BLOCKTYPE BlockType);
void SetVertexBlock(int nIdx);
BLOCK *GetBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,	// �u���b�N�̓����蔻��
	D3DXVECTOR3 *pMove, float fWidth, float fHeight);			// (���݂̈ʒu, �O��̈ʒu, �ړ���, ��, ����)

#endif 
