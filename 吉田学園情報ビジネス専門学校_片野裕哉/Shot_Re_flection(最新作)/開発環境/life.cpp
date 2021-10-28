//=============================================================================
//
//	残機 [life.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_apTexture[] = {};
int CLife::m_nLife;

//=============================================================================
// コンストラク
//=============================================================================
CLife::CLife(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

	m_nLife = 3;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CLife::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player001.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ui000.png", &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CLife::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
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
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{
		pLife = new CLife;

		if (pLife != NULL)
		{
			pLife->Init(pos, scale);
		}
	}
	return pLife;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos + (D3DXVECTOR3(scale.x, 0.f, 0.f) * (float)nCnt), scale / (nCnt * 0.5f + 1));
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	m_pNumber = CNumber::Create(pos + D3DXVECTOR3(scale.x * 1.75f, 0.0f, 0.0f),
							D3DXVECTOR3(scale.x / 2, scale.y, scale.z), 2);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}
	m_pNumber->Uninit();
	delete m_pNumber;

	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CLife::Update(void)
{
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CLife::Draw(void)
{
	m_pNumber->Draw();
}

//=============================================================================
// 残機セット処理
//=============================================================================
void CLife::SetLife(int nLife)
{
	m_nLife = nLife;

	m_pNumber->SetNumber(nLife - 1);
}

//=============================================================================
// 残機加算処理
//=============================================================================
void CLife::AddLife(int nValue)
{
	m_nLife += nValue;

	if (m_nLife < 0)
	{
		m_nLife = 0;
		SetLife(m_nLife);
	}
	else if (m_nLife >= 10)
	{
		m_nLife = 9;
		SetLife(m_nLife);
	}
	else if (m_nLife >= 0 && m_nLife < 10)
	{
		SetLife(m_nLife);
	}
}