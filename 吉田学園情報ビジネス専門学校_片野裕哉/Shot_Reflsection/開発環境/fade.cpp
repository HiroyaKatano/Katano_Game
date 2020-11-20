//=========================================================================================================================
//
// フェード処理 [fade.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "fade.h"
#include "input.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;			// テクスチャ
FADE g_fade;										// フェードの状態
MODE g_modeNext;									// 次のモード(画面)
D3DXCOLOR g_colorFade;								// フェード色

//=========================================================================================================================
// フェードの初期化処理
//=========================================================================================================================
HRESULT InitFade(MODE modeNext)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	g_fade = FADE_IN;

	g_modeNext = modeNext;

	// 頂点カラーの設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// 頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//=========================================================================================================================
// フェードの終了処理
//=========================================================================================================================
void UninitFade(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	// テクスチャの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=========================================================================================================================
// フェードの更新処理
//=========================================================================================================================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


	if (g_fade == FADE_NONE)
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.025f;

		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}
	else if (g_fade == FADE_OUT)
	{
		g_colorFade.a += 0.025f;

		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			
			SetMode(g_modeNext);
		}
	}
	g_pVtxBuffFade->Unlock();
}

//=========================================================================================================================
// フェードの描画処理
//=========================================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	// フェードの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数
}

//=========================================================================================================================
// フェードのセット処理
//=========================================================================================================================
void SetFade(FADE fade, MODE modeNext)
{	
	g_fade = fade;
	g_modeNext = modeNext;
}

//=========================================================================================================================
// フェードの取得
//=========================================================================================================================
FADE GetFade(void)
{
	return g_fade;
}
