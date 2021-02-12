//=========================================================================================================================
//
// �^�C�g���w�b�_�[ [title.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TITLE_H_
#define _TIELE_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define TITLE_BG_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			// �w�i�F(��, ��, ��, �����x)

#define TITLE_LOGOSHADOW_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	// ���S�e�F(��, ��, ��, �����x)

#define TITLE_LOGO_COLOR (D3DXCOLOR(0.0f, 0.66f, 1.0f, 1.0f))		// ���S�F(��, ��, ��, �����x)

#define ENTER_SIGN_COLOR_OFF (D3DXCOLOR(0.15f, 1.0f, 1.0f, 0.0f))		// �G���^�[�T�C��OFF�F(��, ��, ��, �����x)
#define ENTER_SIGN_COLOR_ON (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// �G���^�[�T�C��ON�F(��, ��, ��, �����x)

#define MAX_TYPE_TITLE (4)
#define TITLE_BG_SIZE_X (SCREEN_WIDTH_R * 4)
#define TITLE_BG_SIZE_Y (SCREEN_HEIGHT_U)
#define TITLE_LOGOB_SIZE_X (936.0f)
#define TITLE_LOGOB_SIZE_Y (116.0f)
#define TITLE_LOGOF_SIZE_X (550.0f)
#define TITLE_LOGOF_SIZE_Y (274.0f)
#define FLASHING_ENTER_SIZE_X (381.0f)
#define FLASHING_ENTER_SIZE_Y (55.0f)

#define MOVE_BG_U (0.00017f)
#define MOVE_TITLE_BG_V (0.00075f)

//=========================================================================================================================
// �\���̂̒�`
//=========================================================================================================================
typedef enum
{
	ENTERSTATE_WAIT = 0,	// �ҋ@���
	ENTERSTATE_ACTIVE,		// �J�n
	ENTERSTATE_MAX
} ENTERSTATE;				// 

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nType;			// ���
} TITLELOGO;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitTitle(void);															// �Q�[���̏���������
void UninitTitle(void);															// �Q�[���̏I������
void UpdateTitle(void);															// �Q�[���̍X�V����
void DrawTitle(void);															// �Q�[���̕`�揈��

#endif