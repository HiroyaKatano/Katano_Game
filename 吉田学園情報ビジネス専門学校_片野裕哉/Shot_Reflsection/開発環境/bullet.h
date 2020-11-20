//=========================================================================================================================
//
// �o���b�g�w�b�_�[ [bullet.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "Score.h"


//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_MODE_BULLET (6)
#define MAX_BULLET (1024)
#define MOVE_PLAYER_BULLET (5.0f)
#define MOVE_ENEMY_BULLET (10.0f)
#define LIFE_BULLET (250)
#define BULLET_NORMAL_SIZE_X (10)
#define BULLET_NORMAL_SIZE_Y (10)
#define BULLET_LASER_SIZE_X (10)
#define BULLET_LASER_SIZE_Y (10)
#define BULLET_WAVE_SIZE_X (50)
#define BULLET_WAVE_SIZE_Y (10)
#define BULLET_BOMBER_SIZE_X (20)
#define BULLET_BOMBER_SIZE_Y (20)
#define BULLET_CIRCLE_SIZE_X (20)
#define BULLET_CIRCLE_SIZE_Y (20)

#define BULLET_NORMAL_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// �ʏ�e�̐F

#define LASER_COLOR (D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.40f))	// ���[�U�[�̐F

//=========================================================================================================================
// �e�̎��
//=========================================================================================================================
typedef enum
{
	BULLETTYPE_PLAYER = 0,	// ���@
	BULLETTYPE_ENEMY,		// �G
	BULLETTYPE_MAX
}BULLETTYPE;

typedef enum
{
	BULLET_NORMAL = 0,		// �ʏ�e
	BULLET_LASER,			// ���[�U�[
	BULLET_WAVE,			// �E�F�[�u�e
	BULLET_BOMBER,			// �����e
	BULLET_CIRCLE,			// �~�`�e
	BULLET_MAX
}BULLETMODE;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nLife;			// ����
	D3DXCOLOR col;		// �F
	bool bUse;			// �g�p���Ă��邩�ǂ���
	BULLETTYPE type;	// �e�̎��
	BULLETMODE mode;	// �e�̐���
	int nAttack;		// �U����
}BULLET;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitBullet(void);															// �|���S���̏���������
void UninitBullet(void);															// �|���S���̏I������
void UpdateBullet(void);															// �|���S���̍X�V����
void DrawBullet(void);																// �|���S���̕`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type, BULLETMODE mode, int nAttack);		// 
void SetVertexBullet(int nIdx);
BULLET *GetBullet(void);

#endif