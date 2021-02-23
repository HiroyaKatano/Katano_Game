////=========================================================================================================================
////
//// ゴール [goal.cpp]
//// Author:Hiroya Katano
////
////=========================================================================================================================
//#include "goal.h"
//
////========================================================================================================================
//// マクロ定義
////========================================================================================================================
//#define GOAL_SIZE_VERTEX_X (8.4f)	// ゴールの横半径
//#define GOAL_SIZE_Y (36.0f)			// ゴールの縦幅
//
////=========================================================================================================================
//// グローバル変数
////=========================================================================================================================
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;	// 頂点バッファ
//LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			// テクスチャ
//GOAL g_goal;										// ゴールの構造体
//
////=========================================================================================================================
//// ゴールの初期化処理
////=========================================================================================================================
//HRESULT InitGoal(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	// デバイスの取得
//	pDevice = GetDevice();
//
//	// テクスチャの読み込み
//	/*D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal_star.png", &g_pTextureGoal);*/
//
//	// 頂点バッファの生成
//	if (FAILED(pDevice->CreateVertexBuffer(
//		sizeof(VERTEX_2D) * MAX_GOAL * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffGoal,
//		NULL)))
//	{
//		return E_FAIL;
//	}
//
//	// ゴール情報の初期化
//	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
//	{
//		g_goal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_goal.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_goal.col = GOAL_COLOR;
//		g_goal.fWidth = GOAL_SIZE_VERTEX_X;
//		g_goal.fHeight = GOAL_SIZE_Y;
//		g_goal.bUse = false;
//	}
//
//	// 構造体のポインタ変数
//	VERTEX_2D *pVtx;
//
//	// 頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
//	{
//		//// 頂点座標の設定
//		//SetVertexGoal(nCntGoal);
//
//		pVtx[0].pos = D3DXVECTOR3(g_goal.pos.x, g_goal.pos.y + g_goal.fHeight, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_goal.pos.x, g_goal.pos.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y + g_goal.fHeight, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y, 0.0f);
//
//		// rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		// 頂点カラーの設定
//		pVtx[0].col = GOAL_COLOR;
//		pVtx[1].col = GOAL_COLOR;
//		pVtx[2].col = GOAL_COLOR;
//		pVtx[3].col = GOAL_COLOR;
//
//		// 頂点情報の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
//	}
//
//	// 頂点バッファをアンロックする
//	g_pVtxBuffGoal->Unlock();
//
//	return S_OK;
//}
//
////=========================================================================================================================
//// ゴールの終了処理
////=========================================================================================================================
//void UninitGoal(void)
//{
//	// 頂点バッファの開放
//	if (g_pVtxBuffGoal != NULL)
//	{
//		g_pVtxBuffGoal->Release();
//		g_pVtxBuffGoal = NULL;
//	}
//
//	// テクスチャの開放
//	if (g_pTextureGoal != NULL)
//	{
//		g_pTextureGoal->Release();
//		g_pTextureGoal = NULL;
//	}
//}
//
////=========================================================================================================================
//// ゴールの更新処理
////=========================================================================================================================
//void UpdateGoal(void)
//{
//	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
//	{
//		if (g_goal.bUse == true)
//		{
//			g_goal.pos += g_goal.move;
//
//			SetVertexGoal(nCntGoal);
//		}
//	}
//}
//
////=========================================================================================================================
//// ゴールの描画処理
////=========================================================================================================================
//void DrawGoal(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	// デバイスの取得
//	pDevice = GetDevice();
//
//	// 頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));
//
//	// 頂点フォ―マットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++)
//	{
//		if (g_goal.bUse == true)
//		{
//			// テクスチャの設定
//			pDevice->SetTexture(0, g_pTextureGoal);
//
//			// ゴールの描画
//			pDevice->DrawPrimitive(
//				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
//				nCntGoal * 4,								// 描画を開始する頂点インデックス
//				2);								// 描画するプリミティブの数
//		}
//	}
//}
//
////=========================================================================================================================
//// ゴールのセット処理
////=========================================================================================================================
//void SetGoal(D3DXVECTOR3 GoalPos, D3DXVECTOR3 GoalMove, float fGoalWigth, float fGoalHeight)
//{
//	GOAL *pGoal;
//	pGoal = &g_goal;
//
//	for (int nCntGoal = 0; nCntGoal < MAX_GOAL; nCntGoal++, pGoal++)
//	{
//		if (pGoal->bUse == false)
//		{
//			// 位置の設定
//			pGoal->pos = GoalPos;
//
//			pGoal->move = GoalMove;
//
//			pGoal->fWidth = fGoalWigth;
//
//			pGoal->fHeight = fGoalHeight;
//
//			SetVertexGoal(0);
//
//			pGoal->bUse = true;
//
//			break;
//		}
//	}
//}
//
//
////=========================================================================================================================
//// 
////=========================================================================================================================
//void SetVertexGoal(int nIdx)
//{
//	VERTEX_2D *pVtx;
//	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx += nIdx * 4;
//
//
//	pVtx[0].pos = D3DXVECTOR3(g_goal.pos.x, g_goal.pos.y + g_goal.fHeight, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_goal.pos.x, g_goal.pos.y, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y + g_goal.fHeight, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_goal.pos.x + g_goal.fWidth, g_goal.pos.y, 0.0f);
//
//	// 頂点カラーの設定
//	pVtx[0].col = GOAL_COLOR;
//	pVtx[1].col = GOAL_COLOR;
//	pVtx[2].col = GOAL_COLOR;
//	pVtx[3].col = GOAL_COLOR;
//
//	// 頂点情報の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
//
//
//	// 頂点バッファの開放
//	g_pVtxBuffGoal->Unlock();
//}
//
////=========================================================================================================================
//// ゴールの取得
////=========================================================================================================================
//GOAL *GetGoal(void)
//{
//	return &g_goal;
//}