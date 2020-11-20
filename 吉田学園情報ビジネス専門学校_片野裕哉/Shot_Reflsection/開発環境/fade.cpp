//=========================================================================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "fade.h"
#include "input.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;			// �e�N�X�`��
FADE g_fade;										// �t�F�[�h�̏��
MODE g_modeNext;									// ���̃��[�h(���)
D3DXCOLOR g_colorFade;								// �t�F�[�h�F

//=========================================================================================================================
// �t�F�[�h�̏���������
//=========================================================================================================================
HRESULT InitFade(MODE modeNext)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	g_fade = FADE_IN;

	g_modeNext = modeNext;

	// ���_�J���[�̐ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �t�F�[�h�̏I������
//=========================================================================================================================
void UninitFade(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=========================================================================================================================
// �t�F�[�h�̍X�V����
//=========================================================================================================================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


	if (g_fade == FADE_NONE)
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.025f;

		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}
	else if (g_fade == FADE_OUT)
	{
		g_colorFade.a += 0.025f;

		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			
			SetMode(g_modeNext);
		}
	}
	g_pVtxBuffFade->Unlock();
}

//=========================================================================================================================
// �t�F�[�h�̕`�揈��
//=========================================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	// �t�F�[�h�̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�
}

//=========================================================================================================================
// �t�F�[�h�̃Z�b�g����
//=========================================================================================================================
void SetFade(FADE fade, MODE modeNext)
{	
	g_fade = fade;
	g_modeNext = modeNext;
}

//=========================================================================================================================
// �t�F�[�h�̎擾
//=========================================================================================================================
FADE GetFade(void)
{
	return g_fade;
}
