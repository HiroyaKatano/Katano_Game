//=============================================================================
//
// マネージャー [manager.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h" 
#include "renderer.h"
#include "scene2D.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "bulletPower.h"
#include "titleLogo.h"

//==============================================================================
// 静的メンバ変数
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;

CLife *CManager::m_pLife = NULL;

CTitle *CManager::m_pTitle = NULL;					// タイトルモード
CGame *CManager::m_pGame = NULL;					// ゲームモード
CResult *CManager::m_pResult = NULL;					// ゲームモード

CManager::MODE CManager::m_mode = MODE_TITLE;		// 現在のゲームモード
CFade *CManager::m_pFade = NULL;
CSound *CManager::m_pSound = NULL;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CManager::CManager()
{


}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CManager::~CManager()
{


}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	// キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// タイトルロゴテクスチャのロード
	CTitleLogo::Load();

	// 背景テクスチャのロード
	CBg::Load();

	// バレットテクスチャのロード
	CBullet::Load();

	// エフェクトテクスチャのロード
	CEffect::Load();

	// 爆発テクスチャのロード
	CExplosion::Load();

	// 敵テクスチャのロード
	CEnemy::Load();

	// プレイヤーテクスチャのロード
	CPlayer::Load();

	// ナンバーテクスチャのロード
	CNumber::Load();

	// 残機テクスチャのロード
	CLife::Load();

	// 弾のゲージテクスチャのロード
	CBulletPower::Load();

	// サウンドの初期化処理
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	// フェードの初期化処理
	//m_pFade = new CFade;
	//if (m_pFade != NULL)
	//{
	//	m_pFade->Init(m_mode);
	//}

	SetMode(m_mode);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CManager::Uninit()
{
	// 全てのオブジェクトの破棄
	CScene::ReleaseAll();

	// 弾のゲージテクスチャのロード
	CBulletPower::Unload();

	// 残機テクスチャのロード
	CLife::Unload();

	// ナンバーテクスチャのロード
	CNumber::Unload();

	// プレイヤーテクスチャのアンロード
	CPlayer::Unload();

	// バレットテクスチャのアンロード
	CBullet::Unload();

	// エネミーテクスチャのアンロード
	CEnemy::Unload();

	// 爆発テクスチャのアンロード
	CExplosion::Unload();

	// 背景テクスチャのアンロード
	CBg::Unload();
	
	// タイトルロゴテクスチャのアンロード
	CTitleLogo::Unload();

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// サウンドの終了処理
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// フェードの終了処理
	/*if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}*/
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update()
{
	// キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	if (m_pInputKeyboard->GetPress(DIK_P) != true)
	{
		// レンダラーの更新処理
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Update();
		}

		// フェードの更新処理
		//if (m_pFade != NULL)
		//{
		//	m_pFade->Update();
		//}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// レンダリングクラスの取得
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボードクラスの取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// モードの破棄
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
		}

		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
		}
		break;

	default:
		break;
	}

	// オブジェクト破棄
	CScene::ReleaseAll();

	// モードの設定
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle->Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame->Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult->Create();
		}
		break;

	default:
		break;
	}
}