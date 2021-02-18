//=========================================================================================================================
//
// 立体 [Solid.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Solid.h"

//
// マクロ定義
//
#define MAX_SOLID (256)			// 立体の最大数
#define SOLID_SIZE (200)			// 立体の大きさ
#define SOLID_X (2)				// 立体の横
#define SOLID_Y (2)				// 立体の縦

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;			// 中心座標
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	bool bUse;					// 使用しているかどうか
}SOLID;

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSolid = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSolid = NULL;		// インデックスバッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSolid = NULL;			// テクスチャへのポインタ
SOLID g_aSolid[MAX_SOLID];								// 立体の情報

													//
													// 初期化処理
													//
HRESULT InitSolid(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	SOLID *pSolid = &g_aSolid[0];						// 立体の構造体のポインタ

													// デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		pSolid->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSolid->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSolid->bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall003.jpg", &g_pTextureSolid);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ((SOLID_X + 1) * (SOLID_Y + 1)) * MAX_SOLID,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSolid,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

										// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffSolid->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[4].pos = D3DXVECTOR3(pSolid->pos.x + 0.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[5].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[6].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
		pVtx[7].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y, pSolid->pos.z);
		pVtx[8].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

		pVtx += ((SOLID_X + 1) * (SOLID_Y + 1));
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSolid->Unlock();

	// インデックスバッファの生成
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((SOLID_X * SOLID_Y) * 3 + (SOLID_Y - 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSolid,
		NULL)))
	{
		return E_FAIL;
	}

	WORD *pIdx;					// インデックス情報へのポインタ

								// インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffSolid->Lock(0, 0, (void**)&pIdx, 0);

	// 番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	// インデックスバッファをアンロックする
	g_pIdxBuffSolid->Unlock();

	for (int SetCntSolid = 0; SetCntSolid < 2; SetCntSolid++)
	{
		SetSolid(D3DXVECTOR3(-50.0f + SOLID_SIZE * SetCntSolid, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSolid(D3DXVECTOR3(50.0f + -SOLID_SIZE * SetCntSolid, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		SetSolid(D3DXVECTOR3(100.0f, 0.0f, 50.0f + -SOLID_SIZE * SetCntSolid), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
		SetSolid(D3DXVECTOR3(-100.0f, 0.0f, -50.0f + SOLID_SIZE * SetCntSolid), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	}

	return S_OK;
}


//
// 終了処理
//
void UninitSolid(void)
{
	// テクスチャの開放
	if (g_pTextureSolid != NULL)
	{
		g_pTextureSolid->Release();
		g_pTextureSolid = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffSolid != NULL)
	{
		g_pVtxBuffSolid->Release();
		g_pVtxBuffSolid = NULL;
	}

	// インデックスバッファの破棄
	if (g_pVtxBuffSolid != NULL)
	{
		g_pIdxBuffSolid->Release();
		g_pIdxBuffSolid = NULL;
	}
}


//
// 更新処理
//
void UpdateSolid(void)
{

}


//
// 描画処理
//
void DrawSolid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	SOLID *pSolid = &g_aSolid[0];						// 立体の構造体のポインタ
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用マトリックス


	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		if (pSolid->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pSolid->mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pSolid->rot.y, pSolid->rot.x, pSolid->rot.z);
			D3DXMatrixMultiply(&pSolid->mtxWorld, &pSolid->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pSolid->pos.x, pSolid->pos.y, pSolid->pos.z);
			D3DXMatrixMultiply(&pSolid->mtxWorld, &pSolid->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pSolid->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSolid, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffSolid);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSolid);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,							// プリミティブの種類
				0,												// 
				0,												// 
				((SOLID_X + 1) * (SOLID_Y + 1)),				// 頂点の数
				0,												// 描画を開始する頂点インデックス
				SOLID_X * SOLID_Y * 2 + (SOLID_Y - 1) * 4);		// 描画するプリミティブの数
		}
	}
}


//
// 立体の配置
//
void SetSolid(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 構造体のポインタ変数
	SOLID *pSolid = &g_aSolid[0];

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		if (pSolid->bUse == false)
		{
			// 位置の設定
			pSolid->pos = pos;

			// 角度の設定
			pSolid->rot = rot;

			// 頂点座標の設定
			SetVertexSolid(nCnt);

			// 使用状態をtrueにする
			pSolid->bUse = true;

			break;
		}
	}
}


//-----------------------------------------------------------------
// 立体の頂点座標の設定
//-----------------------------------------------------------------
void SetVertexSolid(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_3D *pVtx;
	SOLID *pSolid = &g_aSolid[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSolid->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nIdx * ((SOLID_X + 1) * (SOLID_Y + 1));
	pSolid += nIdx;

	// 頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	//pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	//pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	//pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[4].pos = D3DXVECTOR3(pSolid->pos.x + 0.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[5].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[6].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	pVtx[7].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y, pSolid->pos.z);
	pVtx[8].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);

	// 頂点バッファをアンロックする
	g_pVtxBuffSolid->Unlock();
}