//===========================================================
//
// �`���[�g���A������[tutorial.cpp]
// Author �匴�叫
//
//===========================================================
#include "tutorial.h"
#include "input.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "field.h"
#include "map.h"
#include "player.h"
#include "enemymanager.h"
#include "enemy_weak.h"
#include "itemmanager.h"
#include "collision.h"
#include "tutorialUI.h"

//===========================================================
// �ÓI�����o�ϐ�
//===========================================================
CPlayer *CTutorial::m_pPlayer = nullptr;
CEnemyManager *CTutorial::m_pEnemyManager = nullptr;
CItemManager* CTutorial::m_pItemManager = nullptr;
CMap *CTutorial::m_pMap = nullptr;
CTutorialUI *CTutorial::m_pUI = nullptr;

//===========================================================
// �R���X�g���N�^
//===========================================================
CTutorial::CTutorial()
{
	m_pField = nullptr;
	m_pEnemy = nullptr;
	m_pItemManager = nullptr;
	m_pStart = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CTutorial::~CTutorial()
{
	
}

//===========================================================
// ��������
//===========================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;

		pTutorial->Init();
	}

	return pTutorial;
}

//===========================================================
// ����������
//===========================================================
HRESULT CTutorial::Init(void)
{
	// �t�B�[���h�̐���
	if (m_pField == nullptr)
	{
		m_pField = CField::Create();
		m_pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\FIELD\\concreat.png"));
		m_pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pField->SetSize(5000.0f, 5000.0f);
		m_pField->SetDraw(true);
	}

	// �����蔻��
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create();
	}

	if (m_pStart == nullptr)
	{
		m_pStart = CObject2D::Create();
		m_pStart->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\start.png"));
		m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.9f, 0.0f));
		m_pStart->SetSize(200.0f, 50.0f);
		m_pStart->SetDraw(true);
	}

	// �}�b�v�̐���
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	// �G�}�l�[�W���̐���
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = CEnemyManager::Create();
	}

	if (m_pItemManager == nullptr)
	{
		m_pItemManager = CItemManager::Create("data\\TEXT\\itemset_tutorial.txt");
	}

	if (m_pUI == nullptr)
	{
		m_pUI = CTutorialUI::Create();
	}
	
	// �v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
		m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 500.0f));
		m_pPlayer->SetMobile();
	}

	CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CTutorial::Uninit(void)
{
	CManager::Getinstance()->GetSound()->Stop();

	// �j��
	// �t�B�[���h
	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// �w�i
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// �}�b�v
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	// �G�̔j��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		m_pEnemyManager = nullptr;
	}

	// �A�C�e���̔j��
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Uninit();
		m_pItemManager = nullptr;
	}

	if (m_pUI != nullptr)
	{
		m_pUI->Uninit();
		m_pUI = nullptr;
	}

	// �v���C���[
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	CObject::ReleaseAll();
}

//===========================================================
// �X�V����
//===========================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true)
	{//ENTER�L�[�����������V�[�����^�C�g���̂Ƃ�

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_GAME);
		}
	}

	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Update();

		if (CEnemyManager::GetNum() <= 0)
		{
			m_pEnemyManager = nullptr;

			m_pEnemyManager = CEnemyManager::Create();
		}
	}
	
	// ���ׂčX�V
	CObject::UpdateAll();
}

//===========================================================
// �`�揈��
//===========================================================
void CTutorial::Draw(void)
{
	
}