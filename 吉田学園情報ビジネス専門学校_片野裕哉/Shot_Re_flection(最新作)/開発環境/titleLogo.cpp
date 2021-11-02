//=============================================================================
//
//	�w�i [bg.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "titleLogo.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_apTexture[] = {};

//=============================================================================
// �R���X�g���N
//=============================================================================
CTitleLogo::CTitleLogo(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title002.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title003.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �w�i�̐���
//=============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTitleLogo *pTitleLogo = NULL;

	if (pTitleLogo == NULL)
	{
		pTitleLogo = new CTitleLogo;

		if (pTitleLogo != NULL)
		{
			pTitleLogo->Init(pos, scale);
		}
	}
	return pTitleLogo;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		m_fPosTexU[nCnt] = 0.0f;
		m_fPosTexV[nCnt] = 0.0f;
		m_aPos[nCnt] = pos;
		if (nCnt != 2)
		{
			m_aScale[nCnt] = scale;
		}
		else if (nCnt == 2)
		{
			m_aScale[nCnt] = scale - D3DXVECTOR3(0.f, scale.y / 2, 0.f);
		}
	}


	// �w�i�X�s�[�h
	m_fSpeed[0] = SCROL_SPPED01;
	m_fSpeed[1] = SCROL_SPPED02;
	m_fSpeed[2] = SCROL_SPPED03;

	m_bFlashSign = false;

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTitleLogo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTitleLogo::Update(void)
{
	// �L�[�{�[�h�֌W
	CInputKeyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		if (nCnt != 2)
		{
			if (m_aPos[nCnt].y < SCREEN_HEIGHT / 4)
			{
				m_aPos[nCnt].y += 2.f;
			}
		}
		else if (nCnt == 2)
		{
			if (m_aPos[nCnt].y < SCREEN_HEIGHT * 4/5)
			{
				m_aPos[nCnt].y += 5.f;
			}
		}
		m_apScene2D[nCnt]->SetPosition(m_aPos[nCnt], m_aScale[nCnt]);
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTitleLogo::Draw(void)
{

}