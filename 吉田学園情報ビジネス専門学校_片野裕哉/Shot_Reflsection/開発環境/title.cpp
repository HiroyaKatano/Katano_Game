//=========================================================================================================================
//
// タイトル [title.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureTitleBG = NULL;			// タイトル背景テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			// タイトルロゴテクスチャ
LPDIRECT3DTEXTURE9 g_pTextureTitleLogoShadow = NULL;	// タイトルロゴ影テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureEnterSign = NULL;			// エンターサインテクスチャ
D3DXVECTOR3 g_posTitleBG; 								// タイトル背景の位置
D3DXVECTOR3 g_posTitleLogo;								// タイトルロゴの位置
D3DXVECTOR3 g_posTitleLogoShadow;						// タイトルロゴ影の位置
D3DXVECTOR3 g_posEnterSign;								// エンターサインの位置
D3DXCOLOR g_colorEnterSign;								// エンターサインの色
float g_fBGTexU = 0;
float g_fBGTexV = 0;
ENTERSTATE g_enterstate;
int g_nEnterSignTimer;

//=========================================================================================================================
// タイトルの初期化処理
//=========================================================================================================================
HRESULT InitTitle(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg001.png", &g_pTextureTitleBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title001.png", &g_pTextureTitleLogoShadow);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title002.png", &g_pTextureTitleLogo);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title003.png", &g_pTextureEnterSign);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TYPE_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	g_enterstate = ENTERSTATE_WAIT;
	g_nEnterSignTimer = 0;

	// タイトル背景の中心座標
	g_posTitleBG.x = SCREEN_WIDTH / 2;
	g_posTitleBG.y = SCREEN_HEIGTH / 2;

	// タイトルロゴ影の中心座標
	g_posTitleLogoShadow.x = SCREEN_WIDTH / 2;
	g_posTitleLogoShadow.y = -50.0f;

	// タイトルロゴの中心座標
	g_posTitleLogo.x = SCREEN_WIDTH / 2;
	g_posTitleLogo.y = -45.0f;

	// エンターサインの中心座標
	g_posEnterSign.x = SCREEN_WIDTH / 2;
	g_posEnterSign.y = 850.0f;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	g_posTitleBG = D3DXVECTOR3(g_posTitleBG.x, g_posTitleBG.y, 0.0f);
	g_posTitleLogoShadow = D3DXVECTOR3(g_posTitleLogoShadow.x, g_posTitleLogoShadow.y, 0.0f);
	g_posTitleLogo = D3DXVECTOR3(g_posTitleLogo.x, g_posTitleLogo.y, 0.0f);
	g_posEnterSign = D3DXVECTOR3(g_posEnterSign.x, g_posEnterSign.y, 0.0f);

	// 頂点カラーの設定
	g_colorEnterSign = ENTER_SIGN_COLOR_OFF;

	for (int nCntTitle = 0; nCntTitle < MAX_TYPE_TITLE; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// タイトル背景
			pVtx[0].pos = D3DXVECTOR3(600, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(600, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TITLE_BG_SIZE_X - 600, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TITLE_BG_SIZE_X - 600, 0, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_BG_COLOR;
			pVtx[1].col = TITLE_BG_COLOR;
			pVtx[2].col = TITLE_BG_COLOR;
			pVtx[3].col = TITLE_BG_COLOR;
			break;
		case 1:
			// タイトルロゴ影
			pVtx[0].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[1].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[2].col = TITLE_LOGOSHADOW_COLOR;
			pVtx[3].col = TITLE_LOGOSHADOW_COLOR;
			break;
		case 2:
			// タイトルロゴ
			pVtx[0].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_LOGO_COLOR;
			pVtx[1].col = TITLE_LOGO_COLOR;
			pVtx[2].col = TITLE_LOGO_COLOR;
			pVtx[3].col = TITLE_LOGO_COLOR;
			break;
		case 3:
			// エンターサイン
			pVtx[0].pos = D3DXVECTOR3(g_posEnterSign.x - (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y + (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posEnterSign.x - (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y - (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posEnterSign.x + (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y + (FLASHING_ENTER_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posEnterSign.x + (FLASHING_ENTER_SIZE_X / 2), g_posEnterSign.y - (FLASHING_ENTER_SIZE_Y / 2), 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = g_colorEnterSign;
			pVtx[1].col = g_colorEnterSign;
			pVtx[2].col = g_colorEnterSign;
			pVtx[3].col = g_colorEnterSign;
			break;
		default:
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

		pVtx += 4;
	}


	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//=========================================================================================================================
// タイトルの終了処理
//=========================================================================================================================
void UninitTitle(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// タイトル背景テクスチャの開放
	if (g_pTextureTitleBG != NULL)
	{				   
		g_pTextureTitleBG->Release();
		g_pTextureTitleBG = NULL;
	}

	// タイトルロゴテクスチャの開放
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}

	// タイトルロゴ影テクスチャの開放
	if (g_pTextureTitleLogoShadow != NULL)
	{
		g_pTextureTitleLogoShadow->Release();
		g_pTextureTitleLogoShadow = NULL;
	}

	// エンターサインテクスチャの開放
	if (g_pTextureEnterSign != NULL)
	{
		g_pTextureEnterSign->Release();
		g_pTextureEnterSign = NULL;
	}
}

//=========================================================================================================================
// タイトルの更新処理
//=========================================================================================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	// 変数宣言
	int nFade = GetFade();

	g_fBGTexU -= MOVE_TITLE_BG_U;
	g_fBGTexV -= MOVE_TITLE_BG_V;



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// タイトル背景
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fBGTexU, 1.0f + g_fBGTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + g_fBGTexU, 0.0f + g_fBGTexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + g_fBGTexU, 1.0f + g_fBGTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fBGTexU, 0.0f + g_fBGTexV);

	// タイトルロゴ影
	pVtx[4].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posTitleLogoShadow.x - (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y + (TITLE_LOGOB_SIZE_Y / 2), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posTitleLogoShadow.x + (TITLE_LOGOB_SIZE_X / 2), g_posTitleLogoShadow.y - (TITLE_LOGOB_SIZE_Y / 2), 0.0f);

	// タイトルロゴ
	pVtx[8].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[9].pos = D3DXVECTOR3(g_posTitleLogo.x - (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[10].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y + (TITLE_LOGOF_SIZE_Y / 2), 0.0f);
	pVtx[11].pos = D3DXVECTOR3(g_posTitleLogo.x + (TITLE_LOGOF_SIZE_X / 2), g_posTitleLogo.y - (TITLE_LOGOF_SIZE_Y / 2), 0.0f);

	// エンターサイン
	if (g_posTitleLogoShadow.y < 300.0f)
	{
		g_posTitleLogoShadow.y += 2.0f;
		g_posTitleLogo.y += 2.0f;
	}
	else if (g_posTitleLogoShadow.y >= 300.0f)
	{
		g_nEnterSignTimer += 1;

		if (g_enterstate == ENTERSTATE_WAIT)
		{
			if (g_nEnterSignTimer % 60 < 30)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_ON;
			}
			else if (g_nEnterSignTimer % 60 >= 30)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_OFF;
			}
		}
		else if (g_enterstate == ENTERSTATE_ACTIVE)
		{
			if (g_nEnterSignTimer % 10 < 5)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_ON;
			}
			else if (g_nEnterSignTimer % 10 >= 5)
			{
				g_colorEnterSign = ENTER_SIGN_COLOR_OFF;
			}
		}

	}

	pVtx[12].col = g_colorEnterSign;
	pVtx[13].col = g_colorEnterSign;
	pVtx[14].col = g_colorEnterSign;
	pVtx[15].col = g_colorEnterSign;

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_TITLE);
		}
		else if (nFade == FADE_NONE && g_posTitleLogoShadow.y >= 250.0f)
		{
			SetFade(FADE_OUT, MODE_GAME);
			g_enterstate = ENTERSTATE_ACTIVE;
		}

		// タイトルロゴ影
		g_posTitleLogoShadow.y = 300.0f;

		// タイトルロゴ
		g_posTitleLogo.y = 305.0f;
	}
}

//=========================================================================================================================
// タイトルの描画処理
//=========================================================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		// テクスチャの設定
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureTitleBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureTitleLogoShadow);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureTitleLogo);
			break;
		case 3:
			pDevice->SetTexture(0, g_pTextureEnterSign);
			break;
		default:
			break;
		}

		// タイトルの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCnt * 4,						// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}
