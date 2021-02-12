//=========================================================================================================================
//
// プレイヤー [player.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "player.h"
#include "block.h"
#include "wire.h"
#include "Score.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				// テクスチャ
PLAYER g_player;
int g_nAnimInterval;


//=========================================================================================================================
// プレイヤーの初期化処理
//=========================================================================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &g_pTexturePlayer);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL)))
	{
		return E_FAIL;
	}

	// プレイヤー情報の初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fWidth = 0.0f;
	g_player.fHeight = 0.0f;
	g_player.bJump = true;
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fLengthPlayer = 0.0f;
	g_player.fAnglePlayer = 0.0f;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = PLAYER_FLASH;

	g_nAnimInterval = 0;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さ
	g_player.fLengthPlayer = sqrtf(PLAYER_SIZE_VERTEX_X * PLAYER_SIZE_VERTEX_X + PLAYER_SIZE_Y * PLAYER_SIZE_Y);

	// 対角線の角度
	g_player.fAnglePlayer = atan2f(PLAYER_SIZE_VERTEX_X, PLAYER_SIZE_Y);

	// プレイヤーの回転角
	g_player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 中心座標の設定
	g_player.pos = D3DXVECTOR3(20.0f, SCREEN_HEIGHT_U - 25.0f, 0.0f);

	// プレイヤーの幅と高さの設定
	g_player.fWidth = PLAYER_SIZE_VERTEX_X;
	g_player.fHeight = PLAYER_SIZE_Y;

	// 頂点座標の設定

	//pVtx[0].pos.x = g_player.pos.x + sinf(g_player.fAnglePlayer + D3DX_PI * 1.75f) * g_player.fLengthPlayer;
	//pVtx[0].pos.y = g_player.pos.y + cosf(g_player.fAnglePlayer + D3DX_PI * 1.75f) * g_player.fLengthPlayer;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = g_player.pos.x + sinf(D3DX_PI * 1.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	//pVtx[1].pos.y = g_player.pos.y + cosf(D3DX_PI * 1.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = g_player.pos.x + sinf(D3DX_PI * 0.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	//pVtx[2].pos.y = g_player.pos.y + cosf(D3DX_PI * 0.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = g_player.pos.x + sinf(g_player.fAnglePlayer + D3DX_PI * 0.75f) * g_player.fLengthPlayer;
	//pVtx[3].pos.y = g_player.pos.y + cosf(g_player.fAnglePlayer + D3DX_PI * 0.75f) * g_player.fLengthPlayer;
	//pVtx[3].pos.z = 0.0f;

	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 1.0f / TEXTURE_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffplayer->Unlock();

	return S_OK;
}

//=========================================================================================================================
// プレイヤーの終了処理
//=========================================================================================================================
void UninitPlayer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//=========================================================================================================================
// プレイヤーの更新処理
//=========================================================================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;
	BLOCK *pBlock;
	WIRE *pWire;
	/*XINPUT_GAMEPAD Gamepad;
	XINPUT_STATE state;*/

	pPlayer = GetPlayer();
	pBlock = GetBlock();
	pWire = GetWire();
	/*Gamepad = *PXINPUT_GAMEPAD;*/

	// 前回の位置を保存
	pPlayer->posOld = pPlayer->pos;

	// プレイヤーとワイヤーの接地点との角度
	pPlayer->rotPlayer.z = atan2f(pPlayer->pos.x - pWire->pos.x,
							(pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);
	
	if (pPlayer->state == PLAYERSTATE_NORMAL)
	{
		pPlayer->nCounterState = PLAYER_FLASH;

		// プレイヤーの移動・ジャンプ操作
		if (GetKeyboardTrigger(DIK_SPACE) == true && pPlayer->bJump == false)
		{
			pPlayer->move.y = -PLAYER_JUMP;
			pPlayer->bJump = true;
		}

		//if (Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//{
		//	// A ボタンが押された
		//	pPlayer->move.y = -PLAYER_JUMP;
		//	pPlayer->bJump = true;
		//}

		if (GetKeyboardPress(DIK_W) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD / 1.4f, -WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD / 1.4f, -WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, -WIRE_EXTEND_SPD, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD / 1.4f, WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD / 1.4f, WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, WIRE_EXTEND_SPD, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}
		else
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
			{
				if (pWire->bContact == true)
				{
					//pPlayer->move.x -= PLAYER_SPD;
				}
				else if (pWire->bContact == false)
				{
					pPlayer->move.x -= PLAYER_SPD;
					if (GetKeyboardPress(DIK_D) == true)
					{
						pPlayer->move.x += PLAYER_SPD;
					}

				}
			}
			pWire = GetWire();
			if (pPlayer->bJump == false)
			{
				g_nAnimInterval++;

				if (g_nAnimInterval % 10 == 0)
				{
					pPlayer->nCounterAnim++;
				}

			}



			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f + UV_V);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f + UV_V);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
			{
				if (pWire->bContact == true)
				{
				}
				else if (pWire->bContact == false)
				{
					pPlayer->move.x += PLAYER_SPD;
					if (GetKeyboardPress(DIK_A) == true)
					{
						pPlayer->move.x -= PLAYER_SPD;
					}

				}
			}
			pWire = GetWire();
			if (pPlayer->bJump == false)
			{
				g_nAnimInterval++;

				if (g_nAnimInterval % 10 == 0)
				{
					pPlayer->nCounterAnim++;
				}

			}


			//for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
			//{
			//	if (pWire->bContact == true)
			//	{
			//	}
			//}
			//pWire = GetWire();

			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f);
		}

		if (GetKeyboardRelease(DIK_A) == true && pPlayer->nCounterAnim % 2 == 1)
		{
			pPlayer->nCounterAnim++;

			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f + UV_V);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f + UV_V);
		}
		else if (GetKeyboardRelease(DIK_D) == true && pPlayer->nCounterAnim % 2 == 1)
		{
			pPlayer->nCounterAnim++;

			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f);
		}

		//if (GetKeyboardPress(DIK_W) == true)
		//{
		//	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
		//	{
		//		if (pWire->bContact == true)
		//		{
		//			pPlayer->move.x += (0.0f + (pWire->pos.x - pPlayer->pos.x)) * 0.05f;
					//pPlayer->move.y += (0.0f + (pWire->pos.y - pPlayer->pos.y)) * 0.05f;
		//		}
		//	}
		//}
		//pWire = GetWire();

		//if (GetKeyboardPress(DIK_S) == true)
		//{
		//	g_player.move.y += PLAYER_SPD;
		//}

		for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
		{
			if (pWire->bContact == true)
			{
				if (GetKeyboardTrigger(DIK_W) == true)
				{
					pPlayer->move.y -= 12.0f;
				}

				if (GetKeyboardTrigger(DIK_S) == true)
				{
					pPlayer->move.y += 5.0f;
				}

				if (GetKeyboardTrigger(DIK_A) == true)
				{
					pPlayer->move.x -= 5.0f;
				}

				if (GetKeyboardTrigger(DIK_D) == true)
				{
					pPlayer->move.x += 5.0f;
				}

			}
		}
		pWire = GetWire();



		// 移動量の減衰
		for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
		{
			if (pWire->bContact == true)
			{
				pPlayer->move.x += (pWire->pos.x - pPlayer->pos.x) * 0.005f;
				pPlayer->move.y += (0.0f + (pWire->pos.y - pPlayer->pos.y)) * 0.005f;
				if (pWire->fHeight >= WIRE_MAX_SIZE_Y)
				{
					if (pPlayer->move.y > 0)
					{


						//pPlayer->move.y *= -0.8f;

					}
					//pPlayer->move.y -= GRAVITY;
				}
				else if (pWire->fHeight < WIRE_MAX_SIZE_Y)
				{

				}
				pPlayer->move.y += GRAVITY;

				pPlayer->move.x += (0.0f - pPlayer->move.x) * 0.008f;

			}
			else if (pWire->bContact == false)
			{
				pPlayer->move.y += GRAVITY;
				if (pPlayer->bJump == false)
				{
					pPlayer->move.x += (0.0f - pPlayer->move.x) * SPD_DECAY;
				}
				else if (pPlayer->bJump == true)
				{
					pPlayer->move.x += (0.0f - pPlayer->move.x) * 0.2f;
				}

			}
		}
		pWire = GetWire();




		// 位置の更新
		pPlayer->pos.x += pPlayer->move.x;
		pPlayer->pos.y += pPlayer->move.y;


		// プレイヤーが画面外に出た時の修正動作
		if (pPlayer->pos.x < SCREEN_WIDTH_L + pPlayer->fWidth)
		{
			pPlayer->pos.x = SCREEN_WIDTH_L + pPlayer->fWidth;
			pPlayer->move.x = 0.0f;
		}

		if (pPlayer->pos.x > SCREEN_WIDTH_R - pPlayer->fWidth)
		{
			pPlayer->pos.x = SCREEN_WIDTH_R - pPlayer->fWidth;
			pPlayer->move.x = 0.0f;
		}

		if (pPlayer->pos.y < SCREEN_HEIGHT_T - pPlayer->fHeight)
		{
			pPlayer->pos.y = SCREEN_HEIGHT_T - pPlayer->fHeight;
		}

		if (pPlayer->pos.y > SCREEN_HEIGHT_U + 310)
		{
			pPlayer->state = PLAYERSTATE_WAIT;
			pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		//for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
		//{
		//	if (pBlock->bUse == true)
		//	{
		//		if (g_player.pos.x + g_player.fWidth > pBlock->pos.x &&
		//			g_player.pos.x - g_player.fWidth < pBlock->pos.x + pBlock->fWidth)
		//		{
		//			if (g_player.posOld.y <= pBlock->pos.y)
		//			{
		//				if (g_player.pos.y > pBlock->pos.y)
		//				{
		//					g_player.pos.y = pBlock->pos.y - 0.1f;
		//					g_player.move.y = 0.0f;
		//					g_player.bJump = false;
		//				}
		//			}
		//			else if (g_player.posOld.y - g_player.fHeight >= pBlock->pos.y + pBlock->fHeight)
		//			{
		//				if (g_player.pos.y - g_player.fHeight < pBlock->pos.y + pBlock->fHeight)
		//				{
		//					g_player.pos.y = (pBlock->pos.y + pBlock->fHeight) + g_player.fHeight;
		//					g_player.move.y = 1.0f;
		//				}
		//			}
		//		}

		//		if (g_player.pos.y > pBlock->pos.y &&
		//			g_player.pos.y - g_player.fHeight < pBlock->pos.y + pBlock->fHeight)
		//		{
		//			if (g_player.posOld.x - g_player.fWidth >= pBlock->pos.x + pBlock->fWidth)
		//			{
		//				if (g_player.pos.x - g_player.fWidth < pBlock->pos.x + pBlock->fWidth)
		//				{
		//					g_player.pos.x = (pBlock->pos.x + pBlock->fWidth) + g_player.fWidth + 0.1f;
		//					g_player.move.x = 0.0f;
		//				}
		//			}
		//			else if (g_player.posOld.x + g_player.fWidth <= pBlock->pos.x)
		//			{
		//				if (g_player.pos.x + g_player.fWidth > pBlock->pos.x)
		//				{
		//					g_player.pos.x = pBlock->pos.x - g_player.fWidth - 0.1f;
		//					g_player.move.x = 0.0f;
		//				}
		//			}
		//		}
		//	}
		//}

		// プレイヤーとブロックとの接触時の処理
		//CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fWidth, g_player.fHeight);
		if (CollisionBlock(&pPlayer->pos, &pPlayer->posOld, &pPlayer->move, pPlayer->fWidth, pPlayer->fHeight) == true)
		{
			pPlayer->bJump = false;
		}
		else if (CollisionBlock(&pPlayer->pos, &pPlayer->posOld, &pPlayer->move, pPlayer->fWidth, pPlayer->fHeight) == false)
		{
			pPlayer->bJump = true;
		}

		//// 回転
		//if (GetKeyboardPress(DIK_Q) == true)
		//{
		//	g_rotplayer.z += 0.1f;
		//	if (g_rotplayer.z > D3DX_PI)
		//	{
		//		g_rotplayer.z -= D3DX_PI * PLAYER_SPD;
		//	}
		//}
		//else if (GetKeyboardPress(DIK_E) == true)
		//{
		//	g_rotplayer.z -= 0.1f;
		//	if (g_rotplayer.z > D3DX_PI)
		//	{
		//		g_rotplayer.z -= D3DX_PI * PLAYER_SPD;
		//	}
		//}

	}
	else if (pPlayer->state == PLAYERSTATE_WAIT)
	{
		pPlayer->pos = D3DXVECTOR3(20.0f, SCREEN_HEIGHT_U - 25.0f, 0.0f);

		pPlayer->nCounterState -= TIMER_COUNT;

		if (pPlayer->nCounterState <= 0)
		{
			pPlayer->state = PLAYERSTATE_NORMAL;

			pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
		}
		else if (pPlayer->nCounterState <= PLAYER_FLASH && pPlayer->nCounterState > 0)
		{
			if (pPlayer->nCounterState % 5 == 0)
			{
				pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
			}
		}
	}

	//pPlayer->fLengthPlayer = sqrtf(PLAYER_SIZE_VERTEX_X * PLAYER_SIZE_VERTEX_X + PLAYER_SIZE_Y * PLAYER_SIZE_Y);

	//pPlayer->fAnglePlayer = atan2f(PLAYER_SIZE_VERTEX_X, PLAYER_SIZE_Y);

	// 頂点座標の更新
	//pVtx[0].pos.x = pPlayer->pos.x + sinf(pPlayer->rotPlayer.z + -D3DX_PI / 2) * PLAYER_SIZE_VERTEX_X;
	//pVtx[0].pos.y = pPlayer->pos.y + cosf(pPlayer->rotPlayer.z + -D3DX_PI / 2) * PLAYER_SIZE_VERTEX_X;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = pPlayer->pos.x - sinf(pPlayer->rotPlayer.z + pPlayer->fAnglePlayer) * pPlayer->fLengthPlayer;
	//pVtx[1].pos.y = pPlayer->pos.y - cosf(pPlayer->rotPlayer.z + pPlayer->fAnglePlayer) * pPlayer->fLengthPlayer;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = pPlayer->pos.x + sinf(pPlayer->rotPlayer.z + D3DX_PI / 2) * PLAYER_SIZE_VERTEX_X;
	//pVtx[2].pos.y = pPlayer->pos.y + cosf(pPlayer->rotPlayer.z + D3DX_PI / 2) * PLAYER_SIZE_VERTEX_X;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = pPlayer->pos.x - sinf(pPlayer->rotPlayer.z - pPlayer->fAnglePlayer) * pPlayer->fLengthPlayer;
	//pVtx[3].pos.y = pPlayer->pos.y - cosf(pPlayer->rotPlayer.z - pPlayer->fAnglePlayer) * pPlayer->fLengthPlayer;
	//pVtx[3].pos.z = 0.0f;

	pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - PLAYER_SIZE_VERTEX_X, pPlayer->pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x - PLAYER_SIZE_VERTEX_X, pPlayer->pos.y - PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + PLAYER_SIZE_VERTEX_X, pPlayer->pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + PLAYER_SIZE_VERTEX_X, pPlayer->pos.y - PLAYER_SIZE_Y, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// プレイヤーの描画処理
//=========================================================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));
	
	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	// プレイヤーの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,								// 描画を開始する頂点インデックス
		2);								// 描画するプリミティブの数
}

//=========================================================================================================================
// プレイヤーの取得
//=========================================================================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=========================================================================================================================
// プレイヤーのヒット処理
//=========================================================================================================================
bool HitPlayer(int nDamage)
{

	return true;
}
