//=========================================================================================================================
//
// �S�[�� [goal.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "goal.h"

//========================================================================================================================
// �}�N����`
//========================================================================================================================
#define GOAL_SPD (1.0f)				// �S�[���̑��x(�㉺)
#define GOAL_SPD_DECAY (0.25f)		// �ړ��̒�R�l

#define GOAL_COLOR_R (1.0f)			// �w�i�F(��)
#define GOAL_COLOR_G (1.0f)			// �w�i�F(��)
#define GOAL_COLOR_B (1.0f)			// �w�i�F(��)
#define GOAL_COLOR_A (1.0f)			// �w�i�F(�����x)

#define GOAL_SIZE_VERTEX_X (8.4f)	// �S�[���̉����a
#define GOAL_SIZE_Y (36.0f)			// �S�[���̏c��

#define MAX_GOAL (1)				// �S�[���̐�

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;	// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			// �e�N�X�`��
GOAL g_goal;										// �S�[���̍\����

//=========================================================================================================================
// �S�[���̏���������
//=========================================================================================================================
HRESULT InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal_star.png", &g_pTextureGoal);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 *MAX_GOAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL)))
	{
		return E_FAIL;
	}

	// �S�[�����̏�����
	g_goal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.fWidth = 0.0f;
	g_goal.fHeight = 0.0f;
	g_goal.bUse = false;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_goal.pos.x - g_goal.fWidth, g_goal.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_goal.pos.x - g_goal.fWidth, g_goal.pos.y - g_goal.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y - g_goal.fHeight, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
	pVtx[1].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
	pVtx[2].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
	pVtx[3].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �S�[���̏I������
//=========================================================================================================================
void UninitGoal(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
}

//=========================================================================================================================
// �S�[���̍X�V����
//=========================================================================================================================
void UpdateGoal(void)
{

}

//=========================================================================================================================
// �S�[���̕`�揈��
//=========================================================================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	// �S�[���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�
}

//=========================================================================================================================
// �S�[���̎擾
//=========================================================================================================================
GOAL *GetGoal(void)
{
	return &g_goal;
}

//=========================================================================================================================
// �S�[���̃Z�b�g����
//=========================================================================================================================
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight)
{
	GOAL *pGoal;
	pGoal = &g_goal;

	if (pGoal->bUse == false)
	{
		// �ʒu�̐ݒ�
		pGoal->pos = pos;

		pGoal->move = move;

		pGoal->fWidth = fWigth;

		pGoal->fHeight = fHeight;

		pGoal->bUse = true;

		
	}
}


////=========================================================================================================================
//// 
////=========================================================================================================================
//void SetVertexGoal(void)
//{
//	VERTEX_2D *pVtx;
//	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx[0].pos = D3DXVECTOR3(g_goal.pos.x - g_goal.fWidth, g_goal.pos.y, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_goal.pos.x - g_goal.fWidth, g_goal.pos.y - g_goal.fHeight, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y - g_goal.fHeight, 0.0f);
//
//	// ���_�J���[�̐ݒ�
//	pVtx[0].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
//	pVtx[1].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
//	pVtx[2].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
//	pVtx[3].col = D3DXCOLOR(GOAL_COLOR_R, GOAL_COLOR_G, GOAL_COLOR_B, GOAL_COLOR_A);
//
//	// ���_���̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
//
//
//	// ���_�o�b�t�@�̊J��
//	g_pVtxBuffGoal->Unlock();
//}