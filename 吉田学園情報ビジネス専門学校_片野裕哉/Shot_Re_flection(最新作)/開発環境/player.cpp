//=============================================================================
//
// プレイヤー [player.cpp]
// Author : Hiroya Katano
//
//=============================================================================
#include "player.h"
#include "bullet.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "explosion.h"
#include "sound.h"
#include "life.h"
#include "effect.h"
#include "game.h"
#include "bulletPower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLY_SIZE_VTX	(100.0f)	// ポリゴンの横の半径
#define ROLL_SPD		(0.02f)		// ポリゴン回転速度
#define SCELE_SPD		(0.03f)		// ポリゴンの拡縮速度
#define SCELE_MIN		(0.5f)		// ポリゴンの最小縮小倍率
#define SCELE_MAX		(2.0f)		// ポリゴンの最大拡大倍率

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;			// テクスチャ
CPlayer::PLAYERSTATE CPlayer::m_state = CPlayer::PLAYERSTATE_NONE;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	m_nPlayerCnt = CLife::GetLife();
	m_nPlayerInvincibleCnt = 0;
	m_nAbsorbBulletCnt = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//動的確保
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;

	//初期の呼び出し
	pPlayer->Init(pos, scale);

	//// 中心座標の設定
	//m_Polygon.pos = SetPos();
	//// プレイヤーの回転角
	//m_Polygon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//// 対角線の長さ
	//m_Polygon.fLength = sqrtf(POLY_SIZE_VTX * POLY_SIZE_VTX + POLY_SIZE_VTX * POLY_SIZE_VTX);
	//// 対角線の角度
	//m_Polygon.fAngle = atan2f(POLY_SIZE_VTX, POLY_SIZE_VTX);

	//テクスチャ生成
	pPlayer->BindTexture(m_pTexture);

	//値を返す
	return pPlayer;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_scale = scale;

	CScene2D::Init(pos, scale);

	// オブジェクトの種類の設定
	SetObjType(OBJTYPE_PLAYER);

	m_state = PLAYERSTATE_NONE;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPlayer::Update(void)
{
	m_nPlayerCnt = CLife::GetLife();

	//キーボード情報の取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CSound *pSound = CManager::GetSound();

	m_nAbsorbBulletCnt = CBullet::GetAbsorbedCnt();

	// 位置の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//D3DXCOLOR col;
	//col = GetColor();

	//// 回転処理
	//m_Polygon.rot.z += ROLL_SPD;
	//if (m_Polygon.rot.z > D3DX_PI)
	//{
	//	m_Polygon.rot.z -= D3DX_PI * 2.0f;
	//}

	//// 拡大縮小切り替え
	//if (m_Polygon.fScale < SCELE_MIN)
	//{
	//	m_Polygon.bExpansion = true;
	//}
	//else if (m_Polygon.fScale > SCELE_MAX)
	//{
	//	m_Polygon.bExpansion = false;
	//}

	//// 拡大縮小処理
	//if (m_Polygon.bExpansion == true)
	//{
	//	m_Polygon.fScale += SCELE_SPD;
	//}
	//else
	//{
	//	m_Polygon.fScale -= SCELE_SPD;
	//}

	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{ // キー入力処理
		m_nSelectBullet = CBullet::USEBULLET_NONE;
	}
	if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{ // キー入力処理
		m_nSelectBullet = CBullet::USEBULLET_TRACKING;
	}
	if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{ // キー入力処理
		m_nSelectBullet = CBullet::USEBULLET_SPREAD;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{ // キー入力処理
		if (pInputKeyboard->GetPress(DIK_RSHIFT) == true)
		{
			pos.x -= 5.0f;
		}
		else
		{
			pos.x -= 15.0f;
		}
	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{ // キー入力処理
		if (pInputKeyboard->GetPress(DIK_RSHIFT) == true)
		{
			pos.x += 5.0f;
		}
		else
		{
			pos.x += 15.0f;
		}
	}
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{ // キー入力処理
		if (pInputKeyboard->GetPress(DIK_RSHIFT) == true)
		{
			pos.y -= 5.0f;
		}
		else
		{
			pos.y -= 15.0f;
		}
	}
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{ // キー入力処理
		if (pInputKeyboard->GetPress(DIK_RSHIFT) == true)
		{
			pos.y += 5.0f;
		}
		else
		{
			pos.y += 15.0f;
		}
	}
	if (pos.x - m_scale.x / 2 < 0.0f)
	{
		pos.x = m_scale.x / 2;
	}
	if (pos.x + m_scale.x / 2 > SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - m_scale.x / 2;
	}
	if (pos.y - m_scale.y / 2 < 0.0f)
	{
		pos.y = m_scale.y / 2;
	}
	if (pos.y + m_scale.y / 2 > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - m_scale.y / 2;
	}

	if (m_state == PLAYERSTATE_APPEAR)
	{
		if (m_nPlayerInvincibleCnt > 0)
		{
			m_nPlayerInvincibleCnt--;

			if (m_nPlayerInvincibleCnt % 4 != 0)
			{
				SetPlayerCol(0.5);
			}
			if (m_nPlayerInvincibleCnt % 4 == 0)
			{
				SetPlayerCol(1.0);
			}
		}
		else if (m_nPlayerInvincibleCnt <= 0)
		{
			SetPlayerCol(1.0);
			m_state = PLAYERSTATE_NONE;
		}
	}
	else if (m_state == PLAYERSTATE_NONE)
	{
		if (pInputKeyboard->GetRelase(DIK_SPACE) == true)
		{
			m_nCnt = 0;
		}

		if (pInputKeyboard->GetPress(DIK_SPACE) == true)
		{ // 弾の生成
			if (m_nCnt % 3 == 0 && m_nAbsorbBulletCnt > 0)
			{
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - m_scale.y / 2, pos.z),
					D3DXVECTOR3(25.0f, 25.0f, 0.0f),
					D3DXVECTOR3(0.0f, -20.0f, 0.0f),
					CBullet::BULLETTYPE_PLAYER,
					(CBullet::USEBULLET)m_nSelectBullet);
				pSound->Play(CSound::SOUND_LABEL_SE_SHOT);

				CGame::GetBullet()->AddAbsorbedCnt(-1);
				CGame::GetBulletPower()->AddBulletPower(-1);
			}
			m_nCnt++;
		}

		//if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		//{
		//	int nSetBullet = CBullet::GetAbsorbedCnt();
		//	for (int nCnt = 0; nCnt < nSetBullet; nCnt++)
		//	{
		//	float angle = rand() % 11 * (D3DX_PI / 180.0f);
		//	float speed = rand() % 6 + 15.f;
		//		CBullet::Create(pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f),
		//			D3DXVECTOR3(cosf(angle + m_fAngle)*speed, sinf(angle + m_fAngle)*-speed, 0.0f),
		//			CBullet::BULLETTYPE_PLAYER, CBullet::USEBULLET_NONE);
		//	}
		//	CBullet::ResetAbsorbedCnt();
		//}
	}
	else if (m_state == PLAYERSTATE_DEATH)
	{
		if (m_nPlayerCnt >= 0)
		{
			m_state = PLAYERSTATE_APPEAR;

			m_nPlayerInvincibleCnt = 120;

			pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 6 / 7, 0.0f);
		}
	}

	//m_fAngle += 0.02f;

	//if (m_fAngle > D3DX_PI * 0.75f)
	//{
	//	m_fAngle -= D3DX_PI * 0.5f;
	//}
	//else if (m_fAngle < D3DX_PI * 0.25f)
	//{
	//	m_fAngle += D3DX_PI * 0.5f;
	//}

	//CEffect::Create(D3DXVECTOR3(pos.x + cosf(m_fAngle)*100.0f, pos.y + sinf(m_fAngle)*-100.0f, 0.0f)
	//	,D3DXVECTOR3(60.0f, 60.0f, 0.0f),D3DXCOLOR(0.4f, 0.4f, 1.f, 1.f), 15);

	SetPosition(pos, m_scale);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
void CPlayer::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &m_pTexture);
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CPlayer::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// プレイヤーの状態の設定
//*****************************************************************************
void CPlayer::SetPlayerState(PLAYERSTATE PlayerState)
{
	m_state = PlayerState;
}