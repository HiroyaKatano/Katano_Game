//
//
// ライト [light.cpp]
//
//
//
#include "light.h"

//
// グローバル変数
//
D3DLIGHT9 g_alight[3];		// ライトの情報

//
// 初期化処理
//
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;								// デバイスのポインタ
	D3DXVECTOR3 vecDir0;									// 設定用方向ベクトル
	D3DXVECTOR3 vecDir1;									// 設定用方向ベクトル
	D3DXVECTOR3 vecDir2;									// 設定用方向ベクトル

	// デバイスの取得
	pDevice = GetDevice();

	// ライトをクリアする
	ZeroMemory(&g_alight, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{

		// ライトの種類を設定
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向を設定
		vecDir0 = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir0, &vecDir0);					// 正規化する

		vecDir1 = D3DXVECTOR3(0.5f, -0.8f, 0.4f);
		D3DXVec3Normalize(&vecDir1, &vecDir1);					// 正規化する

		vecDir2 = D3DXVECTOR3(-0.2f, 0.5f, 0.2f);
		D3DXVec3Normalize(&vecDir2, &vecDir2);					// 正規化する

		switch (nCntLight)
		{
		case 0:
			g_alight[nCntLight].Direction = vecDir0;
			break;
		case 1:
			g_alight[nCntLight].Direction = vecDir1;
			break;
		case 2:
			g_alight[nCntLight].Direction = vecDir2;
			break;
		default:
			break;
		}

		// ライトを設定する
		pDevice->SetLight(nCntLight, &g_alight[nCntLight]);
		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}

	
}


//
// 終了処理
//
void UninitLight(void)
{

}


//
// 更新処理
//
void UpdateLight(void)
{

}
