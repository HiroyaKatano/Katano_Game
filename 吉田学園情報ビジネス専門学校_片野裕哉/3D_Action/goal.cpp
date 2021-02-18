//=========================================================================================================================
//
// �S�[���A�C�e�� [goal.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "goal.h"
#include "camera.h"

//
// �}�N����`
//

//
// �O���[�o���ϐ�
//
GOAL g_goal;								// �S�[���A�C�e��
char *g_aModel_G_File[MODEL_G_LABEL_MAX] =
{
	"data\\MODEL\\block000.x"		// �u���b�N
};		// ���f���̃t�@�C���ꗗ
LPDIRECT3DTEXTURE9 g_apTextureModel_G[256] = {};	// �e�N�X�`���ւ̃|�C���^

//
// ����������
//
void InitGoal(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_goal.pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	g_goal.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_goal.nNumModel = 0;

	for (int nCntModel = 0; nCntModel < MAX_MODEL_G; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			g_aModel_G_File[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_goal.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_goal.aModel[nCntModel].nNumMatModel,
			&g_goal.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// ���_��
		DWORD sizeFVF = NULL;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^

		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

		g_goal.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_goal.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// ���_�����擾
		nNumvtx = g_goal.aModel[nCntModel].pMeshModel->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_goal.aModel[nCntModel].pMeshModel->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_goal.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

			// ���S�Ă̒��_�����r���ăS�[���A�C�e���̍ŏ��l�E�ő�l�𔲂��o��
			if (g_goal.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_goal.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_goal.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_goal.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_goal.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_goal.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_goal.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_goal.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ���S�Ă̒��_�����r���ăS�[���A�C�e���̍ŏ��l�E�ő�l�𔲂��o��

			pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_goal.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_goal.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goal.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel_G[nCntMat]);
			}// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		}

		g_goal.nNumModel++;
	}

	// �S�p�[�c�̊K�w�\���ݒ�
	g_goal.aModel[0].nIdxModelParent = -1;						// �e�̃C���f�b�N�X��ݒ�
	g_goal.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu�̏����ݒ�
	g_goal.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_goal.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_goal.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�
}


//
// �I������
//
void UninitGoal(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_G; nCntModel++)
	{
		// ���b�V���̔j��
		if (g_goal.aModel[nCntModel].pMeshModel != NULL)
		{
			g_goal.aModel[nCntModel].pMeshModel->Release();
			g_goal.aModel[nCntModel].pMeshModel = NULL;
		}

		// �}�e���A���̔j��
		if (g_goal.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_goal.aModel[nCntModel].pBuffMatModel->Release();
			g_goal.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// �X�V����
//
void UpdateGoal(void)
{
}


//
// �`�揈��
//
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

												// �S�[���A�C�e���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_goal.mtxWorld);

	// �S�[���A�C�e���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.rot.y, g_goal.rot.x, g_goal.rot.z);

	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxRot);

	// �S�[���A�C�e���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_goal.pos.x, g_goal.pos.y, g_goal.pos.z);

	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxTrans);

	// �S�[���A�C�e���̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_goal.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_goal.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;							// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_goal.aModel[nCntModel].mtxWorld);

		// �S�[���A�C�e���̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.aModel[nCntModel].rot.y, g_goal.aModel[nCntModel].rot.x, g_goal.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld, &g_goal.aModel[nCntModel].mtxWorld, &mtxRot);

		// �S�[���A�C�e���̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_goal.aModel[nCntModel].pos.x, g_goal.aModel[nCntModel].pos.y, g_goal.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld, &g_goal.aModel[nCntModel].mtxWorld, &mtxTrans);

		// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_goal.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_goal.aModel[g_goal.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_goal.mtxWorld;
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_goal.aModel[nCntModel].mtxWorld,
			&g_goal.aModel[nCntModel].mtxWorld,
			&mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_goal.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_goal.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_goal.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// ���f��(�p�[�c)�̕`��
		 // �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureModel_G[nCntMat]);

			// �S�[���A�C�e��(�p�[�c)�̕`��
			g_goal.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//
// �S�[���A�C�e���̎擾
//
GOAL *GetGoal(void)
{
	return &g_goal;
}
