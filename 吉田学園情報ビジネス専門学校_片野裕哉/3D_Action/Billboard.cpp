//=========================================================================================================================
//
// ビルボード [Billboard.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Billboard.h"
#include "input.h"
#include "camera.h"

//
//
//
#define BILLBOARD_SPD (2.0f)
#define BILLBOARD_SPD_DECAY (0.4f)

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			// テクスチャへのポインタ
BILLBOARD g_Billboard;

//
// 初期化処理
//
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tree000.png", &g_pTextureBillboard);

	g_Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Billboard.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Billboard.pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	// 
	pVtx[0].pos = D3DXVECTOR3(g_Billboard.pos.x - 25.0f, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Billboard.pos.x - 25.0f, g_Billboard.pos.y + 50.0f, g_Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Billboard.pos.x + 25.0f, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Billboard.pos.x + 25.0f, g_Billboard.pos.y + 50.0f, g_Billboard.pos.z);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitBillboard(void)
{
	// テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

}


//
// 更新処理
//
void UpdateBillboard(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Billboard.move.x += sinf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z += cosf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Billboard.move.x -= sinf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z -= cosf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Billboard.move.x -= cosf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z += sinf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Billboard.move.x += cosf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z -= sinf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	g_Billboard.move.x += (0.0f - g_Billboard.move.x) * BILLBOARD_SPD_DECAY;
	g_Billboard.move.z += (0.0f - g_Billboard.move.z) * BILLBOARD_SPD_DECAY;

	g_Billboard.pos.x += g_Billboard.move.x;
	g_Billboard.pos.z += g_Billboard.move.z;
}


//
// 描画処理
//
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ

	D3DXMATRIX mtxView;								// ビューマトリックス取得用

	D3DXMATRIX mtxTrans;							// 計算用マトリックス

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファの更新
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Billboard.mtxWorld);

	// ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_Billboard.mtxWorld, NULL, &mtxView);	// 逆行列を求める
	g_Billboard.mtxWorld._41 = 0.0f;
	g_Billboard.mtxWorld._42 = 0.0f;
	g_Billboard.mtxWorld._43 = 0.0f;

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Billboard.pos.x, g_Billboard.pos.y, g_Billboard.pos.z);

	D3DXMatrixMultiply(&g_Billboard.mtxWorld, &g_Billboard.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Billboard.mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	// デスティネーション(描画先)の合成方法の設定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数


	// デスティネーション(描画先)の合成方法の設定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}