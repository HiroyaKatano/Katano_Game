//=============================================================================
//
// 弾 [bullet.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "effect.h" 
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "enemy.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;			// テクスチャ

//*****************************************************************************
// テクスチャ読込処理
//*****************************************************************************
HRESULT CEffect::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CEffect::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEffect::~CEffect()
{


}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col, int nLife)
{
	CEffect *pEffect = NULL;
	pEffect = new CEffect;
	if (pEffect != NULL)
	{
		pEffect->Init(pos, scale, col);
	}
	pEffect->BindTexture(m_pTexture);

	pEffect->m_nLife = nLife;

	return pEffect;
}

//*****************************************************************************
// ポリゴンの初期化処理
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col)
{
	// 移動値を設定
	m_col = col;

	// 大きさを設定
	m_scale = scale;

	// CScene2Dを呼び出し
	CScene2D::Init(pos, scale);

	// オブジェクトの種類の設定
	CScene2D::SetObjType(OBJTYPE_EFFECT);

	CScene2D::SetEffect(col, 1.f);

	return S_OK;
}

//*****************************************************************************
// ポリゴンの終了処理
//*****************************************************************************
void CEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
// ポリゴンの更新処理
//*****************************************************************************
void CEffect::Update()
{
	//弾のライフを減らす
	m_nLife--;

	//エフェクトをだんだん透明にする
	CScene2D::SetEffect(m_col, (float)m_nLife / 100);

	//弾のライフが0以下になったとき
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//*****************************************************************************
// ポリゴンの描画処理
//*****************************************************************************
void CEffect::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//加算合成
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//加算合成を外す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

