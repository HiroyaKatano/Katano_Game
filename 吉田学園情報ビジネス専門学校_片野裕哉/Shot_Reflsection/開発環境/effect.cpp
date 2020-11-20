//=========================================================================================================================
//
// エフェクト処理 [effect.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "input.h"
#include "enemy.h"
#include "effect.h"

//=========================================================================================================================
// 構造体の定義
//=========================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;		// 色
	float fDecay;			// 移動の減衰
	float fRadius;			// 半径
	float nCntAlpha;		// α値の移動
	int nLife;				// 寿命
	bool bUse;				// 使用しているかどうか
}Effect;

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
Effect g_aEffect[MAX_EFFECT];						// エフェクトの情報

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fDecay = NULL;
		g_aEffect[nCntEffect].fRadius = NULL;
		g_aEffect[nCntEffect].nCntAlpha = NULL;
		g_aEffect[nCntEffect].nLife = NULL;
		g_aEffect[nCntEffect].bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EFFECT,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, EFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(EFFECT_SIZE, EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE, 0.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[1].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[2].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[3].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitEffect(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateEffect(void)
{
	Effect *pEffect;
	VERTEX_2D *pVtx;

	pEffect = &g_aEffect[0];

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		g_aEffect[nCntEffect].col.a -= 0.04f;

		if (g_aEffect[nCntEffect].col.a <= 0.0f)	//0.0fになったら何もしない
		{
			g_aEffect[nCntEffect].bUse = false;
		}

		//頂点カラーの設定
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;
		// 次の情報にいく
		pVtx += 4;

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//エフェクトの描画処理
//=========================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// デスティネーション(描画先)の合成方法の設定

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			// エフェクトの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntEffect * 4,					// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// デスティネーション(描画先)の合成方法の設定
}

//=========================================================================================================================
// エフェクトの設定
//=========================================================================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fDecay, float fRadius, float fCntAlpha, int nLife)
{
	Effect *pEffect;
	VERTEX_2D *pVtx;

	pEffect = &g_aEffect[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// 爆発の設定
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y + 20.0f, 0.0f);	//Zは0.0固定
			pVtx[1].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y - 20.0f, 0.0f);

			// 位置設定
			pEffect->pos = pos;

			// 移動量の設定
			pEffect->move = move;

			// 色設定
			pEffect->col = col;

			// 移動量の減少値
			pEffect->fDecay = fDecay;

			// 半径の設定
			pEffect->fRadius = fRadius;

			// α値の移動量
			pEffect->nCntAlpha = fCntAlpha;

			// 寿命の設定
			pEffect->nLife = nLife;

			// trueで返す
			pEffect->bUse = true;

			break;
		}
	}
	// 頂点バッファをアンロッ クする
	g_pVtxBuffEffect->Unlock();
}