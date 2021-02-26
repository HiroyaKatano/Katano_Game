//=========================================================================================================================
//
// ステージセレクト [StageSelect.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "StageSelect.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageSelect = NULL;				// 頂点バッファ
LPDIRECT3DTEXTURE9 g_apTextureStageSelect[MAX_BG_STAGESELECT] = {};	// ステージセレクト画面のテクスチャ
char *g_aStageSelectFileName[MAX_BG_STAGESELECT] =
{// ステージセレクト画面のテクスチャ一覧
	"data\\TEXTURE\\sky000.jpg",
	"data\\TEXTURE\\Stage01.jpg",
	"data\\TEXTURE\\Stage02.jpg",
	"data\\TEXTURE\\Stage03.jpg",
	"data\\TEXTURE\\Stage04.jpg",
	"data\\TEXTURE\\StageSelect_Logo.png",
	"data\\TEXTURE\\Stage1_Logo.png",
	"data\\TEXTURE\\Stage2_Logo.png",
	"data\\TEXTURE\\Stage3_Logo.png",
	"data\\TEXTURE\\Stage4_Logo.png",
};
D3DXVECTOR3 g_aposStageSelect[MAX_BG_STAGESELECT] = {};				// ステージセレクト画面のテクスチャの位置
float g_fTexStageSelect_U = 0;
float g_fTexStageSelect_V = 0;

int g_StageSelect;													// ステージ選択用

//=========================================================================================================================
// ステージセレクトの初期化処理
//=========================================================================================================================
HRESULT InitStageSelect(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	for (int nCnt = 0; nCnt < MAX_BG_STAGESELECT; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, g_aStageSelectFileName[nCnt], &g_apTextureStageSelect[nCnt]);
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX_NUM * MAX_BG_STAGESELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStageSelect,
		NULL)))
	{
		return E_FAIL;
	}

	

	for (int nCntStage = 0; nCntStage < MAX_BG_STAGESELECT; nCntStage++)
	{
		switch (nCntStage)
		{
		case 0:
			// ステージセレクト背景の中心座標
			g_aposStageSelect[nCntStage].x = SCREEN_WIDTH_R / 2;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U / 2;
			break;
		case 1:
			// ステージ1の中心座標
			g_aposStageSelect[nCntStage].x = (float)SCREEN_WIDTH_R / 4;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U * 2 / 7;
			break;
		case 2:
			// ステージ2の中心座標
			g_aposStageSelect[nCntStage].x = (float)SCREEN_WIDTH_R * 3 / 4;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U * 2 / 7;
			break;
		case 3:
			// ステージ3の中心座標
			g_aposStageSelect[nCntStage].x = (float)SCREEN_WIDTH_R / 4;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U * 11 / 15;
			break;
		case 4:
			// ステージ4の中心座標
			g_aposStageSelect[nCntStage].x = (float)SCREEN_WIDTH_R * 3 / 4;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U * 11 / 15;
			break;
		case 5:
			// Stage Selectの中心座標
			g_aposStageSelect[nCntStage].x = SCREEN_WIDTH_R / 2;
			g_aposStageSelect[nCntStage].y = SCREEN_HEIGHT_U / 17;
			break;
		case 6:
			// Stage1の中心座標
			g_aposStageSelect[nCntStage].x = g_aposStageSelect[1].x;
			g_aposStageSelect[nCntStage].y = g_aposStageSelect[1].y;
			break;
		case 7:
			// Stage2の中心座標
			g_aposStageSelect[nCntStage].x = g_aposStageSelect[2].x;
			g_aposStageSelect[nCntStage].y = g_aposStageSelect[2].y;
			break;
		case 8:
			// Stage3の中心座標
			g_aposStageSelect[nCntStage].x = g_aposStageSelect[3].x;
			g_aposStageSelect[nCntStage].y = g_aposStageSelect[3].y;
			break;
		case 9:
			// Stage4の中心座標
			g_aposStageSelect[nCntStage].x = g_aposStageSelect[4].x;
			g_aposStageSelect[nCntStage].y = g_aposStageSelect[4].y;
			break;
		default:
			break;
		}
		// 頂点座標の設定
		g_aposStageSelect[nCntStage] = D3DXVECTOR3(g_aposStageSelect[nCntStage].x, g_aposStageSelect[nCntStage].y, Z_AXIS_ZERO);
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	//g_aposStageSelect[] = D3DXVECTOR3(g_aposStageSelect[].x, g_aposStageSelect[].y, Z_AXIS_ZERO);
	//g_posStageSelectLogo = D3DXVECTOR3(g_posStageSelectLogo.x, g_posStageSelectLogo.y, Z_AXIS_ZERO);

	for (int nCntStageSelect = 0; nCntStageSelect < MAX_BG_STAGESELECT; nCntStageSelect++)
	{
		switch (nCntStageSelect)
		{
		case 0:
			// ステージセレクト背景
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH_L, STAGESELECT_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH_L, SCREEN_HEIGHT_T, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(STAGESELECT_BG_SIZE_X, STAGESELECT_BG_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(STAGESELECT_BG_SIZE_X, SCREEN_HEIGHT_T, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_B_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_B_COLOR;
			break;
		case 1:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 2:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 3:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 4:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 5:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGESELECT_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGESELECT_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGESELECT_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGESELECT_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 6:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 7:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 8:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		case 9:
			// ステージ1の頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[1].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x - STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[2].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y + STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);
			pVtx[3].pos = D3DXVECTOR3(g_aposStageSelect[nCntStageSelect].x + STAGE_LOGO_VTX_SIZE_X, g_aposStageSelect[nCntStageSelect].y - STAGE_LOGO_VTX_SIZE_Y, Z_AXIS_ZERO);

			// 頂点カラーの設定
			pVtx[0].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[1].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[2].col = STAGESELECT_NEUTORAL_COLOR;
			pVtx[3].col = STAGESELECT_NEUTORAL_COLOR;
			break;
		default:
			break;
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += VTX_NUM;
	}


	// 頂点バッファをアンロックする
	g_pVtxBuffStageSelect->Unlock();

	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//=========================================================================================================================
// ステージセレクトの終了処理
//=========================================================================================================================
void UninitStageSelect(void)
{
	StopSound();

	// 頂点バッファの開放
	if (g_pVtxBuffStageSelect != NULL)
	{
		g_pVtxBuffStageSelect->Release();
		g_pVtxBuffStageSelect = NULL;
	}

	// ステージセレクト画面のテクスチャの開放
	for (int nCnt = 0; nCnt < MAX_BG_STAGESELECT; nCnt++)
	{
		if (g_apTextureStageSelect[nCnt] != NULL)
		{
			g_apTextureStageSelect[nCnt]->Release();
			g_apTextureStageSelect[nCnt] = NULL;
		}
	}

}

//=========================================================================================================================
// ステージセレクトの更新処理
//=========================================================================================================================
void UpdateStageSelect(void)
{
	VERTEX_2D *pVtx;

	g_fTexStageSelect_U += MOVE_STAGESELECT_BG_V;


	// 変数宣言
	int nFade = GetFade();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			switch (g_StageSelect)
			{
			case STAGE_ONE:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_TWO:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_THREE:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			case STAGE_FOUR:
				if (nFade == FADE_NONE)
				{
					SetFade(FADE_OUT, MODE_GAME);
				}
				break;
			}
			PlaySound(SOUND_LABEL_SE_ENTER);
		}


		if (GetKeyboardTrigger(DIK_D) == true)
		{

			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_TWO)
			{
			g_StageSelect += 1;
				if (g_StageSelect > STAGE_TWO)
				{
					g_StageSelect = STAGE_ONE;
				}
			}
			else if (g_StageSelect == STAGE_THREE || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect += 1;
				if (g_StageSelect > STAGE_FOUR)
				{
					g_StageSelect = STAGE_THREE;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_A) == true)
		{

			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_TWO)
			{
				g_StageSelect -= 1;
				if (g_StageSelect < STAGE_ONE)
				{
					g_StageSelect = STAGE_TWO;
				}
			}
			else if (g_StageSelect == STAGE_THREE || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect -= 1;
				if (g_StageSelect < STAGE_THREE)
				{
					g_StageSelect = STAGE_FOUR;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_S) == true)
		{
			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_THREE)
			{
				g_StageSelect += 2;
				if (g_StageSelect > STAGE_THREE)
				{
					g_StageSelect = STAGE_ONE;
				}
			}
			else if (g_StageSelect == STAGE_TWO || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect += 2;
				if (g_StageSelect > STAGE_FOUR)
				{
					g_StageSelect = STAGE_TWO;
				}
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{
			if (g_StageSelect == STAGE_ONE || g_StageSelect == STAGE_THREE)
			{
				g_StageSelect -= 2;
				if (g_StageSelect < STAGE_ONE)
				{
					g_StageSelect = STAGE_THREE;
				}
			}
			else if (g_StageSelect == STAGE_TWO || g_StageSelect == STAGE_FOUR)
			{
				g_StageSelect -= 2;
				if (g_StageSelect < STAGE_TWO)
				{
					g_StageSelect = STAGE_FOUR;
				}
			}
		}

		// ステージセレクト背景
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_fTexStageSelect_U, 1.0f + g_fTexStageSelect_V);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_fTexStageSelect_U, 0.0f + g_fTexStageSelect_V);
		pVtx[2].tex = D3DXVECTOR2(1.0f + g_fTexStageSelect_U, 1.0f + g_fTexStageSelect_V);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_fTexStageSelect_U, 0.0f + g_fTexStageSelect_V);

		for (int nSelectStage = 0; nSelectStage < MAX_BG_STAGESELECT; nSelectStage++)
		{
			if (g_StageSelect == 0)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 2:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 5:
					break;
				case 6:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 7:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 8:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 9:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 1)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 3:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 5:
					break;
				case 6:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 7:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 8:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 9:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 2)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 5:
					break;
				case 6:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 7:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 8:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 9:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				}
			}
			else if (g_StageSelect == 3)
			{
				switch (nSelectStage)
				{
				case 0:
					break;
				case 1:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 2:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 3:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				case 4:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 5:
					break;
				case 6:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 7:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 8:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_SELECT_COLOR;
					pVtx[1].col = STAGE_SELECT_COLOR;
					pVtx[2].col = STAGE_SELECT_COLOR;
					pVtx[3].col = STAGE_SELECT_COLOR;
					break;
				case 9:
					// 頂点カラーの設定
					pVtx[0].col = STAGE_NOT_SELECT_COLOR;
					pVtx[1].col = STAGE_NOT_SELECT_COLOR;
					pVtx[2].col = STAGE_NOT_SELECT_COLOR;
					pVtx[3].col = STAGE_NOT_SELECT_COLOR;
					break;
				}
			}

			pVtx += VTX_NUM;
		}

		// 頂点バッファをアンロックする
		g_pVtxBuffStageSelect->Unlock();


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (nFade == FADE_IN)
			{
				SetFade(FADE_NONE, MODE_STAGESELECT);
			}
			else if (nFade == FADE_NONE)
			{
				PlaySound(SOUND_LABEL_SE_ENTER);

				SetFade(FADE_OUT, MODE_GAME);
			}

		}
	}
}

//=========================================================================================================================
// ステージセレクトの描画処理
//=========================================================================================================================
void DrawStageSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStageSelect, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_BG_STAGESELECT; nCnt++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureStageSelect[nCnt]);

		// ステージセレクトの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCnt * VTX_NUM,						// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}

int GetStageNumber(void)
{
	return g_StageSelect;
}