//=========================================================================================================================
//
// パーティクル [Particle.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Particle.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "player.h"

//
//
//
#define MAX_PARTICLE (2048)			// パーティクルの最大数
#define PARTICLE_SIZE (2.0f)		// パーティクルの大きさ
#define PARTICLE_SPD (5.0f)			// パーティクルの移動量(速度)
#define PARTICLE_LIFE (100)			// パーティクルの寿命

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			// テクスチャへのポインタ
PARTICLE g_aParticle[MAX_PARTICLE];						// パーティクルの情報

//
// 初期化処理
//
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureParticle);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].bUse = false;
		g_aParticle[nCnt].nLife = 0;
	}


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - PARTICLE_SIZE, g_aParticle[nCnt].pos.y - PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - PARTICLE_SIZE, g_aParticle[nCnt].pos.y + PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + PARTICLE_SIZE, g_aParticle[nCnt].pos.y - PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + PARTICLE_SIZE, g_aParticle[nCnt].pos.y + PARTICLE_SIZE, g_aParticle[nCnt].pos.z);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitParticle(void)
{
	// テクスチャの開放
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}


//
// 更新処理
//
void UpdateParticle(void)
{
	Camera *pCamera = GetCamera();
	PARTICLE *pParticle = &g_aParticle[0];
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	if (GetKeyboardPress(DIK_9) == true)
	{
		SetParticle(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y) * PARTICLE_SPD, 0.0f, cosf(pPlayer->rot.y) * PARTICLE_SPD));
	}

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			pParticle->pos.x -= pParticle->move.x;
			pParticle->pos.z -= pParticle->move.z;

			g_aParticle[nCnt].nLife++;
			if (g_aParticle[nCnt].nLife >= PARTICLE_LIFE)
			{
				pParticle->bUse = false;
				g_aParticle[nCnt].nLife = 0;
			}
		}
	}
}


//
// 描画処理
//
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	PARTICLE *pParticle = &g_aParticle[0];

	D3DXMATRIX mtxView;								// ビューマトリックス取得用
	D3DXMATRIX mtxTrans;							// 計算用マトリックス

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zバッファを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// デスティネーション(描画先)の合成方法の設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pParticle->mtxWorld);

			// ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pParticle->mtxWorld, NULL, &mtxView);	// 逆行列を求める
			pParticle->mtxWorld._41 = 0.0f;
			pParticle->mtxWorld._42 = 0.0f;
			pParticle->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pParticle->pos.x, pParticle->pos.y, pParticle->pos.z);

			D3DXMatrixMultiply(&pParticle->mtxWorld, &pParticle->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pParticle->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle);

			

			// ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCnt * 4,						// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数

		}
	}

	// デスティネーション(描画先)の合成方法の設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテスト戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// 標準に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
// パーティクルの設定
//
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	PARTICLE *pParticle = &g_aParticle[0];

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == false)
		{
			pParticle->pos = pos;

			pParticle->move = move;

			pParticle->bUse = true;

			break;
		}
	}
}
