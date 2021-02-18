//=========================================================================================================================
//
// プレイヤー [player.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#include "player.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "goal.h"
#include "fade.h"

//
// マクロ定義
//
#define MODEL_SPD (2.0f)	// プレイヤーの移動量
#define SPD_DECAY (0.4f)	// 移動量の減衰係数

//
// グローバル変数
//
PLAYER g_player;								// プレイヤー
char *g_aModelFile[MODEL_LABEL_MAX] =
{
	"data\\MODEL\\player_model\\00_body_00.x",		// 胴体
	"data\\MODEL\\player_model\\01_neck_00.x",		// 首
	"data\\MODEL\\player_model\\02_head_00.x",		// 頭部
	"data\\MODEL\\player_model\\03_armR_T_00.x",	// 右腕(肘上)
	"data\\MODEL\\player_model\\04_elbowR_00.x",	// 右肘
	"data\\MODEL\\player_model\\05_armR_U_00.x",	// 右腕(肘下)
	"data\\MODEL\\player_model\\06_armL_T_00.x",	// 左腕(肘上)
	"data\\MODEL\\player_model\\07_elbowL_00.x",	// 左肘
	"data\\MODEL\\player_model\\08_armL_U_00.x",	// 左腕(肘下)
	"data\\MODEL\\player_model\\09_legR_T_00.x",	// 右脚(腿)
	"data\\MODEL\\player_model\\10_kneeR_00.x",	// 右膝
	"data\\MODEL\\player_model\\11_legR_U_00.x",	// 右脚(脹脛)
	"data\\MODEL\\player_model\\12_footR_00.x",		// 右足
	"data\\MODEL\\player_model\\13_legL_T_00.x",	// 左脚(腿)
	"data\\MODEL\\player_model\\14_kneeL_00.x",	// 左膝
	"data\\MODEL\\player_model\\15_legL_U_00.x",	// 左脚(脹脛)
	"data\\MODEL\\player_model\\16_footL_00.x",		// 左足
	"data\\MODEL\\player_model\\17_katana_00.x",	// 刀
};		// モデルのファイル一覧
LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// テクスチャへのポインタ

//
// 初期化処理
//
void InitPlayer(void)
{
	SavePlayerData();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bGoal = false;
	g_player.nNumModel = 0;

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			g_aModelFile[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_player.aModel[nCntModel].nNumMatModel,
			&g_player.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// 頂点数
		DWORD sizeFVF = NULL;		// 頂点フォーマットのサイズ
		BYTE *pVtxBuff = NULL;		// 頂点バッファのポインタ

		D3DXMATERIAL *pMat;	// マテリアルへのポインタ

		g_player.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_player.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// 頂点数を取得
		nNumvtx = g_player.aModel[nCntModel].pMeshModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMeshModel->GetFVF());

		// 頂点バッファをロック
		g_player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入

			// ↓全ての頂点数を比較してプレイヤーの最小値・最大値を抜き出す
			if (g_player.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_player.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_player.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_player.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_player.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_player.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_player.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ↑全ての頂点数を比較してプレイヤーの最小値・最大値を抜き出す

			pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分ポインタを進める
		}

		g_player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// ↓このファイル名を使用してテクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}// ↑このファイル名を使用してテクスチャを読み込む
		}

		g_player.nNumModel++;
	}

	// 全パーツの階層構造設定
	g_player.aModel[0].nIdxModelParent = -1;						// 親のインデックスを設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 66.5f, 0.0f);			// 位置の初期設定
	g_player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[1].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 38.2f, 0.0f);		// 位置の初期設定
	g_player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[2].nIdxModelParent = 1;							// 親のインデックスを設定
	g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[2].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[3].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 33.5f, 1.0f);		// 位置の初期設定
	g_player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[3].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[4].nIdxModelParent = 3;							// 親のインデックスを設定
	g_player.aModel[4].pos = D3DXVECTOR3(-22.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[4].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[5].nIdxModelParent = 4;							// 親のインデックスを設定
	g_player.aModel[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[5].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[6].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[6].pos = D3DXVECTOR3(10.0f, 33.5f, 1.0f);		// 位置の初期設定
	g_player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[6].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[7].nIdxModelParent = 6;							// 親のインデックスを設定
	g_player.aModel[7].pos = D3DXVECTOR3(22.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[7].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[8].nIdxModelParent = 7;							// 親のインデックスを設定
	g_player.aModel[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[8].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[9].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[9].pos = D3DXVECTOR3(-6.0f, -1.0f, 1.0f);		// 位置の初期設定
	g_player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[9].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[10].nIdxModelParent = 9;							// 親のインデックスを設定
	g_player.aModel[10].pos = D3DXVECTOR3(-0.5f, -26.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[10].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[11].nIdxModelParent = 10;							// 親のインデックスを設定
	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// 位置の初期設定
	g_player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[11].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[12].nIdxModelParent = 11;							// 親のインデックスを設定
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[12].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[13].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[13].pos = D3DXVECTOR3(6.0f, -1.0f, 1.0f);		// 位置の初期設定
	g_player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[13].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[14].nIdxModelParent = 13;							// 親のインデックスを設定
	g_player.aModel[14].pos = D3DXVECTOR3(0.5f, -26.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[14].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[14].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[15].nIdxModelParent = 14;							// 親のインデックスを設定
	g_player.aModel[15].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// 位置の初期設定
	g_player.aModel[15].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[15].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[15].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[16].nIdxModelParent = 15;							// 親のインデックスを設定
	g_player.aModel[16].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[16].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[16].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[17].nIdxModelParent = 4;							// 親のインデックスを設定
	g_player.aModel[17].pos = D3DXVECTOR3(-21.5f, 0.0f, -0.5f);		// 位置の初期設定
	g_player.aModel[17].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[17].rot = D3DXVECTOR3(-1.5f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[17].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定



	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置の初期設定
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 移動量の初期設定
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向きの初期設定
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 目的の向きの初期設定
}


//
// 終了処理
//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// メッシュの破棄
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		// マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// 更新処理
//
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();
	GOAL *pGoal = GetGoal();

	if (((pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z) - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) -
		(0.0f) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0 &&
		(0.0f) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) -
		((pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x) - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z)) >= 0 &&
		((pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z) - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z)) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) -
		(0.0f) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0 &&
		(0.0f) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) -
		((pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x) - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
		g_player.bGoal = true;
	}

	/*if (g_player.pos.x < pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x &&
		g_player.pos.x > pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)
	{
		if (g_player.pos.z < pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z &&
			g_player.pos.z > pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}*/

	if (g_player.bGoal == false)
	{

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SetFade(FADE_OUT, MODE_RESULT);
		}

		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_player.rotDest.y = (-D3DX_PI + pCamera->rot.y);

			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}
			g_player.move.x += sinf(pCamera->rot.y) * MODEL_SPD;
			g_player.move.z += cosf(pCamera->rot.y) * MODEL_SPD;
		}

		if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_player.rotDest.y = (pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x -= sinf(pCamera->rot.y) * MODEL_SPD;
			g_player.move.z -= cosf(pCamera->rot.y) * MODEL_SPD;
		}

		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_player.rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x -= cosf(pCamera->rot.y) * MODEL_SPD;
			g_player.move.z += sinf(pCamera->rot.y) * MODEL_SPD;
		}

		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_player.rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x += cosf(pCamera->rot.y) * MODEL_SPD;
			g_player.move.z -= sinf(pCamera->rot.y) * MODEL_SPD;
		}

		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_player.rotDest.y -= 0.2f;
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}
		}

		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{
			g_player.rotDest.y += 0.2f;
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
		}

		if (GetKeyboardPress(DIK_I) == true)
		{
			g_player.move.y += MODEL_SPD;
		}

		if (GetKeyboardPress(DIK_K) == true)
		{
			g_player.move.y -= MODEL_SPD;
		}

	}
	else if (g_player.bGoal == true)
	{
		g_player.rotDest.y += 0.3f;
		g_player.move.y += 1.0f;
	}

	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if ((g_player.rotDest.y - g_player.rot.y) < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	g_player.move.x += (0.0f - g_player.move.x) * SPD_DECAY;
	g_player.move.z += (0.0f - g_player.move.z) * SPD_DECAY;
	g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;

	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;
	g_player.pos.y += g_player.move.y;
}


//
// 描画処理
//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// 計算用マトリックス
		D3DXMATRIX mtxParent;							// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// プレイヤーの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

		// プレイヤーの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// 各パーツの親のマトリックスを設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
							&g_player.aModel[nCntModel].mtxWorld,
							&mtxParent);

		// 各パーツのワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// モデル(パーツ)の描画
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			// プレイヤー(パーツ)の描画
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}


//
// プレイヤーの取得
//
PLAYER *GetPlayer(void)
{
	return &g_player;
}


//
// プレイヤーデータの保存
//
void SavePlayerData(void)
{
	//// ファイルのポインタ
	//FILE *pFile;
	//char cModelName[2048];
	//char search[] = "MODEL_FILENAME = ";
	//char searchend[] = ".x";
	//char *start_ptr;		/* 検索開始位置 */
	//char *end_ptr;			/* 検索終了位置 */
	//char *search_ptr;		/* 検索結果文字位置 */
	//char key[11];			/* 検索キー */
	//int search_cnt;			/* 検索結果文字数 */
	//int return_code = 0;

	//pFile = fopen("data\\MOTION_DATA\\motion_my_model.txt", "r");

	//while (fgets(cModelName, 255, pFile))
	//{
	//	start_ptr = search;
	//	end_ptr = searchend;
	//	if (strstr(cModelName, search))
	//	{

	//	}
	//}

	//fclose(pFile);
}


//
// モーション
//
void MotionPlayer(void)
{
	
}
