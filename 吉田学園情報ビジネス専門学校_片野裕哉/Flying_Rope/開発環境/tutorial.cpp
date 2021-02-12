//=========================================================================================================================
//
// チュートリアル [tutorial.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;		// テクスチャ

//=========================================================================================================================
// チュートリアルの初期化処理
//=========================================================================================================================
HRESULT InitTutorial(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.jpg", &g_pTextureTutorial);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_LEFT_X, TUTORIAL_POS_UNDER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_POS_LEFT_X, TUTORIAL_POS_TOP_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_RIGHT_X, TUTORIAL_POS_UNDER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_POS_RIGHT_X, TUTORIAL_POS_TOP_Y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[1].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[2].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);
	pVtx[3].col = D3DCOLOR_RGBA(TUTORIAL_COLOR_R, TUTORIAL_COLOR_G, TUTORIAL_COLOR_B, TUTORIAL_COLOR_A);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//=========================================================================================================================
// チュートリアルの終了処理
//=========================================================================================================================
void UninitTutorial(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
}

//=========================================================================================================================
// チュートリアルの更新処理
//=========================================================================================================================
void UpdateTutorial(void)
{
	//VERTEX_2D *pVtx;
	int nFade = GetFade();

	//g_fTexU += MOVE_FIRST_TUTORIAL_U;


	//// 頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexU, 1.0f + g_fTexV);
	//pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexU, 0.0f + g_fTexV);
	//pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexU, 1.0f + g_fTexV);
	//pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexU, 0.0f + g_fTexV);

	//// 頂点バッファをアンロックする
	//g_pVtxBuffTutorial->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
	}
}

//=========================================================================================================================
// チュートリアルの描画処理
//=========================================================================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	// チュートリアルの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数

}
