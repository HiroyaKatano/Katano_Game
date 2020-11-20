//=========================================================================================================================
//
// プレイヤーヘッダー [player.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "BG.h"

//========================================================================================================================
// マクロ定義
//========================================================================================================================
#define PLAYER_SPD (1.8f)										// プレイヤーの速度
#define SPD_DECAY (0.16f)										// 移動の抵抗値

#define VERTEX_X (1)											// 中心からの端までの距離 (x)
#define VERTEX_Y (50)											// 中心からの端までの距離 (y)
#define PLAYER_SIZE_X (32.5f)
#define PLAYER_SIZE_Y (32.5f)

#define MAX_PATTERN     (1)										// アニメーションパターンNo.の最大数
#define TEXTURE_X		(1)										// アニメーションパターンNo.の横の最大数
#define TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数

#define PLAY_ANIM       ((1.0f / TEXTURE_X) * g_player.nPatternAnim)   // テクスチャの動作
#define UV_U			(1.0f / TEXTURE_X + PLAY_ANIM)			// Uの値
#define UV_V			(1.0f / TEXTURE_Y)						// Vの値
#define PLAYER_COLOR_R (255)														// 背景色(赤)
#define PLAYER_COLOR_G (255)														// 背景色(緑)
#define PLAYER_COLOR_B (255)														// 背景色(青)
#define PLAYER_COLOR_A (255)														// 背景色(透明度)

#define WINDOW_TOP (BG_POS_TOP_Y + PLAYER_SIZE_Y)
#define WINDOW_UNDER (BG_POS_UNDER_Y - PLAYER_SIZE_Y)
#define WINDOW_LEFT (BG_POS_LEFT_X + PLAYER_SIZE_X)
#define WINDOW_RIGHT (BG_POS_RIGHT_X - PLAYER_SIZE_X)

//=========================================================================================================================
// プレイヤーの状態
//=========================================================================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	// 出現
	PLAYERSTATE_NORMAL,		// 通常
	PLAYERSTATE_WAIT,		// 出現待ち
	PLAYERSTATE_DEATH,		// 死亡
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef enum
{
	SELECT_NORMAL = 0,
	SELECT_LASER,
	SELECT_WAVE,
	SELECT_BOMBER,
	SELECT_CIRCLE,
	SELECT_MAX
}SELECTBULLET;

typedef struct
{
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNo.
	D3DXVECTOR3 pos;		// プレイヤーの位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotPlayer;	// プレイヤーの回転角
	float fLengthPlayer;	// プレイヤーの対角線の長さ
	float fAnglePlayer;		// プレイヤーの対角線の角度
	int nMachine;			// 残機
	PLAYERSTATE state;		// 状態
	int nCounterState;		// 状態カウンタ
	int nCounterDisp;		// 表示カウンタ
	bool bDisp;				// 表示ON/OFF
	SELECTBULLET SelectBullet;
}PLAYER;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitPlayer(void);															// ポリゴンの初期化処理
void UninitPlayer(void);															// ポリゴンの終了処理
void UpdatePlayer(void);															// ポリゴンの更新処理
void DrawPlayer(void);																// ポリゴンの描画処理
PLAYER *GetPlayer(void);
bool HitPlayer(int nDamage);

#endif