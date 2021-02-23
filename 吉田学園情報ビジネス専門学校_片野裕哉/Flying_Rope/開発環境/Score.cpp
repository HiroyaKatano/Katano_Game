//=========================================================================================================================
//
// スコア [Score.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "Score.h"
#include "BG.h"

//
// グローバル変数
//
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;					// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;				// 頂点バッファへのポインタ
int g_nScore;

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number_04.png", &g_pTextureScore);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(SCORE_LEFT_X + SCORE_WIDTH_X * nCntScore, SCORE_LOW_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_LEFT_X + SCORE_WIDTH_X * nCntScore, SCORE_HIGH_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_RIGHT_X + SCORE_WIDTH_X * nCntScore, SCORE_LOW_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_RIGHT_X + SCORE_WIDTH_X * nCntScore, SCORE_HIGH_Y, 0.0f);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X, 1.0f / SCORE_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(SCORE_COLOR_R, SCORE_COLOR_G, SCORE_COLOR_B, SCORE_COLOR_A);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	g_nScore = 200000;

	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitScore(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateScore(void)
{

}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);

		// 敵の描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCntScore * 4,					// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}

//=========================================================================================================================
// スコアの加算処理
//=========================================================================================================================
void AddScore(int nValue)
{
	// 変数宣言
	int nData = 10000000;	// 割る数
	int aNumber[8];			// スコアを格納
	g_nScore -= nValue;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// スコアを格納
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		aNumber[nCntScore] = (g_nScore / nData) % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X + aNumber[nCntScore] * 0.1f, 1.0f / SCORE_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_X + aNumber[nCntScore] * 0.1f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}