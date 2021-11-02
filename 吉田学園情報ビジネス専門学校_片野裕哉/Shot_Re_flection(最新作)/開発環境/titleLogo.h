//=============================================================================
//
//	�^�C�g�����S [titleLogo.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

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
#define MAX_TITLE_TEX			(3)

#define SCROL_SPPED01			(0.0005f)
#define SCROL_SPPED02			(0.001f)
#define SCROL_SPPED03			(0.0025f)

//-------------------------------------------------------------------------------
// �w�i�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CTitleLogo : public CScene
{
public:
	CTitleLogo(int nPriority = 0);
	~CTitleLogo();

	static HRESULT Load(void);
	static void Unload(void);
	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void) { return m_aPos[0]; }
	D3DXVECTOR3 GetScale(void) { return m_aScale[0]; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX];			// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_TITLE_TEX];							// 2D�|���S���̃|�C���^
	float m_fSpeed[MAX_TITLE_TEX];									// �X�N���[���̃X�s�[�h
	float m_fPosTexU[MAX_TITLE_TEX];								// �e�N�X�`����U���W
	float m_fPosTexV[MAX_TITLE_TEX];								// �e�N�X�`����V���W
	D3DXVECTOR3 m_aPos[MAX_TITLE_TEX];
	D3DXVECTOR3 m_aScale[MAX_TITLE_TEX];

	bool m_bFlashSign;
};

#endif
