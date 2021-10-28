//=============================================================================
//
// �o���b�g [explosion.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExplosion :public CScene2D
{
public:
	CExplosion(int nPriority = 2);
	~CExplosion();

	static void Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_scale;
	int m_nCounterAnim;			// �J�E���^�[
	int m_nPatternAnim;			// �p�^�[��No.
};

#endif
