//========================================================================================================================
//
// �G�l�~�[�w�b�_�[ [enemy.h]
// Author:Hiroya Katano
//
//========================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "input.h"

//========================================================================================================================
// �}�N����`
//========================================================================================================================
#define MAX_TYPE_ENEMY (4)	// �G�̎�ސ�
#define MAX_ENEMY (256)	// �G�̍ő吔
#define ENEMY_SIZE_X (25)	// �G�̃T�C�Y
#define ENEMY_SIZE_Y (25)	// �G�̃T�C�Y

#define BOSS_SIZE_X (200)	// �{�X�̃T�C�Y
#define BOSS_SIZE_Y (200)	// �{�X�̃T�C�Y

#define ENEMY_VERTEX_X			(600.0f)

#define MAX_ENEMY_PATTERN     (1)											// �A�j���[�V�����p�^�[��No.�̍ő吔
#define ENEMY_TEXTURE_X		(1)											// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define ENEMY_TEXTURE_Y		(1)											// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define MOVE_ENEMY		(4.0f)										// �G�̈ړ���

#define PLAY_ENEMY_ANIM       ((1.0f / ENEMY_TEXTURE_X) * g_nPatternEnemyAnim)		// �e�N�X�`���̓���
#define ENEMY_UV_U			(1.0f / ENEMY_TEXTURE_X + PLAY_ENEMY_ANIM)				// U�̒l
#define ENEMY_UV_V			(1.0f / ENEMY_TEXTURE_Y)							// V�̒l

#define ENEMY_COLOR_R (255)														// �w�i�F(��)
#define ENEMY_COLOR_G (255)														// �w�i�F(��)
#define ENEMY_COLOR_B (255)														// �w�i�F(��)
#define ENEMY_COLOR_A (255)														// �w�i�F(�����x)

#define MAX_COUNT		(500)										// �J�E���g

#define MAX_LINE (3)

//========================================================================================================================
// �\���̂̒�`
//========================================================================================================================
typedef enum
{
	FHASE_0 = 0,
	FHASE_1,
	FHASE_2,
	FHASE_3,
	FHASE_BOSS
}FHASE;

typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTASE_MAX
}ENEMYSTATE;					// �G�̏��

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nType;			// ���
	bool bUse;			// �g�p���Ă��邩�ǂ���
	ENEMYSTATE state;	// ���
	int nCounterState;	// ��ԃJ�E���^�[
	int nLife;			// �̗�
	int nCounterEnemy;
	int nCounterBullet;
	FHASE fhase;
} ENEMY;

//========================================================================================================================
// �v���g�^�C�v�錾
//========================================================================================================================
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void SetVertexEnemy(int nIdx);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);
void Fhase1st(void);
void Fhase2nd(void);
void Fhase3rd(void);
void Fhase4th(void);
void FhaseBoss(void);

#endif
