//=============================================================================
//
//	残機 [bulletPower.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "bulletPower.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBulletPower::m_apTexture[] = {};			// テクスチャ
int CBulletPower::m_nBulletPower;

//=============================================================================
// コンストラク
//=============================================================================
CBulletPower::CBulletPower(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
	m_nBulletPower = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletPower::~CBulletPower()
{
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBulletPower::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge000.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge002.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CBulletPower::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE_TEX; nCnt++)
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
// バレットパワーの生成
//=============================================================================
CBulletPower *CBulletPower::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CBulletPower *pBulletPower = NULL;

	if (pBulletPower == NULL)
	{
		pBulletPower = new CBulletPower;

		if (pBulletPower != NULL)
		{
			pBulletPower->Init(pos, scale);
		}
	}
	return pBulletPower;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBulletPower::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE_TEX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}
	m_pos = pos;
	m_scale = scale;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH/2 - 40.f, 50.f, 0.f)
			+ D3DXVECTOR3(40.f * nCnt, 0.f, 0.f), D3DXVECTOR3(40.f, 80.f, 0.f), 0);
	}

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBulletPower::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE_TEX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
	}

	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBulletPower::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE_TEX; nCnt++)
	{
		if (nCnt == 1)
		{
			m_apScene2D[nCnt]->SetGauge(m_pos,D3DXVECTOR3(m_scale.x, m_scale.y, m_scale.z));
		}
		else
		{
			m_apScene2D[nCnt]->SetPosition(m_pos, m_scale);
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBulletPower::Draw(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
// 弾の数セット処理
//=============================================================================
void CBulletPower::SetBulletPower(int nBulletPower)
{
	m_nBulletPower = nBulletPower;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[0]->SetNumber((m_nBulletPower / 10) % 10);
		m_apNumber[1]->SetNumber((m_nBulletPower) % 10);
	}
}

//=============================================================================
// 残機加算処理
//=============================================================================
void CBulletPower::AddBulletPower(int nValue)
{
	m_nBulletPower += nValue;

	if (m_nBulletPower < 0)
	{
		m_nBulletPower = 0;
		SetBulletPower(m_nBulletPower);
	}
	else if (m_nBulletPower >= 51)
	{
		m_nBulletPower = 50;
		SetBulletPower(m_nBulletPower);
	}
	else if (m_nBulletPower >= 0 && m_nBulletPower < 50)
	{
		SetBulletPower(m_nBulletPower);
	}
}