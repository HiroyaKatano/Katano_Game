//=========================================================================================================================
//
// �^�C�g�� [title.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureTitleBG = NULL;			// �^�C�g���w�i�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			// �^�C�g�����S�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureTitleLogoShadow = NULL;	// �^�C�g�����S�e�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureEnterSign = NULL;			// �G���^�[�T�C���e�N�X�`��
D3DXVECTOR3 g_posTitleBG; 								// �^�C�g���w�i�̈ʒu
D3DXVECTOR3 g_posTitleLogo;								// �^�C�g�����S�̈ʒu
D3DXVECTOR3 g_posTitleLogoShadow;						// �^�C�g�����S�e�̈ʒu
D3DXVECTOR3 g_posEnterSign;								// �G���^�[�T�C���̈ʒu
D3DXCOLOR g_colorEnterSign;								// �G���^�[�T�C���̐F
float g_fBGTexU = 0;
float g_fBGTexV = 0;
ENTERSTATE g_enterstate;
int g_nEnterSignTimer;

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

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg001.png", &g_pTextureTitleBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title001.png", &g_pTextureTitleLogoShadow);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title002.png", &g_pTextureTitleLogo);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title003.png", &g_pTextureEnterSign);

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

	g_enterstate = ENTERSTATE_WAIT;
	g_nEnterSignTimer = 0;

	// �^�C�g���w�i�̒��S���W
	g_posTitleBG.x = SCREEN_WIDTH / 2;
	g_posTitleBG.y = SCREEN_HEIGTH / 2;

	// �^�C�g�����S�e�̒��S���W
	g_posTitleLogoShadow.x = SCREEN_WIDTH / 2;
	g_posTitleLogoShadow.y = -50.0f;

	// �^�C�g�����S�̒��S���W
	g_posTitleLogo.x = SCREEN_WIDTH / 2;
	g_posTitleLogo.y = -45.0f;

	// �G���^�[�T�C���̒��S���W
	g_posEnterSign.x = SCREEN_WIDTH / 2;
	g_posEnterSign.y = 850.0f;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	g_posTitleBG = D3DXVECTOR3(g_posTitleBG.x, g_posTitleBG.y, 0.0f);
	g_posTitleLogoShadow = D3DXVECTOR3(g_posTitleLogoShadow.x, g_posTitleLogoShadow.y, 0.0f);
	g_posTitleLogo = D3DXVECTOR3(g_posTitleLogo.x, g_posTitleLogo.y, 0.0f);
	g_posEnterSign = D3DXVECTOR3(g_posEnterSign.x, g_posEnterSign.y, 0.0f);

	// ���_�J���[�̐ݒ�
	g_colorEnterSign = ENTER_SIGN_COLOR_OFF;

	for (int nCntTitle = 0; nCntTitle < MAX_TYPE_TITLE; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// �^�C�g���w�i
			pVtx[0].pos = D3DXVECTOR3(600, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(600, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TITLE_BG_SIZE_X - 600, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TITLE_BG_SIZE_X - 600, 0, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_BG_COLOR;
			pVtx[1].col = TITLE_BG_COLOR;
			pVtx[2].col = TITLE_BG_COLOR;
			pVtx[3].col = TITLE_BG_COLOR;
			break;
		case 1:
			// �^�C�g�����S�e
			pVtx[0].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[1].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[2].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[3].col = TITLE_LOGOSHADOW_COLOR;
			break;
		case 2:
			// �^�C�g�����S
			pVtx[0].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = TITLE_LOGO_COLOR;
			pVtx[1].col = TITLE_LOGO_COLOR;
			pVtx[2].col = TITLE_LOGO_COLOR;
			pVtx[3].col = TITLE_LOGO_COLOR;
			break;
		case 3:
			// �G���^�[�T�C��
			pVtx[0].pos = D3DXVECTOR3(g_posEnterSign.x - (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y + (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posEnterSign.x - (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y - (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posEnterSign.x + (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y + (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posEnterSign.x + (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y - (FLASHING_ENTER_SIZE_Y / 2), 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_colorEnterSign;
			pVtx[1].col = g_colorEnterSign;
			pVtx[2].col = g_colorEnterSign;
			pVtx[3].col = g_colorEnterSign;
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

	PlaySound(SOUND_LABEL_BGM002);

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
	if (g_pTextureTitleBG != NULL)
	{				   
		g_pTextureTitleBG->Release();
		g_pTextureTitleBG = NULL;
	}

	// �^�C�g�����S�e�N�X�`���̊J��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}

	// �^�C�g�����S�e�e�N�X�`���̊J��
	if (g_pTextureTitleLogoShadow != NULL)
	{
		g_pTextureTitleLogoShadow->Release();
		g_pTextureTitleLogoShadow = NULL;
	}

	// �G���^�[�T�C���e�N�X�`���̊J��
	if (g_pTextureEnterSign != NULL)
	{
		g_pTextureEnterSign->Release();
		g_pTextureEnterSign = NULL;
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

	g_fBGTexU -= MOVE_TITLE_BG_U;
	g_fBGTexV -= MOVE_TITLE_BG_V;



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g���w�i
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fBGTexU, 1.0f + g_fBGTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + g_fBGTexU, 0.0f + g_fBGTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + g_fBGTexU, 1.0f + g_fBGTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fBGTexU, 0.0f + g_fBGTexV);

	// �^�C�g�����S�e
	pVtx[4].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);

	// �^�C�g�����S
	pVtx[8].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[9].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[10].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[11].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);

	// �G���^�[�T�C��
	if (g_posTitleLogoShadow.y < 300.0f)
	{
		g_posTitleLogoShadow.y += 2.0f;
		g_posTitleLogo.y += 2.0f;
	}
	else if (g_posTitleLogoShadow.y >= 300.0f)
	{
		g_nEnterSignTimer += 1;

		if (g_enterstate == ENTERSTATE_WAIT)
		{
			if (g_nEnterSignTimer % 60 < 30)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_ON;
			}
			else if (g_nEnterSignTimer % 60 >= 30)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_OFF;
			}
		}
		else if (g_enterstate == ENTERSTATE_ACTIVE)
		{
			if (g_nEnterSignTimer % 10 < 5)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_ON;
			}
			else if (g_nEnterSignTimer % 10 >= 5)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_OFF;
			}
		}

	}

	pVtx[12].col = g_colorEnterSign;
	pVtx[13].col = g_colorEnterSign;
	pVtx[14].col = g_colorEnterSign;
	pVtx[15].col = g_colorEnterSign;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_TITLE);
		}
		else if (nFade == FADE_NONE && g_posTitleLogoShadow.y >= 250.0f)
		{
			SetFade(FADE_OUT, MODE_GAME);
			g_enterstate = ENTERSTATE_ACTIVE;
		}

		// �^�C�g�����S�e
		g_posTitleLogoShadow.y = 300.0f;

		// �^�C�g�����S
		g_posTitleLogo.y = 305.0f;
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
			pDevice->SetTexture(0, g_pTextureTitleBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureTitleLogoShadow);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureTitleLogo);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureEnterSign);
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
