//=========================================================================================================================
//
// �A�C�e�� [item.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "item.h"
#include "player.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_TYPE_ITEM] = {};			// �e�N�X�`��
ITEM g_aItem[MAX_ITEM];						// �����̏��

//=========================================================================================================================
// �A�C�e���̏���������
//=========================================================================================================================
HRESULT InitItem(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtex;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemL.png", &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemW.png", &g_apTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemC.png", &g_apTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemB.png", &g_apTextureItem[3]);



	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtex, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_���W�̐ݒ�
		SetVertexItem(nCntItem);

		// rhw�̐ݒ�
		pVtex[0].rhw = 1.0f;
		pVtex[1].rhw = 1.0f;
		pVtex[2].rhw = 1.0f;
		pVtex[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtex[0].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[1].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[2].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);
		pVtex[3].col = D3DCOLOR_RGBA(ITEM_COLOR_R, ITEM_COLOR_G, ITEM_COLOR_B, ITEM_COLOR_A);

		// ���_���̐ݒ�
		pVtex[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtex[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtex[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtex[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtex += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �A�C�e���̏I������
//=========================================================================================================================
void UninitItem(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

	for (int nCntType = 0; nCntType < MAX_TYPE_ITEM; nCntType++)
	{
		// �e�N�X�`���̊J��
		if (g_apTextureItem != NULL)
		{
			g_apTextureItem[nCntType]->Release();
			g_apTextureItem[nCntType] = NULL;
		}
	}
}

//=========================================================================================================================
// �A�C�e���̍X�V����
//=========================================================================================================================
void UpdateItem(void)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos += g_aItem[nCntItem].move;
		SetVertexItem(nCntItem);

		if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x && pPlayer->pos.y >= g_aItem[nCntItem].pos.y)
		{// �e���o���A�̒��S����E�����A�㑤���瓖��������
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((pPlayer->pos.x - g_aItem[nCntItem].pos.x) * (pPlayer->pos.x - g_aItem[nCntItem].pos.x)
					+ (pPlayer->pos.y - g_aItem[nCntItem].pos.y) * (pPlayer->pos.y - g_aItem[nCntItem].pos.y)))) >= 0)
			{// �~���m�̓����蔻��
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (pPlayer->pos.x >= g_aItem[nCntItem].pos.x && g_aItem[nCntItem].pos.y > pPlayer->pos.y)
		{// �e���o���A�̒��S����E�����A�������瓖��������
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((pPlayer->pos.x - g_aItem[nCntItem].pos.x) * (pPlayer->pos.x - g_aItem[nCntItem].pos.x)
					+ (g_aItem[nCntItem].pos.y - pPlayer->pos.y) * (g_aItem[nCntItem].pos.y - pPlayer->pos.y)))) >= 0)
			{// �~���m�̓����蔻��
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (g_aItem[nCntItem].pos.x > pPlayer->pos.x && pPlayer->pos.y >= g_aItem[nCntItem].pos.y)
		{// �e���o���A�̒��S���獶�����A�㑤���瓖��������
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((g_aItem[nCntItem].pos.x - pPlayer->pos.x) * (g_aItem[nCntItem].pos.x - pPlayer->pos.x)
					+ (pPlayer->pos.y - g_aItem[nCntItem].pos.y) * (pPlayer->pos.y - g_aItem[nCntItem].pos.y)))) >= 0)
			{// �~���m�̓����蔻��
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
		else if (g_aItem[nCntItem].pos.x > pPlayer->pos.x && g_aItem[nCntItem].pos.y > pPlayer->pos.y)
		{// �e���o���A�̒��S���獶�����A�������瓖��������
			if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
				- (sqrtf((g_aItem[nCntItem].pos.x - pPlayer->pos.x) * (g_aItem[nCntItem].pos.x - pPlayer->pos.x)
					+ (g_aItem[nCntItem].pos.y - pPlayer->pos.y) * (g_aItem[nCntItem].pos.y - pPlayer->pos.y)))) >= 0)
			{// �~���m�̓����蔻��
				HitItem(nCntItem, g_aItem[nCntItem].nType);

				g_aItem[nCntItem].bUse = false;
			}
		}
	}
}

//=========================================================================================================================
// �A�C�e���̕`�揈��
//=========================================================================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].nType]);

		if (g_aItem[nCntItem].bUse == true)
		{
			// �A�C�e���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntItem * 4,					// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}
}

//=========================================================================================================================
// �A�C�e���̐ݒ�
//=========================================================================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	ITEM *pItem;
	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == false)
		{
			// �ʒu�̐ݒ�
			pItem->pos = pos;

			pItem->move = move;

			// ���_���W�̐ݒ�
			SetVertexItem(nCntItem);

			pItem->nType = nType;

			pItem->bUse = true;
			break;
		}
	}
}

//=========================================================================================================================
//
//=========================================================================================================================
void SetVertexItem(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZE_X, g_aItem[nIdx].pos.y + ITEM_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZE_X, g_aItem[nIdx].pos.y - ITEM_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZE_X, g_aItem[nIdx].pos.y + ITEM_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZE_X, g_aItem[nIdx].pos.y - ITEM_SIZE_Y, 0.0f);

	// ���_�o�b�t�@�̊J��
	g_pVtxBuffItem->Unlock();
}


//
//
//
bool HitItem(int nIdx, int nType)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	switch (g_aItem[nIdx].nType)
	{
	case 0:
		pPlayer->SelectBullet = SELECT_LASER;
		break;
	case 1:
		pPlayer->SelectBullet = SELECT_WAVE;
		break;
	case 2:
		pPlayer->SelectBullet = SELECT_CIRCLE;
		break;
	case 3:
		pPlayer->SelectBullet = SELECT_BOMBER;
		break;
	default:
		break;
	}

	return true;
}
