//===============================================================================================================
//
// �Q�[�� [game.cpp]
// Author:Katano Hiroya
//
//===============================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "wall.h"
#include "Billboard.h"
#include "meshfield.h"
#include "bullet.h"
#include "player.h"
#include "particle.h"
#include "fade.h"
#include "goal.h"

#include <stdio.h>

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
//void DrawInfo(void);

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPD3DXFONT g_pInfoFont = NULL;					// �t�H���g�ւ̃|�C���^
bool g_bPause;								// �|�[�Y���Ă��邩�ǂ���

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT InitGame(void)
{
	g_bPause = false;

	InitLight();

	InitCamera();

	InitMeshField();

	InitWall();

	InitShadow();

	InitBillboard();

	InitBullet();

	InitParticle();

	InitGoal();

	InitPlayer();

	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitGame(void)
{
	UninitPlayer();

	UninitGoal();

	UninitParticle();

	UninitBullet();

	UninitBillboard();

	UninitShadow();

	UninitWall();

	UninitMeshField();

	UninitCamera();

	UninitLight();
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateLight();

		UpdateCamera();

		UpdateMeshField();

		UpdateWall();

		UpdateBillboard();

		UpdateGoal();

		UpdatePlayer();

		UpdateParticle();

		UpdateBullet();

		UpdateShadow();
	}
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVIEWPORT9 viewportDef;

	// �`��̊J�n
	pDevice->GetViewport(&viewportDef);

	SetCamera(0);

	DrawMeshField();

	DrawWall();

	DrawShadow();

	//DrawBillboard();

	DrawBullet();

	DrawParticle();

	DrawGoal();

	DrawPlayer();

	pDevice->GetViewport(&viewportDef);
}