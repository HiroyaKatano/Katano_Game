//=============================================================================
//
//	�w�i [bg.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[] = {};

//=============================================================================
// �R���X�g���N
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
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
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;

		if (pBg != NULL)
		{
			pBg->Init(pos, scale);
		}
	}
	return pBg;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		m_fPosTexU[nCnt] = 0.0f;
		m_fPosTexV[nCnt] = 0.0f;
	}

	// �w�i�X�s�[�h
	m_fSpeed[0] = SCROL_SPPED01;
	m_fSpeed[1] = SCROL_SPPED02;
	m_fSpeed[2] = SCROL_SPPED03;

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CBg::Update(void)
{
	// �L�[�{�[�h�֌W
	CInputKeyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (plnputKeyboard->GetPress(DIK_D) == true)
		{
			m_fPosTexU[nCnt] += m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_A) == true)
		{
			m_fPosTexU[nCnt] -= m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_W) == true)
		{
			m_fPosTexV[nCnt] -= m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_S) == true)
		{
			m_fPosTexV[nCnt] += m_fSpeed[nCnt] * 0.5f;
		}

		m_fPosTexV[nCnt] -= m_fSpeed[nCnt];

		m_apScene2D[nCnt]->SetBgTex(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CBg::Draw(void)
{

}