//=========================================================================================================================
//
// �`���[�g���A�� [tutorial.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;		// �e�N�X�`��

//=========================================================================================================================
// �`���[�g���A���̏���������
//=========================================================================================================================
HRESULT InitTutorial(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.jpg", &g_pTextureTutorial);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_LEFT_X, TUTORIAL_POS_UNDER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_POS_LEFT_X, TUTORIAL_POS_TOP_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_RIGHT_X, TUTORIAL_POS_UNDER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_POS_RIGHT_X, TUTORIAL_POS_TOP_Y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[1].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[2].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[3].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �`���[�g���A���̏I������
//=========================================================================================================================
void UninitTutorial(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
}

//=========================================================================================================================
// �`���[�g���A���̍X�V����
//=========================================================================================================================
void UpdateTutorial(void)
{
	//VERTEX_2D *pVtx;
	int nFade = GetFade();

	//g_fTexU += MOVE_FIRST_TUTORIAL_U;


	//// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexU, 1.0f + g_fTexV);
	//pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexU, 0.0f + g_fTexV);
	//pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexU, 1.0f + g_fTexV);
	//pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexU, 0.0f + g_fTexV);

	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffTutorial->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
	}
}

//=========================================================================================================================
// �`���[�g���A���̕`�揈��
//=========================================================================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	// �`���[�g���A���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�

}
