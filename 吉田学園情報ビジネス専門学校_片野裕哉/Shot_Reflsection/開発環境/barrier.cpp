//=========================================================================================================================
//
// �o���A [barrier.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "barrier.h"
#include "player.h"
#include "Score.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBarrier = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureBarrier = NULL;			// �e�N�X�`��
BARRIER g_Barrier;

//=========================================================================================================================
// �o���A�̏���������
//=========================================================================================================================
HRESULT InitBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\barrier001.png", &g_pTextureBarrier);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBarrier,
		NULL)))
	{
		return E_FAIL;
	}

	// �A�j���[�V�����J�E���^�[�ƃA�j���[�V�����p�^�[��No.�̏�����
	g_Barrier.nCounterAnim = 0;
	g_Barrier.nPatternAnim = 0;
	g_Barrier.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Barrier.state = BARRIERSTATE_WAIT;
	g_Barrier.nCounterState = BARRIER_TIMER;
	g_Barrier.nCounterDisp = 0;
	g_Barrier.bDisp = true;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒���
	g_Barrier.fLengthBarrier = sqrtf(VERTEX_X * VERTEX_X + VERTEX_Y * VERTEX_Y);

	// �Ίp���̊p�x
	g_Barrier.fAngleBarrier = atan2f(VERTEX_X, VERTEX_Y);

	// �o���A�̉�]�p
	g_Barrier.rotBarrier = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//pVtx[0].pos.x = g_pos.x + sinf(g_fAngleBarrier + D3DX_PI * 1.75f) * g_fLengthBarrier;
	//pVtx[0].pos.y = g_pos.y + cosf(g_fAngleBarrier + D3DX_PI * 1.75f) * g_fLengthBarrier;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = g_pos.x + sinf(D3DX_PI * 1.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[1].pos.y = g_pos.y + cosf(D3DX_PI * 1.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = g_pos.x + sinf(D3DX_PI * 0.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[2].pos.y = g_pos.y + cosf(D3DX_PI * 0.25f - g_fAngleBarrier) * g_fLengthBarrier;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = g_pos.x + sinf(g_fAngleBarrier + D3DX_PI * 0.75f) * g_fLengthBarrier;
	//pVtx[3].pos.y = g_pos.y + cosf(g_fAngleBarrier + D3DX_PI * 0.75f) * g_fLengthBarrier;
	//pVtx[3].pos.z = 0.0f;

	pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
	pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 1.0f / TEXTURE_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBarrier->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �o���A�̏I������
//=========================================================================================================================
void UninitBarrier(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBarrier != NULL)
	{
		g_pVtxBuffBarrier->Release();
		g_pVtxBuffBarrier = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBarrier != NULL)
	{
		g_pTextureBarrier->Release();
		g_pTextureBarrier = NULL;
	}
}

//=========================================================================================================================
// �o���A�̍X�V����
//=========================================================================================================================
void UpdateBarrier(void)
{
	VERTEX_2D *pVtx;
	BULLET *pBullet;
	PLAYER *pPlayer;

	pBullet = GetBullet();
	pPlayer = GetPlayer();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Barrier.state == BARRIERSTATE_ACTIVE)
	{// �o���A�W�J��

		// ����Q�[�W�̏���
		g_Barrier.nCounterState -= BARRIER_COST;
		
		// �ʒu�̍X�V
		g_Barrier.pos.x = pPlayer->pos.x;
		g_Barrier.pos.y = pPlayer->pos.y;

		pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

		if (g_Barrier.nCounterState <= 0)
		{
			g_Barrier.state = BARRIERSTATE_WAIT;

			pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
			pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A);
		}
		else if (g_Barrier.nCounterState <= BARRIER_FLASH && g_Barrier.nCounterState > 0)
		{
			if (g_Barrier.nCounterState % 5 == 0)
			{
				pVtx[0].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[1].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[2].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
				pVtx[3].col = D3DXCOLOR(BARRIER_COLOR_R, BARRIER_COLOR_G, BARRIER_COLOR_B, BARRIER_COLOR_A * (g_Barrier.nCounterState % FLASH_TIMING));
			}
		}
	}
	else if (g_Barrier.state == BARRIERSTATE_WAIT)
	{// �o���A��W�J���Ă��Ȃ���
		if (g_Barrier.nCounterState >= 0 && g_Barrier.nCounterState < BARRIER_TIMER && pPlayer->state == PLAYERSTATE_NORMAL)
		{// ����Q�[�W���ő�܂ŗ��܂��Ă��炸�A�v���C���[���ʏ��Ԃ̎�

			// ����Q�[�W�̉�
			g_Barrier.nCounterState += 1;
		}
		else if (g_Barrier.nCounterState >= BARRIER_TIMER)
		{// ����Q�[�W���ő�ȏ�̎�

			// ����Q�[�W���ő�l�𒴂��Ȃ��悤�ɕ␳
			g_Barrier.nCounterState = BARRIER_TIMER;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBarrier->Unlock();
}

//=========================================================================================================================
// �o���A�̕`�揈��
//=========================================================================================================================
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBarrier, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBarrier);

	if (g_Barrier.state == BARRIERSTATE_ACTIVE)
	{
		// �o���A�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			0,								// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}

//=========================================================================================================================
// �o���A�̐ݒ�
//=========================================================================================================================
void SetBarrier(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Barrier.state == BARRIERSTATE_WAIT)
	{
		// �ʒu�̐ݒ�
		g_Barrier.pos = pos;

		pVtx[0].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Barrier.pos.x - BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y + BARRIER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Barrier.pos.x + BARRIER_SIZE_X, g_Barrier.pos.y - BARRIER_SIZE_Y, 0.0f);

		g_Barrier.state = BARRIERSTATE_ACTIVE;
	}
}


//=========================================================================================================================
// �o���A�̎擾
//=========================================================================================================================
BARRIER *GetBarrier(void)
{
	return &g_Barrier;
}

//=========================================================================================================================
// �o���A�̃q�b�g����
//=========================================================================================================================
bool HitBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETMODE mode,int nDamage)
{

	SetBullet(pos, move * -2, LIFE_BULLET, BULLETTYPE_PLAYER, mode, nDamage * 10);

	AddScore(nDamage);

	return true;
}
