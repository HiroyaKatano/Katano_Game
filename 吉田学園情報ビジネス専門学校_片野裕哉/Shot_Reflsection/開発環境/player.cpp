//=========================================================================================================================
//
// プレイヤー [player.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "player.h"
#include "effect.h"
#include "explosion.h"
#include "barrier.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureplayer = NULL;			// テクスチャ
PLAYER g_player;
int g_nInterval;

//=========================================================================================================================
// プレイヤーの初期化処理
//=========================================================================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &g_pTextureplayer);

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

	// アニメーションカウンターとアニメーションパターンNo.の初期化
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;

	g_player.nMachine = 2;
	g_player.state = PLAYERSTATE_APPEAR;
	g_player.nCounterState = 30;
	g_player.nCounterDisp = 0;
	g_player.bDisp = true;
	g_player.SelectBullet = SELECT_NORMAL;

	g_nInterval = 0;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さ
	g_player.fLengthPlayer = sqrtf(PLAYER_SIZE_X * PLAYER_SIZE_X + PLAYER_SIZE_Y * PLAYER_SIZE_Y);

	// 対角線の角度
	g_player.fAnglePlayer = atan2f(PLAYER_SIZE_X, PLAYER_SIZE_Y);

	// プレイヤーの回転角
	g_player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 中心座標の設定
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f);

	// 頂点座標の設定

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.fAnglePlayer + D3DX_PI * 1.75f) * g_player.fLengthPlayer;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.fAnglePlayer + D3DX_PI * 1.75f) * g_player.fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(D3DX_PI * 1.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	pVtx[1].pos.y = g_player.pos.y + cosf(D3DX_PI * 1.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(D3DX_PI * 0.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	pVtx[2].pos.y = g_player.pos.y + cosf(D3DX_PI * 0.25f - g_player.fAnglePlayer) * g_player.fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.fAnglePlayer + D3DX_PI * 0.75f) * g_player.fLengthPlayer;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.fAnglePlayer + D3DX_PI * 0.75f) * g_player.fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);

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
	if (g_pTextureplayer != NULL)
	{
		g_pTextureplayer->Release();
		g_pTextureplayer = NULL;
	}
}

//=========================================================================================================================
// プレイヤーの更新処理
//=========================================================================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	BULLET *pBullet;
	ENEMY *pEnemy;
	BARRIER *pBarrier;
	
	pBullet = GetBullet();
	pEnemy = GetEnemy();
	pBarrier = GetBarrier();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.state == PLAYERSTATE_APPEAR)
	{
		g_player.nCounterState -= 1;

		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y + 10 * g_player.nCounterState, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y + 10 * g_player.nCounterState, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y + 10 * g_player.nCounterState, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y + 10 * g_player.nCounterState, 0.0f);

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			g_player.nCounterState = 30;
		}
	}
	else if (g_player.state == PLAYERSTATE_NORMAL)
	{
		// プレイヤーの位置を更新
		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.move.x -= sinf(D3DX_PI / 2) * PLAYER_SPD;
				g_player.move.y -= cosf(D3DX_PI / 2) * PLAYER_SPD;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.move.x -= sinf(D3DX_PI / 2) * PLAYER_SPD;
				g_player.move.y += cosf(D3DX_PI / 2) * PLAYER_SPD;
			}
			else
			{
				g_player.move.x -= PLAYER_SPD;
			}
		}

		if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_player.move.x += sinf(D3DX_PI / 2) * PLAYER_SPD;
				g_player.move.y -= cosf(D3DX_PI / 2) * PLAYER_SPD;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_player.move.x += sinf(D3DX_PI / 2) * PLAYER_SPD;
				g_player.move.y += cosf(D3DX_PI / 2) * PLAYER_SPD;
			}
			else
			{
				g_player.move.x += PLAYER_SPD;
			}
		}

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.y -= PLAYER_SPD;
		}

		if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.y += PLAYER_SPD;
		}


		// 位置の更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		// 移動量の減衰
		g_player.move.x += (0.0f - g_player.move.x) * SPD_DECAY;
		g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;

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


		if (g_player.pos.x < WINDOW_LEFT)
		{
			g_player.pos.x = WINDOW_LEFT;
		}

		if (g_player.pos.x > WINDOW_RIGHT)
		{
			g_player.pos.x = WINDOW_RIGHT;
		}

		if (g_player.pos.y < WINDOW_TOP)
		{
			g_player.pos.y = WINDOW_TOP;
		}

		if (g_player.pos.y > WINDOW_UNDER)
		{
			g_player.pos.y = WINDOW_UNDER;
		}


		//// 頂点座標の更新
		//pVtx[0].pos.x = g_pos.x + sinf(g_rotplayer.z + (g_fAngleplayer + D3DX_PI * 1.75f)) * g_fLengthplayer;
		//pVtx[0].pos.y = g_pos.y + cosf(g_rotplayer.z + (g_fAngleplayer + D3DX_PI * 1.75f)) * g_fLengthplayer;
		//pVtx[0].pos.z = 0.0f;

		//pVtx[1].pos.x = g_pos.x + sinf(g_rotplayer.z + (D3DX_PI * 1.25f - g_fAngleplayer)) * g_fLengthplayer;
		//pVtx[1].pos.y = g_pos.y + cosf(g_rotplayer.z + (D3DX_PI * 1.25f - g_fAngleplayer)) * g_fLengthplayer;
		//pVtx[1].pos.z = 0.0f;

		//pVtx[2].pos.x = g_pos.x + sinf(g_rotplayer.z + (D3DX_PI * 0.25f - g_fAngleplayer)) * g_fLengthplayer;
		//pVtx[2].pos.y = g_pos.y + cosf(g_rotplayer.z + (D3DX_PI * 0.25f - g_fAngleplayer)) * g_fLengthplayer;
		//pVtx[2].pos.z = 0.0f;

		//pVtx[3].pos.x = g_pos.x + sinf(g_rotplayer.z + (g_fAngleplayer + D3DX_PI * 0.75f)) * g_fLengthplayer;
		//pVtx[3].pos.y = g_pos.y + cosf(g_rotplayer.z + (g_fAngleplayer + D3DX_PI * 0.75f)) * g_fLengthplayer;
		//pVtx[3].pos.z = 0.0f;

		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y + PLAYER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE_X, g_player.pos.y - PLAYER_SIZE_Y, 0.0f);

		if (pBarrier->nCounterState == BARRIER_TIMER)
		{
			if (GetKeyboardTrigger(DIK_B) == true)
			{
				SetBarrier(D3DXVECTOR3(g_player.pos));

			}
		}

		if (pBarrier->state == BARRIERSTATE_WAIT)
		{// バリアが展開されていない時

			// 弾の発射
			switch (g_player.SelectBullet)
			{// 弾の種別判断

			case SELECT_NORMAL:
				if (GetKeyboardTrigger(DIK_SPACE) == true)
				{
					D3DXVECTOR3 pos;
					D3DXVECTOR3 move;
					pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 50, 0.0f);
					move = D3DXVECTOR3(0.0f, MOVE_PLAYER_BULLET, 0.0f);
					SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_NORMAL, 200);
					PlaySound(SOUND_LABEL_SE_SHOT);
				}
				break;
			case SELECT_LASER:
				if (GetKeyboardPress(DIK_SPACE) == true)
				{
					D3DXVECTOR3 pos;
					D3DXVECTOR3 move;
					pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 50, 0.0f);
					move = D3DXVECTOR3(0.0f, MOVE_PLAYER_BULLET, 0.0f);
					SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_LASER, 5);
					SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_LASER, 5);
					SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_LASER, 5);
					PlaySound(SOUND_LABEL_SE_SHOT);
				}
				break;
			case SELECT_WAVE:
				if (GetKeyboardPress(DIK_SPACE) == true)
				{
					g_nInterval += 1;

					if (g_nInterval % 10 == 0)
					{
						D3DXVECTOR3 pos;
						D3DXVECTOR3 move;
						pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 50, 0.0f);
						move = D3DXVECTOR3(0.0f, MOVE_PLAYER_BULLET, 0.0f);
						SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_WAVE, 500);
						PlaySound(SOUND_LABEL_SE_SHOT);
					}
				}
				break;
			case SELECT_BOMBER:
				if (GetKeyboardTrigger(DIK_SPACE) == true)
				{
					D3DXVECTOR3 pos;
					D3DXVECTOR3 move;
					pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 50, 0.0f);
					move = D3DXVECTOR3(0.0f, MOVE_PLAYER_BULLET, 0.0f);
					SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_BOMBER, 100);
					PlaySound(SOUND_LABEL_SE_SHOT);
				}
				break;
			case SELECT_CIRCLE:
				if (GetKeyboardPress(DIK_SPACE) == true)
				{
					g_nInterval += 1;

					if (g_nInterval % 15 == 0)
					{
						D3DXVECTOR3 pos;
						D3DXVECTOR3 move;
						pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 50, 0.0f);
						move = D3DXVECTOR3(0.0f, MOVE_PLAYER_BULLET, 0.0f);
						SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_CIRCLE, 50);
						SetBullet(D3DXVECTOR3(g_player.pos.x - 30, g_player.pos.y - 10, 0.0f), D3DXVECTOR3(-3.0f, MOVE_PLAYER_BULLET - 3.0f, 0.0f), LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_CIRCLE, 200);
						SetBullet(D3DXVECTOR3(g_player.pos.x + 30, g_player.pos.y - 10, 0.0f), D3DXVECTOR3(3.0f, MOVE_PLAYER_BULLET - 3.0f, 0.0f), LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_CIRCLE, 200);
						SetBullet(D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y - 40, 0.0f), D3DXVECTOR3(-2.0f, MOVE_PLAYER_BULLET - 1.0f, 0.0f), LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_CIRCLE, 200);
						SetBullet(D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y - 40, 0.0f), D3DXVECTOR3(2.0f, MOVE_PLAYER_BULLET - 1.0f, 0.0f), LIFE_BULLET, BULLETTYPE_PLAYER, BULLET_CIRCLE, 200);
						PlaySound(SOUND_LABEL_SE_SHOT);
					}
				}
				break;
			}


			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (pEnemy->pos.y - ENEMY_SIZE_Y <= g_player.pos.y &&
						pEnemy->pos.y + ENEMY_SIZE_Y >= g_player.pos.y &&
						pEnemy->pos.x - ENEMY_SIZE_X + pEnemy->move.x <= g_player.pos.x &&
						pEnemy->pos.x + ENEMY_SIZE_X + pEnemy->move.x >= g_player.pos.x)
					{
						HitPlayer(1);
					}
				}
			}
		}
	}
	else if (g_player.state == PLAYERSTATE_WAIT)
	{
		g_player.nCounterState -= 1;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_APPEAR;
			g_player.nCounterState = 30;
		}
	}
	else if (g_player.state == PLAYERSTATE_DEATH)
	{
		g_player.state = PLAYERSTATE_WAIT;

		pBarrier->state = BARRIERSTATE_WAIT;

		g_player.SelectBullet = SELECT_NORMAL;

		g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGTH + 50, 0.0f);
	}


	if (GetKeyboardTrigger(DIK_6) == true)
	{
		g_player.SelectBullet = SELECT_NORMAL;
	}


	if (GetKeyboardTrigger(DIK_7) == true)
	{
		g_player.SelectBullet = SELECT_LASER;
	}

	if (GetKeyboardTrigger(DIK_8) == true)
	{
		g_player.SelectBullet = SELECT_WAVE;

		g_nInterval = 0;
	}

	if (GetKeyboardTrigger(DIK_9) == true)
	{
		g_player.SelectBullet = SELECT_BOMBER;
	}

	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_player.SelectBullet = SELECT_CIRCLE;
	}

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
	pDevice->SetTexture(0, g_pTextureplayer);

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
	VERTEX_2D *pVtx;

	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	SetExplosion(D3DXVECTOR3(g_player.pos.x + g_player.move.x, g_player.pos.y, g_player.pos.z), EXPLOSION_ENEMY);

	PlaySound(SOUND_LABEL_SE_EXPLOSION);
	
	g_player.state = PLAYERSTATE_DEATH;

	if (g_player.nMachine > 0)
	{
		g_player.nMachine--;
	}

	return true;
}
