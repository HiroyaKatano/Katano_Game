//=============================================================================
//
//	フェード [fade.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//-------------------------------------------------------------------------------
// 背景クラス(派生クラス)
//-------------------------------------------------------------------------------
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// 何もしていない
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト
		FADE_MAX,
	} FADE;

	HRESULT Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(FADE fade, CManager::MODE modeNext);
	static FADE GetFade(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	static FADE m_fade;						// フェードの状態
	static CManager::MODE m_modeNext;		// 次のモード
	D3DXCOLOR m_colorFade;					// フェード色
};

#endif
