//=========================================================================================================================
//
// タイトル [title.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "title.h"
#include "input.h"
#include "fade.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_TYPE_TITLE (3)

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// 頂点バッファ
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TYPE_TITLE] = {};	// タイトル背景テクスチャ

D3DXVECTOR3 g_posTitleName; 								// タイトル名の位置
D3DXVECTOR3 g_posEnterSign; 								// エンターサインの位置

TITLE g_aTitle[MAX_TYPE_TITLE];								// タイトルの情報

char *g_aTextureTitleFile[TEX_TITLE_LABEL_MAX] =
{
	"data\\TEXTURE\\title_bg.jpg",			// タイトル背景
	"data\\TEXTURE\\title_name.png",		// タイトル名
	"data\\TEXTURE\\enter_sign.png",
};		// タイトル画像のファイル一覧

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
	
	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, g_aTextureTitleFile[nCnt], &g_apTextureTitle[nCnt]);

		// 情報の初期化
		g_aTitle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

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

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 中心座標の設定
	g_posTitleName = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f);
	g_posEnterSign = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 0.0f);

	for (int nCntTitle = 0; nCntTitle < MAX_TYPE_TITLE; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// タイトル背景
			pVtx[0].pos = D3DXVECTOR3(0.0f, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TITLE_BG_SIZE_X, TITLE_BG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TITLE_BG_SIZE_X, 0.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_NORMAL_COLOR;
			pVtx[1].col = TITLE_NORMAL_COLOR;
			pVtx[2].col = TITLE_NORMAL_COLOR;
			pVtx[3].col = TITLE_NORMAL_COLOR;
			break;
		case 1:
			// タイトル背景
			pVtx[0].pos = D3DXVECTOR3(g_posTitleName.x - TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y + TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTitleName.x - TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y - TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTitleName.x + TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y + TITLE_NAME_VERTEX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTitleName.x + TITLE_NAME_VERTEX_SIZE_X, g_posTitleName.y - TITLE_NAME_VERTEX_SIZE_Y, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_NAME_COLOR;
			pVtx[1].col = TITLE_NAME_COLOR;
			pVtx[2].col = TITLE_NAME_COLOR;
			pVtx[3].col = TITLE_NAME_COLOR;
			break;
		case 2:
			// タイトル背景
			pVtx[0].pos = D3DXVECTOR3(g_posEnterSign.x - ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y + ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posEnterSign.x - ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y - ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posEnterSign.x + ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y + ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posEnterSign.x + ENTER_SIGN_VERTEX_SIZE_X, g_posEnterSign.y - ENTER_SIGN_VERTEX_SIZE_Y, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = TITLE_NORMAL_COLOR;
			pVtx[1].col = TITLE_NORMAL_COLOR;
			pVtx[2].col = TITLE_NORMAL_COLOR;
			pVtx[3].col = TITLE_NORMAL_COLOR;
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
	for (int nCnt = 0; nCnt < MAX_TYPE_TITLE; nCnt++)
	{
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
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

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// タイトル背景
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_TITLE);
		}
		else if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
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
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
			break;
		case 1:
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
			break;
		case 2:
			pDevice->SetTexture(0, g_apTextureTitle[nCnt]);
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
