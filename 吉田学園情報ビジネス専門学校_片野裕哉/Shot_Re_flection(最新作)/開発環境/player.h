//=============================================================================
//
// プレイヤー[playyer.h]
// Author:Hiroya Katano
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define PLAYER_START_CNT (3)		// プレイヤーの開始残機

//================================================================================
// プレイヤークラス
//================================================================================
class CPlayer :public CScene2D
{
public:

	CPlayer(int nPriority = 2);										//コンストラクタ
	~CPlayer();														//デストラクタ

	typedef enum
	{
		PLAYERSTATE_APPEAR = 0,	// 出現
		PLAYERSTATE_NONE,		// 通常
		PLAYERSTATE_DEATH,		// 死亡
		PLAYERSTATE_WAIT,		// 出現待ち
		PLAYERSTATE_MAX
	}PLAYERSTATE;


	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	static void Load(void);
	static void Unload(void);

	int GetPlayerCnt(void) { return m_nPlayerCnt; }
	static int GetPlayerState(void) { return m_state; }
	void SetPlayerState(PLAYERSTATE PlayerState);

	int *GetPlayerBullet(void) { return &m_nSelectBullet; }
	int ReturnAbsorbCnt(void) { return m_nAbsorbBulletCnt; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_scale;
	int m_nSelectBullet;
	int m_nCnt;
	static PLAYERSTATE m_state;
	int m_nPlayerCnt;
	int m_nPlayerInvincibleCnt;
	float m_fAngle;
	int m_nAngleCntTime;
	int m_nAbsorbBulletCnt;
};
#endif