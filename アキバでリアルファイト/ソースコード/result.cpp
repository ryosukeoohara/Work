//===========================================================
//
// ���U���g���[result.cpp]
// Author �匴�叫
//
//===========================================================
#include "result.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "input.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"
#include "fade.h"
#include "map.h"
#include "field.h"
#include "appearanceUI.h"
#include "player.h"
#include "userrankUI.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CResult::CResult()
{
	m_pNumber = nullptr;
	m_pMap = nullptr;
	m_pUserRank = nullptr;
	m_nCounter = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CResult::~CResult()
{

}

//===========================================================
// ��������
//===========================================================
CResult *CResult::Create(void)
{
	CResult *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CResult;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
// ����������
//===========================================================
HRESULT CResult::Init(void)
{
	CField *pField = new CField;

	if (pField != nullptr)
	{
		pField->Init();
		pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\FIELD\\concreat.png"));
		pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pField->SetSize(5000.0f, 5000.0f);
		pField->SetDraw(true);
	}

	// �}�b�v�̐���
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	CObject2D *pBg = new CObject2D;

	if (pBg != nullptr)
	{
		pBg->Init();
		pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\result.png"));
		pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pBg->SetSize(300.0f, 300.0f);
		pBg->SetDraw(true);
	}

	CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CResult::Uninit(void)
{
	CManager::Getinstance()->GetSound()->Stop();

	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// �}�b�v�̔j��
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	CObject::ReleaseAll();
}

//===========================================================
// �X�V����
//===========================================================
void CResult::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true)
	{//ENTER�L�[�����������V�[�����^�C�g���̂Ƃ�

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_TITLE);
		}
	}

	if (m_pNumber == nullptr || m_pUserRank == nullptr)
	{
		m_nCounter++;
	}
	
	if (m_nCounter >= 120)
	{
		if (m_pNumber == nullptr)
		{
			m_pNumber = CAppearanceUI::Create(CAppearanceUI::TYPE_NUMBER);
		}
	}

	if (m_nCounter >= 240)
	{
		if (m_pUserRank == nullptr)
		{
			if (CManager::Getinstance()->GetDefeat() >= 4)
			{
				m_pUserRank = CUserRankUI::Create(CUserRankUI::TYPE_TOP);
			}	
			else if (CManager::Getinstance()->GetDefeat() <= 3 && CManager::Getinstance()->GetDefeat() >= 2)
			{
				m_pUserRank = CUserRankUI::Create(CUserRankUI::TYPE_MIDDLE);
			} 
			else if (CManager::Getinstance()->GetDefeat() <= 1)
			{
				m_pUserRank = CUserRankUI::Create(CUserRankUI::TYPE_UNDER);
			}
			else if (CManager::Getinstance()->GetDefeat() <= 0)
			{
				m_pUserRank = CUserRankUI::Create(CUserRankUI::TYPE_WEAKEST);
			}
			
			m_nCounter = 0;
		}
	}

	if (m_pNumber != nullptr)
	{
		m_pNumber->Update();
	}

	if (m_pUserRank != nullptr)
	{
		m_pUserRank->Update();
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CResult::Draw(void)
{
	
}