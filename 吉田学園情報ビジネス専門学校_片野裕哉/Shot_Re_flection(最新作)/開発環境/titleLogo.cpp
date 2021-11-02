//=============================================================================
//
//	背景 [bg.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "titleLogo.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_apTexture[] = {};

//=============================================================================
// コンストラク
//=============================================================================
CTitleLogo::CTitleLogo(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title002.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title003.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
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
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTitleLogo *pTitleLogo = NULL;

	if (pTitleLogo == NULL)
	{
		pTitleLogo = new CTitleLogo;

		if (pTitleLogo != NULL)
		{
			pTitleLogo->Init(pos, scale);
		}
	}
	return pTitleLogo;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		m_fPosTexU[nCnt] = 0.0f;
		m_fPosTexV[nCnt] = 0.0f;
		m_aPos[nCnt] = pos;
		if (nCnt != 2)
		{
			m_aScale[nCnt] = scale;
		}
		else if (nCnt == 2)
		{
			m_aScale[nCnt] = scale - D3DXVECTOR3(0.f, scale.y / 2, 0.f);
		}
	}


	// 背景スピード
	m_fSpeed[0] = SCROL_SPPED01;
	m_fSpeed[1] = SCROL_SPPED02;
	m_fSpeed[2] = SCROL_SPPED03;

	m_bFlashSign = false;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTitleLogo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTitleLogo::Update(void)
{
	// キーボード関係
	CInputKeyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		if (nCnt != 2)
		{
			if (m_aPos[nCnt].y < SCREEN_HEIGHT / 4)
			{
				m_aPos[nCnt].y += 2.f;
			}
		}
		else if (nCnt == 2)
		{
			if (m_aPos[nCnt].y < SCREEN_HEIGHT * 4/5)
			{
				m_aPos[nCnt].y += 5.f;
			}
		}
		m_apScene2D[nCnt]->SetPosition(m_aPos[nCnt], m_aScale[nCnt]);
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTitleLogo::Draw(void)
{

}