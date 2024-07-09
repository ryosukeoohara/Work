//===========================================================
//
// �Q�[������[game.cpp]
// Author �匴�叫
//
//===========================================================
#include "game.h"
#include "enemyweak.h"
#include "enemyBoss.h"
#include "time.h"
#include "score.h"
#include "slot.h"
#include "itemicon.h"
#include "frame.h"
#include "player.h"
#include "collision.h"
#include "field.h"
#include "map.h"
#include "debugproc.h"
#include "enemymanager.h"
#include "effectline.h"
#include "effectsord.h"
#include "lifegage.h"
#include "icon.h"
#include "displife.h"
#include "target.h"
#include "pause.h"
#include "sky.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "objectMesh.h"
#include "gameUI.h"
#include "bulletUI.h"

//================================================================
//�ÓI�����o�ϐ�
//================================================================
CPlayer *CGame::m_Player = NULL;
CEnemy *CGame::m_Enemy = NULL;
CEnemyManager *CGame::m_EnemyManager = NULL;
CCollision *CGame::m_Collision = NULL;
CMap *CGame::m_Map = NULL;
CDispLife *CGame::m_DispLife = NULL;
CShadow *CGame::m_Shadow = NULL;
CLife *CGame::m_Life = NULL;
CPause *CGame::m_Pause = NULL;
bool CGame::m_bPause = false;

//===========================================================
//�R���X�g���N�^
//===========================================================
CGame::CGame()
{
	
}

//===========================================================
//�R���X�g���N�^
//===========================================================
CGame::CGame(CScene::MODE mode)
{
	
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CGame::~CGame()
{

}

//===========================================================
//�f�X�g���N�^
//===========================================================
CGame *CGame::Create(void)
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;

		pGame->Init();
	}

	return pGame;
}

//===========================================================
//����������
//===========================================================
HRESULT CGame::Init(void)
{
	//�J�����擾
	CCamera *pCamera = CManager::GetCamera();

	pCamera->SetType(CCamera::TYPE_GAME);

	//�t�B�[���h�𐶐�
	CField::Create();

	//CObjectMesh::Create();

	//��𐶐�
	CSky::Create({ 0.0f,0.0f,0.0f });

	if (m_Map == NULL)
	{//�g�p����Ă��Ȃ�������

		//�}�b�v�𐶐�
		m_Map = new CMap;

		//����������
		m_Map->Init();
	}

	if (m_Collision == NULL)
	{//�g�p����Ă��Ȃ�������

		//�����蔻��𐶐�
		m_Collision = new CCollision;

		//����������
		m_Collision->Init();
	}

	if (m_Player == NULL)
	{//�g�p����Ă��Ȃ�������

		//�v���C���[�̐���
		m_Player = new CPlayer({ 780.0f, 0.0f, -1140.0f });

		//����������
		m_Player->Init();
	}

	if (m_EnemyManager == NULL)
	{//�g�p����Ă��Ȃ�������

		//�G�}�l�[�W���̐���
		m_EnemyManager = new CEnemyManager;

		//����������
		m_EnemyManager->Init();
	}

	//����
	CTime::Create();

	//�X�R�A
	CScore::Create();

	//�A�C�e���X���b�g
	CSlot::Create();

	//�A�C�e���A�C�R��
	CItemIcon::Create({ 350.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROXIMITY);
	CItemIcon::Create({ 450.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROJECTILE);

	//�t���[��
	CFrame::Create();

	CLifegage::Create({200.0f, 50.0f, 0.0f});

	CDispLife::Create({ 65.0f, 50.0f, 0.0f });

	CIcon::Create({ 50.0f,50.0f,0.0f }, CIcon::TYPE_PLAYER);

	CBulletUI::Create({80.0f, 400.0f, 0.0f});

	CTarget::Create(CTarget::TYPE_FIRST, { 200.0f, 200.0f, 0.0f });

	CSound *pSound = CManager::GetSound();

	CGameUI::Create({ SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CGameUI::TYPE_AIM00);

	pSound->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	//�����蔻��̔j��
	if (m_Collision != NULL)
	{
		//�}�b�v�̏I������
		m_Collision->Uninit();

		//���������J��
		delete m_Collision;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_Collision = NULL;
	}

	//�v���C���[�̔j��
	if (m_Player != NULL)
	{
		//�v���C���[�̏I������
		m_Player->Uninit();

		//���������J��
		//delete m_Player;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_Player = NULL;
	}

	//�G�}�l�[�W���̔j��
	if (m_EnemyManager != NULL)
	{
		//�G�}�l�[�W���̏I������
		m_EnemyManager->Uninit();

		//���������J��
		delete m_EnemyManager;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_EnemyManager = NULL;
	}

	//�e�̔j��
	if (m_Shadow != NULL)
	{//�g�p����Ă���Ƃ�

		//�e�̏I������
		//m_Shadow->Uninit();

		//���������J��
		//delete m_Shadow;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_Shadow = NULL;
	}

	if (m_Life != NULL)
	{
		m_Life = NULL;
	}

	//�}�b�v�̔j��
	if (m_Map != NULL)
	{//�g�p����Ă��Ȃ�������

		////�}�b�v�̏I������
		//m_Map->Uninit();

		////���������J��
		//delete m_Map;

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_Map = NULL;
	}

	//�|�[�Y�̔j��
	if (m_Pause != NULL)
	{
		//�I������
		m_Pause->Uninit();

		//�g�p���Ă��Ȃ���Ԃɂ���
		m_Pause = NULL;
	}

	CObject::ReleaseAll();
}

//===========================================================
//�X�V����
//===========================================================
void CGame::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	if (m_EnemyManager != NULL)
	{
		m_EnemyManager->Update();
	}

	//if (InputKeyboard->GetTrigger(DIK_P) == true)
	//{//W�L�[�������ꂽ

	//	m_bPause = m_bPause ? false : true;
	//}

	//if (m_bPause == true)
	//{
	//	if (m_Pause == NULL)
	//	{//�g�p����Ă��Ȃ�������

	//		//�|�[�Y�𐶐�
	//		m_Pause = new CPause;

	//		//����������
	//		m_Pause->Init();
	//	}

	//	if (m_Pause != NULL)
	//	{
	//		m_Pause->Update();
	//	}
	//}
	//else
	//{
	//	//�|�[�Y�̔j��
	//	if (m_Pause != NULL)
	//	{
	//		//�I������
	//		m_Pause->Uninit();

	//		//�g�p���Ă��Ȃ���Ԃɂ���
	//		m_Pause = NULL;
	//	}

	//	CObject::UpdateAll();
	//}

	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\n�V�[���F�Q�[��");
}

//===========================================================
//�`�揈��
//===========================================================
void CGame::Draw(void)
{
	
}

//================================================================
//�v���C���[�̎擾
//================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_Player;
}

//================================================================
//�G�̎擾
//================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_Enemy;
}

//================================================================
//�G�̎擾
//================================================================
CEnemyManager *CGame::GetEnemyManager(void)
{
	return m_EnemyManager;
}

//================================================================
//�����蔻��̎擾
//================================================================
CCollision *CGame::GetCollsion(void)
{
	return m_Collision;
}

//================================================================
//�}�b�v�̎擾
//================================================================
CMap *CGame::GetMap(void)
{
	return m_Map;
}

//================================================================
//2D�\���̃��C�t�̎擾
//================================================================
CDispLife *CGame::GetDispLife(void)
{
	return m_DispLife;
}

//================================================================
//�e�\���̎擾
//================================================================
CShadow *CGame::GetShadow(void)
{
	return m_Shadow;
}

//================================================================
//3D�\���̃��C�t�̎擾
//================================================================
CLife *CGame::GetLife(void)
{
	return m_Life;
}

//================================================================
//�|�[�Y�̎擾
//================================================================
CPause *CGame::GetPause(void)
{
	return m_Pause;
}