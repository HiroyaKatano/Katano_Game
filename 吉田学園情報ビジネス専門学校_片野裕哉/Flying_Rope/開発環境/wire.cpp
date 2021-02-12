//
//
//
//
//
//
#include "wire.h"
#include "player.h"
#include "input.h"
#include "block.h"

//
// �}�N����`
//
#define MAX_TYPE_WIRE (1)

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWire = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureWire = NULL;			// �e�N�X�`��
WIRE g_aWire[MAX_WIRE];							// ���C���[�̏��

//
// ����������
//
HRESULT InitWire(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rope.png", &g_pTextureWire);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_WIRE * 4,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWire,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++)
	{
		g_aWire[nCntWire].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWire[nCntWire].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWire[nCntWire].col = WIRE_COLOR;
		g_aWire[nCntWire].fWidth = 0.0f;
		g_aWire[nCntWire].fHeight = 0.0f;
		g_aWire[nCntWire].bUse = false;
		g_aWire[nCntWire].bContact = false;
		g_aWire[nCntWire].rotWire = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWire[nCntWire].fLengthWire = 0.0f;
		g_aWire[nCntWire].fAngleWire = 0.0f;
	}


	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWire->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++)
	{
		SetVertexWire(nCntWire);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = WIRE_COLOR;
		pVtx[1].col = WIRE_COLOR;
		pVtx[2].col = WIRE_COLOR;
		pVtx[3].col = WIRE_COLOR;

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWire->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitWire(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWire != NULL)
	{
		g_pVtxBuffWire->Release();
		g_pVtxBuffWire = NULL;
	}

	// �e�N�X�`���̊J��
	//for (int nCnt = 0; nCnt < MAX_TYPE_WIRE; nCnt++)
	//{
	if (g_pTextureWire != NULL)
	{
		g_pTextureWire->Release();
		g_pTextureWire = NULL;
	}
	//}
}


//
// �X�V����
//
void UpdateWire(void)
{
	WIRE *pWire;
	PLAYER *pPlayer;
	BLOCK *pBlock;
	
	pWire = &g_aWire[0];
	pPlayer = GetPlayer();
	pBlock = GetBlock();

	
	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
	{
		pWire->posOld = pWire->pos;

		if (pWire->bUse == true)
		{
			if (GetKeyboardTrigger(DIK_I) == true || pPlayer->state == PLAYERSTATE_WAIT)
			{
				pWire->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pWire->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pWire->col = WIRE_COLOR;
				pWire->fWidth = 0.0f;
				pWire->fHeight = 0.0f;
				pWire->bUse = false;
				pWire->bContact = false;
				pWire->rotWire = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pWire->fLengthWire = 0.0f;
				pWire->fAngleWire = 0.0f;
			}

			if (pWire->fHeight < WIRE_MAX_SIZE_Y && pWire->bContact == false && pWire->bExtend == true)
			{
				pWire->fHeight += WIRE_EXTEND_SPD;
				pWire->pos += pWire->move;
			}
			else if (pWire->fHeight >= WIRE_MAX_SIZE_Y && pWire->bContact == false && pWire->bExtend == true)
			{
				pWire->bExtend = false;
			}
			else if (pWire->fHeight > 0 && pWire->bContact == false && pWire->bExtend == false)
			{
				pWire->fHeight -= WIRE_EXTEND_SPD;
				pWire->pos.x += (pPlayer->pos.x - pWire->pos.x) * 0.5f;
				pWire->pos.y += ((pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y) * 0.3f;
			}
			if (pWire->fHeight <= 0 && pWire->bContact == false && pWire->bExtend == false)
			{
				pWire->bUse = false;
			}

			// ��]
			pWire->rotWire.z = atan2f(pPlayer->pos.x - pWire->pos.x,
										(pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y);

			pWire->fHeight = sqrtf(
				(pPlayer->pos.x - pWire->pos.x) *
				(pPlayer->pos.x - pWire->pos.x) +
				((pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y) *
				((pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y));

			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
			{

				if (pBlock->bUse == true)
				{
					if (pWire->bExtend == true)
					{
						if (pWire->pos.x > pBlock->pos.x &&
							pWire->pos.x < pBlock->pos.x + pBlock->fWidth)
						{
							if (pWire->posOld.y <= pBlock->pos.y)
							{
								if (pWire->pos.y > pBlock->pos.y)
								{
									pWire->pos.y = pBlock->pos.y;
									pWire->bContact = true;
								}
							}
							else if (pWire->posOld.y >= pBlock->pos.y + pBlock->fHeight)
							{
								if (pWire->pos.y < pBlock->pos.y + pBlock->fHeight)
								{
									pWire->pos.y = pBlock->pos.y + pBlock->fHeight;
									pWire->bContact = true;
								}
							}
						}

						if (pWire->pos.y > pBlock->pos.y &&
							pWire->pos.y < pBlock->pos.y + pBlock->fHeight)
						{
							if (pWire->posOld.x >= pBlock->pos.x + pBlock->fWidth)
							{
								if (pWire->pos.x < pBlock->pos.x + pBlock->fWidth)
								{
									pWire->pos.x = (pBlock->pos.x + pBlock->fWidth);
									pWire->bContact = true;
								}
							}
							else if (pWire->posOld.x <= pBlock->pos.x)
							{
								if (pWire->pos.x > pBlock->pos.x)
								{
									pWire->pos.x = pBlock->pos.x - pWire->fWidth;
									pWire->bContact = true;
								}
							}
						}
					}
				}
			}

			pBlock = GetBlock();


			SetVertexWire(nCntWire);
		}
	}

}


//
// �`�揈��
//
void DrawWire(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWire, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++)
	{
		if (g_aWire[nCntWire].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWire);

			// �v���C���[�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntWire * 4,					// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}
}


//
// ���C���[�̃Z�b�g����
//
void SetWire(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWireWigth, float fWireHeight)
{
	WIRE *pWire;
	pWire = &g_aWire[0];

	for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
	{
		if (pWire->bUse == false)
		{
			// �ʒu�̐ݒ�
			pWire->pos = pos;

			pWire->move = move;

			pWire->fWidth = fWireWigth;

			pWire->fHeight = fWireHeight;

			// ���_���W�̐ݒ�
			SetVertexWire(nCntWire);

			pWire->bUse = true;

			pWire->bExtend = true;

			break;
		}
	}
}


//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexWire(int nIdx)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	g_pVtxBuffWire->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	// �Ίp���̒���
	g_aWire[nIdx].fLengthWire = sqrtf(g_aWire[nIdx].fWidth * g_aWire[nIdx].fWidth + g_aWire[nIdx].fHeight * g_aWire[nIdx].fHeight);

	// �Ίp���̊p�x
	g_aWire[nIdx].fAngleWire = atan2f(g_aWire[nIdx].fWidth, g_aWire[nIdx].fHeight);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = g_aWire[nIdx].pos.x + sinf(g_aWire[nIdx].rotWire.z - g_aWire[nIdx].fAngleWire) * g_aWire[nIdx].fLengthWire;
	pVtx[0].pos.y = g_aWire[nIdx].pos.y + cosf(g_aWire[nIdx].rotWire.z - g_aWire[nIdx].fAngleWire) * g_aWire[nIdx].fLengthWire;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aWire[nIdx].pos.x + sinf(g_aWire[nIdx].rotWire.z + -D3DX_PI / 2) * g_aWire[nIdx].fWidth;
	pVtx[1].pos.y = g_aWire[nIdx].pos.y + cosf(g_aWire[nIdx].rotWire.z + -D3DX_PI / 2) * g_aWire[nIdx].fWidth;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aWire[nIdx].pos.x + sinf(g_aWire[nIdx].rotWire.z + g_aWire[nIdx].fAngleWire) * g_aWire[nIdx].fLengthWire;
	pVtx[2].pos.y = g_aWire[nIdx].pos.y + cosf(g_aWire[nIdx].rotWire.z + g_aWire[nIdx].fAngleWire) * g_aWire[nIdx].fLengthWire;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aWire[nIdx].pos.x + sinf(g_aWire[nIdx].rotWire.z + D3DX_PI / 2) * g_aWire[nIdx].fWidth;
	pVtx[3].pos.y = g_aWire[nIdx].pos.y + cosf(g_aWire[nIdx].rotWire.z + D3DX_PI / 2) * g_aWire[nIdx].fWidth;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = WIRE_COLOR;
	pVtx[1].col = WIRE_COLOR;
	pVtx[2].col = WIRE_COLOR;
	pVtx[3].col = WIRE_COLOR;

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	// ���_�o�b�t�@�̊J��
	g_pVtxBuffWire->Unlock();
}


//
// ���C���[�̏��擾
//
WIRE *GetWire(void)
{
	return &g_aWire[0];
}