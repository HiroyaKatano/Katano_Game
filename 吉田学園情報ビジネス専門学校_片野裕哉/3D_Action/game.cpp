//===============================================================================================================
//
// ゲーム [game.cpp]
// Author:Katano Hiroya
//
//===============================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "wall.h"
#include "Billboard.h"
#include "meshfield.h"
#include "bullet.h"
#include "player.h"
#include "particle.h"
#include "fade.h"
#include "goal.h"

#include <stdio.h>

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
//void DrawInfo(void);

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPD3DXFONT g_pInfoFont = NULL;					// フォントへのポインタ
bool g_bPause;								// ポーズしているかどうか

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitGame(void)
{
	g_bPause = false;

	InitLight();

	InitCamera();

	InitMeshField();

	InitWall();

	InitShadow();

	InitBillboard();

	InitBullet();

	InitParticle();

	InitGoal();

	InitPlayer();

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitGame(void)
{
	UninitPlayer();

	UninitGoal();

	UninitParticle();

	UninitBullet();

	UninitBillboard();

	UninitShadow();

	UninitWall();

	UninitMeshField();

	UninitCamera();

	UninitLight();
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateLight();

		UpdateCamera();

		UpdateMeshField();

		UpdateWall();

		UpdateBillboard();

		UpdateGoal();

		UpdatePlayer();

		UpdateParticle();

		UpdateBullet();

		UpdateShadow();
	}
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVIEWPORT9 viewportDef;

	// 描画の開始
	pDevice->GetViewport(&viewportDef);

	SetCamera(0);

	DrawMeshField();

	DrawWall();

	DrawShadow();

	//DrawBillboard();

	DrawBullet();

	DrawParticle();

	DrawGoal();

	DrawPlayer();

	pDevice->GetViewport(&viewportDef);
}