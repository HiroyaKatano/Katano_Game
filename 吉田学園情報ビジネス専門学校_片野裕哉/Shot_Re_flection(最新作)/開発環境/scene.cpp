//=============================================================================
//
// シーン [scene.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CScene *CScene::m_apScene[MAX_PRIORITY_NUM][MAX_POLY2D] = {};
int CScene::m_nNumAll = 0;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene::CScene(int nCntPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
	{
		if (m_apScene[nCntPriority][nCntScene] == NULL)
		{
			m_apScene[nCntPriority][nCntScene] = this;
			// 自分の優先順位を設定
			m_nPriority = nCntPriority;
			// 自分の番号を設定
			m_nID = nCntScene;
			// ポリゴンの総数の加算
			m_nNumAll++;
			break;
		}
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene::~CScene()
{


}

//*****************************************************************************
// 全ての破棄
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
// 全ての更新
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
// 全ての描画
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
// 破棄処理
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
// 位置の設定
//=============================================================================
D3DXVECTOR3 CScene::SetPos(void)
{
	return D3DXVECTOR3(SCREEN_WIDTH * (float)(m_nNumAll * 2 - 1) / (MAX_POLY2D * 2), SCREEN_HEIGHT / 2, 0.0f);
}
