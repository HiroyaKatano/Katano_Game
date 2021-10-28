//=============================================================================
//
//	ナンバー [number.cpp]
//	Author:Hiroya Katano
//
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_TEX_X (10)
#define NUM_TEX_Y (1)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;


//=============================================================================
// コンストラク
//=============================================================================
CNumber::CNumber()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CNumber::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CNumber::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ナンバーの生成
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nNumber)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			pNumber->Init(pos, scale, nNumber);
		}
	}
	return pNumber;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nNumber)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;

	m_scale = scale;

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y + m_scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x / 2.0f, m_pos.y - m_scale.y / 2.0f, 0.0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f / NUM_TEX_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / NUM_TEX_X + nNumber * 0.1f, 1.0f / NUM_TEX_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / NUM_TEX_X + nNumber * 0.1f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数
}

//=============================================================================
// ナンバーセット処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f / NUM_TEX_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / NUM_TEX_X + nNumber * 0.1f, 1.0f / NUM_TEX_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / NUM_TEX_X + nNumber * 0.1f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}