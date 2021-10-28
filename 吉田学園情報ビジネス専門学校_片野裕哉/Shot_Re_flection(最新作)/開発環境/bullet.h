//=============================================================================
//
// �o���b�g [bullet.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ABSORBDISTANCE (110.0f)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet :public CScene2D
{
public:
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,		// �v���C���[
		BULLETTYPE_ENEMY,		// �G
		BULLETTYPE_MAX
	} BULLETTYPE;

	typedef enum
	{
		USEBULLET_NONE = 0,
		USEBULLET_TRACKING,		// �ǔ��e
		USEBULLET_SPREAD,		// �g�U�e
		USEBULLET_MAX
	} USEBULLET;

	CBullet(int nPriority = 1);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLETTYPE bulletType, USEBULLET useBullet);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLETTYPE bulletType, USEBULLET useBullet);
	static void Load(void);
	static void Unload(void);

	void BulletTracking(void);
	void BulletSpread(void);
	static int GetAbsorbedCnt(void) { return m_nAbsorbedBulletCnt; }
	void AddAbsorbedCnt(int nCnt) { m_nAbsorbedBulletCnt += nCnt; }
	static void ResetAbsorbedCnt(void) { m_nAbsorbedBulletCnt = 0; }

private:
	int m_life;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_move, m_move2;			// �ړ���
	BULLETTYPE m_bulletType;
	USEBULLET m_useBullet;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_EneBulCnt;
	static int m_nAbsorbedBulletCnt;
	bool m_bRockOn;
	bool m_bAbsorbOn;

	int m_EneLife;
};

#endif
