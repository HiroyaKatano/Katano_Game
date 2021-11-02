//=============================================================================
//
// 2D�|���S�� [scene2D.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h" 
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "bulletPower.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{


}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene2D::~CScene2D()
{


}

//*****************************************************************************
// �|���S���̏���������
//*****************************************************************************
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2.0f, m_Polygon.pos.y + m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2.0f, m_Polygon.pos.y - m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x + m_Polygon.scale.x / 2.0f, m_Polygon.pos.y + m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x + m_Polygon.scale.x / 2.0f, m_Polygon.pos.y - m_Polygon.scale.y / 2.0f, 0.0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// �|���S���̏I������
//*****************************************************************************
void CScene2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//*****************************************************************************
// �|���S���̍X�V����
//*****************************************************************************
void CScene2D::Update()
{
	
}

//*****************************************************************************
// �|���S���̕`�揈��
//*****************************************************************************
void CScene2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�
}

//*****************************************************************************
// ��������
//*****************************************************************************
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, scale);
	}

	return pScene2D;
}

//*****************************************************************************
// �ʒu�ݒ菈��
//*****************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ʒu�̐ݒ�
	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	m_Polygon.fLength = sqrtf(scale.x / 2 * scale.x / 2 + scale.y / 2 * scale.y / 2);

	m_Polygon.fAngle = atan2f(scale.x, scale.y);

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�v���C���[�̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x + sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y - cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x + sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y + cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y - cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y + cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//*****************************************************************************
// �ʒu�̎擾
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_Polygon.pos;
}

//*****************************************************************************
// �e�N�X�`���̊��蓖�ď���
//*****************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}


//=============================================================================
// �����e�N�X�`���ݒ�
//=============================================================================
void CScene2D::SetExplosionTex(int nCnt)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(nCnt / 8.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(nCnt / 8.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / 8.0f + (nCnt / 8.0f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 8.0f + (nCnt / 8.0f), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �w�i�e�N�X�`���ݒ�
//=============================================================================
void CScene2D::SetBgTex(float fTexU, float fTexV)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(fTexU, 1.0f + fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU, 0.0f + fTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + fTexU, 1.0f + fTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fTexU, 0.0f + fTexV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̓����x(effect)
//=============================================================================
void CScene2D::SetEffect(D3DXCOLOR col, float nData)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, nData);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̓����x(�v���C���[)
//=============================================================================
void CScene2D::SetPlayerCol(float nData)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// �Q�[�W��������
//*****************************************************************************
void CScene2D::SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBulletMax)
{
	//�ʒu�̐ݒ�
	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	int nBulletNum = CGame::GetBulletPower()->GetBulletPower();

	//�ϐ��錾
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nBulletMax == 50)
	{
		//�v���C���[�̈ʒu��ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * nBulletNum / nBulletMax,
			m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * nBulletNum / nBulletMax,
			m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}
	else if (nBulletMax == 0)
	{
		//�v���C���[�̈ʒu��ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}
	else
	{
		//�v���C���[�̈ʒu��ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * (nBulletNum % 40) / nBulletMax,
			m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * (nBulletNum % 40) / nBulletMax,
			m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}