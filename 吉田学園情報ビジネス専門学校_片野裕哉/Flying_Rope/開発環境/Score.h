//========================================================================================================================
//
// �X�R�A�w�b�_�[ [Score.h]
// Author:Hiroya Katano
//
//========================================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#include "input.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_SCORE (8)	// �X�R�A�̍ő包��
#define SCORE_WIDTH_X			(30.0f)											// �X�R�A�̕�
#define SCORE_LEFT_X			(SCREEN_WIDTH_R - (MAX_SCORE + 1) * SCORE_WIDTH_X)	// ��X���W
#define SCORE_RIGHT_X			(SCREEN_WIDTH_R - MAX_SCORE * SCORE_WIDTH_X)	// �EX���W
#define SCORE_HIGH_Y			(3.75f)											// ��Y���W
#define SCORE_LOW_Y				(60.0f)											// ��Y���W

#define MAX_SCORE_PATTERN     (10)									// �A�j���[�V�����p�^�[��No.�̍ő吔
#define SCORE_TEXTURE_X		(10)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define SCORE_TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define SCORE_PLAY_ANIM       ((1.0f / SCORE_TEXTURE_X) * pScore->nPatternAnim)   // �e�N�X�`���̓���
#define SCORE_UV_U			(1.0f / SCORE_TEXTURE_X + SCORE_PLAY_ANIM)			// U�̒l
#define SCORE_UV_V			(1.0f / SCORE_TEXTURE_Y)						// V�̒l

#define SCORE_COLOR_R (255)														// �w�i�F(��)
#define SCORE_COLOR_G (255)														// �w�i�F(��)
#define SCORE_COLOR_B (255)														// �w�i�F(��)
#define SCORE_COLOR_A (255)														// �w�i�F(�����x)

#define RIHGT_BG_COLOR_R (255)														// �w�i�F(��)
#define RIHGT_BG_COLOR_G (255)														// �w�i�F(��)
#define RIHGT_BG_COLOR_B (255)														// �w�i�F(��)
#define RIHGT_BG_COLOR_A (255)														// �w�i�F(�����x)

#define LEFT_BG_COLOR_R (255)														// �w�i�F(��)
#define LEFT_BG_COLOR_G (255)														// �w�i�F(��)
#define LEFT_BG_COLOR_B (255)														// �w�i�F(��)
#define LEFT_BG_COLOR_A (255)														// �w�i�F(�����x)

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

#endif
