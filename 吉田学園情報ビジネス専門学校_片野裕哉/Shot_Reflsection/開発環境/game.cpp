//=========================================================================================================================
//
// �Q�[����� [game.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "game.h"
#include "player.h"
#include "BG.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "Score.h"
#include "fade.h"
#include "effect.h"
#include "pause.h"
#include "item.h"
#include "ui.h"
#include "barrier.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
bool g_bPause = false;									// �|�[�Y�����ǂ���

//=========================================================================================================================
// �Q�[����ʂ̏���������
//=========================================================================================================================
HRESULT InitGame(void)
{
	// BG�̏���������
	InitBG();

	// �v���C���[�̏���������
	InitPlayer();

	// �X�R�A�̏���������
	InitScore();

	// �G�̏���������
	InitEnemy();

	// �e�̏���������
	InitBullet();

	//
	InitBarrier();

	// �����̏���������
	InitExplosion();

	// �G�t�F�N�g�̏���������
	InitEffect();

	//
	InitItem();

	//
	InitUi();

	// 
	InitPause();

	return S_OK;
}

//=========================================================================================================================
// �Q�[����ʂ̏I������
//=========================================================================================================================
void UninitGame(void) 
{
	//
	StopSound();

	//
	g_bPause = false;
	UninitPause();

	//
	UninitUi();

	//
	UninitItem();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �����̏I������
	UninitExplosion();

	// 
	UninitBarrier();

	// �e�̏I������
	UninitBullet();

	// �G�̏I������
	UninitEnemy();

	// �X�R�A�̏I������
	UninitScore();

	// �v���C���[�̏I������
	UninitPlayer();

	// BG�̏I������
	UninitBG();
}

//=========================================================================================================================
// �Q�[����ʂ̍X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	EXPLOSION *pExplosion;

	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	pExplosion = GetExplosion();
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		SetPause(g_bPause);
	}


	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		// BG�̍X�V����
		UpdateBG();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �G�̍X�V����
		UpdateEnemy();

		// �e�̍X�V����
		UpdateBullet();

		//
		UpdateBarrier();

		// �����̍X�V����
		UpdateExplosion();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		//
		UpdateItem();

		//
		UpdateUi();

		// �X�R�A�̍X�V����
		UpdateScore();
	}



	

	if (pPlayer->nMachine <= 0 || (FHASE_BOSS && pEnemy->nCounterEnemy <= 0))
	{
		if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//=========================================================================================================================
// �Q�[����ʂ̕`�揈��
//=========================================================================================================================
void DrawGame(void)
{
		// BG�̕`�揈��
		DrawBG();

		//
		DrawItem();

		// �G�̕`�揈��
		DrawEnemy();

		// �e�̕`�揈��
		DrawBullet();

		// �v���C���[�̕`�揈��
		DrawPlayer();

		// �o���A�̕`�揈��
		DrawBarrier();

		// �����̕`�揈��
		DrawExplosion();

		// �G�t�F�N�g�̕`�揈��
		DrawEffect();

		//
		DrawUi();

		// �X�R�A�̕`�揈��
		DrawScore();

		if (g_bPause == true)
		{
			// �|�[�Y���̕`�揈��
			DrawPause();
		}
}

//=========================================================================================================================
// �|�[�Y��ON/OFF
//=========================================================================================================================
void SetPause(bool bPause)
{
	g_bPause = g_bPause ? false : true;
}