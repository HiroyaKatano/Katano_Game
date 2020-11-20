//=========================================================================================================================
//
// 弾 [bullet.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "bullet.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "barrier.h"
#include "effect.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_apTextureBullet[MAX_MODE_BULLET] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
BULLET g_aBullet[MAX_BULLET];						// 弾の情報

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &g_apTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet002.png", &g_apTextureBullet[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_apTextureBullet[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wave.png", &g_apTextureBullet[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bomber.png", &g_apTextureBullet[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\circle.png", &g_apTextureBullet[5]);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].mode = BULLET_NORMAL;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}
	
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		SetVertexBullet(nCntBullet);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// テクスチャの開放
	for (int nCntmode = 0; nCntmode < MAX_MODE_BULLET; nCntmode++)
	{
		if (g_apTextureBullet != NULL)
		{
			g_apTextureBullet[nCntmode]->Release();
			g_apTextureBullet[nCntmode] = NULL;
		}
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateBullet(void)
{
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	BARRIER *pBarrier;

	pBullet = &g_aBullet[0];
	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	pBarrier = GetBarrier();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// 位置の更新
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y -= pBullet->move.y;

			// 頂点座標の設定
			SetVertexBullet(nCntBullet);
			
			pBullet->nLife -= 1;
			// 寿命チェック
			if (pBullet->nLife == 0)
			{
				SetExplosion(pBullet->pos, EXPLOSION_ENEMY);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				pBullet->bUse = false;
			}

			// 画面外チェック
			if (pBullet->pos.y <= 0 || pBullet->pos.y > SCREEN_HEIGTH)
			{
				pBullet->bUse = false;
			}

			if (pBullet->type == BULLETTYPE_PLAYER)
			{
				// 敵との当たり判定
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pBullet->mode == BULLET_NORMAL)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_NORMAL_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_NORMAL_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_NORMAL_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_NORMAL_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_LASER)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_LASER_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_LASER_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_LASER_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_LASER_SIZE_X)
							{
								//pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_WAVE)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_WAVE_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_WAVE_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_WAVE_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_WAVE_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_BOMBER)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_BOMBER_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_BOMBER_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_BOMBER_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_BOMBER_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
								SetExplosion(pEnemy->pos, EXPLOSION_BOMBER);
							}
						}
						else if (pBullet->mode == BULLET_CIRCLE)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_CIRCLE_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_CIRCLE_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_CIRCLE_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_CIRCLE_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
					}
				}
			}
			else if (pBullet->type == BULLETTYPE_ENEMY)
			{// 敵弾の場合
				if (pPlayer->state == PLAYERSTATE_NORMAL && pBarrier->state == BARRIERSTATE_WAIT)
				{// プレイヤーが通常状態の時かつ、バリアが展開されていない時
					if (pPlayer->pos.x >= pBullet->pos.x && pPlayer->pos.y >= pBullet->pos.y)
					{// 弾がプレイヤーの中心から右側かつ、上側から当たった時
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pPlayer->pos.x - pBullet->pos.x) * (pPlayer->pos.x - pBullet->pos.x)
							+ (pPlayer->pos.y - pBullet->pos.y) * (pPlayer->pos.y - pBullet->pos.y)))) >= 18)
						{// 円同士の当たり判定
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pPlayer->pos.x >= pBullet->pos.x && pBullet->pos.y > pPlayer->pos.y)
					{// 弾がプレイヤーの中心から右側かつ、下側から当たった時
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pPlayer->pos.x - pBullet->pos.x) * (pPlayer->pos.x - pBullet->pos.x)
							+ (pBullet->pos.y - pPlayer->pos.y) * (pBullet->pos.y - pPlayer->pos.y)))) >= 18)
						{// 円同士の当たり判定
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pPlayer->pos.x && pPlayer->pos.y >= pBullet->pos.y)
					{// 弾がプレイヤーの中心から左側かつ、上側から当たった時
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pPlayer->pos.x) * (pBullet->pos.x - pPlayer->pos.x)
							+ (pPlayer->pos.y - pBullet->pos.y) * (pPlayer->pos.y - pBullet->pos.y)))) >= 18)
						{// 円同士の当たり判定
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pPlayer->pos.x && pBullet->pos.y > pPlayer->pos.y)
					{// 弾がプレイヤーの中心から左側かつ、下側から当たった時
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pPlayer->pos.x) * (pBullet->pos.x - pPlayer->pos.x)
							+ (pBullet->pos.y - pPlayer->pos.y) * (pBullet->pos.y - pPlayer->pos.y)))) >= 18)
						{// 円同士の当たり判定
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
				}
				else if (pPlayer->state == PLAYERSTATE_NORMAL && pBarrier->state == BARRIERSTATE_ACTIVE)
				{// プレイヤーが通常状態の時かつ、バリアが展開されている時
					if (pBarrier->pos.x >= pBullet->pos.x && pBarrier->pos.y >= pBullet->pos.y)
					{// 弾がバリアの中心から右側かつ、上側から当たった時
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBarrier->pos.x - pBullet->pos.x) * (pBarrier->pos.x - pBullet->pos.x)
								+ (pBarrier->pos.y - pBullet->pos.y) * (pBarrier->pos.y - pBullet->pos.y)))) >= 0)
						{// 円同士の当たり判定
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode,pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBarrier->pos.x >= pBullet->pos.x && pBullet->pos.y > pBarrier->pos.y)
					{// 弾がバリアの中心から右側かつ、下側から当たった時
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBarrier->pos.x - pBullet->pos.x) * (pBarrier->pos.x - pBullet->pos.x)
								+ (pBullet->pos.y - pBarrier->pos.y) * (pBullet->pos.y - pBarrier->pos.y)))) >= 0)
						{// 円同士の当たり判定
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pBarrier->pos.x && pBarrier->pos.y >= pBullet->pos.y)
					{// 弾がバリアの中心から左側かつ、上側から当たった時
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pBarrier->pos.x) * (pBullet->pos.x - pBarrier->pos.x)
								+ (pBarrier->pos.y - pBullet->pos.y) * (pBarrier->pos.y - pBullet->pos.y)))) >= 0)
						{// 円同士の当たり判定
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pBarrier->pos.x && pBullet->pos.y > pBarrier->pos.y)
					{// 弾がバリアの中心から左側かつ、下側から当たった時
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pBarrier->pos.x) * (pBullet->pos.x - pBarrier->pos.x)
								+ (pBullet->pos.y - pBarrier->pos.y) * (pBullet->pos.y - pBarrier->pos.y)))) >= 0)
						{// 円同士の当たり判定
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
				}
			}

			// 敵情報のリセット
			pEnemy = GetEnemy();
		}
	}
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// テクスチャの設定
			if (g_aBullet[nCntBullet].mode == BULLET_NORMAL)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

				switch (g_aBullet[nCntBullet].type)
				{
				case BULLETTYPE_PLAYER:
					pDevice->SetTexture(0, g_apTextureBullet[0]);
					break;
				case BULLETTYPE_ENEMY:
					pDevice->SetTexture(0, g_apTextureBullet[1]);
					break;
				}

			}
			else if (g_aBullet[nCntBullet].mode == BULLET_LASER)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// デスティネーション(描画先)の合成方法の設定

				pDevice->SetTexture(0, g_apTextureBullet[2]);
				
				
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_WAVE)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

				pDevice->SetTexture(0, g_apTextureBullet[3]);
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_BOMBER)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

				pDevice->SetTexture(0, g_apTextureBullet[4]);
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_CIRCLE)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定

				pDevice->SetTexture(0, g_apTextureBullet[5]);
			}

			// 弾の描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntBullet * 4,					// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーション(描画先)の合成方法の設定
}

//=========================================================================================================================
// 弾の設定
//=========================================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type, BULLETMODE mode, int nAttack)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			// 位置の設定
			pBullet->pos = pos;

			// 頂点座標の設定
			SetVertexBullet(nCntBullet);

			pBullet->move = move;

			pBullet->nLife = nLife;

			pBullet->type = type;

			pBullet->mode = mode;

			pBullet->nAttack = nAttack;

			pBullet->bUse = true;

			break;
		}
	}
}

//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexBullet(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aBullet[nIdx].mode == BULLET_NORMAL)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_NORMAL_SIZE_Y, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_LASER)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_LASER_SIZE_Y, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = LASER_COLOR;
		pVtx[1].col = LASER_COLOR;
		pVtx[2].col = LASER_COLOR;
		pVtx[3].col = LASER_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_WAVE)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_WAVE_SIZE_Y, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_BOMBER)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_BOMBER_SIZE_Y, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_CIRCLE)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_CIRCLE_SIZE_Y, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	
	// 頂点バッファの開放
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// 弾の取得
//=========================================================================================================================
BULLET *GetBullet(void)
{
	return &g_aBullet[0];
}