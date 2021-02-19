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
#define PLAYER_SPD (12.0f)	// プレイヤーの移動量
#define SPD_DECAY (0.4f)	// 移動量の減衰係数
#define TEXT_LENGTH		(128)	// テキスト読み込みの最大数
#define DATA_LENGTH		(64)	// データ読み込みの最大数

//
// グローバル変数
//
PLAYER g_player;								// プレイヤー
//char *g_aModelFile[MODEL_LABEL_MAX] =
//{
//	"data\\MODEL\\player_model\\00_body_00.x",		// 胴体
//	"data\\MODEL\\player_model\\01_neck_00.x",		// 首
//	"data\\MODEL\\player_model\\02_head_00.x",		// 頭部
//	"data\\MODEL\\player_model\\03_armR_T_00.x",	// 右腕(肘上)
//	"data\\MODEL\\player_model\\04_elbowR_00.x",	// 右肘
//	"data\\MODEL\\player_model\\05_armR_U_00.x",	// 右腕(肘下)
//	"data\\MODEL\\player_model\\06_armL_T_00.x",	// 左腕(肘上)
//	"data\\MODEL\\player_model\\07_elbowL_00.x",	// 左肘
//	"data\\MODEL\\player_model\\08_armL_U_00.x",	// 左腕(肘下)
//	"data\\MODEL\\player_model\\09_legR_T_00.x",	// 右脚(腿)
//	"data\\MODEL\\player_model\\10_kneeR_00.x",	// 右膝
//	"data\\MODEL\\player_model\\11_legR_U_00.x",	// 右脚(脹脛)
//	"data\\MODEL\\player_model\\12_footR_00.x",		// 右足
//	"data\\MODEL\\player_model\\13_legL_T_00.x",	// 左脚(腿)
//	"data\\MODEL\\player_model\\14_kneeL_00.x",	// 左膝
//	"data\\MODEL\\player_model\\15_legL_U_00.x",	// 左脚(脹脛)
//	"data\\MODEL\\player_model\\16_footL_00.x",		// 左足
//	"data\\MODEL\\player_model\\17_katana_00.x",	// 刀
//};		// モデルのファイル一覧
LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// テクスチャへのポインタ

//
// 初期化処理
//
void InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadPlayerData();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bGoal = false;
	g_player.nNumModel = 0;
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			/*g_aModelFile[nCntModel],*/
			g_player.aModel[nCntModel].aFileName,
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

	//// 全パーツの階層構造設定
	//g_player.aModel[0].nIdxModelParent = -1;						// 親のインデックスを設定
	//g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 66.5f, 0.0f);			// 位置の初期設定
	//g_player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[1].nIdxModelParent = 0;							// 親のインデックスを設定
	//g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 38.2f, 0.0f);		// 位置の初期設定
	//g_player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[2].nIdxModelParent = 1;							// 親のインデックスを設定
	//g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[2].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[3].nIdxModelParent = 0;							// 親のインデックスを設定
	//g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 33.5f, 1.0f);		// 位置の初期設定
	//g_player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[3].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[4].nIdxModelParent = 3;							// 親のインデックスを設定
	//g_player.aModel[4].pos = D3DXVECTOR3(-22.0f, 0.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[4].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[5].nIdxModelParent = 4;							// 親のインデックスを設定
	//g_player.aModel[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[5].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[6].nIdxModelParent = 0;							// 親のインデックスを設定
	//g_player.aModel[6].pos = D3DXVECTOR3(10.0f, 33.5f, 1.0f);		// 位置の初期設定
	//g_player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[6].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[7].nIdxModelParent = 6;							// 親のインデックスを設定
	//g_player.aModel[7].pos = D3DXVECTOR3(22.0f, 0.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[7].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[8].nIdxModelParent = 7;							// 親のインデックスを設定
	//g_player.aModel[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[8].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[9].nIdxModelParent = 0;							// 親のインデックスを設定
	//g_player.aModel[9].pos = D3DXVECTOR3(-6.0f, -1.0f, 1.0f);		// 位置の初期設定
	//g_player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[9].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[10].nIdxModelParent = 9;							// 親のインデックスを設定
	//g_player.aModel[10].pos = D3DXVECTOR3(-0.5f, -26.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[10].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[11].nIdxModelParent = 10;							// 親のインデックスを設定
	//g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// 位置の初期設定
	//g_player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[11].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[12].nIdxModelParent = 11;							// 親のインデックスを設定
	//g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[12].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[13].nIdxModelParent = 0;							// 親のインデックスを設定
	//g_player.aModel[13].pos = D3DXVECTOR3(6.0f, -1.0f, 1.0f);		// 位置の初期設定
	//g_player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[13].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[14].nIdxModelParent = 13;							// 親のインデックスを設定
	//g_player.aModel[14].pos = D3DXVECTOR3(0.5f, -26.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[14].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[14].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[15].nIdxModelParent = 14;							// 親のインデックスを設定
	//g_player.aModel[15].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// 位置の初期設定
	//g_player.aModel[15].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[15].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[15].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[16].nIdxModelParent = 15;							// 親のインデックスを設定
	//g_player.aModel[16].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// 位置の初期設定
	//g_player.aModel[16].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[16].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	//g_player.aModel[17].nIdxModelParent = 4;							// 親のインデックスを設定
	//g_player.aModel[17].pos = D3DXVECTOR3(-21.5f, 0.0f, -0.5f);		// 位置の初期設定
	//g_player.aModel[17].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	//g_player.aModel[17].rot = D3DXVECTOR3(-1.5f, 0.0f, 0.0f);			// 向きの初期設定
	//g_player.aModel[17].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定



	//g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置の初期設定
	//g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 移動量の初期設定
	//g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向きの初期設定
	//g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 目的の向きの初期設定
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

	// 直前の位置の保存
	g_player.posOld = g_player.pos;

	// 重力の発生
	if (g_player.pos.y > 0.0f)
	{
		g_player.move.y += -0.8f;

	}
	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
		g_player.move.y = 0.0f;
		if (g_player.motionTypeOld == MOTIONTYPE_JUMP)
		{
			g_player.nKey = 0;
			g_player.nCounterMotion = 0;
			g_player.motionType = MOTIONTYPE_STEP;
		}
	}

	// ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		//SetBullet(
		//	D3DXVECTOR3(g_player.pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y + 50.0f, g_player.pos.z + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
		//	/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
		//	D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
		//	100);

		g_player.move.y = 50.0f;
		g_player.nKey = 0;
		g_player.nCounterMotion = 0;
		g_player.motionType = MOTIONTYPE_JUMP;
	}

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
			g_player.motionType = MOTIONTYPE_NEUTRAL;
			/*SetFade(FADE_OUT, MODE_RESULT);*/
		}

		// モーションカウンターの加算
		g_player.nCounterMotion++;

		// モーションの更新
		MotionPlayer(g_player.motionType);

		// 移動量の加算
		g_player.pos += g_player.move;

		if (GetKeyboardTrigger(DIK_0) == true)
		{
			g_player.motionType = MOTIONTYPE_ACTION;
		}

		if (GetKeyboardPress(DIK_UP) == true)
		{
			/*g_player.rotDest.y = (-D3DX_PI + pCamera->rot.y);

			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPD;*/


			if (GetKeyboardPress(DIK_LEFT) == true)
			{// 左上方向
				g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_SPD;
				g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{// 右上方向
				g_player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_SPD;
				g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
			}
			else
			{// 上方向
				g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPD;
				g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
			}
			g_player.motionType = MOTIONTYPE_MOVE;
		}

		else if (GetKeyboardPress(DIK_DOWN) == true)
		{



			if (GetKeyboardPress(DIK_LEFT) == true)
			{// 左下方向
				g_player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{// 右下方向
				g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
			}
			else
			{// 下方向
				g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * PLAYER_SPD;
				g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y;
			}
			g_player.motionType = MOTIONTYPE_MOVE;
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{// 左方向
			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);

			g_player.motionType = MOTIONTYPE_MOVE;

		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// 右方向
			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);

			g_player.motionType = MOTIONTYPE_MOVE;

		}

		/*if (GetKeyboardPress(DIK_DOWN) == true)
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

			g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_SPD;
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

			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPD;
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

			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPD;
		}*/

		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 20.0f;
		}

		if (GetKeyboardRelease(DIK_UP) == true || GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 20.0f;
			g_player.motionType = MOTIONTYPE_NEUTRAL;
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
			g_player.move.y += PLAYER_SPD;
		}

		if (GetKeyboardPress(DIK_K) == true)
		{
			g_player.move.y -= PLAYER_SPD;
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
	/*g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;*/

	/*g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;
	g_player.pos.y += g_player.move.y;*/
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
void LoadPlayerData(void)
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

	// ローカル変数宣言
	FILE *pFile;
	char aEqual[2] = { NULL };					// 「=」読み取り用変数
	int nCntFile = 0;							// Xファイルの数
	int nIdxParts = 0;							// パーツ数
	int nMotion = 0;							// モーションの数
	bool bComment = false;						// コメントアウトするか
	char aText[TEXT_LENGTH] = { NULL };			// テキスト読み取り用変数
	char aCharaSet[DATA_LENGTH] = { NULL };		// キャラデータ読み取り用変数
	char aPartsSet[DATA_LENGTH] = { NULL };		// パーツデータ読み取り用変数
	char aMotionSet[DATA_LENGTH] = { NULL };	// モーション読み取り用変数
	char aKeyInfo[DATA_LENGTH] = { NULL };		// キー設定情報読み取り用変数
	char aKey[DATA_LENGTH] = { NULL };			// キー情報読み取り用変数

												// strcmp読み取り用ポインタ
	char *pText = &aText[0];
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeyInfo[0];
	char *pKey = &aKey[0];


	// データの読み込み
	pFile = fopen("data\\MOTION_DATA\\motion_my_model.txt", "r");
	if (pFile != NULL)
	{ //ファイル展開可能
		while (strcmp("END_SCRIPT", pText) != 0)
		{
			aText[0] = { NULL };
			if (bComment == false)
			{// コメントアウトしていない
				fscanf(pFile, "%s", &aText[0]);

				if (aText[0] == '#')
				{// 文字列の先頭が「#」ならばコメントアウトへ
					bComment = true;
				}
				else
				{// 通常時
					if (strcmp("NUM_MODEL", pText) == 0)
					{// モデルの数
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &g_player.nNumModel);
					}
					else if (strcmp("MODEL_FILENAME", pText) == 0)
					{// Xファイル名の読み込み
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &g_player.aModel[nCntFile].aFileName[0]);
						nCntFile++;
					}
					else if (strcmp("CHARACTERSET", pText) == 0)
					{// キャラの情報
						while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
						{// キャラ情報の読み取り
							fscanf(pFile, "%s", &aCharaSet[0]);
							if (strcmp("NUM_PARTS", pCharaSet) == 0)
							{

							}
							else if (strcmp("PARTSSET", pCharaSet) == 0)
							{
								aPartsSet[0] = { NULL };

								while (strcmp("END_PARTSSET", pPartsSet) != 0)
								{
									fscanf(pFile, "%s", &aPartsSet[0]);
									if (strcmp("INDEX", pPartsSet) == 0)
									{// パーツ情報の読み取り
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &nIdxParts);
									}
									else if (strcmp("PARENT", pPartsSet) == 0)
									{// パーツの親情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_player.aModel[nIdxParts].nIdxModelParent);
									}
									else if (strcmp("POS", pPartsSet) == 0)
									{// パーツの位置情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.x);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.y);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.z);
									}
									else if (strcmp("ROT", pPartsSet) == 0)
									{// パーツの角度情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.x);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.y);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.z);
									}
								}
							}
						}
					}
					else if (strcmp("MOTIONSET", pText) == 0)
					{
						// 変数の初期化
						aMotionSet[0] = { NULL };

						// ローカル変数宣言
						int nLoop = 0;
						int nKeySet = 0;

						while (strcmp("END_MOTIONSET", pMotionSet) != 0)
						{// モーションの読み込み
							fscanf(pFile, "%s", &aMotionSet[0]);
							if (strcmp("LOOP", pMotionSet) == 0)
							{// ループするか
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &nLoop);
								if (nLoop == 1)
								{// １の場合ループする
									g_player.bLoopMotion = true;
									g_player.aMotionInfo[nMotion].bLoop = true;
								}
							}
							else if (strcmp("NUM_KEY", pMotionSet) == 0)
							{// キー数の読み込み
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &g_player.nNumKey);
							}

							else if (strcmp("KEYSET", pMotionSet) == 0)
							{// キーの読み込み
							 // ローカル変数宣言
								int nKey = 0;
								// 変数の初期化
								aKeyInfo[0] = { NULL };

								while (strcmp("END_KEYSET", pKeySet) != 0)
								{// キー情報項目の読み込み
									fscanf(pFile, "%s", &aKeyInfo[0]);

									if (aKeyInfo[0] == '#')
									{// コメントアウト
									 // ローカル変数宣言
										char c = NULL;
										char d = NULL;
										fscanf(pFile, "%c", &c);
										while (c != '\n' && d != '\n')
										{
											fscanf(pFile, "%s", &aKey[0]);
											fscanf(pFile, "%c", &d);
										}
									}

									if (strcmp("KEY", pKeySet) == 0)
									{// キー情報の読み込み
										aKey[0] = { NULL };
										while (strcmp("END_KEY", pKey) != 0)
										{// 位置・角度の読み込み
											fscanf(pFile, "%s", &aKey[0]);
											if (strcmp("POS", pKey) == 0)
											{// 位置情報の読み込み
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosX);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosY);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosZ);
											}
											else if (strcmp("ROT", pKey) == 0)
											{// 角度情報の読み込み
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotX);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotY);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotZ);
											}
										}
										nKey++;
									}
									else if (strcmp("FRAME", pKeySet) == 0)
									{// キーフレーム数の読み込み
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].nFlame);
									}
								}
								nKeySet++;
							}
						}
						g_player.aMotionInfo[nMotion].nNumKey = nKeySet;	// キー数の設定
						nMotion++;
					}
				}
			}
			else if (bComment == true)
			{// コメントアウト処理
			 // ローカル変数宣言
				char a = NULL;
				char b = NULL;
				fscanf(pFile, "%c", &a);
				while (a != '\n' && b != '\n')
				{
					fscanf(pFile, "%s", &aText[0]);
					fscanf(pFile, "%c", &b);
				}
				bComment = false;
			}
		}
		fclose(pFile);
	}
	else
	{ // ファイル展開不可
	}
}


//
// モーション
//
void MotionPlayer(MOTIONTYPE motionType)
{
	g_player.nNumKey = g_player.aMotionInfo[motionType].nNumKey;
	g_player.bLoopMotion = g_player.aMotionInfo[motionType].bLoop;

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_player.nCounterMotion == g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame)
		{
			g_player.nCounterMotion = 0;

			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
			{
				g_player.nKey = 0;
			}
			else if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == false)
			{
				if (g_player.motionTypeOld == MOTIONTYPE_STEP)
				{
					g_player.motionType = MOTIONTYPE_NEUTRAL;
					g_player.aModel[0].pos.y = 20.0f;
				}
			}
			else if (g_player.nKey < g_player.nNumKey)
			{
				g_player.nKey++;
			}
		}

		if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			
		}
		else
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			
		}
	}

	// 直前のモーション状態の保存
	g_player.motionTypeOld = g_player.motionType;
}
