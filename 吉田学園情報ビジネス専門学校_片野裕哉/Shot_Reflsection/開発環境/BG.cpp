//=========================================================================================================================
//
// �w�i�̃e�N�X�`�� [BG.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "BG.h"
#include "input.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureFirstBG = NULL;		// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureSecondBG = NULL;		// �e�N�X�`��
float g_fFirstTexU = 0;							
float g_fFirstTexV = 0;
float g_fSecondTexU = 0;
float g_fSecondTexV = 0;

//=========================================================================================================================
// �w�i�̏���������
//=========================================================================================================================
HRESULT InitBG(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg001.png", &g_pTextureFirstBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_bg002.png", &g_pTextureSecondBG);
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg103.png", &g_pTextureBG);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BG_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL)))
	{
		return E_FAIL;
	}
 
	

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BG_TYPE; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_LEFT_X, BG_POS_UNDER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_POS_LEFT_X, BG_POS_TOP_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_RIGHT_X, BG_POS_UNDER_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_POS_RIGHT_X, BG_POS_TOP_Y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �w�i�̏I������
//=========================================================================================================================
void UninitBG(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureFirstBG != NULL)
	{
		g_pTextureFirstBG->Release();
		g_pTextureFirstBG = NULL;
	}

	if (g_pTextureSecondBG != NULL)
	{			 
		g_pTextureSecondBG->Release();
		g_pTextureSecondBG = NULL;
	}
}

//=========================================================================================================================
// �w�i�̍X�V����
//=========================================================================================================================
void UpdateBG(void)
{
	VERTEX_2D *pVtx;

	g_fFirstTexV -= MOVE_BG01;
	g_fSecondTexV -= MOVE_BG02;

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_fFirstTexV -= MOVE_BG01 / 2;
		g_fSecondTexV -= MOVE_BG02 / 2;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_fFirstTexV += MOVE_BG01 / 2;
		g_fSecondTexV += MOVE_BG02 / 2;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_fFirstTexU -= MOVE_BG01 / 2;
		g_fSecondTexU -= MOVE_BG02 / 2;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_fFirstTexU += MOVE_BG01 / 2;
		g_fSecondTexU += MOVE_BG02 / 2;
	}
	

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fFirstTexU, 1.0f + g_fFirstTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + g_fFirstTexU, 0.0f + g_fFirstTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + g_fFirstTexU, 1.0f + g_fFirstTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fFirstTexU, 0.0f + g_fFirstTexV);

	pVtx[4].tex = D3DXVECTOR2(0.0f + g_fSecondTexU, 1.0f + g_fSecondTexV);
	pVtx[5].tex = D3DXVECTOR2(0.0f + g_fSecondTexU, 0.0f + g_fSecondTexV);
	pVtx[6].tex = D3DXVECTOR2(1.0f + g_fSecondTexU, 1.0f + g_fSecondTexV);
	pVtx[7].tex = D3DXVECTOR2(1.0f + g_fSecondTexU, 0.0f + g_fSecondTexV);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// �w�i�̕`�揈��
//=========================================================================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_BG_TYPE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureFirstBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureSecondBG);
			break;
		}

		// �w�i�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * 4,						// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}
