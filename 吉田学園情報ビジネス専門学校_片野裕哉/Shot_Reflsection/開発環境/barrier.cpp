//=========================================================================================================================
//
// バリア [barrier.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "barrier.h"
#include "player.h"
#include "Score.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBarrier = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureBarrier = NULL;			// テクスチャ
BARRIER g_Barrier;

//=========================================================================================================================
// バリアの初期化処理
//=========================================================================================================================
HRESULT InitBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\barrier001.png", &g_pTextureBarrier);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBarrier,
		NULL)))
	{
		return E_FAIL;
	}

	// アニメーションカウンターとアニメーションパターンNo.の初期化
	g_Barrier.nCounterAnim = 0;
	g_Barrier.nPatternAnim = 0;
	g_Barrier.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Barrier.state = BARRIERSTATE_WAIT;
	g_Barrier.nCounterState = BARRIER_TIMER;
	g_Barrier.nCounterDisp = 0;
	g_Barrier.bDisp = true;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さ
	g_Barrier.fLengthBarrier = sqrtf(VERTEX_X * VERTEX_X + VERTEX_Y * VERTEX_Y);

	// 対角線の角度
	g_Barrier.fAngleBarrier = atan2f(VERTEX_X, VERTEX_Y);

	// バリアの回転角
	g_Barrier.rotBarrier = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//pVtx[0].pos.x = g_pos.x + sinf(g_fAngleBarrier + D3DX_PI * 1.75f) * g_fLengthBarrier;
	//pVtx[0].pos.y = g_pos.y + cosf(g_fAngleBarrier + D3DX_PI * 1.75f) * g_fLengthBarrier;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = g_pos.x + sinf(D3DX_PI * 1.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[1].pos.y = g_pos.y + cosf(D3DX_PI * 1.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = g_pos.x + sinf(D3DX_PI * 0.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[2].pos.y = g_pos.y + cosf(D3DX_PI * 0.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = g_pos.x + sinf(g_fAngleBarrier + D3DX_PI * 0.75f) * g_fLengthBarrier;
	//pVtx[3].pos.y = g_pos.y + cosf(g_fAngleBarrier + D3DX_PI * 0.75f) * g_fLengthBarrier;
	//pVtx[3].pos.z = 0.0f;

	pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 1.0f / TEXTURE_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBarrier->Unlock();

	return S_OK;
}

//=========================================================================================================================
// バリアの終了処理
//=========================================================================================================================
void UninitBarrier(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBarrier != NULL)
	{
		g_pVtxBuffBarrier->Release();
		g_pVtxBuffBarrier = NULL;
	}

	// テクスチャの開放
	if (g_pTextureBarrier != NULL)
	{
		g_pTextureBarrier->Release();
		g_pTextureBarrier = NULL;
	}
}

//=========================================================================================================================
// バリアの更新処理
//=========================================================================================================================
void UpdateBarrier(void)
{
	VERTEX_2D *pVtx;
	BULLET *pBullet;
	PLAYER *pPlayer;

	pBullet = GetBullet();
	pPlayer = GetPlayer();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Barrier.state == BARRIERSTATE_ACTIVE)
	{// バリア展開時

		// 特殊ゲージの消費
		g_Barrier.nCounterState -= BARRIER_COST;
		
		// 位置の更新
		g_Barrier.pos.x = pPlayer->pos.x;
		g_Barrier.pos.y = pPlayer->pos.y;

		pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

		if (g_Barrier.nCounterState <= 0)
		{
			g_Barrier.state = BARRIERSTATE_WAIT;

			pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
		}
		else if (g_Barrier.nCounterState <= BARRIER_FLASH && g_Barrier.nCounterState > 0)
		{
			if (g_Barrier.nCounterState % 5 == 0)
			{
				pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
			}
		}
	}
	else if (g_Barrier.state == BARRIERSTATE_WAIT)
	{// バリアを展開していない時
		if (g_Barrier.nCounterState >= 0 && g_Barrier.nCounterState < BARRIER_TIMER && pPlayer->state == PLAYERSTATE_NORMAL)
		{// 特殊ゲージが最大まで溜まっておらず、プレイヤーが通常状態の時

			// 特殊ゲージの回復
			g_Barrier.nCounterState += 1;
		}
		else if (g_Barrier.nCounterState >= BARRIER_TIMER)
		{// 特殊ゲージが最大以上の時

			// 特殊ゲージが最大値を超えないように補正
			g_Barrier.nCounterState = BARRIER_TIMER;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBarrier->Unlock();
}

//=========================================================================================================================
// バリアの描画処理
//=========================================================================================================================
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBarrier, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBarrier);

	if (g_Barrier.state == BARRIERSTATE_ACTIVE)
	{
		// バリアの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			0,								// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}

//=========================================================================================================================
// バリアの設定
//=========================================================================================================================
void SetBarrier(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Barrier.state == BARRIERSTATE_WAIT)
	{
		// 位置の設定
		g_Barrier.pos = pos;

		pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

		g_Barrier.state = BARRIERSTATE_ACTIVE;
	}
}


//=========================================================================================================================
// バリアの取得
//=========================================================================================================================
BARRIER *GetBarrier(void)
{
	return &g_Barrier;
}

//=========================================================================================================================
// バリアのヒット処理
//=========================================================================================================================
bool HitBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETMODE mode,int nDamage)
{

	SetBullet(pos, move * -2, LIFE_BULLET, BULLETTYPE_PLAYER, mode, nDamage * 10);

	AddScore(nDamage);

	return true;
}
