//=========================================================================================================================
//
// DirectX_Sample [main.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define CLASS_NAME "WindowClass"		// ウィンドウクラスの名前
#define WINDOW_NAME "3D_GAME"			// ウィンドウの名前
#define WINDOW_COLOR_R	(0)				// ウィンドウの色(赤)
#define WINDOW_COLOR_G	(0)				// ウィンドウの色(緑)
#define WINDOW_COLOR_B	(0)				// ウィンドウの色(青)
#define WINDOW_COLOR_A	(0)				// ウィンドウの色(透明度)

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);							// 初期化処理
void Uninit(void);																	// 終了処理
void Update(void);																	// 更新処理
void Draw(void);																	// 描画処理
void DrawFPS(void);																	// fps表示

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;					// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3Dデバイスへのポインタ(描画処理に必要)
LPD3DXFONT g_pFont = NULL;					// フォントへのポインタ
int g_nCountFPS;							// FPSカウンタ
MODE g_mode = MODE_TITLE;					// モードの種類

//=========================================================================================================================
// メイン関数
//=========================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};

	HWND hWnd;		// ウィンドウハンドル(識別子)
	MSG  msg;		// メッセージを格納する


	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);



	// ウィンドウの生成
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// 処理実行最終時刻
	DWORD dwFPSLastTime;	// FPS計測最終時刻
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwFrameCount;		// フレームカウント

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();	// 現在時刻を設定
	dwFrameCount = 0;

	//メッセージループ
	while (1)
	{	// Windowsの処理
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// メッセージを取得しなかった場合 "0" を返す
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録解除
	UnregisterClass(
		CLASS_NAME,
		wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================================================================================================
// ウィンドウプロシージャ
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUITメッセージを返す
		break;
	case WM_CLOSE:
		// ×ボタンの設定
		nID = MessageBox(NULL, "ウィンドウを閉じますか？", "確認", (MB_YESNO | MB_ICONEXCLAMATION));
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返す
		}
		else
		{
			return 0;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//// ESCAPEキーの設定
			//nID = MessageBox(NULL, "ウィンドウを閉じますか？", "確認", (MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST));
			//if (nID == IDYES)
			//{
			DestroyWindow(hWnd);	// WM_DESTROYメッセージを返す
									//}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// DIrect3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ディスプレイモードの取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// スクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// スクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ソース(描画元)の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

																			// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 縮小時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 拡大時 補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U値 繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V値 繰り返し

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// α値の合成


	D3DXCreateFont(
		g_pD3DDevice,
		18,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	// 入力の初期化
	InitKeyboard(hInstance, hWnd);

	

	InitFade(MODE_TITLE);

	// モードのセット処理
	SetMode(g_mode);

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void Uninit(void)
{
	// フェードの終了処理
	UninitFade();

	// キー入力の終了処理
	UninitKeyboard();

	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	// タイトル画面の終了処理
	//	UninitTitle();
	//	break;

	//case MODE_GAME:
	//	// ゲーム画面の終了処理
	//	UninitGame();
	//	break;

	//case MODE_RESULT:
	//	// リザルト画面の終了処理
	//	UninitResult();
	//	break;
	//}

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// フォントの開放
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void Update(void)
{
	// 入力の更新
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		// タイトル画面の更新処理
		UpdateTitle();
		break;

	case MODE_GAME:
		// ゲーム画面の更新処理
		UpdateGame();
		break;

	case MODE_RESULT:
		// リザルト画面の更新処理
		UpdateResult();
		break;
	}

	// フェードの更新処理
	UpdateFade();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void Draw(void)
{
	// バックバッファ&Zバッファのクリア(画面クリア)
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(WINDOW_COLOR_R, WINDOW_COLOR_G, WINDOW_COLOR_B, WINDOW_COLOR_A),
		1.0f,
		0);

	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			// タイトル画面の描画処理
			DrawTitle();
			break;

		case MODE_GAME:
			// ゲーム画面の描画処理
			DrawGame();

#ifdef _DEBUG
			// 情報の描画
			DrawInfo();
#endif
			break;
		case MODE_RESULT:
			// リザルト画面の描画処理
			DrawResult();
			break;
		}
		//
		DrawFade();

#ifdef _DEBUG
		//FPSの描画処理
		DrawFPS();
#endif

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================================================
// デバイスの取得
//=========================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================================
// FPSの描画
//=========================================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// テキストの描画
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_BOTTOM,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//-----------------------------------------------------------------------------
// モードの設定
//-----------------------------------------------------------------------------
void SetMode(MODE mode)
{
	//現在の処理を終了
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの終了処理
		UninitTitle();
		break;

	case MODE_GAME:
		//ゲーム画面の終了処理
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}

	//遷移後の処理を初期化
	switch (mode)
	{
	case MODE_TITLE:
		//タイトルの初期化処理
		InitTitle();
		break;

	case MODE_GAME:
		//ゲームの初期化処理
		InitGame();
		break;

	case MODE_RESULT:
		//リザルトの初期化処理
		InitResult();
		break;

	default:
		break;
	}

	g_mode = mode;
}

//=========================================================================================================================
// モードの取得
//=========================================================================================================================
MODE GetMode(void)
{
	return g_mode;
}

//-----------------------------------------------------------------------------
// テキストの表示
//-----------------------------------------------------------------------------
void DrawInfo(void)
{
	Camera *pCamera = GetCamera();
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024];

	int nNum = sprintf(&aStr[0], "[カメラの視点　　　　:(%.2f : %.2f : %.2f)]\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nNum += sprintf(&aStr[nNum], "[カメラの注視　　　　:(%.2f : %.2f : %.2f)]\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	nNum += sprintf(&aStr[nNum], "[カメラの向き　　　　:(%.2f)]\n", pCamera->rot.y);
	nNum += sprintf(&aStr[nNum], "[視点と注視点の距離　:(%.2f)]\n", pCamera->fDistance);
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "*** カメラ移動 ***\n");
	nNum += sprintf(&aStr[nNum], "前移動 : W\n");
	nNum += sprintf(&aStr[nNum], "後移動 : S\n");
	nNum += sprintf(&aStr[nNum], "左移動 : A\n");
	nNum += sprintf(&aStr[nNum], "右移動 : D\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "*** 視点操作 ***\n");
	nNum += sprintf(&aStr[nNum], "上移動 : Y\n");
	nNum += sprintf(&aStr[nNum], "下移動 : N\n");
	nNum += sprintf(&aStr[nNum], "左旋回 : Z\n");
	nNum += sprintf(&aStr[nNum], "右旋回 : C\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "*** 注視点操作 ***\n");
	nNum += sprintf(&aStr[nNum], "上移動 : T\n");
	nNum += sprintf(&aStr[nNum], "下移動 : B\n");
	nNum += sprintf(&aStr[nNum], "左旋回 : Q\n");
	nNum += sprintf(&aStr[nNum], "右旋回 : E\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "視点と注視点の距離調整 : U / M\n");
	nNum += sprintf(&aStr[nNum], "カメラの視点・注視点リセット : SPACE\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "*** モデル操作 ***\n");
	nNum += sprintf(&aStr[nNum], "[モデルの位置　　　　:(%.2f : %.2f : %.2f)]\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	nNum += sprintf(&aStr[nNum], "[モデルの移動量　　　:(%.2f : %.2f : %.2f)]\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);
	nNum += sprintf(&aStr[nNum], "移動 : [ ↑ / ↓ / ← / → ]\n");
	nNum += sprintf(&aStr[nNum], "上昇 : I\n");
	nNum += sprintf(&aStr[nNum], "下降 : K\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "[モデルの向き　　　　:(%.2f)]\n", pPlayer->rot.y);
	nNum += sprintf(&aStr[nNum], "[モデルの目的の向き　:(%.2f)]\n", pPlayer->rotDest.y);
	nNum += sprintf(&aStr[nNum], "左旋回 : LSHIFT\n");
	nNum += sprintf(&aStr[nNum], "右旋回 : RSHIFT\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "モデルの位置・向きリセット : ENTER\n");
	nNum += sprintf(&aStr[nNum], "\n");
	nNum += sprintf(&aStr[nNum], "*** カメラ追従処理 ***\n");
	if (pCamera->bFollow == true)
	{
		nNum += sprintf(&aStr[nNum], "ON / OFF ： [ F4 ] 【 現在：ON 】\n");
	}
	else if (pCamera->bFollow == false)
	{
		nNum += sprintf(&aStr[nNum], "ON / OFF ： [ F4 ] 【 現在：OFF 】\n");
	}
	nNum += sprintf(&aStr[nNum], "☆★☆ ブロックに当たるとリザルトへ ☆★☆\n");

	// テキストの描画
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}