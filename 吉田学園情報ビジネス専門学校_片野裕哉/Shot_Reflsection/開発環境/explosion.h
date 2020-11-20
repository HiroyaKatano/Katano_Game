//=========================================================================================================================
//
// �G�N�X�v���[�W�����w�b�_�[ [explosion.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"


//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_EXPLOSION (256)
#define EXPLOSION_SIZE (50)

#define MAX_EXPLOSION_PATTERN     (8)									// �A�j���[�V�����p�^�[��No.�̍ő吔
#define EXPLOSION_TEXTURE_X		(8)										// �A�j���[�V�����p�^�[��No.�̉��̍ő吔
#define EXPLOSION_TEXTURE_Y		(1)										// �A�j���[�V�����p�^�[��No.�̏c�̍ő吔

#define EXPLOSION_PLAY_ANIM       ((1.0f / EXPLOSION_TEXTURE_X) * pExplosion->nPatternAnim)   // �e�N�X�`���̓���
#define EXPLOSION_UV_U			(1.0f / EXPLOSION_TEXTURE_X + EXPLOSION_PLAY_ANIM)			// U�̒l
#define EXPLOSION_UV_V			(1.0f / EXPLOSION_TEXTURE_Y)						// V�̒l

#define EXPLOSION_COLOR_R (160)														// �w�i�F(��)
#define EXPLOSION_COLOR_G (150)														// �w�i�F(��)
#define EXPLOSION_COLOR_B (150)														// �w�i�F(��)
#define EXPLOSION_COLOR_A (255)														// �w�i�F(�����x)

//========================================================================================================================
// �\���̂̒�`
//========================================================================================================================
typedef enum
{
	EXPLOSION_ENEMY = 0,
	EXPLOSION_BOMBER,
	EXPLOSION_MAX
}EXPLOSIONTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	bool bUse;				// �g�p���Ă��邩�ǂ���
	EXPLOSIONTYPE type;
	int nAttack;
}EXPLOSION;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitExplosion(void);															// �|���S���̏���������
void UninitExplosion(void);															// �|���S���̏I������
void UpdateExplosion(void);															// �|���S���̍X�V����
void DrawExplosion(void);																// �|���S���̕`�揈��
void SetExplosion(D3DXVECTOR3 pos, EXPLOSIONTYPE type);		// 
void SetVertexExplosion(int nIdx);
EXPLOSION *GetExplosion(void);

#endif
