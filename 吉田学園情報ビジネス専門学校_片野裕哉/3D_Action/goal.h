//
//
// �S�[���w�b�_�[ [goal.h]
//
//
//
#ifndef _GOAL_H_
#define _GOAL_H_
#include "main.h"

//
// �}�N����`
//
#define MAX_MODEL_G (1)		// ���f��(�p�[�c)�̍ő吔(����)

//
// �\����
//
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;		// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;	// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMatModel = NULL;			// �}�e���A���̐�
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ���
	D3DXVECTOR3 rot;					// ����
	D3DXVECTOR3 rotDest;				// �ړI�̌���
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	int nIdxModelParent;				// �e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMinModel;			// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;			// ���f���̍ő�l

} MODEL_G;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 rotDest;		// �ړI�̌���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	MODEL_G aModel[MAX_MODEL_G];	// ���f��(�p�[�c)
	int nNumModel;				// ���f��(�p�[�c)�̐�
} GOAL;

typedef enum
{
	MODEL_G_LABEL_GOAL = 0,	// ������
	MODEL_G_LABEL_MAX
} MODEL_G_LABEL;

//
// �v���g�^�C�v�錾
//
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
GOAL *GetGoal(void);

#endif