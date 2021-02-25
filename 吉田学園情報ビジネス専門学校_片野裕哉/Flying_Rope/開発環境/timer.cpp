//=========================================================================================================================
//
// タイマー [タイマー.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "timer.h"
#include "fade.h"
#include "Score.h"
#include "result.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;			// テクスチャ
int g_nTimer;
int g_nCntTimer;

//=========================================================================================================================
// タイマーの初期化処理
//=========================================================================================================================
HRESULT InitTimer(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number_04.png", &g_pTextureTimer);


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_TYPE_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL)))
	{
		return E_FAIL;
	}

	g_nTimer = 60;
	g_nCntTimer = 0;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH * nCntTimer, TIMER_POS_Y + TIMER_HEIGHT, Z_AXIS_ZERO);
		pVtx[1].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH * nCntTimer, TIMER_POS_Y, Z_AXIS_ZERO);
		pVtx[2].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH + TIMER_WIDTH * nCntTimer, TIMER_POS_Y + TIMER_HEIGHT, Z_AXIS_ZERO);
		pVtx[3].pos = D3DXVECTOR3(TIMER_POS_X + TIMER_WIDTH + TIMER_WIDTH * nCntTimer, TIMER_POS_Y, Z_AXIS_ZERO);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[1].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[2].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);
		pVtx[3].col = D3DXCOLOR(TIMER_COLOR_R, TIMER_COLOR_G, TIMER_COLOR_B, TIMER_COLOR_A);

		pVtx += VTX_NUM;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//=========================================================================================================================
// タイマーの終了処理
//=========================================================================================================================
void UninitTimer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

}

//=========================================================================================================================
// タイマーの更新処理
//=========================================================================================================================
void UpdateTimer(void)
{
	int nFade = GetFade();
	RESULT *pResult = GetResult();

	g_nCntTimer++;
	if (g_nCntTimer % 6 == 0 && nFade == FADE_NONE)
	{
		AddScore(300);
	}

	if (g_nCntTimer % 60 == 0 && nFade == FADE_NONE)
	{
		g_nTimer -= 1;
	}

	// 変数宣言
	int nData = 10;	// 割る数
	int aNumber[2];			// スコアを格納

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// スコアを格納
	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		aNumber[nCntTimer] = (g_nTimer / nData) % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f + aNumber[nCntTimer] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + aNumber[nCntTimer] * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + aNumber[nCntTimer] * 0.1f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += VTX_NUM;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();

	if (g_nTimer == 0)
	{
		if (nFade == FADE_NONE)
		{
			pResult->ResultType = RESULTTYPE_FAILED;
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
	
}

//=========================================================================================================================
// タイマーの描画処理
//=========================================================================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTimer = 0; nCntTimer < MAX_TYPE_TIMER; nCntTimer++)
	{
		// テクスチャの設定
		switch (nCntTimer)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureTimer);
			break;
		default:
			break;
		}

		// タイマーの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCntTimer * VTX_NUM,					// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}

