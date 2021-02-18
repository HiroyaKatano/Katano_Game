////=========================================================================================================================
////
//// モデル [model.cpp]
//// Author:Katano Hiroya
////
////=========================================================================================================================
//#include "model.h"
//#include "input.h"
//#include "camera.h"
//#include "bullet.h"
//
////
//// マクロ定義
////
//#define MAX_MODEL (2)		// モデルの数
//#define MODEL_SPD (2.0f)	// モデルの移動量
//#define SPD_DECAY (0.4f)	// 移動量の減衰係数
//
////
//// グローバル変数
////
////LPD3DXMESH g_pMeshModel = NULL;					// メッシュ(頂点情報)へのポインタ
////LPD3DXBUFFER g_pBuffMatModel = NULL;			// マテリアル(材質情報)へのポインタ
////DWORD g_nNumMatModel = NULL;					// マテリアルの数
//MODEL g_aModel[MAX_MODEL];						// モデルの情報
////D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;		// モデルの最小値・最大値
//LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// テクスチャへのポインタ
//
////
//// 初期化処理
////
//void InitModel(void)
//{
//	// デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// Xファイルの読み込み
//		D3DXLoadMeshFromX(
//			"data\\MODEL\\airplane000.x",
//			D3DXMESH_SYSTEMMEM,
//			pDevice,
//			NULL,
//			&g_aModel[nCntModel].pBuffMatModel,
//			NULL,
//			&g_aModel[nCntModel].nNumMatModel,
//			&g_aModel[nCntModel].pMeshModel);
//
//		int nNumvtx = 0;			// 頂点数
//		DWORD sizeFVF = NULL;		// 頂点フォーマットのサイズ
//		BYTE *pVtxBuff = NULL;		// 頂点バッファのポインタ
//
//		D3DXMATERIAL *pMat;	// マテリアルへのポインタ
//
//		g_aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
//		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);
//
//		// 頂点数を取得
//		nNumvtx = g_aModel[nCntModel].pMeshModel->GetNumVertices();
//
//		// 頂点フォーマットのサイズを取得
//		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel].pMeshModel->GetFVF());
//
//		// 頂点バッファをロック
//		g_aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
//		{
//			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入
//
//			// ↓全ての頂点数を比較してモデルの最小値・最大値を抜き出す
//			if (g_aModel[nCntModel].vtxMinModel.x > vtx.x)
//			{
//				g_aModel[nCntModel].vtxMinModel.x = vtx.x;
//			}
//
//			if (g_aModel[nCntModel].vtxMinModel.y > vtx.y)
//			{
//				g_aModel[nCntModel].vtxMinModel.y = vtx.y;
//			}
//
//			if (g_aModel[nCntModel].vtxMinModel.z > vtx.z)
//			{
//				g_aModel[nCntModel].vtxMinModel.z = vtx.z;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.x < vtx.x)
//			{
//				g_aModel[nCntModel].vtxMaxModel.x = vtx.x;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.y < vtx.y)
//			{
//				g_aModel[nCntModel].vtxMaxModel.y = vtx.y;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.z < vtx.z)
//			{
//				g_aModel[nCntModel].vtxMaxModel.z = vtx.z;
//			}
//			// ↑全ての頂点数を比較してモデルの最小値・最大値を抜き出す
//
//			pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分ポインタを進める
//		}
//
//		g_aModel[nCntModel].pMeshModel->UnlockVertexBuffer();
//
//		// マテリアル情報に対するポインタを取得
//		pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
//		{
//			if (pMat[nCntMat].pTextureFilename != NULL)
//			{// ↓このファイル名を使用してテクスチャを読み込む
//				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
//			}// ↑このファイル名を使用してテクスチャを読み込む
//		}
//
//		g_aModel[nCntModel].pos = D3DXVECTOR3(nCntModel * 10.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//}
//
//
////
//// 終了処理
////
//void UninitModel(void)
//{
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// メッシュの破棄
//		if (g_aModel[nCntModel].pMeshModel != NULL)
//		{
//			g_aModel[nCntModel].pMeshModel->Release();
//			g_aModel[nCntModel].pMeshModel = NULL;
//		}
//
//		// マテリアルの破棄
//		if (g_aModel[nCntModel].pBuffMatModel != NULL)
//		{
//			g_aModel[nCntModel].pBuffMatModel->Release();
//			g_aModel[nCntModel].pBuffMatModel = NULL;
//		}
//	}
//}
//
//
////
//// 更新処理
////
//void UpdateModel(void)
//{
//	Camera *pCamera = GetCamera();
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (GetKeyboardTrigger(DIK_RETURN) == true)
//		{
//			g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
//			g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aModel[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		}
//
//		if (GetKeyboardPress(DIK_UP) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (-D3DX_PI + pCamera->rot.y);
//
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//			g_aModel[nCntModel].move.x += sinf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z += cosf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_DOWN) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x -= sinf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z -= cosf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_LEFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x -= cosf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z += sinf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_RIGHT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x += cosf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z -= sinf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_LSHIFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y -= 0.2f;
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//		}
//
//		if (GetKeyboardPress(DIK_RSHIFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y += 0.2f;
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//		}
//
//		if (GetKeyboardPress(DIK_I) == true)
//		{
//			g_aModel[nCntModel].move.y += MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_K) == true)
//		{
//			g_aModel[nCntModel].move.y -= MODEL_SPD;
//		}
//
//
//
//
//		if ((g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) > D3DX_PI)
//		{
//			g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//		}
//		else if ((g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) < -D3DX_PI)
//		{
//			g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//		}
//
//		g_aModel[nCntModel].rot.y += (g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) * 0.1f;
//
//		if (g_aModel[nCntModel].rot.y > D3DX_PI)
//		{
//			g_aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
//		}
//		else if (g_aModel[nCntModel].rot.y < -D3DX_PI)
//		{
//			g_aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
//		}
//
//		g_aModel[nCntModel].move.x += (0.0f - g_aModel[nCntModel].move.x) * SPD_DECAY;
//		g_aModel[nCntModel].move.z += (0.0f - g_aModel[nCntModel].move.z) * SPD_DECAY;
//		g_aModel[nCntModel].move.y += (0.0f - g_aModel[nCntModel].move.y) * SPD_DECAY;
//
//		g_aModel[nCntModel].pos.x += g_aModel[nCntModel].move.x;
//		g_aModel[nCntModel].pos.z += g_aModel[nCntModel].move.z;
//		g_aModel[nCntModel].pos.y += g_aModel[nCntModel].move.y;
//	}
//}
//
//
////
//// 描画処理
////
//void DrawModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
//	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
//	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
//	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
//
//		// 向きを反映
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
//
//		D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);
//
//		// 位置を反映
//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
//
//		D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
//
//		// ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
//
//		// 現在のマテリアルを取得
//		pDevice->GetMaterial(&matDef);
//
//		// マテリアルデータへのポインタを取得
//		pMat = (D3DXMATERIAL *)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
//		{
//			// マテリアルの設定
//			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//			// テクスチャの設定
//			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);
//
//			// モデル(パーツ)の描画
//			g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
//		}
//
//	}
//	// 保存していたマテリアルを戻す
//	pDevice->SetMaterial(&matDef);
//}
//
//
////
//// モデルの取得
////
//MODEL *GetModel(void)
//{
//	return &g_aModel[0];
//}
