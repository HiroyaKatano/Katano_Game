//=========================================================================================================================
//
// 爆発処理 [explosion.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSION];						// 爆発の情報

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Explosion000.png", &g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nAttack = 200;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// 頂点座標の設定
		SetVertexExplosion(nCntExplosion);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / EXPLOSION_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_X, 1.0f / EXPLOSION_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_X, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffExplosion->Unlock();

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitExplosion(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;

	pExplosion = &g_aExplosion[0];
	pEnemy = GetEnemy();
	
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			// カウンターアップ
			pExplosion->nCounterAnim += 1;

			// 4の倍数の時処理
			if ((pExplosion->nCounterAnim % 3) == 0)
			{
				// アニメーションパターンNo.を更新
				pExplosion->nPatternAnim = (pExplosion->nPatternAnim + 1) % MAX_EXPLOSION_PATTERN;
			}

			// アニメーションの更新
			pVtx[0].tex = D3DXVECTOR2(EXPLOSION_PLAY_ANIM, EXPLOSION_UV_V);
			pVtx[1].tex = D3DXVECTOR2(EXPLOSION_PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V);
			pVtx[3].tex = D3DXVECTOR2(EXPLOSION_UV_U, 0.0f);

			// 頂点座標の設定
			SetVertexExplosion(nCntExplosion);

			if (pExplosion->nPatternAnim == 7)
			{
				pExplosion->bUse = false;
				pExplosion->nPatternAnim = 0;
			}

			if (pExplosion->type == EXPLOSION_BOMBER)
			{ 
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
   					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x >= pExplosion->pos.x && pEnemy->pos.y >= pExplosion->pos.y)
						{// 弾がプレイヤーの中心から右側かつ、上側から当たった時
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pEnemy->pos.x - pExplosion->pos.x) * (pEnemy->pos.x - pExplosion->pos.x)
									+ (pEnemy->pos.y - pExplosion->pos.y) * (pEnemy->pos.y - pExplosion->pos.y)))) >= 18)
							{// 円同士の当たり判定
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pEnemy->pos.x >= pExplosion->pos.x && pExplosion->pos.y > pEnemy->pos.y)
						{// 弾がプレイヤーの中心から右側かつ、下側から当たった時
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pEnemy->pos.x - pExplosion->pos.x) * (pEnemy->pos.x - pExplosion->pos.x)
									+ (pExplosion->pos.y - pEnemy->pos.y) * (pExplosion->pos.y - pEnemy->pos.y)))) >= 18)
							{// 円同士の当たり判定
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pExplosion->pos.x > pEnemy->pos.x && pEnemy->pos.y >= pExplosion->pos.y)
						{// 弾がプレイヤーの中心から左側かつ、上側から当たった時
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pExplosion->pos.x - pEnemy->pos.x) * (pExplosion->pos.x - pEnemy->pos.x)
									+ (pEnemy->pos.y - pExplosion->pos.y) * (pEnemy->pos.y - pExplosion->pos.y)))) >= 18)
							{// 円同士の当たり判定
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pExplosion->pos.x > pEnemy->pos.x && pExplosion->pos.y > pEnemy->pos.y)
						{// 弾がプレイヤーの中心から左側かつ、下側から当たった時
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pExplosion->pos.x - pEnemy->pos.x) * (pExplosion->pos.x - pEnemy->pos.x)
									+ (pExplosion->pos.y - pEnemy->pos.y) * (pExplosion->pos.y - pEnemy->pos.y)))) >= 18)
							{// 円同士の当たり判定
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
					}
				}
			}
			

		}
		// 次の情報にいく
		pVtx += 4;

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// 爆発の描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntExplosion * 4,					// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}
}

//=========================================================================================================================
// 爆発の設定
//=========================================================================================================================
void SetExplosion(D3DXVECTOR3 pos, EXPLOSIONTYPE type)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{
			// 位置の設定
			pExplosion->pos = pos;

			// 頂点座標の設定
			SetVertexExplosion(nCntExplosion);

			pExplosion->type = type;

			pExplosion->bUse = true;
			break;
		}
	}
}

//=========================================================================================================================
//
//=========================================================================================================================
void SetVertexExplosion(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);

	// 頂点バッファの開放
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// 爆発の取得
//=========================================================================================================================
EXPLOSION *GetExplosion(void)
{
	return &g_aExplosion[0];
}
