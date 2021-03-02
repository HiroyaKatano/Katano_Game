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
#include "sound.h"

//========================================================================================================================
// マクロ定義
//========================================================================================================================
#define PLAYER_SPD (1.0f)		// プレイヤーの速度
#define SPD_DECAY (0.25f)		// 移動の抵抗値

#define VERTEX_X (1)			// 中心からの端までの距離 (x)
#define VERTEX_Y (50)			// 中心からの端までの距離 (y)
#define PLAYER_SIZE_VERTEX_X (8.4f)
#define PLAYER_SIZE_Y (36.0f)

#define MAX_PATTERN     (4)		// アニメーションパターンNo.の最大数
#define TEXTURE_X		(4)		// アニメーションパターンNo.の横の最大数
#define TEXTURE_Y		(2)		// アニメーションパターンNo.の縦の最大数

#define PLAY_ANIM       ((1.0f / TEXTURE_X) * g_player.nPatternAnim)   // テクスチャの動作
#define UV_U			(1.0f / TEXTURE_X + PLAY_ANIM)			// Uの値
#define UV_V			(1.0f / TEXTURE_Y)						// Vの値

#define PLAYER_COLOR_R (1.0f)	// 背景色(赤)
#define PLAYER_COLOR_G (1.0f)	// 背景色(緑)
#define PLAYER_COLOR_B (1.0f)	// 背景色(青)
#define PLAYER_COLOR_A (1.0f)	// 背景色(透明度)

#define PLAYER_JUMP (12.5f)		// ジャンプ力
#define GRAVITY (0.8f)			// 重力

#define TIMER_COUNT (2)					//
#define TIMER_PLUS (2)					//
#define PLAYER_FLASH (60 * TIMER_PLUS)	//
#define FLASH_TIMING (2 * TIMER_PLUS)	//


#define ANIM_SPD (5)

//=========================================================================================================================
// 構造体の定義
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
	VEC_UP = 0,
	VEC_UPPER_R,
	VEC_RIGHT,
	VEC_LOWER_R,
	VEC_LOW,
	VEC_LOWER_L,
	VEC_LEFT,
	VEC_UPPER_L,
} VEC;


// プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	D3DXVECTOR3 posOld;		// 前回の位置
	D3DXVECTOR3 move;		// 移動量
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bJump;				// ジャンプしているかどうか
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNo.
	D3DXVECTOR3 rotPlayer;	// プレイヤーの回転角
	float fLengthPlayer;	// プレイヤーの対角線の長さ
	float fAnglePlayer;		// プレイヤーの対角線の角度
	PLAYERSTATE state;		// プレイヤーの状態
	int nCounterState;		// 状態カウンタ

	VEC vec;
} PLAYER;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitPlayer(void);															// ポリゴンの初期化処理
void UninitPlayer(void);															// ポリゴンの終了処理
void UpdatePlayer(void);															// ポリゴンの更新処理
void DrawPlayer(void);																// ポリゴンの描画処理
PLAYER *GetPlayer(void);

#endif