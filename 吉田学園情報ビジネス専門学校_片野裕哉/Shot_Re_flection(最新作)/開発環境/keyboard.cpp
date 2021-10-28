//-----------------------------------------------------------------------------
//
// �Q�[������[keyboard.cpp]
// Author:Katano Hiroya
//
//-----------------------------------------------------------------------------
#include "keyboard.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	//�L�[�g���K�[���
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));	//�L�[�����[�X���
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CInputKeyboard::~CInputKeyboard()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//*****************************************************************************
// �I������
//****************************************************************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
// �X�V����
//****************************************************************************
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];

	//�f�o�C�X��񂩂�f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			m_aKeyStateRelease[nKey] = m_aKeyState[nKey] & (~aKeyState[nKey]);
			m_aKeyStateTrigger[nKey] = ~m_aKeyState[nKey] & (aKeyState[nKey]);
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}

}

//*****************************************************************************
// �L�[�{�[�h���̎擾
//*****************************************************************************
//�L�[���������ꍇ
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) != 0;
}

//�L�[���^�b�v�����ꍇ
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//�L�[�𗣂����ꍇ
bool CInputKeyboard::GetRelase(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) != 0;
}