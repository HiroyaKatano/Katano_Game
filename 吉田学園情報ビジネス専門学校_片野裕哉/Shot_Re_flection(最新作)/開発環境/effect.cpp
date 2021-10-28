//=============================================================================
//
// �e [bullet.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "effect.h" 
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "enemy.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;			// �e�N�X�`��

//*****************************************************************************
// �e�N�X�`���Ǎ�����
//*****************************************************************************
HRESULT CEffect::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CEffect::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEffect::~CEffect()
{


}

//*****************************************************************************
// ��������
//*****************************************************************************
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col, int nLife)
{
	CEffect *pEffect = NULL;
	pEffect = new CEffect;
	if (pEffect != NULL)
	{
		pEffect->Init(pos, scale, col);
	}
	pEffect->BindTexture(m_pTexture);

	pEffect->m_nLife = nLife;

	return pEffect;
}

//*****************************************************************************
// �|���S���̏���������
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col)
{
	// �ړ��l��ݒ�
	m_col = col;

	// �傫����ݒ�
	m_scale = scale;

	// CScene2D���Ăяo��
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene2D::SetObjType(OBJTYPE_EFFECT);

	CScene2D::SetEffect(col, 1.f);

	return S_OK;
}

//*****************************************************************************
// �|���S���̏I������
//*****************************************************************************
void CEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
// �|���S���̍X�V����
//*****************************************************************************
void CEffect::Update()
{
	//�e�̃��C�t�����炷
	m_nLife--;

	//�G�t�F�N�g�����񂾂񓧖��ɂ���
	CScene2D::SetEffect(m_col, (float)m_nLife / 100);

	//�e�̃��C�t��0�ȉ��ɂȂ����Ƃ�
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//*****************************************************************************
// �|���S���̕`�揈��
//*****************************************************************************
void CEffect::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���Z����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//���Z�������O��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

