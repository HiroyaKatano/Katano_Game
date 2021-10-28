//=============================================================================
//
// ���U���g [result.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "score.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CBg;

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	static CResult *Create(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void) { D3DXVECTOR3 pos; return pos; }
	D3DXVECTOR3 GetScale(void) { D3DXVECTOR3 scale; return scale; }

	static int GetScore(void) { return m_nScore; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D *m_pScene2D;
	static CBg *m_pBg;
	CScore *m_pScore;
	static int m_nScore;
};

#endif