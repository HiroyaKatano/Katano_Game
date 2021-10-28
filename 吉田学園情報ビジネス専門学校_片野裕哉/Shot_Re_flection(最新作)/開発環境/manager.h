//=============================================================================
//
// マネージャー [manager.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;

class CLife;

class CTitle;
class CGame;
class CResult;
class CFade;
class CSound;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,		// タイトル画面
		MODE_GAME,			// ゲーム画面
		MODE_RESULT,		// リザルト画面
		MODE_MAX
	} MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CFade *GetFade(void) { return m_pFade; }
	static CSound *GetSound(void) { return m_pSound; }

private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CLife *m_pLife;

	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;

	static MODE m_mode;
	static CFade *m_pFade;

	static CSound *m_pSound;
};

#endif