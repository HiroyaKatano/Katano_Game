//=========================================================================================================================
//
// ���U���g [result.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_apTextureResult[2] = {};			// �e�N�X�`��
int g_nResult;

//=========================================================================================================================
// ���U���g�̏���������
//=========================================================================================================================
HRESULT InitResult(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtex;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\failed_cat.jpg", &g_apTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result_cat.jpg", &g_apTextureResult[1]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtex, 0);

	// ���_���W�̐ݒ�
	pVtex[0].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_U, 0.0f);
	pVtex[1].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_T, 0.0f);
	pVtex[2].pos = D3DXVECTOR3(SCREEN_WIDTH_R, SCREEN_HEIGHT_U, 0.0f);
	pVtex[3].pos = D3DXVECTOR3(SCREEN_WIDTH_R, SCREEN_HEIGHT_T, 0.0f);

	// rhw�̐ݒ�
	pVtex[0].rhw = 1.0f;
	pVtex[1].rhw = 1.0f;
	pVtex[2].rhw = 1.0f;
	pVtex[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtex[0].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[1].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[2].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[3].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);

	// ���_���̐ݒ�
	pVtex[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtex[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtex[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtex[3].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//=========================================================================================================================
// ���U���g�̏I������
//=========================================================================================================================
void UninitResult(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=========================================================================================================================
// ���U���g�̍X�V����
//=========================================================================================================================
void UpdateResult(void)
{
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//=========================================================================================================================
// ���U���g�̕`�揈��
//=========================================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	switch (g_nResult)
	{
	case 0:
		pDevice->SetTexture(0, g_apTextureResult[1]);
		break;
	default:
		pDevice->SetTexture(0, g_apTextureResult[0]);
		break;
	}
	

	// ���U���g�̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�
}


//
//
//
int GetResult(void)
{
	return g_nResult;
}
