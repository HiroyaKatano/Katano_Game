//=============================================================================
//
//	�c�@ [life.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture[] = {};
int CLife::m_nLife;

//=============================================================================
// �R���X�g���N
//=============================================================================
CLife::CLife(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

	m_nLife = 3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CLife::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player001.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui000.png", &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`����j��
//=============================================================================
void CLife::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
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
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CLife;

		if (pLife != NULL)
		{
			pLife->Init(pos, scale);
		}
	}
	return pLife;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos + (D3DXVECTOR3(scale.x, 0.f, 0.f) * (float)nCnt), scale / (nCnt * 0.5f + 1));
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	m_pNumber = CNumber::Create(pos + D3DXVECTOR3(scale.x * 1.75f, 0.0f, 0.0f),
							D3DXVECTOR3(scale.x / 2, scale.y, scale.z), 2);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	m_pNumber->Uninit();
	delete m_pNumber;

	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CLife::Update(void)
{
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CLife::Draw(void)
{
	m_pNumber->Draw();
}

//=============================================================================
// �c�@�Z�b�g����
//=============================================================================
void CLife::SetLife(int nLife)
{
	m_nLife = nLife;

	m_pNumber->SetNumber(nLife - 1);
}

//=============================================================================
// �c�@���Z����
//=============================================================================
void CLife::AddLife(int nValue)
{
	m_nLife += nValue;

	if (m_nLife < 0)
	{
		m_nLife = 0;
		SetLife(m_nLife);
	}
	else if (m_nLife >= 10)
	{
		m_nLife = 9;
		SetLife(m_nLife);
	}
	else if (m_nLife >= 0 && m_nLife < 10)
	{
		SetLife(m_nLife);
	}
}