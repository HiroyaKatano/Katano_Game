//=============================================================================
//
//	�X�R�A [score.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_DIGIT (8)		// �X�R�A�̌���

//-------------------------------------------------------------------------------
// �X�R�A�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CScore : public CScene
{
public:
	CScore(int nPriority = 3);
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetScore(int nScore);
	void AddScore(int nValue);
	static int GetScore(void) { return m_nScore; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	CNumber *m_apNumber[SCORE_DIGIT];
	static int m_nScore;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
};

#endif

