//=========================================================================================================================
//
// �^�C�g�� [title.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "title.h"
#include "input.h"
#include "fade.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_TYPE_TITLE (3)

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TYPE_TITLE] = {};	// �^�C�g���w�i�e�N�X�`��

D3DXVECTOR3 g_posTitleName; 								// �^�C�g�����̈ʒu
D3DXVECTOR3 g_posEnterSign; 								// �G���^�[�T�C���̈ʒu

TITLE g_aTitle[MAX_TYPE_TITLE];								// �^�C�g���̏��

char *g_aTextureTitleFile[TEX_TITLE_LABEL_MAX] =
{
	"data\\TEXTURE\\title_bg.jpg",			// �^�C�g���w�i
	"data\\TEXTURE\\title_name.png",		// �^�C�g����
	"data\\TEXTURE\\enter_sign.png",
};		// �^�C�g���摜�̃t�@�C���ꗗ

//=========================================================================================================================
// �^�C�g���̏���������
//=========================================================================================================================
HRESULT InitTitle(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	
	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, g_aTextureTitleFile[nCnt], &g_apTextureTitle[nCnt]);

		// ���̏�����
		g_aTitle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TYPE_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���S���W�̐ݒ�
	g_posTitleName = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f);
	g_posEnterSign = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 0.0f);

	for (int nCntTitle = 0; nCntTitle < MAX_TYPE_TITLE; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// �^�C�g���w�i
			pVtx[0].pos = D3DXVECTOR3(0.0f, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TITLE_BG_SIZE_X, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TITLE_BG_SIZE_X, 0.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_NORMAL_COLOR;
			pVtx[1].col = TITLE_NORMAL_COLOR;
			pVtx[2].col = TITLE_NORMAL_COLOR;
			pVtx[3].col = TITLE_NORMAL_COLOR;
			break;
		case 1:
			// �^�C�g���w�i
			pVtx[0].pos = D3DXVECTOR3(g_posTitleName.x - TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y + TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleName.x - TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y - TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleName.x + TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y + TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleName.x + TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y - TITLE_NAME_VERTEX_SIZE_Y, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_NAME_COLOR;
			pVtx[1].col = TITLE_NAME_COLOR;
			pVtx[2].col = TITLE_NAME_COLOR;
			pVtx[3].col = TITLE_NAME_COLOR;
			break;
		case 2:
			// �^�C�g���w�i
			pVtx[0].pos = D3DXVECTOR3(g_posEnterSign.x - ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y + ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posEnterSign.x - ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y - ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posEnterSign.x + ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y + ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posEnterSign.x + ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y - ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_NORMAL_COLOR;
			pVtx[1].col = TITLE_NORMAL_COLOR;
			pVtx[2].col = TITLE_NORMAL_COLOR;
			pVtx[3].col = TITLE_NORMAL_COLOR;
			break;
		default:
			break;
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += 4;
	}


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	return S_OK;
}

//=========================================================================================================================
// �^�C�g���̏I������
//=========================================================================================================================
void UninitTitle(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// �^�C�g���w�i�e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}
}

//=========================================================================================================================
// �^�C�g���̍X�V����
//=========================================================================================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	// �ϐ��錾
	int nFade = GetFade();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g���w�i
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_TITLE);
		}
		else if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
	}
}

//=========================================================================================================================
// �^�C�g���̕`�揈��
//=========================================================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
			break;
		case 1:
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
			break;
		case 2:
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
			break;
		default:
			break;
		}

		// �^�C�g���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * 4,						// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}
