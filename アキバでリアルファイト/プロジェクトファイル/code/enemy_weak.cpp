//===========================================================
//
// �G�̏��� [enemy.cpp]
// Author : �匴�@�叫
//
//===========================================================
#include "enemy.h"
#include "enemy_weak.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "game.h"
#include "debugproc.h"
#include "score.h"
#include "player.h"
#include "character.h"
#include "collision.h"
#include "enemymanager.h"
#include "utility.h"
#include "gage.h"
#include "camera.h"
#include "particle.h"
#include "item.h"
#include "animation.h"
#include <time.h>
#include  <assert.h>

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int DAMEGE = 10;             // �_���[�W���
	const int ATTACKAGAINCOUNT = 60;   // �čU���ł���܂ł̎���
	const float SPEED = 2.0f;          // ���鑬��
	const float ATTACKLENGHT = 50.0f;  // �U���\�͈�
	const float SEARCHRANGE = 400.0f;  // �T���͈�
	const char* TEXT_NAME = "data\\TEXT\\motion_enemy.txt";  // �e�L�X�g�t�@�C���̖��O
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CEnemyWeak::CEnemyWeak()
{
	m_pLife3D = nullptr;
	m_nBiriBiriCount = 0;
	m_Chase = CHASE_ON;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CEnemyWeak::CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// �l���N���A
	SetPosition(pos);
	SetRotition(rot);
	SetLife(nlife);
	SetState(CEnemy::STATE_NONE);
	m_pLife3D = nullptr;
	m_nBiriBiriCount = 0;
	m_Chase = CHASE_ON;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CEnemyWeak::~CEnemyWeak()
{

}

//===========================================================
// ��������
//===========================================================
CEnemyWeak * CEnemyWeak::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemyWeak *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemyWeak(pos, rot, nlife);

		pEnemy->Init();
	}

	return pEnemy;
}

//===========================================================
// ����������
//===========================================================
HRESULT CEnemyWeak::Init(void)
{
	CEnemy::Init();
	SetType(WEAK);

	ReadText(TEXT_NAME);

	if (m_pLife3D == nullptr)
	{
		m_pLife3D = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, (float)((m_Info.nLife * 0.01f) * 20), CGage3D::TYPE_LIFE);
		m_pLife3D->SetPos(&m_Info.pos);
		m_pLife3D->SetUpHeight(80.0f);
		m_pLife3D->GetBill()->SetEdgeCenter((float)((m_Info.nLife * 0.01f) * 20), 5.0f);
	}
	
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CEnemyWeak::Uninit(void)
{
	CEnemy::Uninit();

	if (m_pLife3D != nullptr)
	{
		m_pLife3D->Uninit();
		m_pLife3D = nullptr;
	}

	CObject::Release();
}

//===========================================================
// �X�V����
//===========================================================
void CEnemyWeak::Update(void)
{
	CEnemy::Update();

	if (m_pLife3D != nullptr)
	{
		m_pLife3D->GetBill()->SetEdgeCenter((float)((m_Info.nLife * 0.01f) * 20), 5.0f);
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CEnemyWeak::Draw(void)
{
	CEnemy::Draw();
}

//===========================================================
// ���䏈��
//===========================================================
void CEnemyWeak::Attack(void)
{
	//�v���C���[�̏��擾
	CPlayer* pPlayer = CPlayer::GetPlayer();

	// �v���C���[���g�p����Ă��Ȃ������ꍇ�����𔲂���
	if (pPlayer == nullptr)
		return;

	// ���[�V�������g�p����Ă��Ȃ������ꍇ�����𔲂���
	if (GetMotion() == nullptr)
		return;

	// �����蔻�肪�g�p����Ă��Ȃ������ꍇ�����𔲂���
	if (CGame::GetCollision() == nullptr)
		return;
	
	if (m_Info.state != STATE_ATTACK)
	{
		m_nAtcCounter++;

		if (m_nAtcCounter >= ATTACKAGAINCOUNT)
		{
			m_nAtcCounter = 0;

			// �U����Ԃɂ���
			m_Info.state = STATE_ATTACK;
			GetMotion()->Set(TYPE_ATTACK);
		}
	}
	else
	{
		if (GetMotion()->GetAttackOccurs() <= GetMotion()->GetNowFrame() && GetMotion()->GetAttackEnd() >= GetMotion()->GetNowFrame())
		{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

			if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), ATTACKLENGHT, pPlayer->GetRadius()) == true)
			{
				pPlayer->Damage(GetMotion()->GetAttackDamege(), GetMotion()->GetKnockBack());
			}
		}
	}
}

//===========================================================
// ���䏈��
//===========================================================
void CEnemyWeak::Move(void)
{
	//�v���C���[�̏��擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	// �v���C���[���g�p����Ă��Ȃ������ꍇ�����𔲂���
	if (pPlayer == nullptr)
		return;

	if (CGame::GetCollision() == nullptr)
		return;
	
	if (m_Chase == CHASE_ON)
	{// �v���C���[��ǔ��ł���Ƃ�

		if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), SEARCHRANGE, pPlayer->GetRadius()) == true)
		{//�~�̒��Ƀv���C���[��������

			m_Info.posOld = m_Info.pos;

			D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

			float fDiffmove = 0.0f;

			if (m_Info.state != STATE_DAMEGE)
			{
				// �ǔ�
				fDiffmove = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, PlayerPos, m_Info.rot.y);

				// �p�x�␳
				fDiffmove = CManager::Getinstance()->GetUtility()->CorrectAngle(fDiffmove);

				m_Info.rot.y += fDiffmove * 0.05f;

				// �p�x�␳
				m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

				//�ړ��ʂ��X�V(����������)
				m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * SPEED;
				m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * SPEED;
			}

			// �v���C���[�Ƃ̋���
			float fLenght = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, PlayerPos);

			if (fLenght <= ATTACKLENGHT)
			{// �U���\�͈͓��ɓ�����

				if (m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_DAMEGE && m_Info.state != STATE_PAINFULDAMAGE)
				{
					m_Info.state = STATE_NEUTRAL;
					GetMotion()->Set(TYPE_NEUTRAL);
				}

				// �ړ�����߂čU������
				Attack();
				m_Info.move.x = 0.0f;
				m_Info.move.z = 0.0f;
			}
			else
			{// �͈͊O

				if (m_Info.state != STATE_DASH && m_Info.state != STATE_DAMEGE && m_Info.state != STATE_PAINFULDAMAGE)
				{// �v���C���[��ǂ������Ă��Ȃ����_���[�W��Ԃł͂Ȃ��Ƃ�

					m_Info.state = STATE_DASH;
					GetMotion()->Set(TYPE_DASH);
				}
			}
		}
		else
		{// �v���C���[���~�̒��ɂ��Ȃ�

			m_Info.move.x = 0.0f;
			m_Info.move.z = 0.0f;

			// �ҋ@��Ԃɂ���
			if (m_Info.state != STATE_NEUTRAL)
			{
				m_Info.state = STATE_NEUTRAL;
				GetMotion()->Set(TYPE_NEUTRAL);
			}
		}
	}

	if (m_Info.state == STATE_PAINFULDAMAGE)
	{
		if (GetMotion()->GetNowFrame() >= 0 && GetMotion()->GetNowFrame() <= 20)
		{
			m_Info.move.x = 0.0f;
			m_Info.move.z = 0.0f;
		}
	}
}

//===========================================================
// ���䏈��
//===========================================================
void CEnemyWeak::Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act)
{
	if (m_Info.state != STATE_DAMEGE && m_Info.state != STATE_HEATDAMEGE && m_Info.state != STATE_PAINFULDAMAGE && m_Info.state != STATE_DEATH)
	{
		m_Info.nLife -= damege;
		m_Info.move = D3DXVECTOR3(sinf(CPlayer::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CPlayer::GetPlayer()->GetRotition().y) * -blowaway);

		if (act == CPlayer::ATTACKTYPE::TYPE_HEATACTBIKE || act == CPlayer::ATTACKTYPE::TYPE_HEATACTREF || act == CPlayer::ATTACKTYPE::TYPE_HEATACTMICROWAVE)
		{
			if (m_Info.state != STATE_HEATDAMEGE)
			{
				m_Info.state = STATE_HEATDAMEGE;
				GetMotion()->Set(TYPE_HEATACTDAMEGE);
			}
		}
		else
		{
			if (m_Info.state != STATE_DAMEGE)
			{
				int a = rand() % 60;
				if (m_Info.nLife <= a && CPlayer::GetPlayer()->GetActType() == CPlayer::TYPE_ATTACK3)
				{
					m_Info.state = STATE_PAINFULDAMAGE;
					GetMotion()->Set(TYPE_HEATACTDAMEGE);
					m_Chase = CHASE_OFF;
				}
				else
				{
					m_Info.state = STATE_DAMEGE;
					GetMotion()->Set(TYPE_DAMEGE);
				}
			}
		}

		CAnimation::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 60.0f, m_Info.pos.z), 30.0f, CBillBoard::TYPE_HIT);
		CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
	}
}