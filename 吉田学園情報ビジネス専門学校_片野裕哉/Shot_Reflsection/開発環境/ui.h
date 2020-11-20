//=========================================================================================================================
//
// UI [ui.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_TYPE_UI (9)
#define UI_COLOR_R (1.0f)
#define UI_COLOR_G (1.0f)
#define UI_COLOR_B (1.0f)
#define UI_COLOR_A (1.0f)
//#define RIHGT_BG_COLOR_R (255)														// �w�i�F(��)
//#define RIHGT_BG_COLOR_G (255)														// �w�i�F(��)
//#define RIHGT_BG_COLOR_B (255)														// �w�i�F(��)
//#define RIHGT_BG_COLOR_A (255)														// �w�i�F(�����x)
//
//#define LEFT_BG_COLOR_R (255)														// �w�i�F(��)
//#define LEFT_BG_COLOR_G (255)														// �w�i�F(��)
//#define LEFT_BG_COLOR_B (255)														// �w�i�F(��)
//#define LEFT_BG_COLOR_A (255)														// �w�i�F(�����x)

#define MINI_PLAYER_X (64.5f)
#define MINI_PLAYER_Y (64.5f)

#define ADD_UP_X (30.0f)
#define ADD_UP_Y (30.0f)

#define NUMBER_X (45.0f)
#define NUMBER_Y (60.0f)
#define MAX_SCORE_PATTERN     (10)									// �A�j���[�V�����p�^�[��No.�̍ő吔
#define NUMBER_TEXTURE_X		(10)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define NUMBER_TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔
#define NUMBER_PLAY_ANIM       ((1.0f / NUMBER_TEXTURE_X) * pNumber->nPatternAnim)   // �e�N�X�`���̓���
#define NUMBER_UV_U			(1.0f / NUMBER_TEXTURE_X + NUMBER_PLAY_ANIM)			// U�̒l
#define NUMBER_UV_V			(1.0f / NUMBER_TEXTURE_Y)						// V�̒l


#define GAUGE_BG_X (330.0f)
#define GAUGE_BG_Y (26.6f)
#define GAUGE_X (300.0f)
#define GAUGE_Y (25.0f)
#define GAUGE_FLAME_X (330.0f)
#define GAUGE_FLAME_Y (26.6f)

#define OPERATION_X (400.0f)
#define OPERATION_Y (368.0f)


//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitUi(void);															// �|���S���̏���������
void UninitUi(void);															// �|���S���̏I������
void UpdateUi(void);															// �|���S���̍X�V����
void DrawUi(void);																// �|���S���̕`�揈��
void ManageMachine(void);
void ManageGauge(void);

#endif
