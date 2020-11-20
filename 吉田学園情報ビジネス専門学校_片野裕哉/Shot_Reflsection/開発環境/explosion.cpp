//=========================================================================================================================
//
// �������� [explosion.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "input.h"
#include "enemy.h"
#include "explosion.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSION];						// �����̏��

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Explosion000.png", &g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nAttack = 200;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���_���W�̐ݒ�
		SetVertexExplosion(nCntExplosion);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[1].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[2].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);
		pVtx[3].col = D3DCOLOR_RGBA(EXPLOSION_COLOR_R, EXPLOSION_COLOR_G, EXPLOSION_COLOR_B, EXPLOSION_COLOR_A);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / EXPLOSION_TEXTURE_Y);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_X, 1.0f / EXPLOSION_TEXTURE_Y);
		pVtx[3].tex = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_X, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffExplosion->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitExplosion(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;

	pExplosion = &g_aExplosion[0];
	pEnemy = GetEnemy();
	
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			// �J�E���^�[�A�b�v
			pExplosion->nCounterAnim += 1;

			// 4�̔{���̎�����
			if ((pExplosion->nCounterAnim % 3) == 0)
			{
				// �A�j���[�V�����p�^�[��No.���X�V
				pExplosion->nPatternAnim = (pExplosion->nPatternAnim + 1) % MAX_EXPLOSION_PATTERN;
			}

			// �A�j���[�V�����̍X�V
			pVtx[0].tex = D3DXVECTOR2(EXPLOSION_PLAY_ANIM, EXPLOSION_UV_V);
			pVtx[1].tex = D3DXVECTOR2(EXPLOSION_PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V);
			pVtx[3].tex = D3DXVECTOR2(EXPLOSION_UV_U, 0.0f);

			// ���_���W�̐ݒ�
			SetVertexExplosion(nCntExplosion);

			if (pExplosion->nPatternAnim == 7)
			{
				pExplosion->bUse = false;
				pExplosion->nPatternAnim = 0;
			}

			if (pExplosion->type == EXPLOSION_BOMBER)
			{ 
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
   					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x >= pExplosion->pos.x && pEnemy->pos.y >= pExplosion->pos.y)
						{// �e���v���C���[�̒��S����E�����A�㑤���瓖��������
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pEnemy->pos.x - pExplosion->pos.x) * (pEnemy->pos.x - pExplosion->pos.x)
									+ (pEnemy->pos.y - pExplosion->pos.y) * (pEnemy->pos.y - pExplosion->pos.y)))) >= 18)
							{// �~���m�̓����蔻��
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pEnemy->pos.x >= pExplosion->pos.x && pExplosion->pos.y > pEnemy->pos.y)
						{// �e���v���C���[�̒��S����E�����A�������瓖��������
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pEnemy->pos.x - pExplosion->pos.x) * (pEnemy->pos.x - pExplosion->pos.x)
									+ (pExplosion->pos.y - pEnemy->pos.y) * (pExplosion->pos.y - pEnemy->pos.y)))) >= 18)
							{// �~���m�̓����蔻��
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pExplosion->pos.x > pEnemy->pos.x && pEnemy->pos.y >= pExplosion->pos.y)
						{// �e���v���C���[�̒��S���獶�����A�㑤���瓖��������
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pExplosion->pos.x - pEnemy->pos.x) * (pExplosion->pos.x - pEnemy->pos.x)
									+ (pEnemy->pos.y - pExplosion->pos.y) * (pEnemy->pos.y - pExplosion->pos.y)))) >= 18)
							{// �~���m�̓����蔻��
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
						else if (pExplosion->pos.x > pEnemy->pos.x && pExplosion->pos.y > pEnemy->pos.y)
						{// �e���v���C���[�̒��S���獶�����A�������瓖��������
							if (((EXPLOSION_SIZE + ENEMY_SIZE_X)
								- (sqrtf((pExplosion->pos.x - pEnemy->pos.x) * (pExplosion->pos.x - pEnemy->pos.x)
									+ (pExplosion->pos.y - pEnemy->pos.y) * (pExplosion->pos.y - pEnemy->pos.y)))) >= 18)
							{// �~���m�̓����蔻��
								HitEnemy(nCntEnemy, pExplosion->nAttack);
							}
						}
					}
				}
			}
			

		}
		// ���̏��ɂ���
		pVtx += 4;

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// �����̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntExplosion * 4,					// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}
}

//=========================================================================================================================
// �����̐ݒ�
//=========================================================================================================================
void SetExplosion(D3DXVECTOR3 pos, EXPLOSIONTYPE type)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{
			// �ʒu�̐ݒ�
			pExplosion->pos = pos;

			// ���_���W�̐ݒ�
			SetVertexExplosion(nCntExplosion);

			pExplosion->type = type;

			pExplosion->bUse = true;
			break;
		}
	}
}

//=========================================================================================================================
//
//=========================================================================================================================
void SetVertexExplosion(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);

	// ���_�o�b�t�@�̊J��
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// �����̎擾
//=========================================================================================================================
EXPLOSION *GetExplosion(void)
{
	return &g_aExplosion[0];
}
