//=============================================================================
//
// レンダリング [renderer.cpp]
// Author : Hiroya Katano
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include <stdio.h>
#include "manager.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数:
//*****************************************************************************


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CRenderer::CRenderer()
{


}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CRenderer::~CRenderer()
{


}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

																// デバイスの生成
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンド(α値の合成)の設定
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ソース(描画元)の合成方法の設定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

																			// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 縮小時 補間
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 拡大時 補間
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U値 繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V値 繰り返し

																			// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数(初期値はD3DTA_TEXTURE)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// 2番目のアルファ引数(初期値はD3DTA_CURRENT)

#ifdef _DEBUG
																			// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 27, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CRenderer::Uninit()
{

#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CRenderer::Update()
{
	CScene::UpdateAll();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CRenderer::Draw()
{
	//CFade *pFade = CManager::GetFade();

	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();

		//pFade->Draw();

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// 各種データ表示
			DrawData();
		}
#endif
		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS = GetFPS();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

#ifdef _DEBUG
//=============================================================================
// 各種データ表示
//=============================================================================
void CRenderer::DrawData(void)
{
	int nCountFPS = GetFPS();

	CPlayer *pPlayer = CGame::GetPlayer();
	int SelectBullet = *pPlayer->GetPlayerBullet();

	int GameCntTime = CGame::GameCntTime();

	CEnemy *pEnemy = CGame::GetEnemy();
	float EnePosDistance = pEnemy->GetDistance();
	float AngleLissajous = pEnemy->GetAngleL();

	float fAlpha = CGame::GetAlpha();
	float fBeta = CGame::GetBeta();
	float fDelta = CGame::GetDelta();
	float fRadiusA = CGame::GetRadiusA();
	float fRadiusB = CGame::GetRadiusB();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024];

	int nNum = sprintf(&aStr[0], "FPS:%d\n", nCountFPS);
	nNum += sprintf(&aStr[nNum], "[通常弾への切替 : キーボードの１ ]\n");
	nNum += sprintf(&aStr[nNum], "[追尾弾への切替 : キーボードの２ ]\n");
	if (SelectBullet == CBullet::USEBULLET_NONE)
	{
		nNum += sprintf(&aStr[nNum], "[プレイヤーの弾の種類 : 通常弾 ]\n");
	}
	else if (SelectBullet == CBullet::USEBULLET_TRACKING)
	{
		nNum += sprintf(&aStr[nNum], "[プレイヤーの弾の種類 : 追尾弾 ]\n");
	}
	nNum += sprintf(&aStr[nNum], "[次のリサージュ曲線の移動敵出現まで残り : %ds ]\n", NEXT_LISSAJOUS /60 - GameCntTime/60);
	nNum += sprintf(&aStr[nNum], "[EnemyPos ～ posの距離 : %.2fs ]\n", EnePosDistance);
	nNum += sprintf(&aStr[nNum], "[EnemyPosを原点としたときのposの角度 : %.2f ]\n", AngleLissajous);
	nNum += sprintf(&aStr[nNum], "\n<TABを押した際に生成されるリサージュ曲線の各種データ>\n");
	nNum += sprintf(&aStr[nNum], "[ Alpha の値 : %.1f ]\n", fAlpha);
	nNum += sprintf(&aStr[nNum], "[ Beta  の値 : %.1f ]\n", fBeta);
	nNum += sprintf(&aStr[nNum], "[ Delta の値 : %.1f ]\n", fDelta);
	nNum += sprintf(&aStr[nNum], "[RadiusAの値 : %.1f ]\n", fRadiusA);
	nNum += sprintf(&aStr[nNum], "[RadiusBの値 : %.1f ]\n", fRadiusB);

	// テキスト描画
	m_pFont->DrawText(NULL, aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
