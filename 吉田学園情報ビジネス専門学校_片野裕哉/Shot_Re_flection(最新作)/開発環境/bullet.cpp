//=============================================================================
//
// �e [bullet.cpp]
// Author : Hiroya Katano
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "bullet.h" 
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"
#include "player.h"
#include "bulletPower.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;			// �e�N�X�`��
int CBullet::m_nAbsorbedBulletCnt;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRockOn = false;
	m_bAbsorbOn = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBullet::~CBullet()
{


}

//*****************************************************************************
// �|���S���̏���������
//*****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, CBullet::BULLETTYPE bulletType, USEBULLET useBullet)
{
	// �����̐ݒ�
	m_life = 150;

	// �傫����ݒ�
	m_scale = scale;

	// �ړ��l��ݒ�
	m_move = move;

	// �e�̎g�p�҂�ݒ�
	m_bulletType = bulletType;

	// �e�̎�ނ�ݒ�
	m_useBullet = useBullet;

	// CScene2D���Ăяo��
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(OBJTYPE_BULLET);

	return S_OK;
}

//*****************************************************************************
// �|���S���̏I������
//*****************************************************************************
void CBullet::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
// �|���S���̍X�V����
//*****************************************************************************
void CBullet::Update()
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	if (m_useBullet == USEBULLET_TRACKING)
	{
		BulletTracking();
	}

	if (m_bulletType == BULLETTYPE_PLAYER)
	{
		// �G�t�F�N�g�𐶐�
		CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(0.4f, 0.4f, 1.f, 1.f), 20);
	}
	
	if (m_bulletType == BULLETTYPE_ENEMY)
	{
		if (m_move2.y < 5.0f && m_EneBulCnt < 60 && m_useBullet == USEBULLET_TRACKING)
		{
			m_move.y += 0.3f;

			m_move2 = m_move;
		}
		if (m_useBullet == USEBULLET_TRACKING)
		{
			// �G�t�F�N�g�𐶐�
			CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(1.f, 0.4f, 0.4f, 1.f), 20);
		}
		else 
		{
			// �G�t�F�N�g�𐶐�
			CEffect::Create(pos, m_scale*2.f, D3DXCOLOR(0.2f, 0.5f, 0.2f, 1.f), 25);
		}
	}

	//�ړ��ʂ�ǉ�
	pos += m_move;

	//�ʒu�̍X�V
	SetPosition(pos, m_scale);

	for (int nCntPrio = 0; nCntPrio < MAX_PRIORITY_NUM; nCntPrio++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			CScene *pScene;
			pScene = GetScene(nCntPrio, nCntScene);
			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				CScore *pScore;
				pScore = CGame::GetScore();

				int nPlayerState = CPlayer::GetPlayerState();
				CPlayer *pPlayer;
				pPlayer = CGame::GetPlayer();

				

				if (objType == OBJTYPE_ENEMY && m_bulletType == BULLETTYPE_PLAYER)
				{
					D3DXVECTOR3 posEnemy = pScene->GetPosition();
					D3DXVECTOR3 scaleEnemy = pScene->GetScale();

					m_EneLife = CGame::GetEnemy()->GetLife();

					if (pos.y - (m_scale.y / 2.0f) < posEnemy.y + (scaleEnemy.y / 2) &&
						pos.y + (m_scale.y / 2.0f) > posEnemy.y - (scaleEnemy.y / 2) &&
						pos.x - (m_scale.x / 2.0f) < posEnemy.x + (scaleEnemy.x / 2) &&
						pos.x + (m_scale.x / 2.0f) > posEnemy.x - (scaleEnemy.x / 2))
					{
						if (m_EneLife > 0)
						{
							CGame::GetEnemy()->AddLife(-1);
						}
						else
						{
							//�G������
							pScene->Uninit();

							//�����̐���
							CExplosion::Create(posEnemy, scaleEnemy);

							// �X�R�A���Z����
							pScore->AddScore(100);
						}

						//�e������
						Uninit();

						return;
					}
				}

				//if (objType == OBJTYPE_BOSS && m_bulletType == BULLETTYPE_PLAYER && BossState == CBoss::BOSSSTATE_NONE)
				//{
				//	D3DXVECTOR3 posBoss = pScene->GetPosition();
				//	D3DXVECTOR3 scaleBoss = pScene->GetScale();
				//	int BossCnt = m_pBoss->GetBossCnt();
				//	

				//	if (pos.y - (m_scale.y / 2.0f) < posBoss.y + (scaleBoss.y / 2) &&
				//		pos.y + (m_scale.y / 2.0f) > posBoss.y - (scaleBoss.y / 2) &&
				//		pos.x - (m_scale.x / 2.0f) < posBoss.x + (scaleBoss.x / 2) &&
				//		pos.x + (m_scale.x / 2.0f) > posBoss.x - (scaleBoss.x / 2))
				//	{
				//		//�G������
				//		pScene->Uninit();

				//		//�����̐���
				//		CExplosion::Create(posBoss, scaleBoss);

				//		// �X�R�A���Z����
				//		pScore->AddScore(100);

				//		//�e������
				//		Uninit();

				//		return;
				//	}
				//}

				if (objType == OBJTYPE_PLAYER && m_bulletType == BULLETTYPE_ENEMY && nPlayerState == CPlayer::PLAYERSTATE_NONE)
				{
					D3DXVECTOR3 posPlayer = pScene->GetPosition();
					D3DXVECTOR3 scalePlayer = pScene->GetScale();
					CLife *pLife = CGame::GetLife();

					float VectorX = posPlayer.x - pos.x;
					float VectorY = posPlayer.y - pos.y;
					float Distance = sqrtf((VectorX * VectorX) + (VectorY * VectorY));

					if (Distance < ABSORBDISTANCE)
					{	
						m_bAbsorbOn = true;
					}

					if (m_bAbsorbOn == true)
					{
						float angle = atan2f(VectorX, VectorY);

						if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
						if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

						//�z�[�~���O�v�Z
						float moveX = sinf(angle)*30.0f;
						float moveY = cosf(angle)*30.0f;

						//�ړ��l�����Z
						m_move.x = moveX;
						m_move.y = moveY;
					}

					if (pos.y - m_scale.y / 2.0f < posPlayer.y + scalePlayer.y / 5 &&
						pos.y + m_scale.y / 2.0f > posPlayer.y - scalePlayer.y / 5 &&
						pos.x - m_scale.x / 2.0f < posPlayer.x + scalePlayer.x / 5 &&
						pos.x + m_scale.x / 2.0f > posPlayer.x - scalePlayer.x / 5)
					{
						//�����̐���
						//CExplosion::Create(posPlayer, scalePlayer);

						////�v���C���[�̎c�@����
						//pLife->AddLife(-1);

						//pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);

						// �X�R�A���Z����
						//pScore->AddScore(-100);

						if (m_nAbsorbedBulletCnt <= 50)
						{
							m_nAbsorbedBulletCnt += 2;
							CGame::GetBulletPower()->AddBulletPower(2);

							if (m_nAbsorbedBulletCnt >= 40 && m_nAbsorbedBulletCnt < 50)
							{
								pScore->AddScore(500);
							}
							else if (m_nAbsorbedBulletCnt == 50)
							{
								pScore->AddScore(5000);
							}
						}
						else if (m_nAbsorbedBulletCnt > 50)
						{
							//�v���C���[�̎c�@����
							pLife->AddLife(-1);
							pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
							m_nAbsorbedBulletCnt = 0;
							CGame::GetBulletPower()->SetBulletPower(0);

							// �X�R�A���Z����
							pScore->AddScore(-5000);
							CExplosion::Create(posPlayer, scalePlayer*3);
						}

						//�e������
						Uninit();

						return;
					}

				}
			}
		}
	}

	//��ʊO����
	if (pos.y + m_scale.y / 2.0f < 0.0f ||
		pos.y - m_scale.y / 2.0f > SCREEN_HEIGHT ||
		pos.x + m_scale.x / 2.0f < 0.0f ||
		pos.x - m_scale.x / 2.0f > SCREEN_WIDTH)
	{
		//�e������
		Uninit();
	}
	else if (m_life == 0)
	{
		//�����̐���
		CExplosion::Create(pos, m_scale);

		//�e������
		Uninit();
	}
	else if (m_life > 0)
	{
		//����
		m_life--;

		m_EneBulCnt++;
	}
}

//*****************************************************************************
// �|���S���̕`�揈��
//*****************************************************************************
void CBullet::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
// ��������
//*****************************************************************************
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLETTYPE bulletType, USEBULLET useBullet)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	if (pBullet != NULL)
	{
		pBullet->Init(pos, scale, move, bulletType, useBullet);
	}
	pBullet->BindTexture(m_pTexture);

	return pBullet;
}

//*****************************************************************************
// �e�N�X�`���Ǎ�����
//*****************************************************************************
void CBullet::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &m_pTexture);
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CBullet::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// �e�̒ǔ�����
//*****************************************************************************
void CBullet::BulletTracking(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	for (int nCntPrio = 0; nCntPrio < MAX_PRIORITY_NUM; nCntPrio++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLY2D; nCntScene++)
		{
			CScene *pScene;
			pScene = GetScene(nCntPrio, nCntScene);

			if (pScene != NULL)
			{
				//��ޔ���Ăяo��
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType != NULL)
				{
					//�v���C���[�̒e�������ꍇ
					if (m_bulletType == BULLETTYPE_PLAYER)
					{
						//��ނ��G�������ꍇ
						if (objType == OBJTYPE_ENEMY)
						{
							//�ʒu�̎擾
							D3DXVECTOR3 posEnemy = pScene->GetPosition();

							//�p�x�v�Z
							float VectorX = posEnemy.x - pos.x;
							float VectorY = posEnemy.y - pos.y;
							float angle = atan2f(VectorX, VectorY);

							if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
							if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

							//�p�x�����l�𒴂���܂Œǐ�
							if ((angle < -D3DX_PI / 1.4f&&angle > -D3DX_PI) ||
								(angle > D3DX_PI / 1.4f&&angle < D3DX_PI))
							{
								//�z�[�~���O�v�Z
								float moveX = sinf(angle)*20.0f;
								float moveY = cosf(angle)*30.0f;

								//�ړ��l�����Z
								m_move.x = moveX;
								m_move.y = moveY;
							}
						}
					}
					else if (m_bulletType == BULLETTYPE_ENEMY)
					{
						//��ނ��G�������ꍇ
						if (objType == OBJTYPE_PLAYER &&/* m_EneBulCnt >= 30 && */m_EneBulCnt < 120 && m_move2.y >= 5.0f && m_bRockOn == false)
						{
							//�ʒu�̎擾
							D3DXVECTOR3 posPlayer = pScene->GetPosition();

							//�p�x�v�Z
							float VectorX = posPlayer.x - pos.x;
							float VectorY = posPlayer.y - pos.y;
							float angle = atan2f(VectorX, VectorY);

							if (angle > D3DX_PI) { angle -= D3DX_PI*2.0f; }
							if (angle < -D3DX_PI) { angle += D3DX_PI*2.0f; }

							//�z�[�~���O�v�Z
							float moveX = sinf(angle)*20.0f;
							float moveY = cosf(angle)*20.0f;

							//�ړ��l�����Z
							m_move.x = moveX;
							m_move.y = moveY;

							m_bRockOn = true;
						}
					}
				}
			}
		}
	}
}

//*****************************************************************************
// �e�̊g�U����
//*****************************************************************************
void CBullet::BulletSpread(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	
}
