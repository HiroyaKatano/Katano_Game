//=========================================================================================================================
//
// �v���C���[ [player.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#include "player.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "goal.h"
#include "fade.h"

//
// �}�N����`
//
#define PLAYER_SPD (12.0f)	// �v���C���[�̈ړ���
#define SPD_DECAY (0.4f)	// �ړ��ʂ̌����W��
#define TEXT_LENGTH		(128)	// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH		(64)	// �f�[�^�ǂݍ��݂̍ő吔

//
// �O���[�o���ϐ�
//
PLAYER g_player;								// �v���C���[
//char *g_aModelFile[MODEL_LABEL_MAX] =
//{
//	"data\\MODEL\\player_model\\00_body_00.x",		// ����
//	"data\\MODEL\\player_model\\01_neck_00.x",		// ��
//	"data\\MODEL\\player_model\\02_head_00.x",		// ����
//	"data\\MODEL\\player_model\\03_armR_T_00.x",	// �E�r(�I��)
//	"data\\MODEL\\player_model\\04_elbowR_00.x",	// �E�I
//	"data\\MODEL\\player_model\\05_armR_U_00.x",	// �E�r(�I��)
//	"data\\MODEL\\player_model\\06_armL_T_00.x",	// ���r(�I��)
//	"data\\MODEL\\player_model\\07_elbowL_00.x",	// ���I
//	"data\\MODEL\\player_model\\08_armL_U_00.x",	// ���r(�I��)
//	"data\\MODEL\\player_model\\09_legR_T_00.x",	// �E�r(��)
//	"data\\MODEL\\player_model\\10_kneeR_00.x",	// �E�G
//	"data\\MODEL\\player_model\\11_legR_U_00.x",	// �E�r(����)
//	"data\\MODEL\\player_model\\12_footR_00.x",		// �E��
//	"data\\MODEL\\player_model\\13_legL_T_00.x",	// ���r(��)
//	"data\\MODEL\\player_model\\14_kneeL_00.x",	// ���G
//	"data\\MODEL\\player_model\\15_legL_U_00.x",	// ���r(����)
//	"data\\MODEL\\player_model\\16_footL_00.x",		// ����
//	"data\\MODEL\\player_model\\17_katana_00.x",	// ��
//};		// ���f���̃t�@�C���ꗗ
LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// �e�N�X�`���ւ̃|�C���^

//
// ����������
//
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadPlayerData();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bGoal = false;
	g_player.nNumModel = 0;
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			/*g_aModelFile[nCntModel],*/
			g_player.aModel[nCntModel].aFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_player.aModel[nCntModel].nNumMatModel,
			&g_player.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// ���_��
		DWORD sizeFVF = NULL;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^

		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

		g_player.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_player.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// ���_�����擾
		nNumvtx = g_player.aModel[nCntModel].pMeshModel->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMeshModel->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

			// ���S�Ă̒��_�����r���ăv���C���[�̍ŏ��l�E�ő�l�𔲂��o��
			if (g_player.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_player.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_player.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_player.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_player.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_player.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_player.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ���S�Ă̒��_�����r���ăv���C���[�̍ŏ��l�E�ő�l�𔲂��o��

			pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		}

		g_player.nNumModel++;
	}

	//// �S�p�[�c�̊K�w�\���ݒ�
	//g_player.aModel[0].nIdxModelParent = -1;						// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 66.5f, 0.0f);			// �ʒu�̏����ݒ�
	//g_player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[1].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 38.2f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[2].nIdxModelParent = 1;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[2].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[3].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 33.5f, 1.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[3].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[4].nIdxModelParent = 3;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[4].pos = D3DXVECTOR3(-22.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[4].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[5].nIdxModelParent = 4;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[5].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[6].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[6].pos = D3DXVECTOR3(10.0f, 33.5f, 1.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[6].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[7].nIdxModelParent = 6;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[7].pos = D3DXVECTOR3(22.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[7].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[8].nIdxModelParent = 7;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[8].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[9].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[9].pos = D3DXVECTOR3(-6.0f, -1.0f, 1.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[9].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[10].nIdxModelParent = 9;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[10].pos = D3DXVECTOR3(-0.5f, -26.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[10].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[11].nIdxModelParent = 10;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// �ʒu�̏����ݒ�
	//g_player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[11].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[12].nIdxModelParent = 11;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[12].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[13].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[13].pos = D3DXVECTOR3(6.0f, -1.0f, 1.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[13].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[14].nIdxModelParent = 13;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[14].pos = D3DXVECTOR3(0.5f, -26.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[14].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[14].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[15].nIdxModelParent = 14;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[15].pos = D3DXVECTOR3(0.0f, -3.5f, -0.5f);		// �ʒu�̏����ݒ�
	//g_player.aModel[15].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[15].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[15].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[16].nIdxModelParent = 15;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[16].pos = D3DXVECTOR3(0.0f, -28.0f, 0.0f);		// �ʒu�̏����ݒ�
	//g_player.aModel[16].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[16].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	//g_player.aModel[17].nIdxModelParent = 4;							// �e�̃C���f�b�N�X��ݒ�
	//g_player.aModel[17].pos = D3DXVECTOR3(-21.5f, 0.0f, -0.5f);		// �ʒu�̏����ݒ�
	//g_player.aModel[17].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	//g_player.aModel[17].rot = D3DXVECTOR3(-1.5f, 0.0f, 0.0f);			// �����̏����ݒ�
	//g_player.aModel[17].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�



	//g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu�̏����ݒ�
	//g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ��ʂ̏����ݒ�
	//g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �����̏����ݒ�
	//g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړI�̌����̏����ݒ�
}


//
// �I������
//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// ���b�V���̔j��
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		// �}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// �X�V����
//
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();
	GOAL *pGoal = GetGoal();

	// ���O�̈ʒu�̕ۑ�
	g_player.posOld = g_player.pos;

	// �d�͂̔���
	if (g_player.pos.y > 0.0f)
	{
		g_player.move.y += -0.8f;

	}
	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
		g_player.move.y = 0.0f;
		if (g_player.motionTypeOld == MOTIONTYPE_JUMP)
		{
			g_player.nKey = 0;
			g_player.nCounterMotion = 0;
			g_player.motionType = MOTIONTYPE_STEP;
		}
	}

	// �W�����v
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		//SetBullet(
		//	D3DXVECTOR3(g_player.pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y + 50.0f, g_player.pos.z + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
		//	/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
		//	D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
		//	100);

		g_player.move.y = 50.0f;
		g_player.nKey = 0;
		g_player.nCounterMotion = 0;
		g_player.motionType = MOTIONTYPE_JUMP;
	}

	if (((pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z) - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) -
		(0.0f) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0 &&
		(0.0f) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) -
		((pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x) - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z)) >= 0 &&
		((pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z) - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z)) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) -
		(0.0f) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0 &&
		(0.0f) * (g_player.pos.x - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) -
		((pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x) - (pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x)) * (g_player.pos.z - (pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)) >= 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
		g_player.bGoal = true;
	}

	/*if (g_player.pos.x < pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.x &&
		g_player.pos.x > pGoal->pos.x + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.x)
	{
		if (g_player.pos.z < pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMaxModel.z &&
			g_player.pos.z > pGoal->pos.z + pGoal->aModel[MODEL_G_LABEL_GOAL].vtxMinModel.z)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}*/

	if (g_player.bGoal == false)
	{

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.motionType = MOTIONTYPE_NEUTRAL;
			/*SetFade(FADE_OUT, MODE_RESULT);*/
		}

		// ���[�V�����J�E���^�[�̉��Z
		g_player.nCounterMotion++;

		// ���[�V�����̍X�V
		MotionPlayer(g_player.motionType);

		// �ړ��ʂ̉��Z
		g_player.pos += g_player.move;

		if (GetKeyboardTrigger(DIK_0) == true)
		{
			g_player.motionType = MOTIONTYPE_ACTION;
		}

		if (GetKeyboardPress(DIK_UP) == true)
		{
			/*g_player.rotDest.y = (-D3DX_PI + pCamera->rot.y);

			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPD;*/


			if (GetKeyboardPress(DIK_LEFT) == true)
			{// �������
				g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_SPD;
				g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{// �E�����
				g_player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_SPD;
				g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
			}
			else
			{// �����
				g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPD;
				g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
			}
			g_player.motionType = MOTIONTYPE_MOVE;
		}

		else if (GetKeyboardPress(DIK_DOWN) == true)
		{



			if (GetKeyboardPress(DIK_LEFT) == true)
			{// ��������
				g_player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{// �E������
				g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
			}
			else
			{// ������
				g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * PLAYER_SPD;
				g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * PLAYER_SPD;
				g_player.rotDest.y = pCamera->rot.y;
			}
			g_player.motionType = MOTIONTYPE_MOVE;
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{// ������
			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);

			g_player.motionType = MOTIONTYPE_MOVE;

		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// �E����
			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);

			g_player.motionType = MOTIONTYPE_MOVE;

		}

		/*if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_player.rotDest.y = (pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_SPD;
		}

		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_player.rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_SPD;
		}

		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_player.rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}

			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_SPD;
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_SPD;
		}*/

		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 20.0f;
		}

		if (GetKeyboardRelease(DIK_UP) == true || GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 20.0f;
			g_player.motionType = MOTIONTYPE_NEUTRAL;
		}

		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			g_player.rotDest.y -= 0.2f;
			if (g_player.rotDest.y < -D3DX_PI)
			{
				g_player.rotDest.y += D3DX_PI * 2.0f;
			}
		}

		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{
			g_player.rotDest.y += 0.2f;
			if (g_player.rotDest.y > D3DX_PI)
			{
				g_player.rotDest.y -= D3DX_PI * 2.0f;
			}
		}

		if (GetKeyboardPress(DIK_I) == true)
		{
			g_player.move.y += PLAYER_SPD;
		}

		if (GetKeyboardPress(DIK_K) == true)
		{
			g_player.move.y -= PLAYER_SPD;
		}

	}
	else if (g_player.bGoal == true)
	{
		g_player.rotDest.y += 0.3f;
		g_player.move.y += 1.0f;
	}

	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if ((g_player.rotDest.y - g_player.rot.y) < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	g_player.move.x += (0.0f - g_player.move.x) * SPD_DECAY;
	g_player.move.z += (0.0f - g_player.move.z) * SPD_DECAY;
	/*g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;*/

	/*g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;
	g_player.pos.y += g_player.move.y;*/
}


//
// �`�揈��
//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;							// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �v���C���[�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

		// �v���C���[�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
							&g_player.aModel[nCntModel].mtxWorld,
							&mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// ���f��(�p�[�c)�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			// �v���C���[(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//
// �v���C���[�̎擾
//
PLAYER *GetPlayer(void)
{
	return &g_player;
}


//
// �v���C���[�f�[�^�̕ۑ�
//
void LoadPlayerData(void)
{
	//// �t�@�C���̃|�C���^
	//FILE *pFile;
	//char cModelName[2048];
	//char search[] = "MODEL_FILENAME = ";
	//char searchend[] = ".x";
	//char *start_ptr;		/* �����J�n�ʒu */
	//char *end_ptr;			/* �����I���ʒu */
	//char *search_ptr;		/* �������ʕ����ʒu */
	//char key[11];			/* �����L�[ */
	//int search_cnt;			/* �������ʕ����� */
	//int return_code = 0;

	//pFile = fopen("data\\MOTION_DATA\\motion_my_model.txt", "r");

	//while (fgets(cModelName, 255, pFile))
	//{
	//	start_ptr = search;
	//	end_ptr = searchend;
	//	if (strstr(cModelName, search))
	//	{

	//	}
	//}

	//fclose(pFile);

	// ���[�J���ϐ��錾
	FILE *pFile;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	int nCntFile = 0;							// X�t�@�C���̐�
	int nIdxParts = 0;							// �p�[�c��
	int nMotion = 0;							// ���[�V�����̐�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };			// �e�L�X�g�ǂݎ��p�ϐ�
	char aCharaSet[DATA_LENGTH] = { NULL };		// �L�����f�[�^�ǂݎ��p�ϐ�
	char aPartsSet[DATA_LENGTH] = { NULL };		// �p�[�c�f�[�^�ǂݎ��p�ϐ�
	char aMotionSet[DATA_LENGTH] = { NULL };	// ���[�V�����ǂݎ��p�ϐ�
	char aKeyInfo[DATA_LENGTH] = { NULL };		// �L�[�ݒ���ǂݎ��p�ϐ�
	char aKey[DATA_LENGTH] = { NULL };			// �L�[���ǂݎ��p�ϐ�

												// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeyInfo[0];
	char *pKey = &aKey[0];


	// �f�[�^�̓ǂݍ���
	pFile = fopen("data\\MOTION_DATA\\motion_my_model.txt", "r");
	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		while (strcmp("END_SCRIPT", pText) != 0)
		{
			aText[0] = { NULL };
			if (bComment == false)
			{// �R�����g�A�E�g���Ă��Ȃ�
				fscanf(pFile, "%s", &aText[0]);

				if (aText[0] == '#')
				{// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
					bComment = true;
				}
				else
				{// �ʏ펞
					if (strcmp("NUM_MODEL", pText) == 0)
					{// ���f���̐�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &g_player.nNumModel);
					}
					else if (strcmp("MODEL_FILENAME", pText) == 0)
					{// X�t�@�C�����̓ǂݍ���
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &g_player.aModel[nCntFile].aFileName[0]);
						nCntFile++;
					}
					else if (strcmp("CHARACTERSET", pText) == 0)
					{// �L�����̏��
						while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
						{// �L�������̓ǂݎ��
							fscanf(pFile, "%s", &aCharaSet[0]);
							if (strcmp("NUM_PARTS", pCharaSet) == 0)
							{

							}
							else if (strcmp("PARTSSET", pCharaSet) == 0)
							{
								aPartsSet[0] = { NULL };

								while (strcmp("END_PARTSSET", pPartsSet) != 0)
								{
									fscanf(pFile, "%s", &aPartsSet[0]);
									if (strcmp("INDEX", pPartsSet) == 0)
									{// �p�[�c���̓ǂݎ��
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &nIdxParts);
									}
									else if (strcmp("PARENT", pPartsSet) == 0)
									{// �p�[�c�̐e���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_player.aModel[nIdxParts].nIdxModelParent);
									}
									else if (strcmp("POS", pPartsSet) == 0)
									{// �p�[�c�̈ʒu���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.x);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.y);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.z);
									}
									else if (strcmp("ROT", pPartsSet) == 0)
									{// �p�[�c�̊p�x���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.x);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.y);
										fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.z);
									}
								}
							}
						}
					}
					else if (strcmp("MOTIONSET", pText) == 0)
					{
						// �ϐ��̏�����
						aMotionSet[0] = { NULL };

						// ���[�J���ϐ��錾
						int nLoop = 0;
						int nKeySet = 0;

						while (strcmp("END_MOTIONSET", pMotionSet) != 0)
						{// ���[�V�����̓ǂݍ���
							fscanf(pFile, "%s", &aMotionSet[0]);
							if (strcmp("LOOP", pMotionSet) == 0)
							{// ���[�v���邩
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &nLoop);
								if (nLoop == 1)
								{// �P�̏ꍇ���[�v����
									g_player.bLoopMotion = true;
									g_player.aMotionInfo[nMotion].bLoop = true;
								}
							}
							else if (strcmp("NUM_KEY", pMotionSet) == 0)
							{// �L�[���̓ǂݍ���
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &g_player.nNumKey);
							}

							else if (strcmp("KEYSET", pMotionSet) == 0)
							{// �L�[�̓ǂݍ���
							 // ���[�J���ϐ��錾
								int nKey = 0;
								// �ϐ��̏�����
								aKeyInfo[0] = { NULL };

								while (strcmp("END_KEYSET", pKeySet) != 0)
								{// �L�[��񍀖ڂ̓ǂݍ���
									fscanf(pFile, "%s", &aKeyInfo[0]);

									if (aKeyInfo[0] == '#')
									{// �R�����g�A�E�g
									 // ���[�J���ϐ��錾
										char c = NULL;
										char d = NULL;
										fscanf(pFile, "%c", &c);
										while (c != '\n' && d != '\n')
										{
											fscanf(pFile, "%s", &aKey[0]);
											fscanf(pFile, "%c", &d);
										}
									}

									if (strcmp("KEY", pKeySet) == 0)
									{// �L�[���̓ǂݍ���
										aKey[0] = { NULL };
										while (strcmp("END_KEY", pKey) != 0)
										{// �ʒu�E�p�x�̓ǂݍ���
											fscanf(pFile, "%s", &aKey[0]);
											if (strcmp("POS", pKey) == 0)
											{// �ʒu���̓ǂݍ���
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosX);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosY);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fPosZ);
											}
											else if (strcmp("ROT", pKey) == 0)
											{// �p�x���̓ǂݍ���
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotX);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotY);
												fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].aKey[nKey].fRotZ);
											}
										}
										nKey++;
									}
									else if (strcmp("FRAME", pKeySet) == 0)
									{// �L�[�t���[�����̓ǂݍ���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_player.aMotionInfo[nMotion].aKeyInfo[nKeySet].nFlame);
									}
								}
								nKeySet++;
							}
						}
						g_player.aMotionInfo[nMotion].nNumKey = nKeySet;	// �L�[���̐ݒ�
						nMotion++;
					}
				}
			}
			else if (bComment == true)
			{// �R�����g�A�E�g����
			 // ���[�J���ϐ��錾
				char a = NULL;
				char b = NULL;
				fscanf(pFile, "%c", &a);
				while (a != '\n' && b != '\n')
				{
					fscanf(pFile, "%s", &aText[0]);
					fscanf(pFile, "%c", &b);
				}
				bComment = false;
			}
		}
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}


//
// ���[�V����
//
void MotionPlayer(MOTIONTYPE motionType)
{
	g_player.nNumKey = g_player.aMotionInfo[motionType].nNumKey;
	g_player.bLoopMotion = g_player.aMotionInfo[motionType].bLoop;

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_player.nCounterMotion == g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame)
		{
			g_player.nCounterMotion = 0;

			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
			{
				g_player.nKey = 0;
			}
			else if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == false)
			{
				if (g_player.motionTypeOld == MOTIONTYPE_STEP)
				{
					g_player.motionType = MOTIONTYPE_NEUTRAL;
					g_player.aModel[0].pos.y = 20.0f;
				}
			}
			else if (g_player.nKey < g_player.nNumKey)
			{
				g_player.nKey++;
			}
		}

		if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			
		}
		else
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey + 1].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nKey].nFlame);
			
		}
	}

	// ���O�̃��[�V������Ԃ̕ۑ�
	g_player.motionTypeOld = g_player.motionType;
}
