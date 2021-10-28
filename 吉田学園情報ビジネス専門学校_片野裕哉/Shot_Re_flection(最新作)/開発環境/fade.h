//=============================================================================
//
//	�t�F�[�h [fade.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//-------------------------------------------------------------------------------
// �w�i�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// �������Ă��Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX,
	} FADE;

	HRESULT Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(FADE fade, CManager::MODE modeNext);
	static FADE GetFade(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	static FADE m_fade;						// �t�F�[�h�̏��
	static CManager::MODE m_modeNext;		// ���̃��[�h
	D3DXCOLOR m_colorFade;					// �t�F�[�h�F
};

#endif
