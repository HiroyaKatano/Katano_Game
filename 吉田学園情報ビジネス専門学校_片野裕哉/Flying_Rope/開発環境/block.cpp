//
//
//
//
//
//
#include "block.h"
#include "player.h"
#include "result.h"
#include "fade.h"

//
// マクロ定義
//
#define MAX_BLOCK (256)
#define MAX_TYPE_BLOCK (2)

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			// テクスチャ
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			// テクスチャ
BLOCK g_aBlock[MAX_BLOCK];							// ブロックの上限

//
// 初期化処理
//
HRESULT InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &g_pTextureBlock);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal_star.png", &g_pTextureGoal);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_BLOCK * VTX_NUM,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aBlock[nCntBlock].col = BLOCK_COLOR;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
	}


	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		SetVertexBlock(nCntBlock);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitBlock(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// テクスチャの開放
	//for (int nCnt = 0; nCnt < MAX_TYPE_BLOCK; nCnt++)
	//{
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
	//}

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
}


//
// 更新処理
//
void UpdateBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			SetVertexBlock(nCntBlock);
		}
	}
	
}


//
// 描画処理
//
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// テクスチャの設定
			switch (g_aBlock[nCntBlock].BlockType)
			{
			case 0:
				pDevice->SetTexture(0, g_pTextureBlock);
				break;
			case 1:
				pDevice->SetTexture(0, g_pTextureGoal);
			default:
				break;
			}
			

			// プレイヤーの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntBlock * VTX_NUM,			// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}
}


//
// ブロックのセット処理
//
void SetBlock(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockMove, float fBlockWigth, float fBlockHeight, BLOCKTYPE BlockType)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{
			// 位置の設定
			pBlock->pos = BlockPos;

			pBlock->move = BlockMove;

			pBlock->fWidth = fBlockWigth;

			pBlock->fHeight = fBlockHeight;

			pBlock->BlockType = BlockType;
			
			// 頂点座標の設定
			SetVertexBlock(nCntBlock);

			pBlock->bUse = true;

			break;
		}
	}
}


//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexBlock(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * VTX_NUM;


	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, Z_AXIS_ZERO);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y, Z_AXIS_ZERO);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, Z_AXIS_ZERO);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, Z_AXIS_ZERO);

	// 頂点カラーの設定
	pVtx[0].col = BLOCK_COLOR;
	pVtx[1].col = BLOCK_COLOR;
	pVtx[2].col = BLOCK_COLOR;
	pVtx[3].col = BLOCK_COLOR;

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aBlock[nIdx].fWidth / g_aBlock[nIdx].fHeight, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aBlock[nIdx].fWidth / g_aBlock[nIdx].fHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	
	// 頂点バッファの開放
	g_pVtxBuffBlock->Unlock();
}


//
// ブロックの情報取得
//
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}


//
//
//
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	BLOCK *pBlock;
	RESULT *pResult = GetResult();

	bool bLand = false;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			if (pPos->x + fWidth > pBlock->pos.x + 1.0f&&
				pPos->x - fWidth < pBlock->pos.x + pBlock->fWidth)
			{// プレイヤーの右端がブロックの左端より右側かつプレイヤーの左端がブロックの右端より左側に位置するとき
				if (pPosOld->y <= pBlock->pos.y - 1.0f)
				{// 前回のプレイヤーの下端がブロックの上端に触れていないとき
					if (pPos->y > pBlock->pos.y - 1.0f)
					{// 現在のプレイヤーの下端がブロックの上端よりも下側に位置するとき
						pPos->y = pBlock->pos.y - 1.0f;
						pMove->y = 0.0f;
						bLand = true;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// ブロックの種類がゴールであった場合
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
 				else if (pPosOld->y - fHeight >= pBlock->pos.y + pBlock->fHeight)
				{// 前回のプレイヤーの上端がブロックの下端に触れていないとき
					if (pPos->y - fHeight < pBlock->pos.y + pBlock->fHeight)
					{// 現在のプレイヤーの上端がブロックの下端より上側に位置するとき
						pPos->y = (pBlock->pos.y + pBlock->fHeight) + fHeight;
						pMove->y = 1.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// ブロックの種類がゴールであった場合
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
			}

			if (pPos->y > pBlock->pos.y &&
				pPos->y - fHeight < pBlock->pos.y + pBlock->fHeight)
			{// 現在のプレイヤーの下端がブロックの上端よりも下側かつプレイヤーの上端がブロックの下端より上側に位置するとき
				if (pPosOld->x - fWidth >= pBlock->pos.x + pBlock->fWidth + 1.0f)
				{// 前回のプレイヤーの左端がブロックの右端に触れていないとき
					if (pPos->x - fWidth < pBlock->pos.x + pBlock->fWidth + 1.0f)
					{// 現在のプレイヤーの左端がブロックの右端より左側に位置するとき
						pPos->x = (pBlock->pos.x + pBlock->fWidth) + fWidth + 1.0f;
						pMove->x = 0.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// ブロックの種類がゴールであった場合
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
				else if (pPosOld->x + fWidth <= pBlock->pos.x)
				{// 前回のプレイヤーの右端がブロックの左端に触れていないとき
					if (pPos->x + fWidth > pBlock->pos.x)
					{// 現在のプレイヤーの右端がブロックの左端より左側に位置するとき
						pPos->x = pBlock->pos.x - fWidth;
						pMove->x = 0.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// ブロックの種類がゴールであった場合
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
			}
		}
	}

	return bLand;
}
