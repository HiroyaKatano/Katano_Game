//=============================================================================
//
// 敵 [enemy.cpp]
// Author : Hiroya Katano
//
//=============================================================================
#include "enemy.h"
#include "bullet.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "explosion.h"
#include "sound.h"
#include "game.h"
#include "life.h"
#include "player.h"
#include "score.h"
#include "effect.h"
#include "bulletPower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[] = {};			// テクスチャ
int CEnemy::m_enemyCnt = 0;
int CEnemy::m_eneCnt2 = 0;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CEnemy::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy000.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy009.png", &m_apTexture[2]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < ENEMY_MAX_TEX; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int nTexNum, ENEMYTYPE enemyType, ENEMYMOVETYPE moveType)
{
	// 動的確保
	CEnemy* pEnemy = NULL;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->EnemyPos = pos;

		pEnemy->m_moveX = move.x;
		pEnemy->m_moveY = move.y;

		// テクスチャ生成
		pEnemy->BindTexture(m_apTexture[nTexNum]);

		pEnemy->m_enemyType = enemyType;
		
		pEnemy->m_enemyMoveType = moveType;

		pEnemy->m_SetLR = move.x;

		pEnemy->AddEnemy(1);

		if (moveType == ENEMYMOVETYPE_NONE)
		{
			pEnemy->AddEneCnt(1);
		}

		// 初期化の呼び出し
		pEnemy->Init(pos, scale);

	}

	// 値を返す
	return pEnemy;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_scale = scale;
	m_nCnt = 0;
	m_fAngle = 0.0f;
	m_SubCnt = 0;

	if (m_enemyType == ENEMYTYPE_ZERO)
	{
		m_nLife = 5;
	}
	else if (m_enemyType == ENEMYTYPE_ONE)
	{
		m_nLife = 10;
	}
	else if (m_enemyType == ENEMYTYPE_TWO)
	{
		m_nLife = 20;
	}

	CScene2D::Init(pos, scale);

	// オブジェクトの種類の設定
	SetObjType(OBJTYPE_ENEMY);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
	AddEnemy(-1);
	if (m_enemyMoveType == ENEMYMOVETYPE_NONE)
	{
		AddEneCnt(-1);
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy::Update(void)
{
	//キーボード情報の取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CSound *pSound = CManager::GetSound();

	// 位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//if (m_nCnt % 120 == 0)
	//{
	//	m_moveX *= -1;
	//}
	//if (EnemyPos.x > SCREEN_WIDTH-500.0f)
	//{
	//	m_moveX *= -1;
	//}
	//if (EnemyPos.x < 500.0f)
	//{
	//	m_moveX *= -1;
	//}

	if (m_enemyMoveType == ENEMYMOVETYPE_NONE)
	{
		pos.x += m_moveX;

		if (m_nCnt < 40)
		{
			pos.y += m_moveY;
		}
	}
	else if (m_enemyMoveType == ENEMYMOVETYPE_CIRCLE)
	{
		pos = MoveCircle(EnemyPos.x, EnemyPos.y, 100.0f);
	}
	else if (m_enemyMoveType == ENEMYMOVETYPE_LISSAJOUS)
	{
		if (m_nCnt == 660)
		{
			m_SubPos = pos;
			SetLissajous(m_Lissajous_SetSubData[0].fAlpha, m_Lissajous_SetSubData[0].fBeta,
				m_Lissajous_SetSubData[0].fDelta, m_Lissajous_SetSubData[0].fRadiusA, m_Lissajous_SetSubData[0].fRadiusB);
			pos = MoveLissajous(m_Lissajous_SetData);
			m_SubDistance = D3DXVECTOR3(m_SubPos.x - pos.x, m_SubPos.y - pos.y, 0.0f);
			EnemyPos = EnemyPos + m_SubDistance;
		}
		else if (m_nCnt == 1260)
		{
			m_SubPos = pos;
			SetLissajous(m_Lissajous_SetSubData[1].fAlpha, m_Lissajous_SetSubData[1].fBeta,
				m_Lissajous_SetSubData[1].fDelta, m_Lissajous_SetSubData[1].fRadiusA, m_Lissajous_SetSubData[1].fRadiusB);
			pos = MoveLissajous(m_Lissajous_SetData);
			m_SubDistance = D3DXVECTOR3(m_SubPos.x - pos.x, m_SubPos.y - pos.y, 0.0f);
			EnemyPos = EnemyPos + m_SubDistance;
		}

		pos = MoveLissajous(m_Lissajous_SetData);

		CEffect::Create(pos, m_scale * 0.7f, D3DXCOLOR(0.6f, 0.2f, 1.0f, 0.2f), 35);
	}
	else if (m_enemyMoveType == ENEMYMOVETYPE_CROSS)
	{
		pos.x += m_moveX;
		pos.y += m_moveY;
		CEffect::Create(pos, m_scale * 0.7f, D3DXCOLOR(0.6f, 0.2f, 1.0f, 0.2f), 35);
	}

	//if (m_nCnt >= 60 && m_nCnt % 120 == 0 && m_enemyType == ENEMYTYPE_ZERO && m_enemyMoveType == ENEMYMOVETYPE_CIRCLE)
	//{ // 弾の生成
	//	CBullet::Create(D3DXVECTOR3(pos.x, pos.y/* - m_scale.y / 2 + 10.0f*/, pos.z),
	//								D3DXVECTOR3(20.f, 20.f, 0.0f),
	//								D3DXVECTOR3(0.0f, 20.0f, 0.0f),
	//								CBullet::BULLETTYPE_ENEMY,
	//								CBullet::USEBULLET_NONE);
	//	pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
	//}
	if (m_nCnt >= 60 && rand() % 90 == 0 && m_enemyMoveType == ENEMYMOVETYPE_LISSAJOUS)
	{ // 弾の生成
		if (pos.x < SCREEN_WIDTH / 2)
		{
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y/* - m_scale.y / 2 + 10.0f*/, pos.z),
				D3DXVECTOR3(20.f, 20.f, 0.0f),
				D3DXVECTOR3(-2.0f, -10.0f, 0.0f),
				CBullet::BULLETTYPE_ENEMY,
				CBullet::USEBULLET_TRACKING);
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
		}
		else
		{
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y/* - m_scale.y / 2 + 10.0f*/, pos.z),
				D3DXVECTOR3(20.f, 20.f, 0.0f),
				D3DXVECTOR3(2.0f, -10.0f, 0.0f),
				CBullet::BULLETTYPE_ENEMY,
				CBullet::USEBULLET_TRACKING);
			pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
		}
	}
	else if (m_nCnt >= 60 && m_nCnt % 60 == 0 && m_enemyMoveType == ENEMYMOVETYPE_NONE)
	{ // 弾の生成
		float angle = 0;

		for (int nCnt = 0; nCnt < BULLET_MAX_ANGLE; nCnt++)
		{
			angle = angle + (D3DX_PI * 2 / BULLET_MAX_ANGLE);
			if (angle > D3DX_PI) { angle -= D3DX_PI * 2; }
			if (angle < -D3DX_PI) { angle += D3DX_PI * 2; }

			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				D3DXVECTOR3(20.f, 20.f, 0.0f),
				D3DXVECTOR3(cosf(angle) *  10.f, sinf(angle) * 10.f, 0.0f),
				CBullet::BULLETTYPE_ENEMY,
				CBullet::USEBULLET_NONE);
		}
		pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
	}
	else if (m_nCnt >= 60 && m_nCnt % 80 == 0 && m_enemyType == ENEMYTYPE_TWO)
	{ // 弾の生成
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
			D3DXVECTOR3(20.f, 20.f, 0.0f),
			D3DXVECTOR3(2.0f, -10.0f, 0.0f),
			CBullet::BULLETTYPE_ENEMY,
			CBullet::USEBULLET_TRACKING);
		pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
	}

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
				int nPlayerState = CPlayer::GetPlayerState();

				if (objType == OBJTYPE_PLAYER && nPlayerState == CPlayer::PLAYERSTATE_NONE)
				{
					D3DXVECTOR3 posPlayer = pScene->GetPosition();
					D3DXVECTOR3 scalePlayer = pScene->GetScale();
					CLife *pLife = CGame::GetLife();
					CPlayer *pPlayer = CGame::GetPlayer();
					CScore *pScore = CGame::GetScore();

					if (pos.y - m_scale.y / 2.0f < posPlayer.y + scalePlayer.y / 6.0f &&
						pos.y + m_scale.y / 2.0f > posPlayer.y - scalePlayer.y / 6.0f &&
						pos.x - m_scale.x / 2.0f < posPlayer.x + scalePlayer.x / 6.0f &&
						pos.x + m_scale.x / 2.0f > posPlayer.x - scalePlayer.x / 6.0f)
					{
						//爆発の生成
						CExplosion::Create(posPlayer, scalePlayer*3);

						//プレイヤーの残機減少
						pLife->AddLife(-1);

						pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

						CGame::GetBulletPower()->SetBulletPower(0);

						// スコア加算処理
						pScore->AddScore(-1000);
					}
				}
			}
		}
	}
	//if (m_nCnt > 120)
	//{
	//	m_nCnt = 0;
	//}
	m_nCnt++;

	if (pos.y > SCREEN_HEIGHT || pos.x > SCREEN_WIDTH + 300 || pos.x < -300)
	{
		Uninit();
	}

#ifdef _DEBUG
	m_fDistance = sqrtf((pos.x - EnemyPos.x) * (pos.x - EnemyPos.x) + (pos.y - EnemyPos.y) * (pos.y - EnemyPos.y));
#endif
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
// 円を描く移動処理
//*****************************************************************************
D3DXVECTOR3 CEnemy::MoveCircle(float fMoveX, float fMoveY, float fRadius)
{
	D3DXVECTOR3 pos;

	m_fAngle += 0.05f;

	if (m_fAngle >= D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2.0f;
	}

	if (m_enemyMoveType == ENEMYMOVETYPE_CIRCLE)
	{
		if (m_SetLR > 0)
		{
			pos = D3DXVECTOR3((fMoveX + cosf(m_fAngle) * fRadius), (fMoveY + sinf(m_fAngle) * fRadius), 0.0f);
			CEffect::Create(pos, D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.8f, 0.2f, 0.5f, 1.0f), 100);
		}
		else if (m_SetLR < 0)
		{
			pos = D3DXVECTOR3((fMoveX + cosf(m_fAngle) * -fRadius), (fMoveY + sinf(-m_fAngle) * -fRadius), 0.0f);
			CEffect::Create(pos, D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.8f, 0.2f, 0.5f, 1.0f), 100);
		}
		else
		{
			pos = D3DXVECTOR3(fMoveX, fMoveY, 0.0f);
		}
	}

	if (m_enemyMoveType == ENEMYMOVETYPE_LISSAJOUS)
	{
		pos = D3DXVECTOR3(fMoveX, fMoveY, 0.0f);
	}

	return pos;
}

//*****************************************************************************
// リサージュ曲線による移動処理
//*****************************************************************************
D3DXVECTOR3 CEnemy::MoveLissajous(LISSAJOUS_SETDATA movedata)
{
	D3DXVECTOR3 pos;

	m_fAngleL += 0.005f;

	if (m_fAngleL >= D3DX_PI)
	{
		m_fAngleL -= D3DX_PI * 2.0f;
	}
	
	if (movedata.fDelta == 0.0f)
	{
		pos = D3DXVECTOR3(
			EnemyPos.x + cosf((movedata.fAlpha * m_fAngleL))*movedata.fRadiusA,
			EnemyPos.y + (-sinf((movedata.fBeta * m_fAngleL) + movedata.fDelta))*movedata.fRadiusB,
			0.0f);
	}
	else
	{
		pos = D3DXVECTOR3(
			EnemyPos.x + cosf((movedata.fAlpha * m_fAngleL))*movedata.fRadiusA,
			EnemyPos.y + (-sinf((movedata.fBeta * m_fAngleL) + D3DX_PI * (1 / movedata.fDelta)))*movedata.fRadiusB,
			0.0f);
	}

	EnemyPos.x += m_moveX;
	EnemyPos.y += m_moveY;

#ifdef _DEBUG
	m_fRadianAngle = atan2f(EnemyPos.y - pos.y, pos.x - EnemyPos.x);
	m_fDigreeAngle = m_fRadianAngle * 180.0f / D3DX_PI;
#endif

	return pos;
}

//*****************************************************************************
// リサージュ曲線の設定処理
//*****************************************************************************
void CEnemy::SetLissajous(float fAlpha, float fBeta, float fDelta, float fRadiusA, float fRadiusB)
{
	m_Lissajous_SetData.fAlpha = fAlpha;
	m_Lissajous_SetData.fBeta = fBeta;
	m_Lissajous_SetData.fDelta = fDelta;
	m_Lissajous_SetData.fRadiusA = fRadiusA;
	m_Lissajous_SetData.fRadiusB = fRadiusB;
}
//*****************************************************************************
// リサージュ曲線の設定処理
//*****************************************************************************
void CEnemy::SetSubLissajous(float fAlpha, float fBeta, float fDelta, float fRadiusA, float fRadiusB)
{
	m_Lissajous_SetSubData[m_SubCnt].fAlpha = fAlpha;
	m_Lissajous_SetSubData[m_SubCnt].fBeta = fBeta;
	m_Lissajous_SetSubData[m_SubCnt].fDelta = fDelta;
	m_Lissajous_SetSubData[m_SubCnt].fRadiusA = fRadiusA;
	m_Lissajous_SetSubData[m_SubCnt].fRadiusB = fRadiusB;

	if (m_SubCnt < 2)
	{
		m_SubCnt++;
	}
}