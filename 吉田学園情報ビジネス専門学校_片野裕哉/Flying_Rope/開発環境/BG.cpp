//=========================================================================================================================
//
// �w�i�̃e�N�X�`�� [BG.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "BG.h"
#include "input.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define FIRST_BG_POS_LEFT_X (SCREEN_WIDTH_L)
#define FIRST_BG_POS_RIGHT_X (2560 * 2)
#define BG_POS_TOP_Y (SCREEN_HEIGHT_T)
#define BG_POS_UNDER_Y (SCREEN_HEIGHT_U)
#define BG_COLOR_R (255)														// �w�i�F(��)
#define BG_COLOR_G (255)														// �w�i�F(��)
#define BG_COLOR_B (255)														// �w�i�F(��)
#define BG_COLOR_A (255)														// �w�i�F(�����x)
#define MAX_BG_TYPE (1)
#define MOVE_FIRST_BG_U (0.0001f)

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureFirstBG = NULL;		// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureSecondBG = NULL;		// �e�N�X�`��
float g_fTexU = 0;							
float g_fTexV = 0;

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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg", &g_pTextureFirstBG);
	
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_BG_TYPE,
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
		switch (nCnt)
		{
		case 0:
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(FIRST_BG_POS_LEFT_X, BG_POS_UNDER_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(FIRST_BG_POS_LEFT_X, BG_POS_TOP_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(FIRST_BG_POS_RIGHT_X, BG_POS_UNDER_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(FIRST_BG_POS_RIGHT_X, BG_POS_TOP_Y, Z_AXIS_ZERO);

			// ���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(MOVE_FIRST_BG_U, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(MOVE_FIRST_BG_U, 0.0f);
			break;
		default:
			break;
		}

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

		
		pVtx += VTX_NUM;
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
}

//=========================================================================================================================
// �w�i�̍X�V����
//=========================================================================================================================
void UpdateBG(void)
{
	VERTEX_2D *pVtx;

	g_fTexU += MOVE_FIRST_BG_U;


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexU, 1.0f + g_fTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexU, 0.0f + g_fTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexU, 1.0f + g_fTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexU, 0.0f + g_fTexV);

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
		default:
			break;
		}

		// �w�i�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * VTX_NUM,						// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}
