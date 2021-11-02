//=============================================================================
//
// �}�l�[�W���[ [manager.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h" 
#include "renderer.h"
#include "scene2D.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "bulletPower.h"
#include "titleLogo.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;

CLife *CManager::m_pLife = NULL;

CTitle *CManager::m_pTitle = NULL;					// �^�C�g�����[�h
CGame *CManager::m_pGame = NULL;					// �Q�[�����[�h
CResult *CManager::m_pResult = NULL;					// �Q�[�����[�h

CManager::MODE CManager::m_mode = MODE_TITLE;		// ���݂̃Q�[�����[�h
CFade *CManager::m_pFade = NULL;
CSound *CManager::m_pSound = NULL;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{


}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{


}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// �^�C�g�����S�e�N�X�`���̃��[�h
	CTitleLogo::Load();

	// �w�i�e�N�X�`���̃��[�h
	CBg::Load();

	// �o���b�g�e�N�X�`���̃��[�h
	CBullet::Load();

	// �G�t�F�N�g�e�N�X�`���̃��[�h
	CEffect::Load();

	// �����e�N�X�`���̃��[�h
	CExplosion::Load();

	// �G�e�N�X�`���̃��[�h
	CEnemy::Load();

	// �v���C���[�e�N�X�`���̃��[�h
	CPlayer::Load();

	// �i���o�[�e�N�X�`���̃��[�h
	CNumber::Load();

	// �c�@�e�N�X�`���̃��[�h
	CLife::Load();

	// �e�̃Q�[�W�e�N�X�`���̃��[�h
	CBulletPower::Load();

	// �T�E���h�̏���������
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	// �t�F�[�h�̏���������
	//m_pFade = new CFade;
	//if (m_pFade != NULL)
	//{
	//	m_pFade->Init(m_mode);
	//}

	SetMode(m_mode);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CManager::Uninit()
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	// �e�̃Q�[�W�e�N�X�`���̃��[�h
	CBulletPower::Unload();

	// �c�@�e�N�X�`���̃��[�h
	CLife::Unload();

	// �i���o�[�e�N�X�`���̃��[�h
	CNumber::Unload();

	// �v���C���[�e�N�X�`���̃A�����[�h
	CPlayer::Unload();

	// �o���b�g�e�N�X�`���̃A�����[�h
	CBullet::Unload();

	// �G�l�~�[�e�N�X�`���̃A�����[�h
	CEnemy::Unload();

	// �����e�N�X�`���̃A�����[�h
	CExplosion::Unload();

	// �w�i�e�N�X�`���̃A�����[�h
	CBg::Unload();
	
	// �^�C�g�����S�e�N�X�`���̃A�����[�h
	CTitleLogo::Unload();

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �T�E���h�̏I������
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// �t�F�[�h�̏I������
	/*if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}*/
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CManager::Update()
{
	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	if (m_pInputKeyboard->GetPress(DIK_P) != true)
	{
		// �����_���[�̍X�V����
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Update();
		}

		// �t�F�[�h�̍X�V����
		//if (m_pFade != NULL)
		//{
		//	m_pFade->Update();
		//}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �����_�����O�N���X�̎擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h�N���X�̎擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// ���[�h�̔j��
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
		}

		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
		}
		break;

	default:
		break;
	}

	// �I�u�W�F�N�g�j��
	CScene::ReleaseAll();

	// ���[�h�̐ݒ�
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle->Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame->Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult->Create();
		}
		break;

	default:
		break;
	}
}