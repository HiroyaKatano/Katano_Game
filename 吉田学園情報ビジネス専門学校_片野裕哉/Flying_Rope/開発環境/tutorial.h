//=========================================================================================================================
//
// �`���[�g���A�� [tutorial.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define TUTORIAL_POS_LEFT_X (SCREEN_WIDTH_L)
#define TUTORIAL_POS_RIGHT_X (SCREEN_WIDTH_R)
#define TUTORIAL_POS_TOP_Y (SCREEN_HEIGHT_T)
#define TUTORIAL_POS_UNDER_Y (SCREEN_HEIGHT_U)
#define TUTORIAL_COLOR_R (255)														// �w�i�F(��)
#define TUTORIAL_COLOR_G (255)														// �w�i�F(��)
#define TUTORIAL_COLOR_B (255)														// �w�i�F(��)
#define TUTORIAL_COLOR_A (255)														// �w�i�F(�����x)
#define MAX_TUTORIAL_TYPE (1)
#define MOVE_FIRST_TUTORIAL_U (0.0001f)

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitTutorial(void);															// �|���S���̏���������
void UninitTutorial(void);															// �|���S���̏I������
void UpdateTutorial(void);															// �|���S���̍X�V����
void DrawTutorial(void);															// �|���S���̕`�揈��

#endif
