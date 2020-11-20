//=========================================================================================================================
//
// UI [ui.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "ui.h"
#include "BG.h"
#include "player.h"
#include "barrier.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureAddUp = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureMachine = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRihgtBG = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLeftBG = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGaugeBG = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGauge = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGaugeFlame = NULL;
LPDIRECT3DTEXTURE9 g_pTextureOperation = NULL;

//=========================================================================================================================
// UIの初期化処理
//=========================================================================================================================
HRESULT InitUi(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &g_pTexturePlayer);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ui000.png", &g_pTextureAddUp);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureMachine);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_bg004.jpg", &g_pTextureRihgtBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_L_bg.jpg", &g_pTextureLeftBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge000.png", &g_pTextureGaugeBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge0010.png", &g_pTextureGauge);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge002.png", &g_pTextureGaugeFlame);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_key.png", &g_pTextureOperation);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TYPE_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL)))
	{
		return E_FAIL;
	}



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUi = 0; nCntUi < MAX_TYPE_UI; nCntUi++)
	{
		// 頂点座標の設定
		switch (nCntUi)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(635.0f - MINI_PLAYER_X / 2, 1045.0f + MINI_PLAYER_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(635.0f - MINI_PLAYER_X / 2, 1045.0f - MINI_PLAYER_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(635.0f + MINI_PLAYER_X / 2, 1045.0f + MINI_PLAYER_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(635.0f + MINI_PLAYER_X / 2, 1045.0f - MINI_PLAYER_Y / 2, 0.0f);
			break;
		case 1:
			pVtx[0].pos = D3DXVECTOR3(685.0f - ADD_UP_X / 2, 1050.0f + ADD_UP_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(685.0f - ADD_UP_X / 2, 1050.0f - ADD_UP_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(685.0f + ADD_UP_X / 2, 1050.0f + ADD_UP_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(685.0f + ADD_UP_X / 2, 1050.0f - ADD_UP_Y / 2, 0.0f);
			break;
		case 2:
			pVtx[0].pos = D3DXVECTOR3(730.0f - NUMBER_X / 2, 1045.0f + NUMBER_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(730.0f - NUMBER_X / 2, 1045.0f - NUMBER_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(730.0f + NUMBER_X / 2, 1045.0f + NUMBER_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(730.0f + NUMBER_X / 2, 1045.0f - NUMBER_Y / 2, 0.0f);
			break;
		case 3:
			pVtx[0].pos = D3DXVECTOR3(BG_POS_RIGHT_X, SCREEN_HEIGTH, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BG_POS_RIGHT_X, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGTH, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			break;
		case 4:
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGTH, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(BG_POS_LEFT_X, SCREEN_HEIGTH, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BG_POS_LEFT_X, 0.0f, 0.0f);
			break;
		case 5:
			pVtx[0].pos = D3DXVECTOR3(1145.0f - GAUGE_BG_X / 2, 1060.0f + GAUGE_BG_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1145.0f - GAUGE_BG_X / 2, 1060.0f - GAUGE_BG_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1145.0f + GAUGE_BG_X / 2, 1060.0f + GAUGE_BG_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1145.0f + GAUGE_BG_X / 2, 1060.0f - GAUGE_BG_Y / 2, 0.0f);
			break;
		case 6:		
			pVtx[0].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f + GAUGE_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f - GAUGE_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1145.0f + GAUGE_X / 2, 1060.0f + GAUGE_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1145.0f + GAUGE_X / 2, 1060.0f - GAUGE_Y / 2, 0.0f);
			break;
		case 7:		
			pVtx[0].pos = D3DXVECTOR3(1145.0f - GAUGE_FLAME_X / 2, 1060.0f + GAUGE_FLAME_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1145.0f - GAUGE_FLAME_X / 2, 1060.0f - GAUGE_FLAME_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1145.0f + GAUGE_FLAME_X / 2, 1060.0f + GAUGE_FLAME_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1145.0f + GAUGE_FLAME_X / 2, 1060.0f - GAUGE_FLAME_Y / 2, 0.0f);
			break;
		case 8:
			pVtx[0].pos = D3DXVECTOR3(BG_POS_RIGHT_X + 300.0f - OPERATION_X / 2, 800.0f + OPERATION_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(BG_POS_RIGHT_X + 300.0f - OPERATION_X / 2, 800.0f - OPERATION_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(BG_POS_RIGHT_X + 300.0f + OPERATION_X / 2, 800.0f + OPERATION_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(BG_POS_RIGHT_X + 300.0f + OPERATION_X / 2, 800.0f - OPERATION_Y / 2, 0.0f);
			break;
		}
		
		switch (nCntUi)
		{
		case 2:
			// 頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / NUMBER_TEXTURE_Y);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 1.0f / NUMBER_TEXTURE_Y);
			pVtx[3].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X, 0.0f);
			break;
		default:
			// 頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
			break;
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(UI_COLOR_R, UI_COLOR_G, UI_COLOR_B, UI_COLOR_A);
		pVtx[1].col = D3DXCOLOR(UI_COLOR_R, UI_COLOR_G, UI_COLOR_B, UI_COLOR_A);
		pVtx[2].col = D3DXCOLOR(UI_COLOR_R, UI_COLOR_G, UI_COLOR_B, UI_COLOR_A);
		pVtx[3].col = D3DXCOLOR(UI_COLOR_R, UI_COLOR_G, UI_COLOR_B, UI_COLOR_A);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();

	return S_OK;
}

//=========================================================================================================================
// UIの終了処理
//=========================================================================================================================
void UninitUi(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{		
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	if (g_pTextureAddUp != NULL)
	{			  
		g_pTextureAddUp->Release();
		g_pTextureAddUp = NULL;
	}

	if (g_pTextureMachine != NULL)
	{			  
		g_pTextureMachine->Release();
		g_pTextureMachine = NULL;
	}

	if (g_pTextureRihgtBG != NULL)
	{
		g_pTextureRihgtBG->Release();
		g_pTextureRihgtBG = NULL;
	}

	if (g_pTextureLeftBG != NULL)
	{
		g_pTextureLeftBG->Release();
		g_pTextureLeftBG = NULL;
	}

	if (g_pTextureGaugeBG != NULL)
	{			 	  
		g_pTextureGaugeBG->Release();
		g_pTextureGaugeBG = NULL;
	}			
				
	if (g_pTextureGauge != NULL)
	{			 
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}			 
				 
	if (g_pTextureGaugeFlame != NULL)
	{			 	   
		g_pTextureGaugeFlame->Release();
		g_pTextureGaugeFlame = NULL;
	}
	if (g_pTextureOperation != NULL)
	{
		g_pTextureOperation->Release();
		g_pTextureOperation = NULL;
	}
}

//=========================================================================================================================
// UIの更新処理
//=========================================================================================================================
void UpdateUi(void)
{
	ManageGauge();

	ManageMachine();
}

//=========================================================================================================================
// UIの描画処理
//=========================================================================================================================
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntUi = 0; nCntUi < MAX_TYPE_UI; nCntUi++)
	{
		// テクスチャの設定
		switch (nCntUi)
		{
		case 0:
			pDevice->SetTexture(0, g_pTexturePlayer);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureAddUp);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureMachine);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureRihgtBG);
			break;
		case 4:
			pDevice->SetTexture(0, g_pTextureLeftBG);
			break;
		case 5:
			pDevice->SetTexture(0, g_pTextureGaugeBG);
			break;
		case 6:
			pDevice->SetTexture(0, g_pTextureGauge);
			break;
		case 7:
			pDevice->SetTexture(0, g_pTextureGaugeFlame);
			break;
		case 8:
			pDevice->SetTexture(0, g_pTextureOperation);
			break;
		}

		// UIの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCntUi * 4,								// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}

//=========================================================================================================================
// 残機の管理
//=========================================================================================================================
void ManageMachine(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	int nNumber = pPlayer->nMachine;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[8].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
	pVtx[9].tex = D3DXVECTOR2(0.0f + nNumber * 0.1f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + nNumber * 0.1f, 1.0f / NUMBER_TEXTURE_Y);
	pVtx[11].tex = D3DXVECTOR2(1.0f / NUMBER_TEXTURE_X + nNumber * 0.1f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();
}


//=========================================================================================================================
// 特殊ゲージの管理
//=========================================================================================================================
void ManageGauge(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	BARRIER *pBarrier;

	pBarrier = GetBarrier();

	int nNumber = pBarrier->nCounterState;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	if (pBarrier->nCounterState == BARRIER_TIMER)
	{
		pVtx[24].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f + GAUGE_Y / 2, 0.0f);
		pVtx[25].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f - GAUGE_Y / 2, 0.0f);
		pVtx[26].pos = D3DXVECTOR3(1145.0f + GAUGE_X / 2, 1060.0f + GAUGE_Y / 2, 0.0f);
		pVtx[27].pos = D3DXVECTOR3(1145.0f + GAUGE_X / 2, 1060.0f - GAUGE_Y / 2, 0.0f);
	}
	else if (pBarrier->nCounterState >= 0 || pBarrier->nCounterState < BARRIER_TIMER)
	{
		pVtx[24].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f + GAUGE_Y / 2, 0.0f);
		pVtx[25].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2, 1060.0f - GAUGE_Y / 2, 0.0f);
		pVtx[27].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2 + GAUGE_X * (nNumber / (BARRIER_TIMER * 1.0f)), 1060.0f - GAUGE_Y / 2, 0.0f);
		pVtx[26].pos = D3DXVECTOR3(1145.0f - GAUGE_X / 2 + GAUGE_X * (nNumber / (BARRIER_TIMER * 1.0f)), 1060.0f + GAUGE_Y / 2, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffUi->Unlock();
}
