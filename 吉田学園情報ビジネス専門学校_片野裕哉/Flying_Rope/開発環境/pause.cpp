//=========================================================================================================================
//
// �|�[�Y��� [pause.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "Pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTexturePauseBG = NULL;			// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;				// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePauseLogo = NULL;			// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureContinue = NULL;			// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;				// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;				// �e�N�X�`��
D3DXVECTOR3 g_posPauseBG;								// ��ʈÓ]�̈ʒu
D3DXVECTOR3 g_posPause;									// ���n�̈ʒu
D3DXVECTOR3 g_posPauseLogo;								// Pause�̈ʒu
D3DXVECTOR3 g_posContinue;								// Continue�̈ʒu
D3DXVECTOR3 g_posRetry;									// Retry�̈ʒu
D3DXVECTOR3 g_posQuit;									// Quit�̈ʒu
int g_Pause_Manu;										// �|�[�Y���j���[�̑I��p

//=========================================================================================================================
// �|�[�Y�̏���������
//=========================================================================================================================
HRESULT InitPause(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause.png", &g_pTexturePause);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PauseLogo.png", &g_pTexturePauseLogo);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Continue.png", &g_pTextureContinue);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Retry.png", &g_pTextureRetry);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Quit.png", &g_pTextureQuit);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_PAUSE_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	g_Pause_Manu = PAUSE_MENU_CONTINUE;

	// ��ʈÓ]�̒��S���W
	g_posPauseBG.x = SCREEN_WIDTH_R / 2;
	g_posPauseBG.y = SCREEN_HEIGHT_U / 2;

	// �|�[�Y���n�̒��S���W
	g_posPause.x = SCREEN_WIDTH_R / 2;
	g_posPause.y = SCREEN_HEIGHT_U / 2;

	// Pause�̒��S���W
	g_posPauseLogo.x = SCREEN_WIDTH_R / 2;
	g_posPauseLogo.y = 100;

	// Continue�̒��S���W
	g_posContinue.x = SCREEN_WIDTH_R / 2;
	g_posContinue.y = 250;

	// Retry�̒��S���W
	g_posRetry.x = SCREEN_WIDTH_R / 2;
	g_posRetry.y = 425;

	// Quit�̒��S���W
	g_posQuit.x = SCREEN_WIDTH_R / 2;
	g_posQuit.y = 600;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	g_posPauseBG = D3DXVECTOR3(g_posPauseBG.x, g_posPauseBG.y, Z_AXIS_ZERO);
	g_posPause = D3DXVECTOR3(g_posPause.x, g_posPause.y, Z_AXIS_ZERO);
	g_posPauseLogo = D3DXVECTOR3(g_posPauseLogo.x, g_posPauseLogo.y, Z_AXIS_ZERO);
	g_posContinue = D3DXVECTOR3(g_posContinue.x, g_posContinue.y, Z_AXIS_ZERO);
	g_posRetry = D3DXVECTOR3(g_posRetry.x, g_posRetry.y, Z_AXIS_ZERO);
	g_posQuit = D3DXVECTOR3(g_posQuit.x, g_posQuit.y, Z_AXIS_ZERO);


	for (int nPause = 0; nPause < MAX_PAUSE_TYPE; nPause++)
	{
		switch (nPause)
		{
		case 0:
			// ��ʈÓ]
			pVtx[0].pos = D3DXVECTOR3(0, PAUSE_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(0, 0, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(PAUSE_BG_SIZE_X, PAUSE_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(PAUSE_BG_SIZE_X, 0, Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = PAUSE_BG_COLOR;
			pVtx[1].col = PAUSE_BG_COLOR;
			pVtx[2].col = PAUSE_BG_COLOR;
			pVtx[3].col = PAUSE_BG_COLOR;
			break;
		case 1:
			// �|�[�Y���n
			pVtx[0].pos = D3DXVECTOR3(g_posPause.x - (PAUSE_SIZE_X / 2), g_posPause.y + (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posPause.x - (PAUSE_SIZE_X / 2), g_posPause.y - (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posPause.x + (PAUSE_SIZE_X / 2), g_posPause.y + (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posPause.x + (PAUSE_SIZE_X / 2), g_posPause.y - (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = PAUSE_COLOR;
			pVtx[1].col = PAUSE_COLOR;
			pVtx[2].col = PAUSE_COLOR;
			pVtx[3].col = PAUSE_COLOR;
			break;
		case 2:
			// �|�[�Y���S
			pVtx[0].pos = D3DXVECTOR3(g_posPauseLogo.x - (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y + (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posPauseLogo.x - (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y - (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posPauseLogo.x + (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y + (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posPauseLogo.x + (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y - (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = PAUSE_LOGO_COLOR;
			pVtx[1].col = PAUSE_LOGO_COLOR;
			pVtx[2].col = PAUSE_LOGO_COLOR;
			pVtx[3].col = PAUSE_LOGO_COLOR;
			break;
		case 3:
			// Continue
			pVtx[0].pos = D3DXVECTOR3(g_posContinue.x - (CONTINUE_SIZE_X / 2), g_posContinue.y + (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posContinue.x - (CONTINUE_SIZE_X / 2), g_posContinue.y - (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posContinue.x + (CONTINUE_SIZE_X / 2), g_posContinue.y + (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posContinue.x + (CONTINUE_SIZE_X / 2), g_posContinue.y - (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = CONTINUE_COLOR;
			pVtx[1].col = CONTINUE_COLOR;
			pVtx[2].col = CONTINUE_COLOR;
			pVtx[3].col = CONTINUE_COLOR;
			break;
		case 4:
			// Retry
			pVtx[0].pos = D3DXVECTOR3(g_posRetry.x - (RETRY_SIZE_X / 2), g_posRetry.y + (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posRetry.x - (RETRY_SIZE_X / 2), g_posRetry.y - (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posRetry.x + (RETRY_SIZE_X / 2), g_posRetry.y + (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posRetry.x + (RETRY_SIZE_X / 2), g_posRetry.y - (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = RETRY_COLOR;
			pVtx[1].col = RETRY_COLOR;
			pVtx[2].col = RETRY_COLOR;
			pVtx[3].col = RETRY_COLOR;
			break;
		case 5:
			// Quit
			pVtx[0].pos = D3DXVECTOR3(g_posQuit.x - (QUIT_SIZE_X / 2), g_posQuit.y + (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posQuit.x - (QUIT_SIZE_X / 2), g_posQuit.y - (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posQuit.x + (QUIT_SIZE_X / 2), g_posQuit.y + (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posQuit.x + (QUIT_SIZE_X / 2), g_posQuit.y - (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = QUIT_COLOR;
			pVtx[1].col = QUIT_COLOR;
			pVtx[2].col = QUIT_COLOR;
			pVtx[3].col = QUIT_COLOR;
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

		pVtx += VTX_NUM;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �|�[�Y�̏I������
//=========================================================================================================================
void UninitPause(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePauseLogo != NULL)
	{
		g_pTexturePauseLogo->Release();
		g_pTexturePauseLogo = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureContinue != NULL)
	{
		g_pTextureContinue->Release();
		g_pTextureContinue = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();
		g_pTextureRetry = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();
		g_pTextureQuit = NULL;
	}
}

//=========================================================================================================================
// �|�[�Y�̍X�V����
//=========================================================================================================================
void UpdatePause(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	int nFade = GetFade();

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			switch (g_Pause_Manu)
			{
			case PAUSE_MENU_CONTINUE:
				SetPause(false);
				break;
			case PAUSE_MENU_RETRY:
				SetFade(FADE_OUT, MODE_GAME);
				break;
			case PAUSE_MENU_QUIT:
				SetFade(FADE_OUT, MODE_TITLE);
				break;
			}
		}


		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_Pause_Manu += 1;

			if (g_Pause_Manu > PAUSE_MENU_QUIT)
			{
				g_Pause_Manu = PAUSE_MENU_CONTINUE;
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_Pause_Manu -= 1;

			if (g_Pause_Manu < PAUSE_MENU_CONTINUE)
			{
				g_Pause_Manu = PAUSE_MENU_QUIT;
			}
		}


		for (int nPause = 0; nPause < MAX_PAUSE_TYPE; nPause++)
		{
			if (g_Pause_Manu == 0)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 5:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_Pause_Manu == 1)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				case 5:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_Pause_Manu == 2)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;		  
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 5:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				}
			}

			pVtx += VTX_NUM;
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPause->Unlock();
	}
}

//=========================================================================================================================
// �|�[�Y�̕`�揈��
//=========================================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_PAUSE_TYPE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTexturePauseBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTexturePause);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTexturePauseLogo);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureContinue);
			break;
		case 4:
			pDevice->SetTexture(0, g_pTextureRetry);
			break;
		case 5:
			pDevice->SetTexture(0, g_pTextureQuit);
			break;
		default:
			break;
		}

		// �|�[�Y�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * VTX_NUM,						// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}


//
//
//