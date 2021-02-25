//=========================================================================================================================
//
// �Q�[����� [game.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#define _CRT_SECURE_NO_WARNINGS	// ���͋���
#include <stdio.h>
#include "game.h"
#include "player.h"
#include "BG.h"
#include "Score.h"
#include "fade.h"
#include "pause.h"
#include "input.h"
#include "wire.h"
#include "block.h"
#include "sound.h"
#include "timer.h"
#include "result.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define MAX_MAPDATA_X (64)
#define MAX_MAPDATA_Y (36)

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
bool g_bPause = false;							// �|�[�Y�����ǂ���
int g_aMapData[MAX_MAPDATA_X][MAX_MAPDATA_Y];	// �}�b�v�f�[�^�i�[��
int g_nBlock_X_Link = 0;						// �u���b�N��X���̘A����
int g_nBlock_Y_Link = 0;						// �u���b�N��Y���̘A����

//=========================================================================================================================
// �Q�[����ʂ̏���������
//=========================================================================================================================
HRESULT InitGame(void)
{
	// �t�@�C���̃|�C���^
	FILE *pFile;
	BLOCK *pBlock;
	pBlock = GetBlock();

	pFile = fopen("data\\MAP_DATA\\map_00.csv", "r");

	// BG�̏���������
	InitBG();

	// �u���b�N�̏�����
	InitBlock();

	//// �S�[���̏�����
	//InitGoal();

	// �u���b�N�̃Z�b�g����
	int nCntX = 0, nCntY = 0;
	char aLine[256];
	while (fgets(aLine, 256, pFile) != NULL)
	{
		nCntX = 0;
		char *pToken = strtok(aLine, ",");
		while (pToken != NULL)
		{
			int nNum = atoi(pToken);
			g_aMapData[nCntX][nCntY] = nNum;

			pToken = strtok(NULL, ",");
			nCntX++;
		}
		nCntY++;
	}
	fclose(pFile);

	for (int nCntY = 0; nCntY < MAX_MAPDATA_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_MAPDATA_X; nCntX++)
		{
			if (g_aMapData[nCntX][nCntY] == 1)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(float((SCREEN_WIDTH_R / MAX_MAPDATA_X) * nCntX), float((SCREEN_HEIGHT_U / MAX_MAPDATA_Y) * nCntY), Z_AXIS_ZERO);
				SetBlock(pos, D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO), (SCREEN_WIDTH_R / MAX_MAPDATA_X), (SCREEN_HEIGHT_U / MAX_MAPDATA_Y), BLOCKTYPE_BLOCK);
			}
			else if (g_aMapData[nCntX][nCntY] == 2)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(float((SCREEN_WIDTH_R / MAX_MAPDATA_X) * nCntX), float((SCREEN_HEIGHT_U / MAX_MAPDATA_Y) * nCntY), Z_AXIS_ZERO);
				SetBlock(pos, D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO), (SCREEN_WIDTH_R / MAX_MAPDATA_X), (SCREEN_HEIGHT_U / MAX_MAPDATA_Y), BLOCKTYPE_GOAL);
			}
		}
	}

	PlaySound(SOUND_LABEL_BGM002);

	// �v���C���[�̏���������
	InitPlayer();

	// ���C���[�̏�����
	InitWire();

	// �X�R�A�̏���������
	InitScore();

	// �|�[�Y�̏���������
	InitPause();

	// �^�C�}�[�̏���������
	InitTimer();

	return S_OK;
}

//=========================================================================================================================
// �Q�[����ʂ̏I������
//=========================================================================================================================
void UninitGame(void) 
{
	// �T�E���h�̒�~����
	StopSound();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �|�[�Y�̏I������
	g_bPause = false;
	UninitPause();

	// �X�R�A�̏I������
	UninitScore();

	//// �S�[���̏I������
	//UninitGoal();

	// ���C���[�̏I������
	UninitWire();

	// �v���C���[�̏I������
	UninitPlayer();

	// �u���b�N�̏I������
	UninitBlock();

	// BG�̏I������
	UninitBG();
}

//=========================================================================================================================
// �Q�[����ʂ̍X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	PLAYER *pPlayer;
	/*GOAL *pGoal;*/

	pPlayer = GetPlayer();
	/*pGoal = GetGoal();*/
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

		// �u���b�N�̍X�V����
		UpdateBlock();

		// ���C���[�̍X�V����
		UpdateWire();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		//// �S�[���̍X�V����
		//UpdateGoal();

		//�^�C�}�[�̍X�V����
		UpdateTimer();

		// �X�R�A�̍X�V����
		UpdateScore();
	}
}

//=========================================================================================================================
// �Q�[����ʂ̕`�揈��
//=========================================================================================================================
void DrawGame(void)
{
		// BG�̕`�揈��
		DrawBG();

		// �u���b�N�̕`�揈��
		DrawBlock();

		// ���C���[�̕`�揈��
		DrawWire();

		//// �S�[���̕`�揈��
		//DrawGoal();

		// �v���C���[�̕`�揈��
		DrawPlayer();

		// �^�C�}�[�̕`�揈��
		DrawTimer();

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