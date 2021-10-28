//=============================================================================
//
// 敵[enemy.h]
// Author:Hiroya Katano
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY (3)		// 敵の最大数
#define ENEMY_MAX_TEX (3)	// 敵のテクスチャ最大数
#define BULLET_MAX_ANGLE (16)

//================================================================================
// 敵クラス
//================================================================================
class CEnemy :public CScene2D
{
public:
	typedef enum
	{
		ENEMYTYPE_NONE = 0,
		ENEMYTYPE_ZERO,
		ENEMYTYPE_ONE,
		ENEMYTYPE_TWO,
		ENEMYTYPE_MAX
	} ENEMYTYPE;

	typedef enum
	{
		ENEMYMOVETYPE_NONE = 0,
		ENEMYMOVETYPE_CIRCLE,
		ENEMYMOVETYPE_LISSAJOUS,
		ENEMYMOVETYPE_CROSS,
		ENEMYMOVETYPE_MAX
	} ENEMYMOVETYPE;

	typedef struct
	{
		float fAlpha;
		float fBeta;
		float fDelta;
		float fRadiusA;
		float fRadiusB;
	} LISSAJOUS_SETDATA;

	CEnemy(int nPriority = 2);
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, int nTexNum, ENEMYTYPE enemyType, ENEMYMOVETYPE moveType);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetEnemyCnt(void) { return m_enemyCnt; }

	D3DXVECTOR3 MoveCircle(float fMoveX, float fMoveY, float fRadius);
	D3DXVECTOR3 MoveLissajous(LISSAJOUS_SETDATA movedata);

	void SetLissajous(float fAlpha, float fBeta, float fDelta, float fRadiusA, float fRadiusB);
	void SetSubLissajous(float fAlpha, float fBeta, float fDelta, float fRadiusA, float fRadiusB);

	int GetLife(void) { return m_nLife; }
	void AddLife(int nDamage) { m_nLife += nDamage; }

	int GetEneCnt2(void) { return m_eneCnt2; }

	void AddEnemy(int nValue) { m_enemyCnt += nValue; }
	void AddEneCnt(int nValue) { m_eneCnt2 += nValue; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_MAX_TEX];
	D3DXVECTOR3 m_scale;
	int m_nCnt;
	ENEMYTYPE m_enemyType;
	float m_moveX, m_moveY;
	static int m_enemyCnt;
	ENEMYMOVETYPE m_enemyMoveType;
	float m_fAngle;
	D3DXVECTOR3 EnemyPos;
	float m_fAngleL;
	float m_SetLR;

	LISSAJOUS_SETDATA m_Lissajous_SetData;
	float m_fDistance;
	float m_fRadianAngle;
	float m_fDigreeAngle;
	D3DXVECTOR3 m_SubPos;
	D3DXVECTOR3 m_SubDistance;
	int m_SubCnt;
	LISSAJOUS_SETDATA m_Lissajous_SetSubData[2];

	int m_nLife;

	static int m_eneCnt2;
};
#endif