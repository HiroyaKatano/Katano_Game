//=========================================================================================================================
//
// 背景のテクスチャ [BG.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "BG.h"
#include "input.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureFirstBG = NULL;		// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureSecondBG = NULL;		// テクスチャ
float g_fTexU = 0;							
float g_fTexV = 0;

//=========================================================================================================================
// 背景の初期化処理
//=========================================================================================================================
HRESULT InitBG(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sky000.jpg", &g_pTextureFirstBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mountain000.png", &g_pTextureSecondBG);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BG_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL)))
	{
		return E_FAIL;
	}
 
	

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BG_TYPE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(FIRST_BG_POS_LEFT_X, BG_POS_UNDER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(FIRST_BG_POS_LEFT_X, BG_POS_TOP_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(FIRST_BG_POS_RIGHT_X, BG_POS_UNDER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(FIRST_BG_POS_RIGHT_X, BG_POS_TOP_Y, 0.0f);

			// 頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(MOVE_FIRST_BG_U, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(MOVE_FIRST_BG_U, 0.0f);
			break;
		case 1:
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(SECOND_BG_POS_LEFT_X, BG_POS_UNDER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SECOND_BG_POS_LEFT_X, BG_POS_UNDER_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SECOND_BG_POS_RIGHT_X, BG_POS_UNDER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SECOND_BG_POS_RIGHT_X, BG_POS_UNDER_Y / 2, 0.0f);

			// 頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			break;
		default:
			break;
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);

		
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();

	return S_OK;
}

//=========================================================================================================================
// 背景の終了処理
//=========================================================================================================================
void UninitBG(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

	// テクスチャの開放
	if (g_pTextureFirstBG != NULL)
	{
		g_pTextureFirstBG->Release();
		g_pTextureFirstBG = NULL;
	}
}

//=========================================================================================================================
// 背景の更新処理
//=========================================================================================================================
void UpdateBG(void)
{
	VERTEX_2D *pVtx;

	g_fTexU += MOVE_FIRST_BG_U;


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexU, 1.0f + g_fTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexU, 0.0f + g_fTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexU, 1.0f + g_fTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexU, 0.0f + g_fTexV);

	// 頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// 背景の描画処理
//=========================================================================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	for (int nCnt = 0; nCnt < MAX_BG_TYPE - 1; nCnt++)
	{
		// テクスチャの設定
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureFirstBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureSecondBG);
			break;
		default:
			break;
		}

		// 背景の描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCnt * 4,						// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}
