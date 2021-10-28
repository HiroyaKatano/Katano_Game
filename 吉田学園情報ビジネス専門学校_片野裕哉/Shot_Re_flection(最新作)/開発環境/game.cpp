//=============================================================================
//
// ゲーム [game.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "game.h"
#include "bg.h"
#include "life.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "data.h"
#include "bullet.h"
#include "bulletPower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CBg *CGame::m_pBg = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CScore *CGame::m_pScore = NULL;
CLife *CGame::m_pLife = NULL;
CData *CGame::m_pData = NULL;
CBulletPower *CGame::m_pBulletPower = NULL;

int CGame::m_nCntTime = 0;
int CGame::m_nEneCnt = 0;

float CGame::m_fAlpha = 1.0f;
float CGame::m_fBeta = 1.0f;
float CGame::m_fDelta = 0.0f;
float CGame::m_fRadiusA = 200.0f;
float CGame::m_fRadiusB = 200.0f;

bool CGame::m_bLissajousOn = false;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{


}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CGame *CGame::Create()
{
	CGame *pGame = new CGame;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;

	// 初期化処理
	pGame->Init(pos, scale);

	return pGame;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// 背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// 残機の生成
	m_pLife = CLife::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	// 弾数の生成
	m_pBulletPower = CBulletPower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(800.0f, 40.0f, 0.0f));

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.26f, SCREEN_HEIGHT / 16, 0.0f), D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 6 / 7, 0.0f), D3DXVECTOR3(75.f, 75.f, 0.0f));

	// 敵の生成
	//for (int nCnt = 0; nCnt < 1; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), 0,
	//		CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_NONE);
	//}
	//for (int nCnt = 0; nCnt < 1; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3(0.f, 0.f, 0.0f),
	//		0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_LISSAJOUS);
	//	//m_pEnemy->SetLissajous(12.0f, 8.0f, 0.0f, 200.0f, 200.0f);
	//	m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
	//	m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
	//	m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
	//}
	//for (int nCnt = 0; nCnt < 2; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (50.f * (nCnt - 0.5f)), 0.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3((nCnt-0.5f), 0.5f, 0.0f),
	//		0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_LISSAJOUS);
	//	switch (nCnt)
	//	{
	//	case 0:
	//		m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
	//		break;
	//	case 1:
	//		m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, -300.0f, 150.0f);
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//for (int nCnt = 0; nCnt < 3; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (50.f * (nCnt - 1)), 200.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3(1.f - (1.f*nCnt), 0.5f, 0.0f),
	//		0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_CIRCLE);
	//}
	//for (int nCnt = 0; nCnt < 5; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (50.f * (nCnt - 2)), 100.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), 1,
	//		CEnemy::ENEMYTYPE_ONE, CEnemy::ENEMYMOVETYPE_NONE);
	//}
	//for (int nCnt = 0; nCnt < 7; nCnt++)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (50.f * (nCnt - 3)), 50.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), 2, 
	//		CEnemy::ENEMYTYPE_TWO, CEnemy::ENEMYMOVETYPE_NONE);
	//}

	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM001);
	m_nCntTime = 0;
	m_nEneCnt = 0;
	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	// キーボードの取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	int EnemyCnt = m_pEnemy->GetEnemyCnt();
	int PlayerCnt = m_pPlayer->GetPlayerCnt();

	int EneCnt2 = m_pEnemy->GetEneCnt2();

	int Score = m_pScore->GetScore();

	//if (pKeyboard->GetTrigger(DIK_0) == true)
	//{
	//	m_bLissajousOn = !m_bLissajousOn;
	//}

	int nRand = rand() % 785398/2;
	float fAngle = (float)nRand;

	if (m_nCntTime % 30 == 0)
	{
		for (int nCnt = 0; nCnt < ENE_X_MAX; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1920.f*nCnt, 0.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f),
				D3DXVECTOR3(cosf(fAngle) * 20.f*(-2 * nCnt + 1), sinf(fAngle) * 15.0f, 0.0f),
				2, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_CROSS);
		}
	}

	if (EneCnt2 < 1)
	{
		for (int nCnt = 0; nCnt < ENE_X_MAX; nCnt++)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (500.f * (nCnt - (0.5f * (ENE_X_MAX - 1)))), 0.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f),
				0, CEnemy::ENEMYTYPE_TWO, CEnemy::ENEMYMOVETYPE_NONE);
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (1000.f * (nCnt - (0.5f * (ENE_X_MAX - 1)))), 0.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f),
			//	0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_NONE);
		}
	}


	if (EnemyCnt < 50)
	{
		if (m_nCntTime % NEXT_LISSAJOUS == 0 || pKeyboard->GetTrigger(DIK_5) == true)
		{
			for (int nCnt = 0; nCnt < ENE_X_MAX; nCnt++)
			{
				//if (m_bLissajousOn == true)
				//{
					m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (50.f * (nCnt - (0.5f * (ENE_X_MAX - 1)))), 0.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3((-0.5f + ((ENE_X_MAX + nCnt) % 2)), 0.5f, 0.0f),
						0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_LISSAJOUS);
					if (nCnt % 2 == 0)
					{
						if (m_nEneCnt % 3 == 0)
						{
							m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(12.0f, 16.0f, 0.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 1)
						{
							m_pEnemy->SetLissajous(12.0f, 10.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(6.0f, 16.0f, 0.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 2)
						{
							m_pEnemy->SetLissajous(9.0f, 15.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(13.0f, 7.0f, 0.0f, 250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}

					}
					else if (nCnt % 2 == 1)
					{
						if (m_nEneCnt % 3 == 0)
						{
							m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(12.0f, 16.0f, 0.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 1)
						{
							m_pEnemy->SetLissajous(12.0f, 10.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(6.0f, 16.0f, 0.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 2)
						{
							m_pEnemy->SetLissajous(9.0f, 15.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(13.0f, 7.0f, 0.0f, -250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
					//}
				}
			}

			for (int nCnt = 0; nCnt < ENE_X_MAX; nCnt++)
			{
				//if (m_bLissajousOn == true)
				//{
					m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (200.f * (nCnt - (0.5f * (ENE_X_MAX - 1)))), -50.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3((-0.5f + ((ENE_X_MAX + nCnt) % 2)), 0.5f, 0.0f),
						1, CEnemy::ENEMYTYPE_ONE, CEnemy::ENEMYMOVETYPE_LISSAJOUS);
					if (nCnt % 2 == 0)
					{
						if (m_nEneCnt % 3 == 0)
						{
							m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(12.0f, 16.0f, 0.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 1)
						{
							m_pEnemy->SetLissajous(12.0f, 10.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(6.0f, 16.0f, 0.0f, 250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 2)
						{
							m_pEnemy->SetLissajous(9.0f, 15.0f, 4.0f, 300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(13.0f, 7.0f, 0.0f, 250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, 300.0f, 100.0f);
						}
					}
					else if (nCnt % 2 == 1)
					{
						if (m_nEneCnt % 3 == 0)
						{
							m_pEnemy->SetLissajous(8.0f, 12.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(12.0f, 16.0f, 0.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 1)
						{
							m_pEnemy->SetLissajous(12.0f, 10.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(6.0f, 16.0f, 0.0f, -250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
						else if (m_nEneCnt % 3 == 2)
						{
							m_pEnemy->SetLissajous(9.0f, 15.0f, 4.0f, -300.0f, 150.0f);
							m_pEnemy->SetSubLissajous(13.0f, 7.0f, 0.0f, -250.0f, 150.0f);
							m_pEnemy->SetSubLissajous(8.0f, 12.0f, 4.0f, -300.0f, 100.0f);
						}
					}
				//}
			}

			//m_nCntTime = 0;


			if (m_nEneCnt > 3)
			{
				m_nEneCnt = 0;
			}
			m_nEneCnt++;

		}
	}
	//else
	//{
	//	m_nCntTime = 119;
	//}

#ifdef _DEBUG
	if (pKeyboard->GetPress(DIK_T) == true)
	{
		m_fAlpha += 0.1f;
	}
	if (pKeyboard->GetPress(DIK_G) == true)
	{
		m_fAlpha -= 0.1f;
	}
	if (pKeyboard->GetPress(DIK_Y) == true)
	{
		m_fBeta += 0.1f;
	}
	if (pKeyboard->GetPress(DIK_H) == true)
	{
		m_fBeta -= 0.1f;
	}
	if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_fDelta += 0.1f;
	}
	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_fDelta -= 0.1f;
	}
	if (pKeyboard->GetPress(DIK_I) == true)
	{
		m_fRadiusA += 10.0f;
	}
	if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_fRadiusA -= 10.0f;
	}
	if (pKeyboard->GetPress(DIK_O) == true)
	{
		m_fRadiusB += 10.0f;
	}
	if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_fRadiusB -= 10.0f;
	}

	if (pKeyboard->GetTrigger(DIK_TAB) == true)
	{
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.f, 0.0f), D3DXVECTOR3(50.f, 50.f, 0.0f), D3DXVECTOR3(0.f, 0.f, 0.0f),
			0, CEnemy::ENEMYTYPE_ZERO, CEnemy::ENEMYMOVETYPE_LISSAJOUS);
		m_pEnemy->SetLissajous(m_fAlpha, m_fBeta, m_fDelta, m_fRadiusA, m_fRadiusB);
	}
#endif

	m_nCntTime++;

	if (pKeyboard->GetTrigger(DIK_RETURN) == true || PlayerCnt <= 0/* || Score >= 2000 *//*|| EnemyCnt <= 0 && BossCnt <= 0*/)
	{
		m_pData->SetScore(CScore::GetScore());
		m_pBullet->ResetAbsorbedCnt();
		//CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
		CManager::SetMode(CManager::MODE_RESULT);
	}

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
	
}

//=============================================================================
// プレイヤークラスの取得
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// バレットクラスの値
//=============================================================================
CBullet *CGame::GetBullet(void)
{
	return m_pBullet;
}

//=============================================================================
// 背景クラスの値
//=============================================================================
CBg *CGame::GetBg(void)
{
	return m_pBg;
}

//=============================================================================
// 敵クラスの取得
//=============================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// スコアクラスの取得
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}
