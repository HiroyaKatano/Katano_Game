//=============================================================================
//
// �G�t�F�N�g [effect.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

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
class CEffect :public CScene2D
{
public:
	CEffect(int nPriority = 1);
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col, int nLife);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);


private:
	int m_nLife;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXCOLOR m_col;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
