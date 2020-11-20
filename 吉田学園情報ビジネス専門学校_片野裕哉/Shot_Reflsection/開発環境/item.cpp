//=========================================================================================================================
//
// アイテム [item.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "item.h"
#include "player.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_TYPE_ITEM] = {};			// テクスチャ
ITEM g_aItem[MAX_ITEM];						// 爆発の情報

//=========================================================================================================================
// アイテムの初期化処理
//=========================================================================================================================
HRESULT InitItem(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtex;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemL.png", &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemW.png", &g_apTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemC.png", &g_apTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemB.png", &g_apTextureItem[3]);



	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtex, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// 頂点座標の設定
		SetVertexItem(nCntItem);

		// rhwの設定
		pVtex[0].rhw = 1.0f;
		pVtex[1].rhw = 1.0f;
		pVtex[2].rhw = 1.0f;
		pVtex[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtex[0].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[1].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[2].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[3].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);

		// 頂点情報の設定
		pVtex[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtex[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtex[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtex[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtex += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

//=========================================================================================================================
// アイテムの終了処理
//=========================================================================================================================
void UninitItem(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

	for (int nCntType = 0; nCntType < MAX_TYPE_ITEM; nCntType++)
	{
		// テクスチャの開放
		if (g_apTextureItem != NULL)
		{
			g_apTextureItem[nCntType]->Release();
			g_apTextureItem[nCntType] = NULL;
		}
	}
}

//=========================================================================================================================
// アイテムの更新処理
//=========================================================================================================================
void UpdateItem(void)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos += g_aItem[nCntItem].move;
		SetVertexItem(nCntItem);

		if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x && pPlayer->pos.y >= g_aItem[nCntItem].pos.y)
		{// 弾がバリアの中心から右側かつ、上側から当たった時
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((pPlayer->pos.x - g_aItem[nCntItem].pos.x) * (pPlayer->pos.x - g_aItem[nCntItem].pos.x)
					+ (pPlayer->pos.y - g_aItem[nCntItem].pos.y) * (pPlayer->pos.y - g_aItem[nCntItem].pos.y)))) >= 0)
			{// 円同士の当たり判定
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x && g_aItem[nCntItem].pos.y > pPlayer->pos.y)
		{// 弾がバリアの中心から右側かつ、下側から当たった時
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((pPlayer->pos.x - g_aItem[nCntItem].pos.x) * (pPlayer->pos.x - g_aItem[nCntItem].pos.x)
					+ (g_aItem[nCntItem].pos.y - pPlayer->pos.y) * (g_aItem[nCntItem].pos.y - pPlayer->pos.y)))) >= 0)
			{// 円同士の当たり判定
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (g_aItem[nCntItem].pos.x > pPlayer->pos.x && pPlayer->pos.y >= g_aItem[nCntItem].pos.y)
		{// 弾がバリアの中心から左側かつ、上側から当たった時
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((g_aItem[nCntItem].pos.x - pPlayer->pos.x) * (g_aItem[nCntItem].pos.x - pPlayer->pos.x)
					+ (pPlayer->pos.y - g_aItem[nCntItem].pos.y) * (pPlayer->pos.y - g_aItem[nCntItem].pos.y)))) >= 0)
			{// 円同士の当たり判定
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (g_aItem[nCntItem].pos.x > pPlayer->pos.x && g_aItem[nCntItem].pos.y > pPlayer->pos.y)
		{// 弾がバリアの中心から左側かつ、下側から当たった時
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((g_aItem[nCntItem].pos.x - pPlayer->pos.x) * (g_aItem[nCntItem].pos.x - pPlayer->pos.x)
					+ (g_aItem[nCntItem].pos.y - pPlayer->pos.y) * (g_aItem[nCntItem].pos.y - pPlayer->pos.y)))) >= 0)
			{// 円同士の当たり判定
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
	}
}

//=========================================================================================================================
// アイテムの描画処理
//=========================================================================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].nType]);

		if (g_aItem[nCntItem].bUse == true)
		{
			// アイテムの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntItem * 4,					// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}
}

//=========================================================================================================================
// アイテムの設定
//=========================================================================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	ITEM *pItem;
	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == false)
		{
			// 位置の設定
			pItem->pos = pos;

			pItem->move = move;

			// 頂点座標の設定
			SetVertexItem(nCntItem);

			pItem->nType = nType;

			pItem->bUse = true;
			break;
		}
	}
}

//=========================================================================================================================
//
//=========================================================================================================================
void SetVertexItem(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZE_X, g_aItem[nIdx].pos.y + ITEM_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZE_X, g_aItem[nIdx].pos.y - ITEM_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZE_X, g_aItem[nIdx].pos.y + ITEM_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZE_X, g_aItem[nIdx].pos.y - ITEM_SIZE_Y, 0.0f);

	// 頂点バッファの開放
	g_pVtxBuffItem->Unlock();
}


//
//
//
bool HitItem(int nIdx, int nType)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	switch (g_aItem[nIdx].nType)
	{
	case 0:
		pPlayer->SelectBullet = SELECT_LASER;
		break;
	case 1:
		pPlayer->SelectBullet = SELECT_WAVE;
		break;
	case 2:
		pPlayer->SelectBullet = SELECT_CIRCLE;
		break;
	case 3:
		pPlayer->SelectBullet = SELECT_BOMBER;
		break;
	default:
		break;
	}

	return true;
}
