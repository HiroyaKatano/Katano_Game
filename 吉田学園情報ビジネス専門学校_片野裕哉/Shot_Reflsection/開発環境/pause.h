//=========================================================================================================================
//
// �|�[�Y��� [pause.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define PAUSE_BG_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))			// �w�i�F
#define PAUSE_BG_SIZE_X (1920.0f)
#define PAUSE_BG_SIZE_Y (1080.0f)

#define PAUSE_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f))			// �F
#define PAUSE_SIZE_X (550.0f)
#define PAUSE_SIZE_Y (650.0f)

#define PAUSE_LOGO_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))		// �F
#define PAUSE_LOGO_SIZE_X (215.0f)
#define PAUSE_LOGO_SIZE_Y (55.0f)

#define CONTINUE_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))			// �F
#define CONTINUE_SIZE_X (420.0f)
#define CONTINUE_SIZE_Y (69.0f)

#define RETRY_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))			// �F0.3f, 0.3f, 0.3f, 1.0f
#define RETRY_SIZE_X (265.0f)
#define RETRY_SIZE_Y (80.0f)

#define QUIT_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))				// �F
#define QUIT_SIZE_X (210.0f)
#define QUIT_SIZE_Y (80.0f)

#define NOT_SELECT_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f))		// ��I�����̐F
#define SELECT_COLOR (D3DXCOLOR(0.0f, 0.5f, 0.9f, 1.0f))			// �I�����̐F

#define MAX_PAUSE_TYPE (6)

//=========================================================================================================================
// �\���̂̒�`
//=========================================================================================================================
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// �R���e�B�j���[
	PAUSE_MENU_RETRY,			// ���g���C
	PAUSE_MENU_QUIT,			// �I��
	PAUSE_MENU_MAX
}PAUSE_MENU;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitPause(void);															// �|���S���̏���������
void UninitPause(void);															// �|���S���̏I������
void UpdatePause(void);															// �|���S���̍X�V����
void DrawPause(void);																// �|���S���̕`�揈��

#endif
