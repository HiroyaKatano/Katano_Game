//
//
// プレイヤーヘッダー [player.h]
//
//
//
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_MODEL (18)		// モデル(パーツ)の最大数(総数)

//
// 構造体
//
//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// ニュートラルモーション
	MOTIONTYPE_MOVE,		// 移動モーション
	MOTIONTYPE_ACTION,		// アクションモーション
	MOTIONTYPE_JUMP,		// ジャンプモーション
	MOTIONTYPE_STEP,		// 着地モーション
	MOTIONTYPE_DAMAGE,		// やられモーション
	MOTIONTYPE_MAX			// モーションの最大数
}MOTIONTYPE;

// キーの構造体
typedef struct
{
	float fPosX;			// 位置X
	float fPosY;			// 位置Y
	float fPosZ;			// 位置Z
	float fRotX;			// 向きX
	float fRotY;			// 向きY
	float fRotZ;			// 向きZ
}KEY;

// キー情報の構造体
typedef struct
{
	int nFlame;				// 再生フレーム
	KEY aKey[MAX_MODEL];	// 各モデルのキー要素
}KEY_INFO;

// モーション情報の構造体
typedef struct
{
	bool bLoop;				// ループするかどうか
	int nNumKey;			// キーの総数
	KEY_INFO aKeyInfo[10];	// キー情報
}MOTION_INFO;

typedef struct
{
	LPD3DXMESH pMeshModel = NULL;		// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;	// マテリアル(材質情報)へのポインタ
	DWORD nNumMatModel = NULL;			// マテリアルの数
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 move;					// 移動量
	D3DXVECTOR3 rot;					// 向き
	D3DXVECTOR3 rotDest;				// 目的の向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	int nIdxModelParent;				// 親のインデックス
	D3DXVECTOR3 vtxMinModel;			// モデルの最小値
	D3DXVECTOR3 vtxMaxModel;			// モデルの最大値
	char aFileName[128];
} MODEL;

typedef struct
{
	D3DXVECTOR3 pos;			// 現在の位置
	D3DXVECTOR3 posOld;			// 過去の位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 rotDest;		// 目的の向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	MODEL aModel[MAX_MODEL];	// モデル(パーツ)
	int nNumModel;				// モデル(パーツ)の数

	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];	// モーション情報
	int nNumMotion = MOTIONTYPE_MAX;				// モーション数
	MOTIONTYPE motionType;		// モーションタイプ
	MOTIONTYPE motionTypeOld;					// 直前のモーションタイプ
	bool bLoopMotion;			// ループするかどうか
	int nNumKey;				// キー数
	int nKey;					// キーNo.
	int nCounterMotion;			// モーションカウンター
	D3DXVECTOR3 posParent;						// 親の座標
	bool bGoal;
} PLAYER;

typedef enum
{
	MODEL_LABEL_BODY = 0,	// 胴体
	MODEL_LABEL_NEEK,		// 首
	MODEL_LABEL_HEAD,		// 頭部
	MODEL_LABEL_ARM_T_R,	// 右腕(肘上)
	MODEL_LABEL_ELBOW_R,	// 右肘
	MODEL_LABEL_ARM_U_R,	// 右腕(肘下)
	MODEL_LABEL_ARM_T_L,	// 左腕(肘上)
	MPDEL_LABEL_ELBOW_L,	// 左肘
	MODEL_LABEL_ARM_U_L,	// 左腕(肘下)
	MODEL_LABEL_LEG_T_R,	// 右脚(腿)
	MODEL_LABEL_KNEE_R,		// 右膝
	MODEL_LABEL_LEG_U_R,	// 右脚(脹脛)
	MODEL_LABEL_FOOT_R,		// 右足
	MODEL_LABEL_LEG_T_L,	// 左脚(腿)
	MODEL_LABEL_KNEE_L,		// 左膝
	MODEL_LABEL_LEG_U_L,	// 左脚(脹脛)
	MODEL_LABEL_FOOT_L,		// 左足
	MODEL_LABEL_KATANA,		// 刀
	MODEL_LABEL_MAX,
} MODEL_LABEL;

//
// プロトタイプ宣言
//
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void LoadPlayerData(void);
void MotionPlayer(MOTIONTYPE motionType);

#endif