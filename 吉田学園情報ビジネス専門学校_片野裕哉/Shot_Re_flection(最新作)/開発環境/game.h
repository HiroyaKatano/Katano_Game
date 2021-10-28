//=============================================================================
//
// ゲーム [game.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CPlayer;
class CScore;
class CEnemy;
class CLife;
class CBullet;
class CData;
class CBulletPower;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENE_X_MAX (2)
#define NEXT_LISSAJOUS (60)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	static CGame *Create(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

	static CPlayer *GetPlayer(void);
	static CBullet *GetBullet(void);
	static CBg *GetBg(void);
	static CEnemy *GetEnemy(void);
	static CScore *GetScore(void);
	static CLife *GetLife(void) { return m_pLife; }
	static CData *GetData(void) { return m_pData; }
	static CBulletPower *GetBulletPower(void) { return m_pBulletPower; }
	static int GameCntTime(void) { return m_nCntTime; }

	static float GetAlpha(void) { return m_fAlpha; }
	static float GetBeta(void) { return m_fBeta; }
	static float GetDelta(void) { return m_fDelta; }
	static float GetRadiusA(void) { return m_fRadiusA; }
	static float GetRadiusB(void) { return m_fRadiusB; }

private:
	static CPlayer *m_pPlayer;
	static CBullet *m_pBullet;
	static CBg *m_pBg;
	static CEnemy *m_pEnemy;
	static CScore *m_pScore;
	static CLife *m_pLife;
	static CData *m_pData;
	static CBulletPower *m_pBulletPower;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;

	static int m_nCntTime;
	static int m_nEneCnt;
	static int m_nEneCnt2;

	static float m_fAlpha;
	static float m_fBeta;
	static float m_fDelta;
	static float m_fRadiusA;
	static float m_fRadiusB;

	static bool m_bLissajousOn;
};

#endif