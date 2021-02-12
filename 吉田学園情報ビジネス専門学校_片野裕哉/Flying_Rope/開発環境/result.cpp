//=========================================================================================================================
//
// リザルト [result.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_apTextureResult[2] = {};			// テクスチャ
int g_nResult;

//=========================================================================================================================
// リザルトの初期化処理
//=========================================================================================================================
HRESULT InitResult(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtex;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\failed_cat.jpg", &g_apTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result_cat.jpg", &g_apTextureResult[1]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtex, 0);

	// 頂点座標の設定
	pVtex[0].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_U, 0.0f);
	pVtex[1].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_T, 0.0f);
	pVtex[2].pos = D3DXVECTOR3(SCREEN_WIDTH_R, SCREEN_HEIGHT_U, 0.0f);
	pVtex[3].pos = D3DXVECTOR3(SCREEN_WIDTH_R, SCREEN_HEIGHT_T, 0.0f);

	// rhwの設定
	pVtex[0].rhw = 1.0f;
	pVtex[1].rhw = 1.0f;
	pVtex[2].rhw = 1.0f;
	pVtex[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtex[0].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[1].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[2].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);
	pVtex[3].col = D3DCOLOR_RGBA(RESULT_COLOR_R, RESULT_COLOR_G, RESULT_COLOR_B, RESULT_COLOR_A);

	// 頂点情報の設定
	pVtex[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtex[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtex[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtex[3].tex = D3DXVECTOR2(1.0, 0.0);

	// 頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//=========================================================================================================================
// リザルトの終了処理
//=========================================================================================================================
void UninitResult(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	// テクスチャの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=========================================================================================================================
// リザルトの更新処理
//=========================================================================================================================
void UpdateResult(void)
{
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//=========================================================================================================================
// リザルトの描画処理
//=========================================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	switch (g_nResult)
	{
	case 0:
		pDevice->SetTexture(0, g_apTextureResult[1]);
		break;
	default:
		pDevice->SetTexture(0, g_apTextureResult[0]);
		break;
	}
	

	// リザルトの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数
}


//
//
//
int GetResult(void)
{
	return g_nResult;
}
