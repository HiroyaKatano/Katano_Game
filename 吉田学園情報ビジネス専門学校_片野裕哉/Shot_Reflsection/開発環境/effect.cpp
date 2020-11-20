//=========================================================================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "input.h"
#include "enemy.h"
#include "effect.h"

//=========================================================================================================================
// �\���̂̒�`
//=========================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;		// �F
	float fDecay;			// �ړ��̌���
	float fRadius;			// ���a
	float nCntAlpha;		// ���l�̈ړ�
	int nLife;				// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
}Effect;

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
Effect g_aEffect[MAX_EFFECT];						// �G�t�F�N�g�̏��

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fDecay = NULL;
		g_aEffect[nCntEffect].fRadius = NULL;
		g_aEffect[nCntEffect].nCntAlpha = NULL;
		g_aEffect[nCntEffect].nLife = NULL;
		g_aEffect[nCntEffect].bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EFFECT,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, EFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(EFFECT_SIZE, EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_SIZE, 0.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[1].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[2].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);
		pVtx[3].col = D3DXCOLOR(EFFECT_COLOR_R, EFFECT_COLOR_G, EFFECT_COLOR_B, EFFECT_COLOR_A);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateEffect(void)
{
	Effect *pEffect;
	VERTEX_2D *pVtx;

	pEffect = &g_aEffect[0];

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		g_aEffect[nCntEffect].col.a -= 0.04f;

		if (g_aEffect[nCntEffect].col.a <= 0.0f)	//0.0f�ɂȂ����牽�����Ȃ�
		{
			g_aEffect[nCntEffect].bUse = false;
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;
		// ���̏��ɂ���
		pVtx += 4;

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//�G�t�F�N�g�̕`�揈��
//=========================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			// �G�t�F�N�g�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntEffect * 4,					// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
}

//=========================================================================================================================
// �G�t�F�N�g�̐ݒ�
//=========================================================================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fDecay, float fRadius, float fCntAlpha, int nLife)
{
	Effect *pEffect;
	VERTEX_2D *pVtx;

	pEffect = &g_aEffect[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// �����̐ݒ�
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y + 20.0f, 0.0f);	//Z��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y - 20.0f, 0.0f);

			// �ʒu�ݒ�
			pEffect->pos = pos;

			// �ړ��ʂ̐ݒ�
			pEffect->move = move;

			// �F�ݒ�
			pEffect->col = col;

			// �ړ��ʂ̌����l
			pEffect->fDecay = fDecay;

			// ���a�̐ݒ�
			pEffect->fRadius = fRadius;

			// ���l�̈ړ���
			pEffect->nCntAlpha = fCntAlpha;

			// �����̐ݒ�
			pEffect->nLife = nLife;

			// true�ŕԂ�
			pEffect->bUse = true;

			break;
		}
	}
	// ���_�o�b�t�@���A�����b �N����
	g_pVtxBuffEffect->Unlock();
}