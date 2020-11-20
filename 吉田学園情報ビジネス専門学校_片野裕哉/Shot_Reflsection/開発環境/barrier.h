//=========================================================================================================================
//
// �o���A�w�b�_�[ [barrier.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "BG.h"

//========================================================================================================================
// �}�N����`
//========================================================================================================================
#define VERTEX_X (1)											// ���S����̒[�܂ł̋��� (x)
#define VERTEX_Y (50)											// ���S����̒[�܂ł̋��� (y)
#define BARRIER_SIZE_X (40.0f)
#define BARRIER_SIZE_Y (40.0f)

#define MAX_PATTERN     (1)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TEXTURE_X		(1)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define BARRIER_COLOR_R (1.0f)														// �w�i�F(��)
#define BARRIER_COLOR_G (1.0f)														// �w�i�F(��)
#define BARRIER_COLOR_B (1.0f)														// �w�i�F(��)
#define BARRIER_COLOR_A (1.0f)														// �w�i�F(�����x)

#define TIMER_PLUS (2)
#define BARRIER_COST (2)
#define BARRIER_TIMER (300 * TIMER_PLUS)
#define BARRIER_FLASH (60 * TIMER_PLUS)
#define FLASH_TIMING (2 * TIMER_PLUS)

//=========================================================================================================================
// �v���C���[�̏��
//=========================================================================================================================
typedef enum
{
	BARRIERSTATE_WAIT = 0,	// �W�J�҂�
	BARRIERSTATE_ACTIVE,	// �W�J���
	BARRIERSTATE_DAMAGE,	// ���ˎ�
	BARRIERSTATE_MAX
}BARRIERSTATE;

typedef struct
{
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	D3DXVECTOR3 pos;		// �o���A�̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotBarrier;	// �o���A�̉�]�p
	float fLengthBarrier;	// �v���C���[�̑Ίp���̒���
	float fAngleBarrier;	// �v���C���[�̑Ίp���̊p�x
	BARRIERSTATE state;		// ���
	int nCounterState;		// ��ԃJ�E���^
	int nCounterDisp;		// �\���J�E���^
	bool bDisp;				// �\��ON/OFF
}BARRIER;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitBarrier(void);															// �|���S���̏���������
void UninitBarrier(void);															// �|���S���̏I������
void UpdateBarrier(void);															// �|���S���̍X�V����
void DrawBarrier(void);																// �|���S���̕`�揈��
void SetBarrier(D3DXVECTOR3 pos);
BARRIER *GetBarrier(void);
bool HitBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETMODE mode,int nDamage);

#endif