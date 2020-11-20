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
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "explosion.h"
#include "BG.h"

//========================================================================================================================
// �}�N����`
//========================================================================================================================
#define PLAYER_SPD (1.8f)										// �v���C���[�̑��x
#define SPD_DECAY (0.16f)										// �ړ��̒�R�l

#define VERTEX_X (1)											// ���S����̒[�܂ł̋��� (x)
#define VERTEX_Y (50)											// ���S����̒[�܂ł̋��� (y)
#define PLAYER_SIZE_X (32.5f)
#define PLAYER_SIZE_Y (32.5f)

#define MAX_PATTERN     (1)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TEXTURE_X		(1)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define PLAY_ANIM       ((1.0f / TEXTURE_X) * g_player.nPatternAnim)   // �e�N�X�`���̓���
#define UV_U			(1.0f / TEXTURE_X + PLAY_ANIM)			// U�̒l
#define UV_V			(1.0f / TEXTURE_Y)						// V�̒l
#define PLAYER_COLOR_R (255)														// �w�i�F(��)
#define PLAYER_COLOR_G (255)														// �w�i�F(��)
#define PLAYER_COLOR_B (255)														// �w�i�F(��)
#define PLAYER_COLOR_A (255)														// �w�i�F(�����x)

#define WINDOW_TOP (BG_POS_TOP_Y + PLAYER_SIZE_Y)
#define WINDOW_UNDER (BG_POS_UNDER_Y - PLAYER_SIZE_Y)
#define WINDOW_LEFT (BG_POS_LEFT_X + PLAYER_SIZE_X)
#define WINDOW_RIGHT (BG_POS_RIGHT_X - PLAYER_SIZE_X)

//=========================================================================================================================
// �v���C���[�̏��
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
	SELECT_NORMAL = 0,
	SELECT_LASER,
	SELECT_WAVE,
	SELECT_BOMBER,
	SELECT_CIRCLE,
	SELECT_MAX
}SELECTBULLET;

typedef struct
{
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	D3DXVECTOR3 pos;		// �v���C���[�̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotPlayer;	// �v���C���[�̉�]�p
	float fLengthPlayer;	// �v���C���[�̑Ίp���̒���
	float fAnglePlayer;		// �v���C���[�̑Ίp���̊p�x
	int nMachine;			// �c�@
	PLAYERSTATE state;		// ���
	int nCounterState;		// ��ԃJ�E���^
	int nCounterDisp;		// �\���J�E���^
	bool bDisp;				// �\��ON/OFF
	SELECTBULLET SelectBullet;
}PLAYER;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitPlayer(void);															// �|���S���̏���������
void UninitPlayer(void);															// �|���S���̏I������
void UpdatePlayer(void);															// �|���S���̍X�V����
void DrawPlayer(void);																// �|���S���̕`�揈��
PLAYER *GetPlayer(void);
bool HitPlayer(int nDamage);

#endif