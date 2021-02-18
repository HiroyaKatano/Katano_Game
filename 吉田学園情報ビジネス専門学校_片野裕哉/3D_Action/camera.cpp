//
//
// カメラ [camera.cpp]
//
//
//
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player.h"

//
// マクロ定義
//
#define CAMERA_POS_R_DISTANCE (10.0f)	// 注視点とモデルの距離
#define CAMERA_SPD (3.0f)				// カメラの速さ
#define CAMERA_SPD_DECAY (0.04f)		// カメラの速度減衰係数

//
// グローバル変数
//
Camera g_camera;		// カメラの情報

//
// 初期化処理
//
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;
	g_camera.bFollow = true;
	g_camera.viewport.X = 0;
	g_camera.viewport.Y = 0;
	g_camera.viewport.Width = SCREEN_WIDTH;
	g_camera.viewport.Height = SCREEN_HEIGHT;
	g_camera.viewport.MinZ = 0.0f;
	g_camera.viewport.MaxZ = 1.0f;
}


//
// 終了処理
//
void UninitCamera(void)
{

}


//
// 更新処理
//
void UpdateCamera(void)
{
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	if (GetKeyboardTrigger(DIK_F4) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.bFollow = g_camera.bFollow ? false : true;
	}

	if (g_camera.bFollow == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;
		}

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.x += sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.z += cosf(g_camera.rot.y) * CAMERA_SPD;
		}

		if (GetKeyboardPress(DIK_S) == true)
		{
			g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.x -= sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.z -= cosf(g_camera.rot.y) * CAMERA_SPD;
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			g_camera.posV.x -= cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.x -= cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posV.z += sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.z += sinf(g_camera.rot.y) * CAMERA_SPD;
		}

		if (GetKeyboardPress(DIK_D) == true)
		{
			g_camera.posV.x += cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.x += cosf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posV.z -= sinf(g_camera.rot.y) * CAMERA_SPD;
			g_camera.posR.z -= sinf(g_camera.rot.y) * CAMERA_SPD;
		}

		if (GetKeyboardPress(DIK_Y) == true)
		{
			g_camera.posV.y += 2.0f;
		}

		if (GetKeyboardPress(DIK_N) == true)
		{
			g_camera.posV.y -= 2.0f;
		}

		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rot.y += 0.02f;
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_C) == true)
		{
			g_camera.rot.y -= 0.02f;
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_T) == true)
		{
			g_camera.posR.y += 2.0f;
		}

		if (GetKeyboardPress(DIK_B) == true)
		{
			g_camera.posR.y -= 2.0f;
		}

		if (GetKeyboardPress(DIK_Q) == true)
		{
			g_camera.rot.y -= 0.02f;
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_E) == true)
		{
			g_camera.rot.y += 0.02f;
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_U) == true)
		{
			if (g_camera.fDistance > 100.0f)
			{
				g_camera.fDistance -= 1.0f;
				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
			}
		}

		if (GetKeyboardPress(DIK_M) == true)
		{
			if (g_camera.fDistance < 300.0f)
			{
				g_camera.fDistance += 1.0f;
				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
			}
		}
	}
	else if (g_camera.bFollow == true)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_camera.posV = D3DXVECTOR3(0.0f, pPlayer->pos.y + 90.0f, -200.0f);
			g_camera.posR = D3DXVECTOR3(0.0f, pPlayer->pos.y, 0.0f);
			g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;
		}

		if (GetKeyboardPress(DIK_Z) == true)
		{
			g_camera.rot.y += 0.02f;
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_C) == true)
		{
			g_camera.rot.y -= 0.02f;
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		if (GetKeyboardPress(DIK_T) == true)
		{
			g_camera.posR.y += 2.0f;
		}

		if (GetKeyboardPress(DIK_B) == true)
		{
			g_camera.posR.y -= 2.0f;
		}

		if (GetKeyboardPress(DIK_Y) == true)
		{
			g_camera.posV.y += 2.0f;
		}

		if (GetKeyboardPress(DIK_N) == true)
		{
			g_camera.posV.y -= 2.0f;
		}

		if (GetKeyboardPress(DIK_U) == true)
		{
			if (g_camera.fDistance > 100.0f)
			{
				g_camera.fDistance -= 1.0f;
				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
			}
		}

		if (GetKeyboardPress(DIK_M) == true)
		{
			if (g_camera.fDistance < 300.0f)
			{
				g_camera.fDistance += 1.0f;
				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
			}
		}

		g_camera.posRDest.x = pPlayer->pos.x - CAMERA_POS_R_DISTANCE * sinf(pPlayer->rot.y);
		g_camera.posRDest.z = pPlayer->pos.z - CAMERA_POS_R_DISTANCE * cosf(pPlayer->rot.y);
		if (pPlayer->bGoal == false)
		{
			g_camera.posRDest.y = pPlayer->pos.y;
			g_camera.posVDest.y = g_camera.posRDest.y + 80.0f;
		}

		g_camera.posVDest.x = pPlayer->pos.x;
		g_camera.posVDest.z = pPlayer->pos.z - g_camera.fDistance;
		

		if (pPlayer->bGoal == true)
		{
			g_camera.posRDest.y += 2.0f;
			g_camera.posVDest.y -= 0.5f;
		}


		g_camera.posR = g_camera.posRDest;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_SPD_DECAY;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_SPD_DECAY;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_SPD_DECAY;
	}
}


//
// 設定
//
void SetCamera(int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	pDevice->SetViewport(&g_camera.viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxPrjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxPrjection,
		D3DXToRadian(45.0f),							// 画角(45度)
		(float)g_camera.viewport.Width / (float)g_camera.viewport.Height,		// 画面比率
		10.0f,											// Zの手前
		1000.0f);										// Zの奥

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxPrjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// プロジェクションマトリックスの作成
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


//
// カメラの取得
//
Camera *GetCamera(void)
{
	return &g_camera;
}
