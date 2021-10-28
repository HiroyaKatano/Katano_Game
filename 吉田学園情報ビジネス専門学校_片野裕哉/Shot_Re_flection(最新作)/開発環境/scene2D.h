//=============================================================================
//
// �V�[�� [scene2D.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_����
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`���̍��W
} VERTEX_2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	D3DXVECTOR3 GetPosition(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetExplosionTex(int nCnt);
	void SetBgTex(float fTexU, float fTexV);

	D3DXVECTOR3 GetScale(void) { return m_Polygon.scale; }

	void CScene2D::SetEffect(D3DXCOLOR col, float nData);

	void CScene2D::SetPlayerCol(float nData);
	//D3DXCOLOR GetColor(void) { return m_col; }

	void SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 scale);


	typedef struct
	{
		D3DXVECTOR3 pos;	// �|���S���̈ʒu
		D3DXVECTOR3 scale;	// �|���S���̊g�k�{��
		float fLength;		// �|���S���̑Ίp���̒���
		float fAngle;		// �|���S���̑Ίp���̊p�x
		D3DXCOLOR col;		// �|���S���̃J���[
	} POLYGON;


private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	
	POLYGON m_Polygon;
};

#endif
