//=============================================================================
//
//	�X�R�A [score.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CScore::m_nScore;

//=============================================================================
// �R���X�g���N
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// �w�i�̐���
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		pScore = new CScore;

		if (pScore != NULL)
		{
			pScore->Init(pos, scale);
		}
	}
	return pScore;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x, pos.y, pos.z)
							+ D3DXVECTOR3(scale.x * nCnt, 0.0f, 0.0f) , scale, 0);
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// �X�R�A�Z�b�g����
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[0]->SetNumber((m_nScore / 10000000) % 10);
		m_apNumber[1]->SetNumber((m_nScore / 1000000) % 10);
		m_apNumber[2]->SetNumber((m_nScore / 100000) % 10);
		m_apNumber[3]->SetNumber((m_nScore / 10000) % 10);
		m_apNumber[4]->SetNumber((m_nScore / 1000) % 10);
		m_apNumber[5]->SetNumber((m_nScore / 100) % 10);
		m_apNumber[6]->SetNumber((m_nScore / 10) % 10);
		m_apNumber[7]->SetNumber((m_nScore) % 10);
	}
}

//=============================================================================
// �X�R�A���Z����
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	if (m_nScore >= 100000000)
	{
		m_nScore = 99999999;
		SetScore(m_nScore);
	}
	else if (m_nScore < 0)
	{
		m_nScore = 0;
		SetScore(m_nScore);
	}
	else if (m_nScore >= 0 && m_nScore < 100000000)
	{
		SetScore(m_nScore);
	}
}