//=========================================================================================================================
//
// ゲーム画面 [game.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#define _CRT_SECURE_NO_WARNINGS	// 入力許可
#include <stdio.h>
#include "game.h"
#include "player.h"
#include "BG.h"
#include "Score.h"
#include "fade.h"
#include "pause.h"
#include "input.h"
#include "wire.h"
#include "block.h"
#include "sound.h"
#include "timer.h"
#include "result.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_MAPDATA_X (64)
#define MAX_MAPDATA_Y (36)

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
bool g_bPause = false;							// ポーズ中かどうか
int g_aMapData[MAX_MAPDATA_X][MAX_MAPDATA_Y];	// マップデータ格納先
int g_nBlock_X_Link = 0;						// ブロックのX軸の連結数
int g_nBlock_Y_Link = 0;						// ブロックのY軸の連結数

//=========================================================================================================================
// ゲーム画面の初期化処理
//=========================================================================================================================
HRESULT InitGame(void)
{
	// ファイルのポインタ
	FILE *pFile;
	BLOCK *pBlock;
	pBlock = GetBlock();

	pFile = fopen("data\\MAP_DATA\\map_00.csv", "r");

	// BGの初期化処理
	InitBG();

	// ブロックの初期化
	InitBlock();

	//// ゴールの初期化
	//InitGoal();

	// ブロックのセット処理
	int nCntX = 0, nCntY = 0;
	char aLine[256];
	while (fgets(aLine, 256, pFile) != NULL)
	{
		nCntX = 0;
		char *pToken = strtok(aLine, ",");
		while (pToken != NULL)
		{
			int nNum = atoi(pToken);
			g_aMapData[nCntX][nCntY] = nNum;

			pToken = strtok(NULL, ",");
			nCntX++;
		}
		nCntY++;
	}
	fclose(pFile);

	for (int nCntY = 0; nCntY < MAX_MAPDATA_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_MAPDATA_X; nCntX++)
		{
			if (g_aMapData[nCntX][nCntY] == 1)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(float((SCREEN_WIDTH_R / MAX_MAPDATA_X) * nCntX), float((SCREEN_HEIGHT_U / MAX_MAPDATA_Y) * nCntY), Z_AXIS_ZERO);
				SetBlock(pos, D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO), (SCREEN_WIDTH_R / MAX_MAPDATA_X), (SCREEN_HEIGHT_U / MAX_MAPDATA_Y), BLOCKTYPE_BLOCK);
			}
			else if (g_aMapData[nCntX][nCntY] == 2)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(float((SCREEN_WIDTH_R / MAX_MAPDATA_X) * nCntX), float((SCREEN_HEIGHT_U / MAX_MAPDATA_Y) * nCntY), Z_AXIS_ZERO);
				SetBlock(pos, D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO), (SCREEN_WIDTH_R / MAX_MAPDATA_X), (SCREEN_HEIGHT_U / MAX_MAPDATA_Y), BLOCKTYPE_GOAL);
			}
		}
	}

	PlaySound(SOUND_LABEL_BGM002);

	// プレイヤーの初期化処理
	InitPlayer();

	// ワイヤーの初期化
	InitWire();

	// スコアの初期化処理
	InitScore();

	// ポーズの初期化処理
	InitPause();

	// タイマーの初期化処理
	InitTimer();

	return S_OK;
}

//=========================================================================================================================
// ゲーム画面の終了処理
//=========================================================================================================================
void UninitGame(void) 
{
	// サウンドの停止処理
	StopSound();

	// タイマーの終了処理
	UninitTimer();

	// ポーズの終了処理
	g_bPause = false;
	UninitPause();

	// スコアの終了処理
	UninitScore();

	//// ゴールの終了処理
	//UninitGoal();

	// ワイヤーの終了処理
	UninitWire();

	// プレイヤーの終了処理
	UninitPlayer();

	// ブロックの終了処理
	UninitBlock();

	// BGの終了処理
	UninitBG();
}

//=========================================================================================================================
// ゲーム画面の更新処理
//=========================================================================================================================
void UpdateGame(void)
{
	PLAYER *pPlayer;
	/*GOAL *pGoal;*/

	pPlayer = GetPlayer();
	/*pGoal = GetGoal();*/
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		SetPause(g_bPause);
	}


	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		// BGの更新処理
		UpdateBG();

		// ブロックの更新処理
		UpdateBlock();

		// ワイヤーの更新処理
		UpdateWire();

		// プレイヤーの更新処理
		UpdatePlayer();

		//// ゴールの更新処理
		//UpdateGoal();

		//タイマーの更新処理
		UpdateTimer();

		// スコアの更新処理
		UpdateScore();
	}
}

//=========================================================================================================================
// ゲーム画面の描画処理
//=========================================================================================================================
void DrawGame(void)
{
		// BGの描画処理
		DrawBG();

		// ブロックの描画処理
		DrawBlock();

		// ワイヤーの描画処理
		DrawWire();

		//// ゴールの描画処理
		//DrawGoal();

		// プレイヤーの描画処理
		DrawPlayer();

		// タイマーの描画処理
		DrawTimer();

		// スコアの描画処理
		DrawScore();

		if (g_bPause == true)
		{
			// ポーズ中の描画処理
			DrawPause();
		}
}

//=========================================================================================================================
// ポーズのON/OFF
//=========================================================================================================================
void SetPause(bool bPause)
{
	g_bPause = g_bPause ? false : true;
}