//=========================================================================================================================
//
// ゴールアイテム [goal.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "goal.h"
#include "camera.h"

//
// マクロ定義
//

//
// グローバル変数
//
GOAL g_goal;								// ゴールアイテム
char *g_aModel_G_File[MODEL_G_LABEL_MAX] =
{
	"data\\MODEL\\block000.x"		// ブロック
};		// モデルのファイル一覧
LPDIRECT3DTEXTURE9 g_apTextureModel_G[256] = {};	// テクスチャへのポインタ

//
// 初期化処理
//
void InitGoal(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_goal.pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	g_goal.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.nNumModel = 0;

	for (int nCntModel = 0; nCntModel < MAX_MODEL_G; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			g_aModel_G_File[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_goal.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_goal.aModel[nCntModel].nNumMatModel,
			&g_goal.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// 頂点数
		DWORD sizeFVF = NULL;		// 頂点フォーマットのサイズ
		BYTE *pVtxBuff = NULL;		// 頂点バッファのポインタ

		D3DXMATERIAL *pMat;	// マテリアルへのポインタ

		g_goal.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_goal.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// 頂点数を取得
		nNumvtx = g_goal.aModel[nCntModel].pMeshModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_goal.aModel[nCntModel].pMeshModel->GetFVF());

		// 頂点バッファをロック
		g_goal.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入

			// ↓全ての頂点数を比較してゴールアイテムの最小値・最大値を抜き出す
			if (g_goal.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_goal.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_goal.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_goal.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_goal.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_goal.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ↑全ての頂点数を比較してゴールアイテムの最小値・最大値を抜き出す

			pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分ポインタを進める
		}

		g_goal.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_goal.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goal.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// ↓このファイル名を使用してテクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel_G[nCntMat]);
			}// ↑このファイル名を使用してテクスチャを読み込む
		}

		g_goal.nNumModel++;
	}

	// 全パーツの階層構造設定
	g_goal.aModel[0].nIdxModelParent = -1;						// 親のインデックスを設定
	g_goal.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置の初期設定
	g_goal.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_goal.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_goal.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定
}


//
// 終了処理
//
void UninitGoal(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_G; nCntModel++)
	{
		// メッシュの破棄
		if (g_goal.aModel[nCntModel].pMeshModel != NULL)
		{
			g_goal.aModel[nCntModel].pMeshModel->Release();
			g_goal.aModel[nCntModel].pMeshModel = NULL;
		}

		// マテリアルの破棄
		if (g_goal.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_goal.aModel[nCntModel].pBuffMatModel->Release();
			g_goal.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// 更新処理
//
void UpdateGoal(void)
{
}


//
// 描画処理
//
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

												// ゴールアイテムのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_goal.mtxWorld);

	// ゴールアイテムの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.rot.y, g_goal.rot.x, g_goal.rot.z);

	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxRot);

	// ゴールアイテムの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_goal.pos.x, g_goal.pos.y, g_goal.pos.z);

	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxTrans);

	// ゴールアイテムのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_goal.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_goal.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// 計算用マトリックス
		D3DXMATRIX mtxParent;							// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_goal.aModel[nCntModel].mtxWorld);

		// ゴールアイテムの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.aModel[nCntModel].rot.y, g_goal.aModel[nCntModel].rot.x, g_goal.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld, &g_goal.aModel[nCntModel].mtxWorld, &mtxRot);

		// ゴールアイテムの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_goal.aModel[nCntModel].pos.x, g_goal.aModel[nCntModel].pos.y, g_goal.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld, &g_goal.aModel[nCntModel].mtxWorld, &mtxTrans);

		// 各パーツの親のマトリックスを設定
		if (g_goal.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_goal.aModel[g_goal.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_goal.mtxWorld;
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld,
			&g_goal.aModel[nCntModel].mtxWorld,
			&mtxParent);

		// 各パーツのワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &g_goal.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_goal.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goal.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// モデル(パーツ)の描画
		 // マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureModel_G[nCntMat]);

			// ゴールアイテム(パーツ)の描画
			g_goal.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}


//
// ゴールアイテムの取得
//
GOAL *GetGoal(void)
{
	return &g_goal;
}
