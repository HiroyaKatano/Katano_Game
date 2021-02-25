//=========================================================================================================================
//
// ポーズ画面 [pause.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "Pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTexturePauseBG = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;				// テクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePauseLogo = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureContinue = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;				// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;				// テクスチャ
D3DXVECTOR3 g_posPauseBG;								// 画面暗転の位置
D3DXVECTOR3 g_posPause;									// 下地の位置
D3DXVECTOR3 g_posPauseLogo;								// Pauseの位置
D3DXVECTOR3 g_posContinue;								// Continueの位置
D3DXVECTOR3 g_posRetry;									// Retryの位置
D3DXVECTOR3 g_posQuit;									// Quitの位置
int g_Pause_Manu;										// ポーズメニューの選択用

//=========================================================================================================================
// ポーズの初期化処理
//=========================================================================================================================
HRESULT InitPause(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Pause.png", &g_pTexturePause);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PauseLogo.png", &g_pTexturePauseLogo);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Continue.png", &g_pTextureContinue);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Retry.png", &g_pTextureRetry);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Quit.png", &g_pTextureQuit);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_PAUSE_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	g_Pause_Manu = PAUSE_MENU_CONTINUE;

	// 画面暗転の中心座標
	g_posPauseBG.x = SCREEN_WIDTH_R / 2;
	g_posPauseBG.y = SCREEN_HEIGHT_U / 2;

	// ポーズ下地の中心座標
	g_posPause.x = SCREEN_WIDTH_R / 2;
	g_posPause.y = SCREEN_HEIGHT_U / 2;

	// Pauseの中心座標
	g_posPauseLogo.x = SCREEN_WIDTH_R / 2;
	g_posPauseLogo.y = 100;

	// Continueの中心座標
	g_posContinue.x = SCREEN_WIDTH_R / 2;
	g_posContinue.y = 250;

	// Retryの中心座標
	g_posRetry.x = SCREEN_WIDTH_R / 2;
	g_posRetry.y = 425;

	// Quitの中心座標
	g_posQuit.x = SCREEN_WIDTH_R / 2;
	g_posQuit.y = 600;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	g_posPauseBG = D3DXVECTOR3(g_posPauseBG.x, g_posPauseBG.y, Z_AXIS_ZERO);
	g_posPause = D3DXVECTOR3(g_posPause.x, g_posPause.y, Z_AXIS_ZERO);
	g_posPauseLogo = D3DXVECTOR3(g_posPauseLogo.x, g_posPauseLogo.y, Z_AXIS_ZERO);
	g_posContinue = D3DXVECTOR3(g_posContinue.x, g_posContinue.y, Z_AXIS_ZERO);
	g_posRetry = D3DXVECTOR3(g_posRetry.x, g_posRetry.y, Z_AXIS_ZERO);
	g_posQuit = D3DXVECTOR3(g_posQuit.x, g_posQuit.y, Z_AXIS_ZERO);


	for (int nPause = 0; nPause < MAX_PAUSE_TYPE; nPause++)
	{
		switch (nPause)
		{
		case 0:
			// 画面暗転
			pVtx[0].pos = D3DXVECTOR3(0, PAUSE_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(0, 0, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(PAUSE_BG_SIZE_X, PAUSE_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(PAUSE_BG_SIZE_X, 0, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = PAUSE_BG_COLOR;
			pVtx[1].col = PAUSE_BG_COLOR;
			pVtx[2].col = PAUSE_BG_COLOR;
			pVtx[3].col = PAUSE_BG_COLOR;
			break;
		case 1:
			// ポーズ下地
			pVtx[0].pos = D3DXVECTOR3(g_posPause.x - (PAUSE_SIZE_X / 2), g_posPause.y + (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posPause.x - (PAUSE_SIZE_X / 2), g_posPause.y - (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posPause.x + (PAUSE_SIZE_X / 2), g_posPause.y + (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posPause.x + (PAUSE_SIZE_X / 2), g_posPause.y - (PAUSE_SIZE_Y / 2), Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = PAUSE_COLOR;
			pVtx[1].col = PAUSE_COLOR;
			pVtx[2].col = PAUSE_COLOR;
			pVtx[3].col = PAUSE_COLOR;
			break;
		case 2:
			// ポーズロゴ
			pVtx[0].pos = D3DXVECTOR3(g_posPauseLogo.x - (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y + (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posPauseLogo.x - (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y - (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posPauseLogo.x + (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y + (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posPauseLogo.x + (PAUSE_LOGO_SIZE_X / 2), g_posPauseLogo.y - (PAUSE_LOGO_SIZE_Y / 2), Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = PAUSE_LOGO_COLOR;
			pVtx[1].col = PAUSE_LOGO_COLOR;
			pVtx[2].col = PAUSE_LOGO_COLOR;
			pVtx[3].col = PAUSE_LOGO_COLOR;
			break;
		case 3:
			// Continue
			pVtx[0].pos = D3DXVECTOR3(g_posContinue.x - (CONTINUE_SIZE_X / 2), g_posContinue.y + (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posContinue.x - (CONTINUE_SIZE_X / 2), g_posContinue.y - (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posContinue.x + (CONTINUE_SIZE_X / 2), g_posContinue.y + (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posContinue.x + (CONTINUE_SIZE_X / 2), g_posContinue.y - (CONTINUE_SIZE_Y / 2), Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = CONTINUE_COLOR;
			pVtx[1].col = CONTINUE_COLOR;
			pVtx[2].col = CONTINUE_COLOR;
			pVtx[3].col = CONTINUE_COLOR;
			break;
		case 4:
			// Retry
			pVtx[0].pos = D3DXVECTOR3(g_posRetry.x - (RETRY_SIZE_X / 2), g_posRetry.y + (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posRetry.x - (RETRY_SIZE_X / 2), g_posRetry.y - (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posRetry.x + (RETRY_SIZE_X / 2), g_posRetry.y + (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posRetry.x + (RETRY_SIZE_X / 2), g_posRetry.y - (RETRY_SIZE_Y / 2), Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = RETRY_COLOR;
			pVtx[1].col = RETRY_COLOR;
			pVtx[2].col = RETRY_COLOR;
			pVtx[3].col = RETRY_COLOR;
			break;
		case 5:
			// Quit
			pVtx[0].pos = D3DXVECTOR3(g_posQuit.x - (QUIT_SIZE_X / 2), g_posQuit.y + (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_posQuit.x - (QUIT_SIZE_X / 2), g_posQuit.y - (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_posQuit.x + (QUIT_SIZE_X / 2), g_posQuit.y + (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_posQuit.x + (QUIT_SIZE_X / 2), g_posQuit.y - (QUIT_SIZE_Y / 2), Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = QUIT_COLOR;
			pVtx[1].col = QUIT_COLOR;
			pVtx[2].col = QUIT_COLOR;
			pVtx[3].col = QUIT_COLOR;
			break;
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += VTX_NUM;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//=========================================================================================================================
// ポーズの終了処理
//=========================================================================================================================
void UninitPause(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePauseLogo != NULL)
	{
		g_pTexturePauseLogo->Release();
		g_pTexturePauseLogo = NULL;
	}

	// テクスチャの開放
	if (g_pTextureContinue != NULL)
	{
		g_pTextureContinue->Release();
		g_pTextureContinue = NULL;
	}

	// テクスチャの開放
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();
		g_pTextureRetry = NULL;
	}

	// テクスチャの開放
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();
		g_pTextureQuit = NULL;
	}
}

//=========================================================================================================================
// ポーズの更新処理
//=========================================================================================================================
void UpdatePause(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	int nFade = GetFade();

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			switch (g_Pause_Manu)
			{
			case PAUSE_MENU_CONTINUE:
				SetPause(false);
				break;
			case PAUSE_MENU_RETRY:
				SetFade(FADE_OUT, MODE_GAME);
				break;
			case PAUSE_MENU_QUIT:
				SetFade(FADE_OUT, MODE_TITLE);
				break;
			}
		}


		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_Pause_Manu += 1;

			if (g_Pause_Manu > PAUSE_MENU_QUIT)
			{
				g_Pause_Manu = PAUSE_MENU_CONTINUE;
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_Pause_Manu -= 1;

			if (g_Pause_Manu < PAUSE_MENU_CONTINUE)
			{
				g_Pause_Manu = PAUSE_MENU_QUIT;
			}
		}


		for (int nPause = 0; nPause < MAX_PAUSE_TYPE; nPause++)
		{
			if (g_Pause_Manu == 0)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// 頂点カラーの設定
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 5:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_Pause_Manu == 1)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				case 5:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				}
			}
			else if (g_Pause_Manu == 2)
			{
				switch (nPause)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;		  
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = NOT_SELECT_COLOR;
					pVtx[1].col = NOT_SELECT_COLOR;
					pVtx[2].col = NOT_SELECT_COLOR;
					pVtx[3].col = NOT_SELECT_COLOR;
					break;
				case 5:
					// 頂点カラーの設定
					pVtx[0].col = SELECT_COLOR;
					pVtx[1].col = SELECT_COLOR;
					pVtx[2].col = SELECT_COLOR;
					pVtx[3].col = SELECT_COLOR;
					break;
				}
			}

			pVtx += VTX_NUM;
		}

		// 頂点バッファをアンロックする
		g_pVtxBuffPause->Unlock();
	}
}

//=========================================================================================================================
// ポーズの描画処理
//=========================================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_PAUSE_TYPE; nCnt++)
	{
		// テクスチャの設定
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTexturePauseBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTexturePause);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTexturePauseLogo);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureContinue);
			break;
		case 4:
			pDevice->SetTexture(0, g_pTextureRetry);
			break;
		case 5:
			pDevice->SetTexture(0, g_pTextureQuit);
			break;
		default:
			break;
		}

		// ポーズの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCnt * VTX_NUM,						// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}


//
//
//