//=========================================================================================================================
//
// �v���C���[�w�b�_�[ [player.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "input.h"
#include "sound.h"

//========================================================================================================================
// �}�N����`
//========================================================================================================================
#define PLAYER_SPD (1.0f)		// �v���C���[�̑��x
#define SPD_DECAY (0.25f)		// �ړ��̒�R�l

#define VERTEX_X (1)			// ���S����̒[�܂ł̋��� (x)
#define VERTEX_Y (50)			// ���S����̒[�܂ł̋��� (y)
#define PLAYER_SIZE_VERTEX_X (8.4f)
#define PLAYER_SIZE_Y (36.0f)

#define MAX_PATTERN     (4)		// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TEXTURE_X		(4)		// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define TEXTURE_Y		(2)		// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define PLAY_ANIM       ((1.0f / TEXTURE_X) * g_player.nPatternAnim)   // �e�N�X�`���̓���
#define UV_U			(1.0f / TEXTURE_X + PLAY_ANIM)			// U�̒l
#define UV_V			(1.0f / TEXTURE_Y)						// V�̒l

#define PLAYER_COLOR_R (1.0f)	// �w�i�F(��)
#define PLAYER_COLOR_G (1.0f)	// �w�i�F(��)
#define PLAYER_COLOR_B (1.0f)	// �w�i�F(��)
#define PLAYER_COLOR_A (1.0f)	// �w�i�F(�����x)

#define PLAYER_JUMP (12.5f)		// �W�����v��
#define GRAVITY (0.8f)			// �d��

#define TIMER_COUNT (2)					//
#define TIMER_PLUS (2)					//
#define PLAYER_FLASH (60 * TIMER_PLUS)	//
#define FLASH_TIMING (2 * TIMER_PLUS)	//


#define ANIM_SPD (5)

//=========================================================================================================================
// �\���̂̒�`
//=========================================================================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	// �o��
	PLAYERSTATE_NORMAL,		// �ʏ�
	PLAYERSTATE_WAIT,		// �o���҂�
	PLAYERSTATE_DEATH,		// ���S
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef enum
{
	VEC_UP = 0,
	VEC_UPPER_R,
	VEC_RIGHT,
	VEC_LOWER_R,
	VEC_LOW,
	VEC_LOWER_L,
	VEC_LEFT,
	VEC_UPPER_L,
} VEC;


// �v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 posOld;		// �O��̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	float fWidth;			// ��
	float fHeight;			// ����
	bool bJump;				// �W�����v���Ă��邩�ǂ���
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	D3DXVECTOR3 rotPlayer;	// �v���C���[�̉�]�p
	float fLengthPlayer;	// �v���C���[�̑Ίp���̒���
	float fAnglePlayer;		// �v���C���[�̑Ίp���̊p�x
	PLAYERSTATE state;		// �v���C���[�̏��
	int nCounterState;		// ��ԃJ�E���^

	VEC vec;
} PLAYER;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitPlayer(void);															// �|���S���̏���������
void UninitPlayer(void);															// �|���S���̏I������
void UpdatePlayer(void);															// �|���S���̍X�V����
void DrawPlayer(void);																// �|���S���̕`�揈��
PLAYER *GetPlayer(void);

#endif