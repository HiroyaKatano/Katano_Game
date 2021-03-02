//
//
//
//
//
//
#include "rope_vec.h"
#include "player.h"
#include "input.h"

//
// マクロ定義
//

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRopeVec = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureRopeVec = NULL;			// テクスチャ
ROPE_VEC g_aRopeVec[MAX_ROPE_VEC];						// ロープの向き表記の情報
AXIS_ROT g_AxisRot;										// 矢印用の回転軸の情報


//
// 初期化処理
//
HRESULT InitRopeVec(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer = GetPlayer();

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rope_vec.png", &g_pTextureRopeVec);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_ROPE_VEC * VTX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRopeVec,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCntRopeVec = 0; nCntRopeVec < MAX_ROPE_VEC; nCntRopeVec++)
	{
		g_aRopeVec[nCntRopeVec].pos = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aRopeVec[nCntRopeVec].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		g_aRopeVec[nCntRopeVec].fWidth = 0.0f;
		g_aRopeVec[nCntRopeVec].fHeight = 0.0f;
		g_aRopeVec[nCntRopeVec].rot = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aRopeVec[nCntRopeVec].fLength = sqrtf(ROPE_VEC_SIZE_VERTEX_X * ROPE_VEC_SIZE_VERTEX_X + ROPE_VEC_SIZE_VERTEX_Y * ROPE_VEC_SIZE_VERTEX_Y);
		g_aRopeVec[nCntRopeVec].fAngle = atan2f(ROPE_VEC_SIZE_VERTEX_X, -ROPE_VEC_SIZE_VERTEX_X);
	}
	
	g_AxisRot.pos = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
	g_AxisRot.rot = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);

	g_AxisRot.pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - PLAYER_SIZE_Y / 2, Z_AXIS_ZERO);

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRopeVec->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRopeVec = 0; nCntRopeVec < MAX_ROPE_VEC; nCntRopeVec++)
	{
		SetVertexRopeVec(nCntRopeVec);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[1].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[2].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[3].col = ROPE_VEC_NOT_NEUTORAL_COLOR;

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += VTX_NUM;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffRopeVec->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitRopeVec(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffRopeVec != NULL)
	{
		g_pVtxBuffRopeVec->Release();
		g_pVtxBuffRopeVec = NULL;
	}

	// テクスチャの開放
	if (g_pTextureRopeVec != NULL)
	{
		g_pTextureRopeVec->Release();
		g_pTextureRopeVec = NULL;
	}
}


//
// 更新処理
//
void UpdateRopeVec(void)
{
	ROPE_VEC *pRopeVec = &g_aRopeVec[0];
	PLAYER *pPlayer = GetPlayer();

	g_AxisRot.pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - PLAYER_SIZE_Y / 2, Z_AXIS_ZERO);
	
	for (int nCnt = 0; nCnt < MAX_ROPE_VEC; nCnt++)
	{
		g_AxisRot.rot.z = D3DX_PI - (nCnt * (D3DX_PI / 4));
		g_aRopeVec[nCnt].rot.z = D3DX_PI - (nCnt * (D3DX_PI / 4));

		SetVertexRopeVec(nCnt);
	}
}


//
// 描画処理
//
void DrawRopeVec(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRopeVec, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRopeVec = 0; nCntRopeVec < MAX_ROPE_VEC; nCntRopeVec++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRopeVec);

		// プレイヤーの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCntRopeVec * VTX_NUM,			// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}


//
// ワイヤーのセット処理
//
void SetRopeVec(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRopeVecWigth, float fRopeVecHeight)
{
	ROPE_VEC *pRopeVec;
	pRopeVec = &g_aRopeVec[0];

	for (int nCntRopeVec = 0; nCntRopeVec < MAX_ROPE_VEC; nCntRopeVec++, pRopeVec++)
	{
			// 位置の設定
			pRopeVec->pos = pos;

			pRopeVec->fWidth = fRopeVecWigth;

			pRopeVec->fHeight = fRopeVecHeight;

			// 頂点座標の設定
			SetVertexRopeVec(nCntRopeVec);

			PlaySound(SOUND_LABEL_SE_ROPE);

			break;
	}
}


//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexRopeVec(int nIdx)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer = GetPlayer();

	g_pVtxBuffRopeVec->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * VTX_NUM;

	g_aRopeVec[nIdx].pos = D3DXVECTOR3(g_AxisRot.pos.x + sinf(g_AxisRot.rot.z) * 50.0f, g_AxisRot.pos.y + cosf(g_AxisRot.rot.z) * 50.0f, Z_AXIS_ZERO);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aRopeVec[nIdx].pos.x + sinf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 0 / 2)) * g_aRopeVec[nIdx].fLength, g_aRopeVec[nIdx].pos.y + cosf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 0 / 4)) * g_aRopeVec[nIdx].fLength, Z_AXIS_ZERO);
	pVtx[1].pos = D3DXVECTOR3(g_aRopeVec[nIdx].pos.x + sinf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * -1 / 2)) * g_aRopeVec[nIdx].fLength, g_aRopeVec[nIdx].pos.y + cosf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * -1 / 2)) * g_aRopeVec[nIdx].fLength, Z_AXIS_ZERO);
	pVtx[2].pos = D3DXVECTOR3(g_aRopeVec[nIdx].pos.x + sinf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 1 / 2)) * g_aRopeVec[nIdx].fLength, g_aRopeVec[nIdx].pos.y + cosf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 1 / 2)) * g_aRopeVec[nIdx].fLength, Z_AXIS_ZERO);
	pVtx[3].pos = D3DXVECTOR3(g_aRopeVec[nIdx].pos.x + sinf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 2 / 2)) * g_aRopeVec[nIdx].fLength, g_aRopeVec[nIdx].pos.y + cosf(g_aRopeVec[nIdx].rot.z + (g_aRopeVec[nIdx].fAngle + D3DX_PI * 2 / 2)) * g_aRopeVec[nIdx].fLength, Z_AXIS_ZERO);


	// 頂点カラーの設定
	if (pPlayer->vec == nIdx)
	{
		pVtx[0].col = ROPE_VEC_NEUTORAL_COLOR;
		pVtx[1].col = ROPE_VEC_NEUTORAL_COLOR;
		pVtx[2].col = ROPE_VEC_NEUTORAL_COLOR;
		pVtx[3].col = ROPE_VEC_NEUTORAL_COLOR;
	}
	else
	{
		pVtx[0].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[1].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[2].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
		pVtx[3].col = ROPE_VEC_NOT_NEUTORAL_COLOR;
	}

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	// 頂点バッファの開放
	g_pVtxBuffRopeVec->Unlock();
}


//
// ワイヤーの情報取得
//
ROPE_VEC *GetRopeVec(void)
{
	return &g_aRopeVec[0];
}