//=============================================================================
//
//	�i���o�[ [number.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//-------------------------------------------------------------------------------
// �i���o�[�N���X(��{�N���X)
//-------------------------------------------------------------------------------
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nNumber);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nNumber);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
};

#endif

