//=========================================================================================================================
//
// ゲーム画面 [game.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "game.h"
#include "player.h"
#include "BG.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "Score.h"
#include "fade.h"
#include "effect.h"
#include "pause.h"
#include "item.h"
#include "ui.h"
#include "barrier.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
bool g_bPause = false;									// ポーズ中かどうか

//=========================================================================================================================
// ゲーム画面の初期化処理
//=========================================================================================================================
HRESULT InitGame(void)
{
	// BGの初期化処理
	InitBG();

	// プレイヤーの初期化処理
	InitPlayer();

	// スコアの初期化処理
	InitScore();

	// 敵の初期化処理
	InitEnemy();

	// 弾の初期化処理
	InitBullet();

	//
	InitBarrier();

	// 爆発の初期化処理
	InitExplosion();

	// エフェクトの初期化処理
	InitEffect();

	//
	InitItem();

	//
	InitUi();

	// 
	InitPause();

	return S_OK;
}

//=========================================================================================================================
// ゲーム画面の終了処理
//=========================================================================================================================
void UninitGame(void) 
{
	//
	StopSound();

	//
	g_bPause = false;
	UninitPause();

	//
	UninitUi();

	//
	UninitItem();

	// エフェクトの終了処理
	UninitEffect();

	// 爆発の終了処理
	UninitExplosion();

	// 
	UninitBarrier();

	// 弾の終了処理
	UninitBullet();

	// 敵の終了処理
	UninitEnemy();

	// スコアの終了処理
	UninitScore();

	// プレイヤーの終了処理
	UninitPlayer();

	// BGの終了処理
	UninitBG();
}

//=========================================================================================================================
// ゲーム画面の更新処理
//=========================================================================================================================
void UpdateGame(void)
{
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	EXPLOSION *pExplosion;

	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	pExplosion = GetExplosion();
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

		// プレイヤーの更新処理
		UpdatePlayer();

		// 敵の更新処理
		UpdateEnemy();

		// 弾の更新処理
		UpdateBullet();

		//
		UpdateBarrier();

		// 爆発の更新処理
		UpdateExplosion();

		// エフェクトの更新処理
		UpdateEffect();

		//
		UpdateItem();

		//
		UpdateUi();

		// スコアの更新処理
		UpdateScore();
	}



	

	if (pPlayer->nMachine <= 0 || (FHASE_BOSS && pEnemy->nCounterEnemy <= 0))
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//=========================================================================================================================
// ゲーム画面の描画処理
//=========================================================================================================================
void DrawGame(void)
{
		// BGの描画処理
		DrawBG();

		//
		DrawItem();

		// 敵の描画処理
		DrawEnemy();

		// 弾の描画処理
		DrawBullet();

		// プレイヤーの描画処理
		DrawPlayer();

		// バリアの描画処理
		DrawBarrier();

		// 爆発の描画処理
		DrawExplosion();

		// エフェクトの描画処理
		DrawEffect();

		//
		DrawUi();

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