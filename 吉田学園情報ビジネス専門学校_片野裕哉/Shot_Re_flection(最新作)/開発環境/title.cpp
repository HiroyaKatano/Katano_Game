//=============================================================================
//
// タイトル [title.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "title.h"
#include "bg.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "titleLogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CBg *CTitle::m_pBg = NULL;
CTitleLogo *CTitle::m_pTitleLogo = NULL;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{


}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CTitle *CTitle::Create()
{
	CTitle *pTitle = new CTitle;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;

	// 初期化処理
	pTitle->Init(pos, scale);

	return pTitle;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// 背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	m_pTitleLogo = CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.f, 0.f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_WIDTH / 5, 0.f));

	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTitle::Uninit()
{
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM000);

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTitle::Update()
{
	// キーボードの取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE_GAME);
		CManager::SetMode(CManager::MODE_GAME);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTitle::Draw()
{

}
