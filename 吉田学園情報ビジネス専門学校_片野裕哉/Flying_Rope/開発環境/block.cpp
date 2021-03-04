//
//
//
//
//
//
#include "block.h"
#include "player.h"
#include "result.h"
#include "fade.h"

//
// �}�N����`
//
#define MAX_BLOCK (256)
#define MAX_TYPE_BLOCK (2)

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			// �e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			// �e�N�X�`��
BLOCK g_aBlock[MAX_BLOCK];							// �u���b�N�̏��

//
// ����������
//
HRESULT InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &g_pTextureBlock);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal_star.png", &g_pTextureGoal);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_BLOCK * VTX_NUM,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, Z_AXIS_ZERO);
		g_aBlock[nCntBlock].col = BLOCK_COLOR;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
	}


	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		SetVertexBlock(nCntBlock);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitBlock(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// �e�N�X�`���̊J��
	//for (int nCnt = 0; nCnt < MAX_TYPE_BLOCK; nCnt++)
	//{
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
	//}

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
}


//
// �X�V����
//
void UpdateBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			SetVertexBlock(nCntBlock);
		}
	}
	
}


//
// �`�揈��
//
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			switch (g_aBlock[nCntBlock].BlockType)
			{
			case 0:
				pDevice->SetTexture(0, g_pTextureBlock);
				break;
			case 1:
				pDevice->SetTexture(0, g_pTextureGoal);
			default:
				break;
			}
			

			// �v���C���[�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntBlock * VTX_NUM,			// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}
}


//
// �u���b�N�̃Z�b�g����
//
void SetBlock(D3DXVECTOR3 BlockPos, D3DXVECTOR3 BlockMove, float fBlockWigth, float fBlockHeight, BLOCKTYPE BlockType)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{
			// �ʒu�̐ݒ�
			pBlock->pos = BlockPos;

			pBlock->move = BlockMove;

			pBlock->fWidth = fBlockWigth;

			pBlock->fHeight = fBlockHeight;

			pBlock->BlockType = BlockType;
			
			// ���_���W�̐ݒ�
			SetVertexBlock(nCntBlock);

			pBlock->bUse = true;

			break;
		}
	}
}


//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexBlock(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * VTX_NUM;


	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, Z_AXIS_ZERO);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y, Z_AXIS_ZERO);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, Z_AXIS_ZERO);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, Z_AXIS_ZERO);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = BLOCK_COLOR;
	pVtx[1].col = BLOCK_COLOR;
	pVtx[2].col = BLOCK_COLOR;
	pVtx[3].col = BLOCK_COLOR;

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aBlock[nIdx].fWidth / g_aBlock[nIdx].fHeight, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aBlock[nIdx].fWidth / g_aBlock[nIdx].fHeight, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	
	// ���_�o�b�t�@�̊J��
	g_pVtxBuffBlock->Unlock();
}


//
// �u���b�N�̏��擾
//
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}


//
//
//
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	BLOCK *pBlock;
	RESULT *pResult = GetResult();

	bool bLand = false;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			if (pPos->x + fWidth > pBlock->pos.x + 1.0f&&
				pPos->x - fWidth < pBlock->pos.x + pBlock->fWidth)
			{// �v���C���[�̉E�[���u���b�N�̍��[���E�����v���C���[�̍��[���u���b�N�̉E�[��荶���Ɉʒu����Ƃ�
				if (pPosOld->y <= pBlock->pos.y - 1.0f)
				{// �O��̃v���C���[�̉��[���u���b�N�̏�[�ɐG��Ă��Ȃ��Ƃ�
					if (pPos->y > pBlock->pos.y - 1.0f)
					{// ���݂̃v���C���[�̉��[���u���b�N�̏�[���������Ɉʒu����Ƃ�
						pPos->y = pBlock->pos.y - 1.0f;
						pMove->y = 0.0f;
						bLand = true;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// �u���b�N�̎�ނ��S�[���ł������ꍇ
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
 				else if (pPosOld->y - fHeight >= pBlock->pos.y + pBlock->fHeight)
				{// �O��̃v���C���[�̏�[���u���b�N�̉��[�ɐG��Ă��Ȃ��Ƃ�
					if (pPos->y - fHeight < pBlock->pos.y + pBlock->fHeight)
					{// ���݂̃v���C���[�̏�[���u���b�N�̉��[���㑤�Ɉʒu����Ƃ�
						pPos->y = (pBlock->pos.y + pBlock->fHeight) + fHeight;
						pMove->y = 1.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// �u���b�N�̎�ނ��S�[���ł������ꍇ
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
			}

			if (pPos->y > pBlock->pos.y &&
				pPos->y - fHeight < pBlock->pos.y + pBlock->fHeight)
			{// ���݂̃v���C���[�̉��[���u���b�N�̏�[�����������v���C���[�̏�[���u���b�N�̉��[���㑤�Ɉʒu����Ƃ�
				if (pPosOld->x - fWidth >= pBlock->pos.x + pBlock->fWidth + 1.0f)
				{// �O��̃v���C���[�̍��[���u���b�N�̉E�[�ɐG��Ă��Ȃ��Ƃ�
					if (pPos->x - fWidth < pBlock->pos.x + pBlock->fWidth + 1.0f)
					{// ���݂̃v���C���[�̍��[���u���b�N�̉E�[��荶���Ɉʒu����Ƃ�
						pPos->x = (pBlock->pos.x + pBlock->fWidth) + fWidth + 1.0f;
						pMove->x = 0.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// �u���b�N�̎�ނ��S�[���ł������ꍇ
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
				else if (pPosOld->x + fWidth <= pBlock->pos.x)
				{// �O��̃v���C���[�̉E�[���u���b�N�̍��[�ɐG��Ă��Ȃ��Ƃ�
					if (pPos->x + fWidth > pBlock->pos.x)
					{// ���݂̃v���C���[�̉E�[���u���b�N�̍��[��荶���Ɉʒu����Ƃ�
						pPos->x = pBlock->pos.x - fWidth;
						pMove->x = 0.0f;

						if (pBlock->BlockType == BLOCKTYPE_GOAL)
						{// �u���b�N�̎�ނ��S�[���ł������ꍇ
							pResult->ResultType = RESULTTYPE_CLEAR;
							SetFade(FADE_OUT, MODE_RESULT);
						}
					}
				}
			}
		}
	}

	return bLand;
}
