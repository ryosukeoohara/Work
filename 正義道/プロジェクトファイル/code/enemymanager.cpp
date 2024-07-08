//===========================================================
//
//�|���S�����o�����[enemy.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "object.h"
#include "manager.h"
#include "camera.h"
#include "enemy.h"
#include "enemyweak.h"
#include "enemymedBoss.h"
#include "enemyBoss.h"
#include "enemymanager.h"
#include "effectline.h"
#include "target.h"
#include "fade.h"

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
int CEnemyManager::m_DieCounter = 0;
int CEnemyManager::m_nNumEneWeakCounter = 0;
int CEnemyManager::m_nNumEneMedBossCounter = 0;
int CEnemyManager::m_nNumEneBossCounter = 0;
int CEnemyManager::m_nNumAll = 0;
int CEnemyManager::m_nIdx = 0;

//================================================================
//�R���X�g���N�^
//================================================================
CEnemyManager::CEnemyManager()
{
	m_DieCounter = 0;
	m_nNumEneWeakCounter = 0;
	m_nNumEneMedBossCounter = 0;
	m_nNumEneBossCounter = 0;
	m_nNumAll = 0;
	m_bAppearExecutive = false;
	m_bAppearBoss = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemyManager::~CEnemyManager()
{

}

//================================================================
//�G�̏���������
//================================================================
HRESULT CEnemyManager::Init(void)
{
	CEnemyNear::Create({ 2300.0f, 0.0f, 2800.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyNear::Create({ 2300.0f, 0.0f, 2600.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyFar::Create({ 2200.0f, 0.0f, 2700.0f }, { 0.0f, -1.56f, 0.0f });

	CEnemyFar::Create({ -1000.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyNear::Create({ -800.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyNear::Create({ -1000.0f, 0.0f, 400.0f }, { 0.0f, 0.0f, 0.0f });

	CEnemyNear::Create({ -402.0f, 0.0f, -1516.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyNear::Create({ -257.0f, 0.0f, -1750.0f }, { 0.0f, 1.2f, 0.0f });
	CEnemyNear::Create({ -440.0f, 0.0f, -1800.0f }, { 0.0f, -2.25f, 0.0f });

	/*CEnemyNear::Create({ -2300.0f, 0.0f, 2400.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyNear::Create({ -2300.0f, 0.0f, 2600.0f }, { 0.0f, 0.0f, 0.0f });
	CEnemyFar::Create({ -2200.0f, 0.0f, 2700.0f }, { 0.0f, -1.56f, 0.0f });*/

	//CEnemyMedBoss::Create({ -1000.0f, 0.0f, 2000.0f }, CEnemyMedBoss::TYPE_001);	   //�G�𐶐�
	//CEnemyMedBoss::Create({ -1000.0f, 0.0f, -1000.0f }, CEnemyMedBoss::TYPE_002);   //�G�𐶐�
	//CEnemyMedBoss::Create({ 1000.0f, 0.0f, -1000.0f }, CEnemyMedBoss::TYPE_003);	   //�G�𐶐�
	
	return S_OK;
}

//================================================================
//�G�̏I������
//================================================================
void CEnemyManager::Uninit(void)
{
	
}

//================================================================
//�G�̍X�V����
//================================================================
void CEnemyManager::Update(void)
{
	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

	if (m_DieCounter >= nNumEnemyWeak && m_bAppearExecutive == false)
	{
		//CCamera *pCamera = CManager::GetCamera();

		//pCamera->SetType(CCamera::TYPE_BOSS);

		CTarget::SetType(CTarget::TYPE_SECOND);

		CEnemyMedBoss::Create({ -1000.0f, 0.0f, 2000.0f }, CEnemyMedBoss::TYPE_001);	   //�G�𐶐�
		CEnemyMedBoss::Create({ -1000.0f, 0.0f, -1000.0f }, CEnemyMedBoss::TYPE_002);   //�G�𐶐�
		CEnemyMedBoss::Create({ 1000.0f, 0.0f, -1000.0f }, CEnemyMedBoss::TYPE_003);	   //�G�𐶐�

		m_DieCounter = 0;

		m_bAppearExecutive = true;
	}

	//�����̑������擾
	int nNumMedBoss = CEnemyManager::GetNumEneMedBoss();

	if (m_DieCounter >= nNumMedBoss && m_bAppearExecutive == true && m_bAppearBoss == false)
	{
		CCamera *pCamera = CManager::GetCamera();

		pCamera->SetType(CCamera::TYPE_BOSS);

		CTarget::SetType(CTarget::TYPE_FINAL);

		CEnemyBoss::Create({ 1000.0f, 0.0f, -1000.0f });	   //�G�𐶐�

		//�W����
		CEffectLine::Create();

		m_DieCounter = 0;

		m_bAppearBoss = true;
	}

	//�����̑������擾
	int nNumBoss = CEnemyManager::GetNumEneBoss();

	if (m_DieCounter >= nNumBoss && m_bAppearExecutive == true && m_bAppearBoss == true)
	{
		CEnemyWeak::UninitWeak();

		CEnemyManager::SetNumEneWeak(0);
		CEnemyManager::SetNumEneMedBoss(0);
		CEnemyManager::SetNumEneBoss(0);
		CEnemyManager::SetNumAll(0);

		m_DieCounter = 0;

		if (pFade->Get() != pFade->FADE_OUT)
		{
			pFade->Set(CScene::MODE_RESULT);
		}

		return;
	}
}

//================================================================
//�G�̕`�揈��
//================================================================
void CEnemyManager::Draw(void)
{

}