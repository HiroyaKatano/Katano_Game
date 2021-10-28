//=============================================================================
//
// �Q�[������[keyboard.h]
// Author:Katano Hiroya
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//================================================================================
//�I�u�W�F�N�g�N���X
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
	BYTE m_aKeyStateTrigger[256];	//�g���K�[
	BYTE m_aKeyStateRelease[256];	//�����[�X
	BYTE m_aKeyStateRepeat[256];	//���s�[�g

};

#endif