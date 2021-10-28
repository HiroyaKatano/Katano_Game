//=============================================================================
//
// �����_�����O [renderer.cpp]
// Author : Hiroya Katano
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include <stdio.h>
#include "manager.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CRenderer::CRenderer()
{


}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CRenderer::~CRenderer()
{


}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h(���l�̍���)�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// �\�[�X(�`�挳)�̍������@�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �k���� ���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �g�厞 ���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U�l �J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V�l �J��Ԃ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����(�����l��D3DTA_TEXTURE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// 2�Ԗڂ̃A���t�@����(�����l��D3DTA_CURRENT)

#ifdef _DEBUG
																			// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 27, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CRenderer::Uninit()
{

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CRenderer::Update()
{
	CScene::UpdateAll();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CRenderer::Draw()
{
	//CFade *pFade = CManager::GetFade();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();

		//pFade->Draw();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �e��f�[�^�\��
			DrawData();
		}
#endif
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS = GetFPS();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

#ifdef _DEBUG
//=============================================================================
// �e��f�[�^�\��
//=============================================================================
void CRenderer::DrawData(void)
{
	int nCountFPS = GetFPS();

	CPlayer *pPlayer = CGame::GetPlayer();
	int SelectBullet = *pPlayer->GetPlayerBullet();

	int GameCntTime = CGame::GameCntTime();

	CEnemy *pEnemy = CGame::GetEnemy();
	float EnePosDistance = pEnemy->GetDistance();
	float AngleLissajous = pEnemy->GetAngleL();

	float fAlpha = CGame::GetAlpha();
	float fBeta = CGame::GetBeta();
	float fDelta = CGame::GetDelta();
	float fRadiusA = CGame::GetRadiusA();
	float fRadiusB = CGame::GetRadiusB();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024];

	int nNum = sprintf(&aStr[0], "FPS:%d\n", nCountFPS);
	nNum += sprintf(&aStr[nNum], "[�ʏ�e�ւ̐ؑ� : �L�[�{�[�h�̂P ]\n");
	nNum += sprintf(&aStr[nNum], "[�ǔ��e�ւ̐ؑ� : �L�[�{�[�h�̂Q ]\n");
	if (SelectBullet == CBullet::USEBULLET_NONE)
	{
		nNum += sprintf(&aStr[nNum], "[�v���C���[�̒e�̎�� : �ʏ�e ]\n");
	}
	else if (SelectBullet == CBullet::USEBULLET_TRACKING)
	{
		nNum += sprintf(&aStr[nNum], "[�v���C���[�̒e�̎�� : �ǔ��e ]\n");
	}
	nNum += sprintf(&aStr[nNum], "[���̃��T�[�W���Ȑ��̈ړ��G�o���܂Ŏc�� : %ds ]\n", NEXT_LISSAJOUS /60 - GameCntTime/60);
	nNum += sprintf(&aStr[nNum], "[EnemyPos �` pos�̋��� : %.2fs ]\n", EnePosDistance);
	nNum += sprintf(&aStr[nNum], "[EnemyPos�����_�Ƃ����Ƃ���pos�̊p�x : %.2f ]\n", AngleLissajous);
	nNum += sprintf(&aStr[nNum], "\n<TAB���������ۂɐ�������郊�T�[�W���Ȑ��̊e��f�[�^>\n");
	nNum += sprintf(&aStr[nNum], "[ Alpha �̒l : %.1f ]\n", fAlpha);
	nNum += sprintf(&aStr[nNum], "[ Beta  �̒l : %.1f ]\n", fBeta);
	nNum += sprintf(&aStr[nNum], "[ Delta �̒l : %.1f ]\n", fDelta);
	nNum += sprintf(&aStr[nNum], "[RadiusA�̒l : %.1f ]\n", fRadiusA);
	nNum += sprintf(&aStr[nNum], "[RadiusB�̒l : %.1f ]\n", fRadiusB);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
