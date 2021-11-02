//=============================================================================
//
// 2Dポリゴン [scene2D.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2D.h" 
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "bulletPower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{


}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene2D::~CScene2D()
{


}

//*****************************************************************************
// ポリゴンの初期化処理
//*****************************************************************************
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
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

	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2.0f, m_Polygon.pos.y + m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2.0f, m_Polygon.pos.y - m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x + m_Polygon.scale.x / 2.0f, m_Polygon.pos.y + m_Polygon.scale.y / 2.0f, 0.0);
	pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x + m_Polygon.scale.x / 2.0f, m_Polygon.pos.y - m_Polygon.scale.y / 2.0f, 0.0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// ポリゴンの終了処理
//*****************************************************************************
void CScene2D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの破棄
	Release();
}

//*****************************************************************************
// ポリゴンの更新処理
//*****************************************************************************
void CScene2D::Update()
{
	
}

//*****************************************************************************
// ポリゴンの描画処理
//*****************************************************************************
void CScene2D::Draw()
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

//*****************************************************************************
// 生成処理
//*****************************************************************************
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, scale);
	}

	return pScene2D;
}

//*****************************************************************************
// 位置設定処理
//*****************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//位置の設定
	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	m_Polygon.fLength = sqrtf(scale.x / 2 * scale.x / 2 + scale.y / 2 * scale.y / 2);

	m_Polygon.fAngle = atan2f(scale.x, scale.y);

	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x + sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y - cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x + sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y + cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y - cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - sinf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength,
		m_Polygon.pos.y + cosf(m_Polygon.fAngle + D3DX_PI) * m_Polygon.fLength, m_Polygon.pos.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//*****************************************************************************
// 位置の取得
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_Polygon.pos;
}

//*****************************************************************************
// テクスチャの割り当て処理
//*****************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}


//=============================================================================
// 爆発テクスチャ設定
//=============================================================================
void CScene2D::SetExplosionTex(int nCnt)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(nCnt / 8.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(nCnt / 8.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / 8.0f + (nCnt / 8.0f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 8.0f + (nCnt / 8.0f), 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 背景テクスチャ設定
//=============================================================================
void CScene2D::SetBgTex(float fTexU, float fTexV)
{
	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(fTexU, 1.0f + fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU, 0.0f + fTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + fTexU, 1.0f + fTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fTexU, 0.0f + fTexV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの透明度(effect)
//=============================================================================
void CScene2D::SetEffect(D3DXCOLOR col, float nData)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, nData);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, nData);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの透明度(プレイヤー)
//=============================================================================
void CScene2D::SetPlayerCol(float nData)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, nData);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// ゲージ増減処理
//*****************************************************************************
void CScene2D::SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nBulletMax)
{
	//位置の設定
	m_Polygon.pos = pos;

	m_Polygon.scale = scale;

	int nBulletNum = CGame::GetBulletPower()->GetBulletPower();

	//変数宣言
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nBulletMax == 50)
	{
		//プレイヤーの位置を設定
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * nBulletNum / nBulletMax,
			m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * nBulletNum / nBulletMax,
			m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}
	else if (nBulletMax == 0)
	{
		//プレイヤーの位置を設定
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}
	else
	{
		//プレイヤーの位置を設定
		pVtx[0].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2, m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * (nBulletNum % 40) / nBulletMax,
			m_Polygon.pos.y + m_Polygon.scale.y / 2, m_Polygon.pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Polygon.pos.x - m_Polygon.scale.x / 2 + m_Polygon.scale.x * (nBulletNum % 40) / nBulletMax,
			m_Polygon.pos.y - m_Polygon.scale.y / 2, m_Polygon.pos.z);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}