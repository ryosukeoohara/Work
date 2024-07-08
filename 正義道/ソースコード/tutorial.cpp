//===============================================================
//
//�`���[�g���A������[tutorial.cpp]
// Author �匴�叫
//
//===============================================================
#include "tutorial.h"
#include "player.h"
#include "field.h"
#include "sky.h"
#include "map.h"
#include "collision.h"
#include "debugproc.h"
#include "slot.h"
#include "itemicon.h"
#include "tutorialUI.h"
#include "fade.h"
#include "tutorialAI.h"
#include "input.h"
#include "sound.h"
#include "tutoriallogo.h"

//===============================================================
//�ÓI�����o�ϐ�
//===============================================================
CPlayer *CTutorial::m_Player = NULL;
CTutorial::TYPE CTutorial::m_type = TYPE_NONE;
bool CTutorial::m_bEndlesson = false;

//===============================================================
//�R���X�g���N�^
//===============================================================
CTutorial::CTutorial()
{
	m_bCrateUI = false;
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CTutorial::~CTutorial()
{

}

//===============================================================
//�N���G�C�g
//===============================================================
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

//===============================================================
//����������
//===============================================================
HRESULT CTutorial::Init(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	m_type = TYPE_LESSON01;

	CField::Create();

	//��𐶐�
	CSky::Create({ 0.0f,0.0f,0.0f });

	if (m_Player == NULL)
	{//�g�p����Ă��Ȃ�������

		//�v���C���[�̐���
		m_Player = new CPlayer({ 780.0f, 0.0f, -800.0f });

		//����������
		m_Player->Init();
	}

	//�`���[�g���A���擱��AI
	CTutorialAI::Create({ 780.0f, 0.0f, -1300.0f }, {0.0f, D3DX_PI, 0.0f});

	//�A�C�e���X���b�g
	CSlot::Create();

	//�A�C�e���A�C�R��
	CItemIcon::Create({ 350.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROXIMITY);
	CItemIcon::Create({ 450.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROJECTILE);

	//�t���[��
	CFrame::Create();

	CTutoriallogo::Create({ 1100.0f, 650.0f, 0.0f });

	pSound->Play(CSound::SOUND_LABEL_BGM003);

	return S_OK;
}

//===============================================================
//�I������
//===============================================================
void CTutorial::Uninit(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

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

	CObject::ReleaseAll();
}

//===============================================================
//�X�V����
//===============================================================
void CTutorial::Update(void)
{
	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//�V�[���̏����擾
	CScene *pScene = CManager::GetScene();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	//�`���[�g���A��UI�̏����擾
	CTutorialUI *pTutoUI = CTutorialUI::GetUI();

	//���ׂẴI�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();

	if (m_Player->GetTutostate() == CPlayer::TUTOSTATE_STOP && m_bCrateUI == false)
	{
		CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM00);

		m_bCrateUI = true;
	}
	
	if (pTutoUI != NULL)
	{
		if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM00 || CTutorialUI::TYPE_AIM01 || CTutorialUI::TYPE_AIM02 || CTutorialUI::TYPE_AIM03 || CTutorialUI::TYPE_AIM04 || CTutorialUI::TYPE_AIM05)
		{
			if (InputKeyboard->GetTrigger(DIK_SPACE) == true)
			{//ENTER�L�[�������ꂽ

				//��ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM00)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON01);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//��ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM01)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON02);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//�O�ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM02)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON03);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//4�ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM03)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON04);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//5�ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM04)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON05);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//�l�ڂ̖ڕW
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM05)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					if (pFade->Get() != pFade->FADE_OUT)
					{
						pFade->Set(CScene::MODE_GAME);
					}

					return;
				}
			}
		}

		//�ړ��̃`���[�g���A��--------------------------------------------------------------------------------------------------------------
 		if (m_bEndlesson == true && m_type == TYPE_LESSON01)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON01)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM01);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON02;

			m_bEndlesson = false;
		}

		//�U���̃`���[�g���A��--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON02)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON02)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM02);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON03;

			m_bEndlesson = false;
		}

		//�z�C�[���̃`���[�g���A��--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON03)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON03)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM03);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON04;

			m_bEndlesson = false;
		}

		//�ˌ��̃`���[�g���A��--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON04)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON04)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM04);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON05;

			m_bEndlesson = false;
		}

		//����̃`���[�g���A��--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON05)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON05)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM05);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_bEndlesson = false;
		}
	}

	if (pDebugProc != NULL)
	{
		pDebugProc->Print("\n�V�[���F�`���[�g���A��");
	}
}

//===============================================================
//�`�揈��
//===============================================================
void CTutorial::Draw(void)
{
	CTutorialUI *pTutorial = CTutorialUI::GetUI();

	if (pTutorial != NULL)
	{
		pTutorial->Draw();
	}
}

//===============================================================
//�`���[�g���A���̃v���C���[���擾
//===============================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_Player;
}