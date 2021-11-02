//=============================================================================
//
// タイトル [title.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CBg;
class CTitleLogo;

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	static CTitle *Create(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void) { D3DXVECTOR3 pos; return pos; }
	D3DXVECTOR3 GetScale(void) { D3DXVECTOR3 scale; return scale; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D *m_pScene2D;
	static CBg *m_pBg;
	static CTitleLogo *m_pTitleLogo;
};

#endif