//=========================================================================================================================
//
// 敵 [enemy.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "enemy.h"
#include "explosion.h"
#include "effect.h"
#include "Score.h"
#include "sound.h"
#include "BG.h"
#include "bullet.h"
#include "item.h"
#include <stdlib.h>

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				// 頂点バッファへのポインタ
ENEMY g_aEnemy[MAX_ENEMY];									// 敵の情報
int g_nCnt;												// カウント
int g_nCounterEnemyAnim;								// アニメーションカウント
int g_nPatternEnemyAnim;								// アニメーションパターン
int g_nTimer;

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;

	//// デバイスの取得
	pDevice = GetDevice();
	pEnemy = &g_aEnemy[0];

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy007.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy008.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy009.png", &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\boss.png", &g_apTextureEnemy[3]);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = NULL;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 1000;
		g_aEnemy[nCntEnemy].nCounterEnemy = 0;
		g_aEnemy[nCntEnemy].nCounterBullet = 1;
		g_aEnemy[nCntEnemy].fhase = FHASE_0;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	g_nCnt = 0;

	g_nTimer = 0;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		SetVertexEnemy(nCntEnemy);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / ENEMY_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_X, 1.0f / ENEMY_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / ENEMY_TEXTURE_X, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffEnemy->Unlock();


	if (pEnemy->fhase == FHASE_0 && pEnemy->nCounterEnemy <= 0)
	{
		pEnemy->fhase = FHASE_1;
		Fhase1st();
	}

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitEnemy(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	for (int nCntType = 0; nCntType < MAX_TYPE_ENEMY; nCntType++)
	{
		// テクスチャの開放
		if (g_apTextureEnemy != NULL)
		{
			g_apTextureEnemy[nCntType]->Release();
			g_apTextureEnemy[nCntType] = NULL;
		}
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateEnemy(void)
{
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;
	BULLET *pBullet;

	// 変数の受け渡し
	pEnemy = &g_aEnemy[0];
	pBullet = GetBullet();

	// 変数の増加
	g_nCnt++;


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	// 敵の更新
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			// 敵の動作
			//if (g_nCnt > 0 && g_nCnt <= MAX_COUNT / 2)
			//{
				pEnemy->pos.x += pEnemy->move.x;
			//}
			//else if (g_nCnt > MAX_COUNT / 2 && g_nCnt <= MAX_COUNT)
			//{
			//	pEnemy->pos.x -= pEnemy->move.x;

			//	if (g_nCnt >= MAX_COUNT)
			//	{
			//		g_nCnt = 0;
			//	}
			//}
			
			pEnemy->pos.y += pEnemy->move.y;

			// 頂点座標の設定
			SetVertexEnemy(nCntEnemy);

			if (pEnemy->pos.x + ENEMY_SIZE_X < BG_POS_LEFT_X ||
				pEnemy->pos.x - ENEMY_SIZE_X > BG_POS_RIGHT_X ||
				pEnemy->pos.y > BG_POS_UNDER_Y + ENEMY_SIZE_Y)
			{
				pEnemy->bUse = false;
				g_aEnemy->nCounterEnemy--;
			}

			if (pEnemy->nCounterBullet > 0)
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;
				pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->move.x, pEnemy->pos.y + ENEMY_SIZE_Y, 0.0f);
				move = D3DXVECTOR3(0.0f, -MOVE_ENEMY_BULLET, 0.0f);
				SetBullet(pos, move, LIFE_BULLET, BULLETTYPE_ENEMY, BULLET_NORMAL, 100);

				pEnemy->nCounterBullet--;
			}
			else if (pEnemy->nCounterBullet <= 0)
			{
				g_nTimer += 1;
				
				if (g_nTimer % 120 == 0)
				{
					pEnemy->nCounterBullet = 1;
				}
			}
		}

		switch (pEnemy->state)
		{
		case ENEMYSTATE_DAMAGE:
			pEnemy->nCounterState--;
			if (pEnemy->nCounterState <= 0)
			{
				pEnemy->state = ENEMYSTATE_NORMAL;

				pVtx[0 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
				pVtx[1 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
				pVtx[2 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
				pVtx[3 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(ENEMY_COLOR_R, ENEMY_COLOR_G, ENEMY_COLOR_B, ENEMY_COLOR_A);
			}
			break;
		}

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	if (pEnemy->fhase == FHASE_1 && pEnemy->nCounterEnemy <= 0)
	{
		pEnemy->fhase = FHASE_2;
		Fhase2nd();
	}
	else if (pEnemy->fhase == FHASE_2 && pEnemy->nCounterEnemy <= 0)
	{
		pEnemy->fhase = FHASE_3;
		Fhase3rd();
	}
	else if (pEnemy->fhase == FHASE_3 && pEnemy->nCounterEnemy <= 0)
	{
		pEnemy->fhase = FHASE_BOSS;
		FhaseBoss();
	}
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

		if (g_aEnemy[nCntEnemy].bUse == true)
			// 敵の描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntEnemy * 4,					// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
	}
}

//=========================================================================================================================
// 敵のセット設定
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	pEnemy->nCounterEnemy++;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			// 位置の設定
			pEnemy->pos = pos;

			pEnemy->move = move;

			//// 頂点座標の設定
			SetVertexEnemy(nCntEnemy);

			pEnemy->nType = nType;

			pEnemy->bUse = true;
			break;
		}
	}
}

//=========================================================================================================================
//
//=========================================================================================================================
void SetVertexEnemy(int nIdx)
{
	VERTEX_2D *pVtx;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE_X, g_aEnemy[nIdx].pos.y + ENEMY_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE_X, g_aEnemy[nIdx].pos.y - ENEMY_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE_X, g_aEnemy[nIdx].pos.y + ENEMY_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE_X, g_aEnemy[nIdx].pos.y - ENEMY_SIZE_Y, 0.0f);

	// テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(PLAY_ENEMY_ANIM, ENEMY_UV_V);
	pVtx[1].tex = D3DXVECTOR2(PLAY_ENEMY_ANIM, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(ENEMY_UV_U, ENEMY_UV_V);
	pVtx[3].tex = D3DXVECTOR2(ENEMY_UV_U, 0.0f);

	// 頂点バッファの開放
	g_pVtxBuffEnemy->Unlock();
}

//
// 敵の取得
//
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=========================================================================================================================
// 敵のヒット処理
//=========================================================================================================================
bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;

	g_aEnemy[nIdx].nLife -= nDamage;

	int nType = rand() % 4;
	int nDrop = rand() % 100;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nIdx].nLife <= 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			//SetEffect(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),0.0f,10.0f,0.015f,60);
			//SetEffect(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),0.0f,10.0f,0.015f,60);
			//SetEffect(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),0.0f,10.0f,0.015f,60);
			SetExplosion(g_aEnemy[nIdx].pos, EXPLOSION_ENEMY);
		}

		if (nDrop >= 0 && nDrop < 25)
		{
			SetItem(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f, 2.5f, 0.0f), 0);
		}
		else if (nDrop >= 25 && nDrop < 50)
		{
			SetItem(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f, 2.5f, 0.0f), 1);
		}
		else if (nDrop >= 50 && nDrop < 75)
		{
			SetItem(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f, 2.5f, 0.0f), 2);
		}
		else if (nDrop >= 75 && nDrop < 100)
		{
			SetItem(D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].move.x, g_aEnemy[nIdx].pos.y, g_aEnemy[nIdx].pos.z), D3DXVECTOR3(0.0f, 2.5f, 0.0f), 3);
		}

		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		if (g_aEnemy[nIdx].nType == 0)
		{
			AddScore(100);
		}
		else if (g_aEnemy[nIdx].nType == 1)
		{
			AddScore(200);
		}
		else if (g_aEnemy[nIdx].nType == 2)
		{
			AddScore(300);
		}
		else if (g_aEnemy[nIdx].nType == 3)
		{
			AddScore(400);
		}
		else if (g_aEnemy[nIdx].nType == 4)
		{
			AddScore(500);
		}
		else if (g_aEnemy[nIdx].nType == 5)
		{
			AddScore(600);
		}
		else if (g_aEnemy[nIdx].nType == 6)
		{
			AddScore(700);
		}

		g_aEnemy[nIdx].bUse = false;

		g_aEnemy->nCounterEnemy--;

		return true;
	}
	else
	{
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 5;

		pVtx[0 + 4 * nIdx].col = D3DCOLOR_RGBA(255, 0, 0, ENEMY_COLOR_A);
		pVtx[1 + 4 * nIdx].col = D3DCOLOR_RGBA(255, 0, 0, ENEMY_COLOR_A);
		pVtx[2 + 4 * nIdx].col = D3DCOLOR_RGBA(255, 0, 0, ENEMY_COLOR_A);
		pVtx[3 + 4 * nIdx].col = D3DCOLOR_RGBA(255, 0, 0, ENEMY_COLOR_A);

		return false;
	}

	g_pVtxBuffEnemy->Unlock();
}


//
//
//
void Fhase1st(void)
{
	// 敵の初期配置
	for (int nCntEnemy = 0; nCntEnemy < MAX_LINE; nCntEnemy++)
	{
		SetEnemy(D3DXVECTOR3(ENEMY_VERTEX_X + (nCntEnemy) * 70.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 3.0f, 0.0f), 0);
		SetEnemy(D3DXVECTOR3(1320.0f + (nCntEnemy) * -70.0f, -600.0f, 0.0f), D3DXVECTOR3(-1.0f, 3.0f, 0.0f), 1);
		SetEnemy(D3DXVECTOR3(910.0f + (nCntEnemy) * 70.0f, -1200.0f, 0.0f), D3DXVECTOR3(0.0f, 3.0f, 0.0f), 2);
		SetEnemy(D3DXVECTOR3(ENEMY_VERTEX_X + (nCntEnemy) * 70.0f, -1200.0f, 0.0f), D3DXVECTOR3(0.5f, 2.0f, 0.0f), 0);
		SetEnemy(D3DXVECTOR3(1320.0f + (nCntEnemy) * -70.0f, -1300.0f, 0.0f), D3DXVECTOR3(-0.5f, 2.0f, 0.0f), 1);
		SetEnemy(D3DXVECTOR3(910.0f + (nCntEnemy) * 70.0f, -1400.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 2);
		//SetEnemy(D3DXVECTOR3(910.0f + (nCntEnemy) * 70.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 3);
	}
}


//
//
//
void Fhase2nd(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 8; nCntEnemy++)
	{
		SetEnemy(D3DXVECTOR3(ENEMY_VERTEX_X + (nCntEnemy + 1) * 70.0f, 500.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.0f), 1);
	}
}


//
//
//
void Fhase3rd(void)
{
}


//
//
//
void Fhase4th(void)
{
}


//
//
//
void FhaseBoss(void)
{
}
