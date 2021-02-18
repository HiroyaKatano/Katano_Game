//=========================================================================================================================
//
// 弾 [bullet.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "player.h"

//
//
//
#define MAX_BULLET (256)		// 弾の最大数
#define BULLET_SIZE (2.0f)		// 弾の大きさ
#define BULLET_SPD (5.0f)		// 弾の移動量(速度)
#define BULLET_LIFE (100)		// 弾の寿命

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// テクスチャへのポインタ
BULLET g_aBullet[MAX_BULLET];						// 弾の情報
int g_aLife[MAX_BULLET];

//
// 初期化処理
//
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].bUse = false;
		g_aLife[nCnt] = 0;
	}
	

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		// 
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x - BULLET_SIZE, g_aBullet[nCnt].pos.y - BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x - BULLET_SIZE, g_aBullet[nCnt].pos.y + BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x + BULLET_SIZE, g_aBullet[nCnt].pos.y - BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x + BULLET_SIZE, g_aBullet[nCnt].pos.y + BULLET_SIZE, g_aBullet[nCnt].pos.z);

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
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}


//
// 終了処理
//
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}


//
// 更新処理
//
void UpdateBullet(void)
{
	Camera *pCamera = GetCamera();
	BULLET *pBullet = &g_aBullet[0];
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	if (GetKeyboardPress(DIK_0) == true)
	{
		SetBullet(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y) * BULLET_SPD, 0.0f, cosf(pPlayer->rot.y) * BULLET_SPD));
	}

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			pBullet->pos.x -= pBullet->move.x;
			pBullet->pos.z -= pBullet->move.z;

			g_aLife[nCnt]++;
			if (g_aLife[nCnt] == BULLET_LIFE)
			{
				pBullet->bUse = false;
				g_aLife[nCnt] = 0;
			}
		}
	}
}


//
// 描画処理
//
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	BULLET *pBullet = &g_aBullet[0];

	D3DXMATRIX mtxView;								// ビューマトリックス取得用
	D3DXMATRIX mtxTrans;							// 計算用マトリックス

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// アルファテスト
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 150);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			// ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView);	// 逆行列を求める
			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);

			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// デスティネーション(描画先)の合成方法の設定
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCnt * 4,						// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
			
		}
	}

	// デスティネーション(描画先)の合成方法の設定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテスト戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
// 弾の設定
//
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	BULLET *pBullet = &g_aBullet[0];

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			pBullet->pos = pos;

			pBullet->move = move;

			pBullet->bUse = true;

			break;
		}
	}
}
