//=============================================================================
//
// �V�[�� [scene.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScene *CScene::m_apScene[MAX_PRIORITY_NUM][MAX_POLY2D] = {};
int CScene::m_nNumAll = 0;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene::CScene(int nCntPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
	{
		if (m_apScene[nCntPriority][nCntScene] == NULL)
		{
			m_apScene[nCntPriority][nCntScene] = this;
			// �����̗D�揇�ʂ�ݒ�
			m_nPriority = nCntPriority;
			// �����̔ԍ���ݒ�
			m_nID = nCntScene;
			// �|���S���̑����̉��Z
			m_nNumAll++;
			break;
		}
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene::~CScene()
{


}

//*****************************************************************************
// �S�Ă̔j��
//*****************************************************************************
void CScene::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
			}
		}
	}
}

//*****************************************************************************
// �S�Ă̍X�V
//*****************************************************************************
void CScene::UpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//*****************************************************************************
// �S�Ă̕`��
//*****************************************************************************
void CScene::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//*****************************************************************************
// �j������
//*****************************************************************************
void CScene::Release()
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nCntPriority = m_nPriority;
		int nID = m_nID;
		delete m_apScene[nCntPriority][nID];
		m_apScene[nCntPriority][nID] = NULL;
		m_nNumAll--;
	}
}


//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
D3DXVECTOR3 CScene::SetPos(void)
{
	return D3DXVECTOR3(SCREEN_WIDTH * (float)(m_nNumAll * 2 - 1) / (MAX_POLY2D * 2), SCREEN_HEIGHT / 2, 0.0f);
}
