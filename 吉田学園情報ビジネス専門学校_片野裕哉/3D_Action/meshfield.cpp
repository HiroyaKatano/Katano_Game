//=========================================================================================================================
//
// メッシュフィールド [meshfield.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "meshfield.h"

//
// マクロ定義
//
#define MAX_FIELD (256)			// 床の最大数
#define FIELD_SIZE (200.0f)		// 床1枚の大きさ
#define FIELD_X (2)				// 床の横
#define FIELD_Z (2)				// 床の奥行

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		// インデックスバッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;			// テクスチャへのポインタ
D3DXVECTOR3 g_posMeshField;								// 位置
D3DXVECTOR3 g_rotMeshField;								// 向き
D3DXMATRIX g_mtxWorldMeshField;							// ワールドマトリックス

//
// 初期化処理
//
HRESULT InitMeshField(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field003.jpg", &g_pTextureMeshField);

	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ((FIELD_X + 1) * (FIELD_Z + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	// 
	//for (int nCntZ = 0; nCntZ < FIELD_Z + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < FIELD_X + 1; nCntX++)
	//	{
	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].pos = 
	//			D3DXVECTOR3(g_posMeshField.x - ((FIELD_SIZE / 2) * FIELD_X) / (1 - (float)nCntX),
	//						g_posMeshField.y, g_posMeshField.z + ((FIELD_SIZE / 2) * FIELD_Z)) / (1 - (float)nCntZ);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].tex = D3DXVECTOR2(0.0f + (float)nCntX, 0.0f + (float)nCntZ);
	//	}
	//}
	pVtx[0].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posMeshField.x - 0.0f, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + 0.0f);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshField.x + 0.0f, g_posMeshField.y, g_posMeshField.z - 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshField.x - 0.0f, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	// 頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();


	// インデックスバッファの生成
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((FIELD_X * FIELD_Z) * 3 + (FIELD_Z - 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	WORD *pIdx;					// インデックス情報へのポインタ

	// インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitMeshField(void)
{
	// テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// インデックスバッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}


//
// 更新処理
//
void UpdateMeshField(void)
{

}


//
// 描画処理
//
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,							// プリミティブの種類
		0,												// 
		0,												// 
		((FIELD_X + 1) * (FIELD_Z + 1)),				// 頂点の数
		0,												// 描画を開始する頂点インデックス
		FIELD_X * FIELD_Z * 2  + (FIELD_Z - 1) * 4);	// 描画するプリミティブの数
}