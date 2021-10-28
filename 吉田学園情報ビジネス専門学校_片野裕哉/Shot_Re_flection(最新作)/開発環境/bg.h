//=============================================================================
//
//	�w�i [bg.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

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
#define MAX_BG					(3)

#define SCROL_SPPED01			(0.0005f)
#define SCROL_SPPED02			(0.001f)
#define SCROL_SPPED03			(0.0025f)

//-------------------------------------------------------------------------------
// �w�i�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];			// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_BG];							// 2D�|���S���̃|�C���^
	float m_fSpeed[MAX_BG];									// �X�N���[���̃X�s�[�h
	float m_fPosTexU[MAX_BG];								// �e�N�X�`����U���W
	float m_fPosTexV[MAX_BG];								// �e�N�X�`����V���W
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
};

#endif
