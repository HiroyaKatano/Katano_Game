//=========================================================================================================================
//
// �v���C���[ [player.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "player.h"
#include "block.h"
#include "wire.h"
#include "Score.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				// �e�N�X�`��
PLAYER g_player;
int g_nAnimInterval;


//=========================================================================================================================
// �v���C���[�̏���������
//=========================================================================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player001.png", &g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,							// 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL)))
	{
		return E_FAIL;
	}

	// �v���C���[���̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fWidth = 0.0f;
	g_player.fHeight = 0.0f;
	g_player.bJump = true;
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fLengthPlayer = 0.0f;
	g_player.fAnglePlayer = 0.0f;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = PLAYER_FLASH;

	g_nAnimInterval = 0;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒���
	g_player.fLengthPlayer = sqrtf(PLAYER_SIZE_VERTEX_X * PLAYER_SIZE_VERTEX_X + PLAYER_SIZE_Y * PLAYER_SIZE_Y);

	// �Ίp���̊p�x
	g_player.fAnglePlayer = atan2f(PLAYER_SIZE_VERTEX_X, PLAYER_SIZE_Y);

	// �v���C���[�̉�]�p
	g_player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���S���W�̐ݒ�
	g_player.pos = D3DXVECTOR3(20.0f, SCREEN_HEIGHT_U - 25.0f, 0.0f);

	// �v���C���[�̕��ƍ����̐ݒ�
	g_player.fWidth = PLAYER_SIZE_VERTEX_X;
	g_player.fHeight = PLAYER_SIZE_Y;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 1.0f / TEXTURE_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffplayer->Unlock();

	return S_OK;
}

//=========================================================================================================================
// �v���C���[�̏I������
//=========================================================================================================================
void UninitPlayer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//=========================================================================================================================
// �v���C���[�̍X�V����
//=========================================================================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;
	BLOCK *pBlock;
	WIRE *pWire;

	pPlayer = GetPlayer();
	pBlock = GetBlock();
	pWire = GetWire();

	// �O��̈ʒu��ۑ�
	pPlayer->posOld = pPlayer->pos;

	// �v���C���[�ƃ��C���[�̐ڒn�_�Ƃ̊p�x
	pPlayer->rotPlayer.z = atan2f(pPlayer->pos.x - pWire->pos.x,
							(pPlayer->pos.y - PLAYER_SIZE_Y / 2) - pWire->pos.y);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);
	
	if (pPlayer->state == PLAYERSTATE_NORMAL)
	{
		pPlayer->nCounterState = PLAYER_FLASH;

		// �v���C���[�̈ړ��E�W�����v����
		if (GetKeyboardTrigger(DIK_SPACE) == true && pPlayer->bJump == false)
		{
			pPlayer->move.y = -PLAYER_JUMP;
			pPlayer->bJump = true;
		}


		if (GetKeyboardPress(DIK_W) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD / 1.4f, -WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD / 1.4f, -WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, -WIRE_EXTEND_SPD, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD / 1.4f, WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD / 1.4f, WIRE_EXTEND_SPD / 1.4f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
			else
			{
				if (GetKeyboardTrigger(DIK_U) == true)
				{
					SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, WIRE_EXTEND_SPD, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
				}
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(-WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}
		else
		{
			if (GetKeyboardTrigger(DIK_U) == true)
			{
				SetWire(pPlayer->pos + D3DXVECTOR3(0.0f, -PLAYER_SIZE_Y / 2, 0.0f), D3DXVECTOR3(WIRE_EXTEND_SPD, 0.0f, 0.0f), WIRE_SIZE_VERTEX_X, WIRE_SIZE_Y);
			}
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
			{
				if (pWire->bContact == true)
				{
				}
				else if (pWire->bContact == false)
				{
					pPlayer->move.x -= PLAYER_SPD;
					if (GetKeyboardPress(DIK_D) == true)
					{
						pPlayer->move.x += PLAYER_SPD;
					}

				}
			}
			pWire = GetWire();
			if (pPlayer->bJump == false)
			{
				g_nAnimInterval++;

				if (g_nAnimInterval % 10 == 0)
				{
					pPlayer->nCounterAnim++;
				}

			}



			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f + UV_V);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f + UV_V);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
			{
				if (pWire->bContact == true)
				{
				}
				else if (pWire->bContact == false)
				{
					pPlayer->move.x += PLAYER_SPD;
					if (GetKeyboardPress(DIK_A) == true)
					{
						pPlayer->move.x -= PLAYER_SPD;
					}

				}
			}
			pWire = GetWire();
			if (pPlayer->bJump == false)
			{
				g_nAnimInterval++;

				if (g_nAnimInterval % 10 == 0)
				{
					pPlayer->nCounterAnim++;
				}

			}



			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f);
		}

		if (GetKeyboardRelease(DIK_A) == true && pPlayer->nCounterAnim % 2 == 1)
		{
			pPlayer->nCounterAnim++;

			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f + UV_V);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y + UV_V);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f + UV_V);
		}
		else if (GetKeyboardRelease(DIK_D) == true && pPlayer->nCounterAnim % 2 == 1)
		{
			pPlayer->nCounterAnim++;

			pPlayer->nPatternAnim = pPlayer->nCounterAnim % MAX_PATTERN;

			pVtx[0].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[1].tex = D3DXVECTOR2(0.0f + PLAY_ANIM, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 1.0f / TEXTURE_Y);
			pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_X + PLAY_ANIM, 0.0f);
		}

		for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
		{
			if (pWire->bContact == true)
			{
				if (GetKeyboardTrigger(DIK_W) == true)
				{
					pPlayer->move.y -= 12.0f;
				}

				if (GetKeyboardTrigger(DIK_S) == true)
				{
					pPlayer->move.y += 5.0f;
				}

				if (GetKeyboardTrigger(DIK_A) == true)
				{
					pPlayer->move.x -= 5.0f;
				}

				if (GetKeyboardTrigger(DIK_D) == true)
				{
					pPlayer->move.x += 5.0f;
				}

			}
		}
		pWire = GetWire();



		// �ړ��ʂ̌���
		for (int nCntWire = 0; nCntWire < MAX_WIRE; nCntWire++, pWire++)
		{
			if (pWire->bContact == true)
			{
				pPlayer->move.x += (pWire->pos.x - pPlayer->pos.x) * 0.005f;
				pPlayer->move.y += (0.0f + (pWire->pos.y - pPlayer->pos.y)) * 0.005f;

				pPlayer->move.y += GRAVITY;

				pPlayer->move.x += (0.0f - pPlayer->move.x) * 0.008f;

			}
			else if (pWire->bContact == false)
			{
				pPlayer->move.y += GRAVITY;
				if (pPlayer->bJump == false)
				{
					pPlayer->move.x += (0.0f - pPlayer->move.x) * SPD_DECAY;
				}
				else if (pPlayer->bJump == true)
				{
					pPlayer->move.x += (0.0f - pPlayer->move.x) * 0.2f;
				}

			}
		}
		pWire = GetWire();




		// �ʒu�̍X�V
		pPlayer->pos.x += pPlayer->move.x;
		pPlayer->pos.y += pPlayer->move.y;


		// �v���C���[����ʊO�ɏo�����̏C������
		if (pPlayer->pos.x < SCREEN_WIDTH_L + pPlayer->fWidth)
		{
			pPlayer->pos.x = SCREEN_WIDTH_L + pPlayer->fWidth;
			pPlayer->move.x = 0.0f;
		}

		if (pPlayer->pos.x > SCREEN_WIDTH_R - pPlayer->fWidth)
		{
			pPlayer->pos.x = SCREEN_WIDTH_R - pPlayer->fWidth;
			pPlayer->move.x = 0.0f;
		}

		if (pPlayer->pos.y < SCREEN_HEIGHT_T - pPlayer->fHeight)
		{
			pPlayer->pos.y = SCREEN_HEIGHT_T - pPlayer->fHeight;
		}

		if (pPlayer->pos.y > SCREEN_HEIGHT_U + 310)
		{
			pPlayer->state = PLAYERSTATE_WAIT;
			pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}


		if (CollisionBlock(&pPlayer->pos, &pPlayer->posOld, &pPlayer->move, pPlayer->fWidth, pPlayer->fHeight) == true)
		{
			pPlayer->bJump = false;
		}
		else if (CollisionBlock(&pPlayer->pos, &pPlayer->posOld, &pPlayer->move, pPlayer->fWidth, pPlayer->fHeight) == false)
		{
			pPlayer->bJump = true;
		}


	}
	else if (pPlayer->state == PLAYERSTATE_WAIT)
	{
		pPlayer->pos = D3DXVECTOR3(20.0f, SCREEN_HEIGHT_U - 25.0f, 0.0f);

		pPlayer->nCounterState -= TIMER_COUNT;

		if (pPlayer->nCounterState <= 0)
		{
			pPlayer->state = PLAYERSTATE_NORMAL;

			pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
			pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
		}
		else if (pPlayer->nCounterState <= PLAYER_FLASH && pPlayer->nCounterState > 0)
		{
			if (pPlayer->nCounterState % 5 == 0)
			{
				pVtx[0].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[1].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[2].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
				pVtx[3].col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A * (pPlayer->nCounterState % FLASH_TIMING));
			}
		}
	}

	pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - PLAYER_SIZE_VERTEX_X, pPlayer->pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x - PLAYER_SIZE_VERTEX_X, pPlayer->pos.y - PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + PLAYER_SIZE_VERTEX_X, pPlayer->pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + PLAYER_SIZE_VERTEX_X, pPlayer->pos.y - PLAYER_SIZE_Y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// �v���C���[�̕`�揈��
//=========================================================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));
	
	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	// �v���C���[�̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�
}

//=========================================================================================================================
// �v���C���[�̎擾
//=========================================================================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}
