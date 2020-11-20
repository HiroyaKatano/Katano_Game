//=========================================================================================================================
//
// �e [bullet.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "bullet.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "barrier.h"
#include "effect.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_apTextureBullet[MAX_MODE_BULLET] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
BULLET g_aBullet[MAX_BULLET];						// �e�̏��

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &g_apTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet002.png", &g_apTextureBullet[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_apTextureBullet[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wave.png", &g_apTextureBullet[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bomber.png", &g_apTextureBullet[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\circle.png", &g_apTextureBullet[5]);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].mode = BULLET_NORMAL;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}
	
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		SetVertexBullet(nCntBullet);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntmode = 0; nCntmode < MAX_MODE_BULLET; nCntmode++)
	{
		if (g_apTextureBullet != NULL)
		{
			g_apTextureBullet[nCntmode]->Release();
			g_apTextureBullet[nCntmode] = NULL;
		}
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateBullet(void)
{
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	BARRIER *pBarrier;

	pBullet = &g_aBullet[0];
	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	pBarrier = GetBarrier();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// �ʒu�̍X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y -= pBullet->move.y;

			// ���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);
			
			pBullet->nLife -= 1;
			// �����`�F�b�N
			if (pBullet->nLife == 0)
			{
				SetExplosion(pBullet->pos, EXPLOSION_ENEMY);
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				pBullet->bUse = false;
			}

			// ��ʊO�`�F�b�N
			if (pBullet->pos.y <= 0 || pBullet->pos.y > SCREEN_HEIGTH)
			{
				pBullet->bUse = false;
			}

			if (pBullet->type == BULLETTYPE_PLAYER)
			{
				// �G�Ƃ̓����蔻��
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pBullet->mode == BULLET_NORMAL)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_NORMAL_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_NORMAL_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_NORMAL_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_NORMAL_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_LASER)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_LASER_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_LASER_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_LASER_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_LASER_SIZE_X)
							{
								//pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_WAVE)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_WAVE_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_WAVE_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_WAVE_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_WAVE_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
						else if (pBullet->mode == BULLET_BOMBER)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_BOMBER_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_BOMBER_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_BOMBER_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_BOMBER_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
								SetExplosion(pEnemy->pos, EXPLOSION_BOMBER);
							}
						}
						else if (pBullet->mode == BULLET_CIRCLE)
						{
							if (pEnemy->pos.y - ENEMY_SIZE_Y + 5 <= pBullet->pos.y + BULLET_CIRCLE_SIZE_Y &&
								pEnemy->pos.y + ENEMY_SIZE_Y - 5 >= pBullet->pos.y - BULLET_CIRCLE_SIZE_Y &&
								pEnemy->pos.x - ENEMY_SIZE_X + 5 + pEnemy->move.x <= pBullet->pos.x + BULLET_CIRCLE_SIZE_X &&
								pEnemy->pos.x + ENEMY_SIZE_X - 5 + pEnemy->move.x >= pBullet->pos.x - BULLET_CIRCLE_SIZE_X)
							{
								pBullet->bUse = false;
								HitEnemy(nCntEnemy, pBullet->nAttack);
							}
						}
					}
				}
			}
			else if (pBullet->type == BULLETTYPE_ENEMY)
			{// �G�e�̏ꍇ
				if (pPlayer->state == PLAYERSTATE_NORMAL && pBarrier->state == BARRIERSTATE_WAIT)
				{// �v���C���[���ʏ��Ԃ̎����A�o���A���W�J����Ă��Ȃ���
					if (pPlayer->pos.x >= pBullet->pos.x && pPlayer->pos.y >= pBullet->pos.y)
					{// �e���v���C���[�̒��S����E�����A�㑤���瓖��������
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pPlayer->pos.x - pBullet->pos.x) * (pPlayer->pos.x - pBullet->pos.x)
							+ (pPlayer->pos.y - pBullet->pos.y) * (pPlayer->pos.y - pBullet->pos.y)))) >= 18)
						{// �~���m�̓����蔻��
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pPlayer->pos.x >= pBullet->pos.x && pBullet->pos.y > pPlayer->pos.y)
					{// �e���v���C���[�̒��S����E�����A�������瓖��������
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pPlayer->pos.x - pBullet->pos.x) * (pPlayer->pos.x - pBullet->pos.x)
							+ (pBullet->pos.y - pPlayer->pos.y) * (pBullet->pos.y - pPlayer->pos.y)))) >= 18)
						{// �~���m�̓����蔻��
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pPlayer->pos.x && pPlayer->pos.y >= pBullet->pos.y)
					{// �e���v���C���[�̒��S���獶�����A�㑤���瓖��������
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pPlayer->pos.x) * (pBullet->pos.x - pPlayer->pos.x)
							+ (pPlayer->pos.y - pBullet->pos.y) * (pPlayer->pos.y - pBullet->pos.y)))) >= 18)
						{// �~���m�̓����蔻��
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pPlayer->pos.x && pBullet->pos.y > pPlayer->pos.y)
					{// �e���v���C���[�̒��S���獶�����A�������瓖��������
						if (((BULLET_NORMAL_SIZE_X + PLAYER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pPlayer->pos.x) * (pBullet->pos.x - pPlayer->pos.x)
							+ (pBullet->pos.y - pPlayer->pos.y) * (pBullet->pos.y - pPlayer->pos.y)))) >= 18)
						{// �~���m�̓����蔻��
							HitPlayer(pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
				}
				else if (pPlayer->state == PLAYERSTATE_NORMAL && pBarrier->state == BARRIERSTATE_ACTIVE)
				{// �v���C���[���ʏ��Ԃ̎����A�o���A���W�J����Ă��鎞
					if (pBarrier->pos.x >= pBullet->pos.x && pBarrier->pos.y >= pBullet->pos.y)
					{// �e���o���A�̒��S����E�����A�㑤���瓖��������
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBarrier->pos.x - pBullet->pos.x) * (pBarrier->pos.x - pBullet->pos.x)
								+ (pBarrier->pos.y - pBullet->pos.y) * (pBarrier->pos.y - pBullet->pos.y)))) >= 0)
						{// �~���m�̓����蔻��
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode,pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBarrier->pos.x >= pBullet->pos.x && pBullet->pos.y > pBarrier->pos.y)
					{// �e���o���A�̒��S����E�����A�������瓖��������
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBarrier->pos.x - pBullet->pos.x) * (pBarrier->pos.x - pBullet->pos.x)
								+ (pBullet->pos.y - pBarrier->pos.y) * (pBullet->pos.y - pBarrier->pos.y)))) >= 0)
						{// �~���m�̓����蔻��
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pBarrier->pos.x && pBarrier->pos.y >= pBullet->pos.y)
					{// �e���o���A�̒��S���獶�����A�㑤���瓖��������
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pBarrier->pos.x) * (pBullet->pos.x - pBarrier->pos.x)
								+ (pBarrier->pos.y - pBullet->pos.y) * (pBarrier->pos.y - pBullet->pos.y)))) >= 0)
						{// �~���m�̓����蔻��
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
					else if (pBullet->pos.x > pBarrier->pos.x && pBullet->pos.y > pBarrier->pos.y)
					{// �e���o���A�̒��S���獶�����A�������瓖��������
						if (((BULLET_NORMAL_SIZE_X + BARRIER_SIZE_X)
							- (sqrtf((pBullet->pos.x - pBarrier->pos.x) * (pBullet->pos.x - pBarrier->pos.x)
								+ (pBullet->pos.y - pBarrier->pos.y) * (pBullet->pos.y - pBarrier->pos.y)))) >= 0)
						{// �~���m�̓����蔻��
							HitBarrier(pBullet->pos, pBullet->move, pBullet->mode, pBullet->nAttack);

							pBullet->bUse = false;
						}
					}
				}
			}

			// �G���̃��Z�b�g
			pEnemy = GetEnemy();
		}
	}
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			if (g_aBullet[nCntBullet].mode == BULLET_NORMAL)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

				switch (g_aBullet[nCntBullet].type)
				{
				case BULLETTYPE_PLAYER:
					pDevice->SetTexture(0, g_apTextureBullet[0]);
					break;
				case BULLETTYPE_ENEMY:
					pDevice->SetTexture(0, g_apTextureBullet[1]);
					break;
				}

			}
			else if (g_aBullet[nCntBullet].mode == BULLET_LASER)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

				pDevice->SetTexture(0, g_apTextureBullet[2]);
				
				
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_WAVE)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

				pDevice->SetTexture(0, g_apTextureBullet[3]);
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_BOMBER)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

				pDevice->SetTexture(0, g_apTextureBullet[4]);
			}
			else if (g_aBullet[nCntBullet].mode == BULLET_CIRCLE)
			{
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

				pDevice->SetTexture(0, g_apTextureBullet[5]);
			}

			// �e�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntBullet * 4,					// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
}

//=========================================================================================================================
// �e�̐ݒ�
//=========================================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type, BULLETMODE mode, int nAttack)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			// �ʒu�̐ݒ�
			pBullet->pos = pos;

			// ���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			pBullet->move = move;

			pBullet->nLife = nLife;

			pBullet->type = type;

			pBullet->mode = mode;

			pBullet->nAttack = nAttack;

			pBullet->bUse = true;

			break;
		}
	}
}

//=========================================================================================================================
// 
//=========================================================================================================================
void SetVertexBullet(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aBullet[nIdx].mode == BULLET_NORMAL)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_NORMAL_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_NORMAL_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_NORMAL_SIZE_Y, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_LASER)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_LASER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_LASER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_LASER_SIZE_Y, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = LASER_COLOR;
		pVtx[1].col = LASER_COLOR;
		pVtx[2].col = LASER_COLOR;
		pVtx[3].col = LASER_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_WAVE)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_WAVE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_WAVE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_WAVE_SIZE_Y, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_BOMBER)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_BOMBER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_BOMBER_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_BOMBER_SIZE_Y, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	else if (g_aBullet[nIdx].mode == BULLET_CIRCLE)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y + BULLET_CIRCLE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_CIRCLE_SIZE_X, g_aBullet[nIdx].pos.y - BULLET_CIRCLE_SIZE_Y, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = BULLET_NORMAL_COLOR;
		pVtx[1].col = BULLET_NORMAL_COLOR;
		pVtx[2].col = BULLET_NORMAL_COLOR;
		pVtx[3].col = BULLET_NORMAL_COLOR;
	}
	
	// ���_�o�b�t�@�̊J��
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// �e�̎擾
//=========================================================================================================================
BULLET *GetBullet(void)
{
	return &g_aBullet[0];
}