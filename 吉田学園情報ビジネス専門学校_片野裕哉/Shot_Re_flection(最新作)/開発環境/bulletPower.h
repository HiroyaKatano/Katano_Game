//=============================================================================
//
//	�e�� [bulletPower.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _BULLETPOWER_H_
#define _BULLETPOWER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_GAUGE_TEX					(4)

//-------------------------------------------------------------------------------
// �w�i�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CBulletPower : public CScene
{
public:
	CBulletPower(int nPriority = 3);
	~CBulletPower();

	static HRESULT Load(void);
	static void Unload(void);
	static CBulletPower *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBulletPower(int nBulletPower);
	void AddBulletPower(int nValue);

	D3DXVECTOR3 GetPosition(void) { return m_aPos[0]; }
	D3DXVECTOR3 GetScale(void) { return m_aScale[0]; }
	static int GetBulletPower(void) { return m_nBulletPower; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_GAUGE_TEX];	// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_GAUGE_TEX];					// 2D�|���S���̃|�C���^
	CNumber *m_apNumber[2];									// �i���o�[�̃|�C���^
	static int m_nBulletPower;								// �e��

	D3DXVECTOR3 m_aPos[MAX_GAUGE_TEX];
	D3DXVECTOR3 m_aScale[MAX_GAUGE_TEX];
};

#endif
