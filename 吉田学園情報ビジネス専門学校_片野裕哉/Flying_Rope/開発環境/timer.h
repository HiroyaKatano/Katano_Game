//=========================================================================================================================
//
// TIMER [timer.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_TYPE_TIMER (2)
#define TIMER_COLOR_R (1.0f)
#define TIMER_COLOR_G (1.0f)
#define TIMER_COLOR_B (1.0f)
#define TIMER_COLOR_A (1.0f)

#define TIMER_WIDTH (30.0f)
#define TIMER_HEIGHT (56.25f)
#define TIMER_POS_X (SCREEN_WIDTH_R / 2 - TIMER_WIDTH / 2)
#define TIMER_POS_Y (SCREEN_HEIGHT_T)


#define NUMBER_X (45.0f)
#define NUMBER_Y (60.0f)
#define MAX_SCORE_PATTERN     (10)									// �A�j���[�V�����p�^�[��No.�̍ő吔
#define NUMBER_TEXTURE_X		(10)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define NUMBER_TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔
#define NUMBER_PLAY_ANIM       ((1.0f / NUMBER_TEXTURE_X) * pNumber->nPatternAnim)   // �e�N�X�`���̓���
#define NUMBER_UV_U			(1.0f / NUMBER_TEXTURE_X + NUMBER_PLAY_ANIM)			// U�̒l
#define NUMBER_UV_V			(1.0f / NUMBER_TEXTURE_Y)						// V�̒l


//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitTimer(void);															// �|���S���̏���������
void UninitTimer(void);															// �|���S���̏I������
void UpdateTimer(void);															// �|���S���̍X�V����
void DrawTimer(void);																// �|���S���̕`�揈��


#endif
