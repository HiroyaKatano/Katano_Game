//=============================================================================
//
// ゲーム制作[keyboard.h]
// Author:Katano Hiroya
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//================================================================================
//オブジェクトクラス
//================================================================================
class CInputKeyboard :public CInput
{

public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelase(int nKey);

private:

	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];	//トリガー
	BYTE m_aKeyStateRelease[256];	//リリース
	BYTE m_aKeyStateRepeat[256];	//リピート

};

#endif