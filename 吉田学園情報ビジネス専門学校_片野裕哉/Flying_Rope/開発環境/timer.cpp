//=========================================================================================================================
//
// �^�C�}�[ [�^�C�}�[.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "timer.h"
#include "fade.h"
#include "Score.h"
#include "result.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;			// �e�N�X�`��
int g_nTimer;
int g_nCntTimer;

//=========================================================================================================================
// �^�C�}�[�̏���������
//=========================================================================================================================
HRESULT InitTimer(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number_04.png", &g_pTextureTimer);


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_TYPE_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL)))
	{
		return E_FAIL;
	}

	g_nTimer = 60;
	g_nCntTimer = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH * nCntTimer, TIMER_POS_Y + TIMER_HEIGHT, Z_AXIS_ZERO);
		pVtx[1].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH * nCntTimer, TIMER_POS_Y, Z_AXIS_ZERO);
		pVtx[2].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH + TIMER_WIDTH * nCntTimer, TIMER_POS_Y + TIMER_HEIGHT, Z_AXIS_ZERO);
		pVtx[3].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH + TIMER_WIDTH * nCntTimer, TIMER_POS_Y, Z_AXIS_ZERO);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[1].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[2].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[3].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);

		pVtx += VTX_NUM;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �^�C�}�[�̏I������
//=========================================================================================================================
void UninitTimer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

}

//=========================================================================================================================
// �^�C�}�[�̍X�V����
//=========================================================================================================================
void UpdateTimer(void)
{
	int nFade = GetFade();
	RESULT *pResult = GetResult();

	g_nCntTimer++;
	if (g_nCntTimer % 6 == 0 && nFade == FADE_NONE)
	{
		AddScore(300);
	}

	if (g_nCntTimer % 60 == 0 && nFade == FADE_NONE)
	{
		g_nTimer -= 1;
	}

	// �ϐ��錾
	int nData = 10;	// ���鐔
	int aNumber[2];			// �X�R�A���i�[

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// �X�R�A���i�[
	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		aNumber[nCntTimer] = (g_nTimer / nData) % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + aNumber[nCntTimer] * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + aNumber[nCntTimer] * 0.1f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += VTX_NUM;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

	if (g_nTimer == 0)
	{
		if (nFade == FADE_NONE)
		{
			pResult->ResultType = RESULTTYPE_FAILED;
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
	
}

//=========================================================================================================================
// �^�C�}�[�̕`�揈��
//=========================================================================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCntTimer)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureTimer);
			break;
		default:
			break;
		}

		// �^�C�}�[�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCntTimer * VTX_NUM,					// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}

