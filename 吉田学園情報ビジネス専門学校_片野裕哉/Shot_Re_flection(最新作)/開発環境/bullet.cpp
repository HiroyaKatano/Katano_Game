//=============================================================================
//
// 弾 [bullet.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "bullet.h" 
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"
#include "player.h"
#include "bulletPower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;			// テクスチャ
int CBullet::m_nAbsorbedBulletCnt;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRockOn = false;
	m_bAbsorbOn = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBullet::~CBullet()
{


}

//*****************************************************************************
// ポリゴンの初期化処理
//*****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, CBullet::BULLETTYPE bulletType, USEBULLET useBullet)
{
	// 寿命の設定
	m_life = 150;

	// 大きさを設定
	m_scale = scale;

	// 移動値を設定
	m_move = move;

	// 弾の使用者を設定
	m_bulletType = bulletType;

	// 弾の種類を設定
	m_useBullet = useBullet;

	// CScene2Dを呼び出し
	CScene2D::Init(pos, scale);

	// オブジェクトの種類の設定
	SetObjType(OBJTYPE_BULLET);

	return S_OK;
}

//*****************************************************************************
// ポリゴンの終了処理
//*****************************************************************************
void CBullet::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
// ポリゴンの更新処理
//*****************************************************************************
void CBullet::Update()
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	if (m_useBullet == USEBULLET_TRACKING)
	{
		BulletTracking();
	}

	if (m_bulletType == BULLETTYPE_PLAYER)
	{
		// エフェクトを生成
		CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(0.4f, 0.4f, 1.f, 1.f), 20);
	}
	
	if (m_bulletType == BULLETTYPE_ENEMY)
	{
		if (m_move2.y < 5.0f && m_EneBulCnt < 60 && m_useBullet == USEBULLET_TRACKING)
		{
			m_move.y += 0.3f;

			m_move2 = m_move;
		}
		if (m_useBullet == USEBULLET_TRACKING)
		{
			// エフェクトを生成
			CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(1.f, 0.4f, 0.4f, 1.f), 20);
		}
		else 
		{
			// エフェクトを生成
			CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(0.2f, 0.5f, 0.2f, 1.f), 25);
		}
	}

	//移動量を追加
	pos += m_move;

	//位置の更新
	SetPosition(pos, m_scale);

	for (int nCntPrio = 0; nCntPrio < MAX_PRIORITY_NUM; nCntPrio++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			CScene *pScene;
			pScene = GetScene(nCntPrio, nCntScene);
			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				CScore *pScore;
				pScore = CGame::GetScore();

				int nPlayerState = CPlayer::GetPlayerState();
				CPlayer *pPlayer;
				pPlayer = CGame::GetPlayer();

				

				if (objType == OBJTYPE_ENEMY && m_bulletType == BULLETTYPE_PLAYER)
				{
					D3DXVECTOR3 posEnemy = pScene->GetPosition();
					D3DXVECTOR3 scaleEnemy = pScene->GetScale();

					m_EneLife = CGame::GetEnemy()->GetLife();

					if (pos.y - (m_scale.y / 2.0f) < posEnemy.y + (scaleEnemy.y / 2) &&
						pos.y + (m_scale.y / 2.0f) > posEnemy.y - (scaleEnemy.y / 2) &&
						pos.x - (m_scale.x / 2.0f) < posEnemy.x + (scaleEnemy.x / 2) &&
						pos.x + (m_scale.x / 2.0f) > posEnemy.x - (scaleEnemy.x / 2))
					{
						if (m_EneLife > 0)
						{
							CGame::GetEnemy()->AddLife(-1);
						}
						else
						{
							//敵を消す
							pScene->Uninit();

							//爆発の生成
							CExplosion::Create(posEnemy, scaleEnemy);

							// スコア加算処理
							pScore->AddScore(100);
						}

						//弾を消す
						Uninit();

						return;
					}
				}

				//if (objType == OBJTYPE_BOSS && m_bulletType == BULLETTYPE_PLAYER && BossState == CBoss::BOSSSTATE_NONE)
				//{
				//	D3DXVECTOR3 posBoss = pScene->GetPosition();
				//	D3DXVECTOR3 scaleBoss = pScene->GetScale();
				//	int BossCnt = m_pBoss->GetBossCnt();
				//	

				//	if (pos.y - (m_scale.y / 2.0f) < posBoss.y + (scaleBoss.y / 2) &&
				//		pos.y + (m_scale.y / 2.0f) > posBoss.y - (scaleBoss.y / 2) &&
				//		pos.x - (m_scale.x / 2.0f) < posBoss.x + (scaleBoss.x / 2) &&
				//		pos.x + (m_scale.x / 2.0f) > posBoss.x - (scaleBoss.x / 2))
				//	{
				//		//敵を消す
				//		pScene->Uninit();

				//		//爆発の生成
				//		CExplosion::Create(posBoss, scaleBoss);

				//		// スコア加算処理
				//		pScore->AddScore(100);

				//		//弾を消す
				//		Uninit();

				//		return;
				//	}
				//}

				if (objType == OBJTYPE_PLAYER && m_bulletType == BULLETTYPE_ENEMY && nPlayerState == CPlayer::PLAYERSTATE_NONE)
				{
					D3DXVECTOR3 posPlayer = pScene->GetPosition();
					D3DXVECTOR3 scalePlayer = pScene->GetScale();
					CLife *pLife = CGame::GetLife();

					float VectorX = posPlayer.x - pos.x;
					float VectorY = posPlayer.y - pos.y;
					float Distance = sqrtf((VectorX * VectorX) + (VectorY * VectorY));

					if (Distance < ABSORBDISTANCE)
					{	
						m_bAbsorbOn = true;
					}

					if (m_bAbsorbOn == true)
					{
						float angle = atan2f(VectorX, VectorY);

						if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
						if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

						//ホーミング計算
						float moveX = sinf(angle)*30.0f;
						float moveY = cosf(angle)*30.0f;

						//移動値を換算
						m_move.x = moveX;
						m_move.y = moveY;
					}

					if (pos.y - m_scale.y / 2.0f < posPlayer.y + scalePlayer.y / 5 &&
						pos.y + m_scale.y / 2.0f > posPlayer.y - scalePlayer.y / 5 &&
						pos.x - m_scale.x / 2.0f < posPlayer.x + scalePlayer.x / 5 &&
						pos.x + m_scale.x / 2.0f > posPlayer.x - scalePlayer.x / 5)
					{
						//爆発の生成
						//CExplosion::Create(posPlayer, scalePlayer);

						////プレイヤーの残機減少
						//pLife->AddLife(-1);

						//pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

						// スコア加算処理
						//pScore->AddScore(-100);

						if (m_nAbsorbedBulletCnt <= 50)
						{
							m_nAbsorbedBulletCnt += 2;
							CGame::GetBulletPower()->AddBulletPower(2);

							if (m_nAbsorbedBulletCnt >= 40 && m_nAbsorbedBulletCnt < 50)
							{
								pScore->AddScore(500);
							}
							else if (m_nAbsorbedBulletCnt == 50)
							{
								pScore->AddScore(5000);
							}
						}
						else if (m_nAbsorbedBulletCnt > 50)
						{
							//プレイヤーの残機減少
							pLife->AddLife(-1);
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
							m_nAbsorbedBulletCnt = 0;
							CGame::GetBulletPower()->SetBulletPower(0);

							// スコア加算処理
							pScore->AddScore(-5000);
							CExplosion::Create(posPlayer, scalePlayer*3);
						}

						//弾を消す
						Uninit();

						return;
					}

				}
			}
		}
	}

	//画面外処理
	if (pos.y + m_scale.y / 2.0f < 0.0f ||
		pos.y - m_scale.y / 2.0f > SCREEN_HEIGHT ||
		pos.x + m_scale.x / 2.0f < 0.0f ||
		pos.x - m_scale.x / 2.0f > SCREEN_WIDTH)
	{
		//弾を消す
		Uninit();
	}
	else if (m_life == 0)
	{
		//爆発の生成
		CExplosion::Create(pos, m_scale);

		//弾を消す
		Uninit();
	}
	else if (m_life > 0)
	{
		//寿命
		m_life--;

		m_EneBulCnt++;
	}
}

//*****************************************************************************
// ポリゴンの描画処理
//*****************************************************************************
void CBullet::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLETTYPE bulletType, USEBULLET useBullet)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	if (pBullet != NULL)
	{
		pBullet->Init(pos, scale, move, bulletType, useBullet);
	}
	pBullet->BindTexture(m_pTexture);

	return pBullet;
}

//*****************************************************************************
// テクスチャ読込処理
//*****************************************************************************
void CBullet::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture);
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CBullet::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// 弾の追尾処理
//*****************************************************************************
void CBullet::BulletTracking(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPosition();

	for (int nCntPrio = 0; nCntPrio < MAX_PRIORITY_NUM; nCntPrio++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			CScene *pScene;
			pScene = GetScene(nCntPrio, nCntScene);

			if (pScene != NULL)
			{
				//種類判定呼び出し
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType != NULL)
				{
					//プレイヤーの弾だった場合
					if (m_bulletType == BULLETTYPE_PLAYER)
					{
						//種類が敵だった場合
						if (objType == OBJTYPE_ENEMY)
						{
							//位置の取得
							D3DXVECTOR3 posEnemy = pScene->GetPosition();

							//角度計算
							float VectorX = posEnemy.x - pos.x;
							float VectorY = posEnemy.y - pos.y;
							float angle = atan2f(VectorX, VectorY);

							if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
							if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

							//角度が一定値を超えるまで追跡
							if ((angle < -D3DX_PI / 1.4f&&angle > -D3DX_PI) ||
								(angle > D3DX_PI / 1.4f&&angle < D3DX_PI))
							{
								//ホーミング計算
								float moveX = sinf(angle)*20.0f;
								float moveY = cosf(angle)*30.0f;

								//移動値を換算
								m_move.x = moveX;
								m_move.y = moveY;
							}
						}
					}
					else if (m_bulletType == BULLETTYPE_ENEMY)
					{
						//種類が敵だった場合
						if (objType == OBJTYPE_PLAYER &&/* m_EneBulCnt >= 30 && */m_EneBulCnt < 120 && m_move2.y >= 5.0f && m_bRockOn == false)
						{
							//位置の取得
							D3DXVECTOR3 posPlayer = pScene->GetPosition();

							//角度計算
							float VectorX = posPlayer.x - pos.x;
							float VectorY = posPlayer.y - pos.y;
							float angle = atan2f(VectorX, VectorY);

							if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
							if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

							//ホーミング計算
							float moveX = sinf(angle)*20.0f;
							float moveY = cosf(angle)*20.0f;

							//移動値を換算
							m_move.x = moveX;
							m_move.y = moveY;

							m_bRockOn = true;
						}
					}
				}
			}
		}
	}
}

//*****************************************************************************
// 弾の拡散処理
//*****************************************************************************
void CBullet::BulletSpread(void)
{
	//位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	
}
