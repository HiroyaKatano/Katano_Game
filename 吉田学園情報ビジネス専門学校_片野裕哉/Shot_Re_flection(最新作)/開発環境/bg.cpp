//=============================================================================
//
//	背景 [bg.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[] = {};

//=============================================================================
// コンストラク
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 背景の生成
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;

		if (pBg != NULL)
		{
			pBg->Init(pos, scale);
		}
	}
	return pBg;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		m_fPosTexU[nCnt] = 0.0f;
		m_fPosTexV[nCnt] = 0.0f;
	}

	// 背景スピード
	m_fSpeed[0] = SCROL_SPPED01;
	m_fSpeed[1] = SCROL_SPPED02;
	m_fSpeed[2] = SCROL_SPPED03;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBg::Update(void)
{
	// キーボード関係
	CInputKeyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (plnputKeyboard->GetPress(DIK_D) == true)
		{
			m_fPosTexU[nCnt] += m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_A) == true)
		{
			m_fPosTexU[nCnt] -= m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_W) == true)
		{
			m_fPosTexV[nCnt] -= m_fSpeed[nCnt] * 0.5f;
		}
		if (plnputKeyboard->GetPress(DIK_S) == true)
		{
			m_fPosTexV[nCnt] += m_fSpeed[nCnt] * 0.5f;
		}

		m_fPosTexV[nCnt] -= m_fSpeed[nCnt];

		m_apScene2D[nCnt]->SetBgTex(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBg::Draw(void)
{

}