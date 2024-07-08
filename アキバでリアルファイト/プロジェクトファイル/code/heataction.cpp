//===========================================================
//
// �q�[�g�A�N�V����[heataction.cpp]
// Author �匴�叫
//
//===========================================================
#include "heataction.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "utility.h"
#include "game.h"
#include "itemmanager.h"
#include "collision.h"
#include "motion.h"
#include "MyEffekseer.h"
#include "enemymanager.h"
#include "camera.h"
#include "sound.h"
#include "particle.h"
#include "item.h"
#include "tutorial.h"

// �������O��Ԃ��`
namespace
{
	const int MICROWAVE = 3600;  // �q�[�g�A�N�V����:�d�q�����W���ēx���p�\�ɂȂ�܂ł̎���
	const int MICRO = 60;


	const D3DXVECTOR3 CAMERA_ROT[CPlayer::HEAT_MAX] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI * -0.38f),

	};  // �q�[�g�A�N�V�������̃J�����ʒu

	const D3DXVECTOR3 TUTORIALCAMERAROT[CPlayer::HEAT_MAX] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),

	};  // �q�[�g�A�N�V�������̃J�����ʒu

	const float CAMERA_DISTNCE[CPlayer::HEAT_MAX] =
	{
		300.0f,
		300.0f,
		200.0f,

	};  // �q�[�g�A�N�V�������̃J�����̋���

	const D3DXVECTOR3 ENEMY_GRAP_POS[CEnemy::MAX] =
	{
		D3DXVECTOR3(-10.0f, -10.0f, 60.0f),
		D3DXVECTOR3(-15.0f, -10.0f, 80.0f),
	};
}

//===========================================================
// ����������
//===========================================================
void CHeatAction::Init(void)
{
	m_bInMicroWave = false;
}

//===========================================================
// �I������
//===========================================================
void CHeatAction::Uninit(void)
{

}

//===========================================================
// �X�V����
//===========================================================
void CHeatAction::Updata(void)
{
	switch (m_pPlayer->GetHeatAct())
	{
	case CPlayer::HEAT_NONE:  // �Ȃ���Ȃ�
		break;
	case CPlayer::HEAT_SMASH: // ���]�Ԃ�������

		BikeCrash(m_pPlayer, m_pEnemy);
		break;
	case CPlayer::HEAT_FIRE:  // �d�q�����W

		MicroWave(m_pPlayer, m_pEnemy, nullptr);
		break;
	case CPlayer::HEAT_MAX:
		break;
	default:
		break;
	}
}

//===========================================================
// ���]�Ԃ��g�����q�[�g�A�N�V���������鏈��
//===========================================================
void CHeatAction::BikeCrash(CPlayer* pPlayer, CEnemy* pEnemy)
{
	if (pEnemy != nullptr)
	{
		// �v���C���[�̌����擾
		D3DXVECTOR3 PlayerRot = pPlayer->GetRotition();

		// �G�̕����Ɍ�������
		PlayerRot.y += CManager::Getinstance()->GetUtility()->MoveToPosition(pPlayer->GetPosition(), pEnemy->GetPosition(), pPlayer->GetRotition().y);
		PlayerRot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(PlayerRot.y);

		// �v���C���[�̌����ݒ�
		pPlayer->SetRotition(PlayerRot);

		// �����蔻��
		if (pPlayer->GetMotion()->GetAttackOccurs() <= pPlayer->GetMotion()->GetNowFrame()
			&& pPlayer->GetMotion()->GetAttackEnd() >= pPlayer->GetMotion()->GetNowFrame())
		{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���ȉ�

			if (CGame::GetCollision()->ItemEnemy(pPlayer->GetGrapItem(), pEnemy, 50.0f, 50.0f, 100.0f) == true)
			{// �͈͓�

				if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
				{
					// �����Ă����A�C�e��������
					if (CTutorial::GetItemManager())
						CTutorial::GetItemManager()->Release(pPlayer->GetGrapItem()->GetID());

					// �^�[�Q�b�g�ȊO�̓G�̕`����ĊJ
					if (CTutorial::GetEnemyManager())
						CTutorial::GetEnemyManager()->SetTrue(pEnemy->GetIdxID());
				}

				if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
				{
					// �����Ă����A�C�e��������
					if (CGame::GetItemManager())
						CGame::GetItemManager()->Release(pPlayer->GetGrapItem()->GetID());

					// �^�[�Q�b�g�ȊO�̓G�̕`����ĊJ
					if (CGame::GetEnemyManager() )
						CGame::GetEnemyManager()->SetTrue(pEnemy->GetIdxID());
				}
				

				if (pEnemy->GetMotion())
					pEnemy->GetMotion()->Set(CEnemy::TYPE_HEATACTDAMEGE);
				
				// �����Ă����A�C�e��������
				pPlayer->SetGrapItem(nullptr);

				// �G�̈ʒu�擾
				D3DXVECTOR3 Enempos = pEnemy->GetPosition();

				pPlayer->SetbHeatActFlag(false);

				// �G�t�F�N�g�̍Đ�
				CManager::Getinstance()->GetMyEffekseer()->Set(CMyEffekseer::m_apEfkName[CMyEffekseer::TYPE_IMPACT], ::Effekseer::Vector3D(Enempos.x, Enempos.y, Enempos.z),
					::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(25.0f, 25.0f, 25.0f));
			}
		}
	}
}

//===========================================================
// �d�q�����W���g�����q�[�g�A�N�V���������鏈��
//===========================================================
void CHeatAction::MicroWave(CPlayer* pPlayer, CEnemy* pEnemy, CItem* pItem)
{
	if (m_bInMicroWave == false && pPlayer->GetMotion()->IsFinish() == true)
	{
		// �v���C���[�̌����擾
		D3DXVECTOR3 PlayerRot = pPlayer->GetRotition();

		// �d�q�����W�̕����Ɍ�������
		PlayerRot.y += CManager::Getinstance()->GetUtility()->MoveToPosition(pPlayer->GetPosition(), pEnemy->GetPosition(), pPlayer->GetRotition().y);
		PlayerRot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(PlayerRot.y);
		
		if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
		{
			pPlayer->SetPosition(D3DXVECTOR3(-160.0f, 0.0f, 210.0f));
		}

		if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
		{
			pPlayer->SetPosition(D3DXVECTOR3(-720.0f, 0.0f, 580.0f));
		}

		// �v���C���[�Ƃ̊֌W��؂�
		{
			pEnemy->SetCurrent(nullptr);
			pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// �v���C���[�̃��[�V�������g�p����Ă��Ȃ������ꍇ�����𔲂���
			if (pPlayer->GetMotion() == nullptr)
				return;

			pPlayer->GetMotion()->Set(CPlayer::TYPE_NEUTRAL);
			pPlayer->SetState(CPlayer::STATE_NEUTRAL);
		}

		// �d�q�����W�Ƃ̊֌W�����
		{
			// �A�C�e���F�d�q�����W���Ȃ������ꍇ����������
			if (pPlayer->GetItem() == nullptr)
				return;
			
			pEnemy->SetCurrent(pPlayer->GetItem()->GetMtxWorld());
			pEnemy->SetPosition(D3DXVECTOR3(0.0f, -70.0f, -30.0f));
			pEnemy->SetRotition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

			// ��Ԃƃ��[�V������ݒ�
			if (pEnemy->GetState() != CEnemy::STATE_HEATACTELECTROWAIT)
			{
				pEnemy->SetState(CEnemy::STATE_HEATACTELECTROWAIT);

				// �G�̃��[�V�������g�p����Ă��Ȃ������ꍇ�����𔲂���
				if (pEnemy->GetMotion() == nullptr)
					return;

				// �q�[�g�A�N�V����:�d�q�����W�ɓ��������đ҂��Ă�����
				pEnemy->GetMotion()->Set(CEnemy::TYPE_HEATACTELECTROWAIT);
				CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_GRASS);

				// �K���X�Ђ̃p�[�e�B�N���𐶐�
				CParticle::Create(pPlayer->GetItem()->GetPosition(), CParticle::TYPE_GLASS);

				// �d�q�����W�̒��ɓ�����
				m_bInMicroWave = true;
			}
		}
	}
	
	if (m_bInMicroWave == true)
	{
		m_nHeatActTime++;
	}

	if (pEnemy->GetState() == CEnemy::STATE_HEATACTELECTROWAIT)
	{
		if (m_nHeatActTime > 60)
		{
			if (pEnemy->GetState() != CEnemy::STATE_HEATACTELECTRO)
			{
				pEnemy->SetState(CEnemy::STATE_HEATACTELECTRO);
				pEnemy->GetMotion()->Set(CEnemy::TYPE_HEATACTELECTRO);
				CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);

				if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
				{
					CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, -1.3f, 0.0f));
				}

				if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
				{
					CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(CAMERA_ROT[0].x, CAMERA_ROT[0].y, CAMERA_ROT[0].z));
				}
				
			}

			m_nHeatActTime = 0;
		}
	}

	if (m_nHeatActTime > 120 && pEnemy->GetState() == CEnemy::STATE_HEATACTELECTRO)
	{
		if (pEnemy->GetState() != CEnemy::STATE_HEATACTFAINTING)
		{
			pEnemy->SetState(CEnemy::STATE_HEATACTFAINTING);
			pEnemy->GetMotion()->Set(CEnemy::TYPE_HEATACTFAINTING);
			pEnemy->Damege(100, 0.0f, CPlayer::TYPE_HEATACTMICROWAVE);
			CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
			pPlayer->SetState(CPlayer::STATE_NEUTRAL);
			pPlayer->SetUseMicroCount(3600);
			CGame::GetEnemyManager()->SetTrue(CPlayer::GetPlayer()->GetGrapEnemy()->GetIdxID());
			CPlayer::GetPlayer()->SetGrapEnemy(nullptr);
			pEnemy->SetPosition(D3DXVECTOR3(CPlayer::GetPlayer()->GetItem()->GetPosition().x, 0.0f, CPlayer::GetPlayer()->GetItem()->GetPosition().z));
			pEnemy->SetCurrent(nullptr);
			pPlayer->SetbHeatActFlag(false);
		}

		m_nHeatActTime = 0;
	}

	if (pEnemy->GetState() == CEnemy::STATE_HEATACTELECTRO)
	{
		if (m_nHeatActTime % 20 == 0)
		{
			CParticle::Create(CPlayer::GetPlayer()->GetItem()->GetPosition(), CParticle::TYPE_SMOOK);
		}
	}
}

//===========================================================
// �s���A�N�V������ݒ�
//===========================================================
void CHeatAction::SetAction(CPlayer::HEAT heatact, CPlayer* pPlayer, CEnemy* pEnemy)
{
	m_pPlayer = pPlayer;
	m_pEnemy = pEnemy;

	pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	pEnemy->SetChase(CEnemy::CHASE_OFF);
	//pEnemy->SetDraw()
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �q�[�g�A�N�V�����̃J�������[�h�ɂ���
	CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_HEAT);
	
	CManager::Getinstance()->GetCamera()->SetDistnce(CAMERA_DISTNCE[heatact]);

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(TUTORIALCAMERAROT[heatact].x, TUTORIALCAMERAROT[heatact].y, TUTORIALCAMERAROT[heatact].z));
	}

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(CAMERA_ROT[heatact].x, CAMERA_ROT[heatact].y, CAMERA_ROT[heatact].z));
	}

	switch (heatact)
	{
	case CPlayer::HEAT_NONE:  // �Ȃ���Ȃ�
		break;
	case CPlayer::HEAT_SMASH: // ���]�Ԃ�������

		if(pPlayer->GetMotion())
		pPlayer->GetMotion()->Set(CPlayer::TYPE_THROW);

		//BikeCrash(pPlayer, pEnemy);
		break;
	case CPlayer::HEAT_FIRE:  // �d�q�����W

		//MicroWave(pPlayer, pEnemy, nullptr);
		break;
	case CPlayer::HEAT_MAX:
		break;
	default:
		break;
	}
}