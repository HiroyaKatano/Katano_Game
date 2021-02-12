//=========================================================================================================================
//
// �X�R�A [Score.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "Score.h"
#include "BG.h"

//
// �O���[�o���ϐ�
//
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
int g_nScore;

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number_04.png", &g_pTextureScore);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCORE_LEFT_X + SCORE_WIDTH_X * nCntScore, SCORE_LOW_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_LEFT_X + SCORE_WIDTH_X * nCntScore, SCORE_HIGH_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_RIGHT_X + SCORE_WIDTH_X * nCntScore, SCORE_LOW_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_RIGHT_X + SCORE_WIDTH_X * nCntScore, SCORE_HIGH_Y, 0.0f);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X, 1.0f / SCORE_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	g_nScore = 200000;

	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitScore(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateScore(void)
{

}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		// �G�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCntScore * 4,					// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}

//=========================================================================================================================
// �X�R�A�̉��Z����
//=========================================================================================================================
void AddScore(int nValue)
{
	// �ϐ��錾
	int nData = 10000000;	// ���鐔
	int aNumber[8];			// �X�R�A���i�[
	g_nScore -= nValue;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �X�R�A���i�[
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		aNumber[nCntScore] = (g_nScore / nData) % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X + aNumber[nCntScore] * 0.1f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X + aNumber[nCntScore] * 0.1f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}