//=========================================================================================================================
//
// バリアヘッダー [barrier.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_
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
#define VERTEX_X (1)											// 中心からの端までの距離 (x)
#define VERTEX_Y (50)											// 中心からの端までの距離 (y)
#define BARRIER_SIZE_X (40.0f)
#define BARRIER_SIZE_Y (40.0f)

#define MAX_PATTERN     (1)										// アニメーションパターンNo.の最大数
#define TEXTURE_X		(1)										// アニメーションパターンNo.の横の最大数
#define TEXTURE_Y		(1)										// アニメーションパターンNo.の縦の最大数

#define BARRIER_COLOR_R (1.0f)														// 背景色(赤)
#define BARRIER_COLOR_G (1.0f)														// 背景色(緑)
#define BARRIER_COLOR_B (1.0f)														// 背景色(青)
#define BARRIER_COLOR_A (1.0f)														// 背景色(透明度)

#define TIMER_PLUS (2)
#define BARRIER_COST (2)
#define BARRIER_TIMER (300 * TIMER_PLUS)
#define BARRIER_FLASH (60 * TIMER_PLUS)
#define FLASH_TIMING (2 * TIMER_PLUS)

//=========================================================================================================================
// プレイヤーの状態
//=========================================================================================================================
typedef enum
{
	BARRIERSTATE_WAIT = 0,	// 展開待ち
	BARRIERSTATE_ACTIVE,	// 展開状態
	BARRIERSTATE_DAMAGE,	// 反射時
	BARRIERSTATE_MAX
}BARRIERSTATE;

typedef struct
{
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNo.
	D3DXVECTOR3 pos;		// バリアの位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotBarrier;	// バリアの回転角
	float fLengthBarrier;	// プレイヤーの対角線の長さ
	float fAngleBarrier;	// プレイヤーの対角線の角度
	BARRIERSTATE state;		// 状態
	int nCounterState;		// 状態カウンタ
	int nCounterDisp;		// 表示カウンタ
	bool bDisp;				// 表示ON/OFF
}BARRIER;

//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitBarrier(void);															// ポリゴンの初期化処理
void UninitBarrier(void);															// ポリゴンの終了処理
void UpdateBarrier(void);															// ポリゴンの更新処理
void DrawBarrier(void);																// ポリゴンの描画処理
void SetBarrier(D3DXVECTOR3 pos);
BARRIER *GetBarrier(void);
bool HitBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETMODE mode,int nDamage);

#endif