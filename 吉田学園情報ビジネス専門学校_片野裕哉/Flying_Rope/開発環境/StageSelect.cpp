//=========================================================================================================================
//
// �X�e�[�W�Z���N�g [StageSelect.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "StageSelect.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageSelect = NULL;	// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureStageSelectBG = NULL;		// �X�e�[�W�Z���N�g�w�i�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureStage1 = NULL;				// �X�e�[�W1�̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureStage2 = NULL;				// �X�e�[�W2�̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureStage3 = NULL;				// �X�e�[�W3�̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureStage4 = NULL;				// �X�e�[�W4�̃e�N�X�`��
D3DXVECTOR3 g_posStageSelectBG; 						// �X�e�[�W�Z���N�g�w�i�̈ʒu
D3DXVECTOR3 g_posStage1; 								// �X�e�[�W1�̈ʒu
D3DXVECTOR3 g_posStage2; 								// �X�e�[�W2�̈ʒu
D3DXVECTOR3 g_posStage3; 								// �X�e�[�W3�̈ʒu
D3DXVECTOR3 g_posStage4; 								// �X�e�[�W4�̈ʒu
float g_fTexStageSelect_U = 0;
float g_fTexStageSelect_V = 0;

int g_StageSelect;										// �X�e�[�W�I��p

//=========================================================================================================================
// �X�e�[�W�Z���N�g�̏���������
//=========================================================================================================================
HRESULT InitStageSelect(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg", &g_pTextureStageSelectBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Stage01.jpg", &g_pTextureStage1);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Stage02.jpg", &g_pTextureStage2);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Stage03.jpg", &g_pTextureStage3);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Stage04.jpg", &g_pTextureStage4);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_BG_STAGESELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStageSelect,
		NULL)))
	{
		return E_FAIL;
	}

	

	for (int nCntStage = 0; nCntStage < MAX_BG_STAGESELECT; nCntStage++)
	{
		switch (nCntStage)
		{
		case 0:
			// �X�e�[�W�Z���N�g�w�i�̒��S���W
			g_posStageSelectBG.x = SCREEN_WIDTH_R / 2;
			g_posStageSelectBG.y = SCREEN_HEIGHT_U / 2;
			break;
		case 1:
			// �X�e�[�W1�̒��S���W
			g_posStage1.x = (float)SCREEN_WIDTH_R / 4;
			g_posStage1.y = SCREEN_HEIGHT_U * 2 / 7;
			break;
		case 2:
			// �X�e�[�W2�̒��S���W
			g_posStage2.x = (float)SCREEN_WIDTH_R * 3 / 4;
			g_posStage2.y = SCREEN_HEIGHT_U * 2 / 7;
			break;
		case 3:
			// �X�e�[�W3�̒��S���W
			g_posStage3.x = (float)SCREEN_WIDTH_R / 4;
			g_posStage3.y = SCREEN_HEIGHT_U * 11 / 15;
			break;
		case 4:
			// �X�e�[�W4�̒��S���W
			g_posStage4.x = (float)SCREEN_WIDTH_R * 3 / 4;
			g_posStage4.y = SCREEN_HEIGHT_U * 11 / 15;
			break;
		default:
			break;
		}
		
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	g_posStageSelectBG = D3DXVECTOR3(g_posStageSelectBG.x, g_posStageSelectBG.y, Z_AXIS_ZERO);
	//g_posStageSelectLogo = D3DXVECTOR3(g_posStageSelectLogo.x, g_posStageSelectLogo.y, Z_AXIS_ZERO);

	for (int nCntStageSelect = 0; nCntStageSelect < MAX_BG_STAGESELECT; nCntStageSelect++)
	{
		switch (nCntStageSelect)
		{
		case 0:
			// �X�e�[�W�Z���N�g�w�i
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH_L, STAGESELECT_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_T, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(STAGESELECT_BG_SIZE_X, STAGESELECT_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(STAGESELECT_BG_SIZE_X, SCREEN_HEIGHT_T, Z_AXIS_ZERO);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_B_COLOR;
			break;
		case 1:
			// �X�e�[�W1�̒��_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posStage1.x - STAGE_VTX_SIZE_X, g_posStage1.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posStage1.x - STAGE_VTX_SIZE_X, g_posStage1.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posStage1.x + STAGE_VTX_SIZE_X, g_posStage1.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posStage1.x + STAGE_VTX_SIZE_X, g_posStage1.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 2:
			// �X�e�[�W1�̒��_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posStage2.x - STAGE_VTX_SIZE_X, g_posStage2.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posStage2.x - STAGE_VTX_SIZE_X, g_posStage2.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posStage2.x + STAGE_VTX_SIZE_X, g_posStage2.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posStage2.x + STAGE_VTX_SIZE_X, g_posStage2.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 3:
			// �X�e�[�W1�̒��_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posStage3.x - STAGE_VTX_SIZE_X, g_posStage3.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posStage3.x - STAGE_VTX_SIZE_X, g_posStage3.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posStage3.x + STAGE_VTX_SIZE_X, g_posStage3.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posStage3.x + STAGE_VTX_SIZE_X, g_posStage3.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 4:
			// �X�e�[�W1�̒��_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posStage4.x - STAGE_VTX_SIZE_X, g_posStage4.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posStage4.x - STAGE_VTX_SIZE_X, g_posStage4.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posStage4.x + STAGE_VTX_SIZE_X, g_posStage4.y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posStage4.x + STAGE_VTX_SIZE_X, g_posStage4.y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		default:
			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

			break;
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += VTX_NUM;
	}


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStageSelect->Unlock();

	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//=========================================================================================================================
// �X�e�[�W�Z���N�g�̏I������
//=========================================================================================================================
void UninitStageSelect(void)
{
	StopSound();

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffStageSelect != NULL)
	{
		g_pVtxBuffStageSelect->Release();
		g_pVtxBuffStageSelect = NULL;
	}

	// �X�e�[�W�Z���N�g�w�i�e�N�X�`���̊J��
	if (g_pTextureStageSelectBG != NULL)
	{
		g_pTextureStageSelectBG->Release();
		g_pTextureStageSelectBG = NULL;
	}

	// �X�e�[�W1�̃e�N�X�`���̊J��
	if (g_pTextureStage1 != NULL)
	{
		g_pTextureStage1->Release();
		g_pTextureStage1 = NULL;
	}

	// �X�e�[�W2�̃e�N�X�`���̊J��
	if (g_pTextureStage2 != NULL)
	{
		g_pTextureStage2->Release();
		g_pTextureStage2 = NULL;
	}

	// �X�e�[�W3�̃e�N�X�`���̊J��
	if (g_pTextureStage3 != NULL)
	{
		g_pTextureStage3->Release();
		g_pTextureStage3 = NULL;
	}

	// �X�e�[�W4�̃e�N�X�`���̊J��
	if (g_pTextureStage4 != NULL)
	{
		g_pTextureStage4->Release();
		g_pTextureStage4 = NULL;
	}

}

//=========================================================================================================================
// �X�e�[�W�Z���N�g�̍X�V����
//=========================================================================================================================
void UpdateStageSelect(void)
{
	VERTEX_2D *pVtx;

	g_fTexStageSelect_U += MOVE_STAGESELECT_BG_V;


	// �ϐ��錾
	int nFade = GetFade();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			switch (g_StageSelect)
			{
			case STAGE_ONE:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_TWO:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_THREE:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_FOUR:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			}
		}


		if (GetKeyboardTrigger(DIK_D) == true)
		{

			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_TWO)
			{
			g_StageSelect += 1;
				if (g_StageSelect > STAGE_TWO)
				{
					g_StageSelect = STAGE_ONE;
				}
			}
			else if (g_StageSelect == STAGE_THREE || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect += 1;
				if (g_StageSelect > STAGE_FOUR)
				{
					g_StageSelect = STAGE_THREE;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_A) == true)
		{

			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_TWO)
			{
				g_StageSelect -= 1;
				if (g_StageSelect < STAGE_ONE)
				{
					g_StageSelect = STAGE_TWO;
				}
			}
			else if (g_StageSelect == STAGE_THREE || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect -= 1;
				if (g_StageSelect < STAGE_THREE)
				{
					g_StageSelect = STAGE_FOUR;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_S) == true)
		{
			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_THREE)
			{
				g_StageSelect += 2;
				if (g_StageSelect > STAGE_THREE)
				{
					g_StageSelect = STAGE_ONE;
				}
			}
			else if (g_StageSelect == STAGE_TWO || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect += 2;
				if (g_StageSelect > STAGE_FOUR)
				{
					g_StageSelect = STAGE_TWO;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{
			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_THREE)
			{
				g_StageSelect -= 2;
				if (g_StageSelect < STAGE_ONE)
				{
					g_StageSelect = STAGE_THREE;
				}
			}
			else if (g_StageSelect == STAGE_TWO || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect -= 2;
				if (g_StageSelect < STAGE_TWO)
				{
					g_StageSelect = STAGE_FOUR;
				}
			}
		}

		// �X�e�[�W�Z���N�g�w�i
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexStageSelect_U, 1.0f + g_fTexStageSelect_V);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexStageSelect_U, 0.0f + g_fTexStageSelect_V);
		pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexStageSelect_U, 1.0f + g_fTexStageSelect_V);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexStageSelect_U, 0.0f + g_fTexStageSelect_V);

		for (int nSelectStage = 0; nSelectStage < MAX_BG_STAGESELECT; nSelectStage++)
		{
			if (g_StageSelect == 0)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 2:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 1)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 2)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 3)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// ���_�J���[�̐ݒ�
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				}
			}

			pVtx += VTX_NUM;
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStageSelect->Unlock();


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (nFade == FADE_IN)
			{
				SetFade(FADE_NONE, MODE_STAGESELECT);
			}
			else if (nFade == FADE_NONE)
			{
				PlaySound(SOUND_LABEL_SE_ENTER);

				SetFade(FADE_OUT, MODE_GAME);
			}

		}
	}
}

//=========================================================================================================================
// �X�e�[�W�Z���N�g�̕`�揈��
//=========================================================================================================================
void DrawStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStageSelect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_BG_STAGESELECT; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureStageSelectBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureStage1);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureStage2);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureStage3);
			break;
		case 4:
			pDevice->SetTexture(0, g_pTextureStage4);
			break;
		default:
			break;
		}

		// �X�e�[�W�Z���N�g�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * VTX_NUM,						// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}

int GetStageNumber(void)
{
	return g_StageSelect;
}