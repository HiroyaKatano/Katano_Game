//=========================================================================================================================
//
// �X�e�[�W�Z���N�g�w�b�_�[ [StageSelect.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _STAGESELECT_H_
#define _TIELE_H_
#include "main.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define STAGESELECT_NEUTORAL_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			// �w�i�F(��, ��, ��, �����x)
#define STAGESELECT_NEUTORAL_B_COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			// �w�i�F(��, ��, ��, �����x)

#define STAGE_NOT_SELECT_COLOR (D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f))			// �w�i�F(��, ��, ��, �����x)
#define STAGE_SELECT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			// �w�i�F(��, ��, ��, �����x)

#define MAX_BG_STAGESELECT (10)
#define STAGESELECT_BG_SIZE_X (SCREEN_WIDTH_R * 4)
#define STAGESELECT_BG_SIZE_Y (SCREEN_HEIGHT_U)

#define STAGE_TEX_RES (30)

#define STAGE_VTX_SIZE_X (16 * STAGE_TEX_RES / 2)
#define STAGE_VTX_SIZE_Y (9 * STAGE_TEX_RES / 2)

#define STAGESELECT_LOGO_VTX_SIZE_X (132)
#define STAGE_LOGO_VTX_SIZE_X (65)
#define STAGE_LOGO_VTX_SIZE_Y (20)

#define MOVE_STAGESELECT_BG_V (0.00017f)

#define QUARTER_ONE (1 / 4)
#define QUARTER_THREE (3 / 4)

//=========================================================================================================================
// �\���̂̒�`
//=========================================================================================================================

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nType;			// ���
} STAGEINFO;

typedef enum
{
	STAGE_ONE = 0,
	STAGE_TWO,
	STAGE_THREE,
	STAGE_FOUR,
	STAGE_MAX,
} STAGE_NUM;

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
HRESULT InitStageSelect(void);															// �Q�[���̏���������
void UninitStageSelect(void);															// �Q�[���̏I������
void UpdateStageSelect(void);															// �Q�[���̍X�V����
void DrawStageSelect(void);															// �Q�[���̕`�揈��
int GetStageNumber(void);

#endif