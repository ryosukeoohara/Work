//===========================================================
//
//�|���S�����o�����[title.cpp]
//Author �匴�叫
//
//===========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "field.h"
#include "debugproc.h"
#include "renderer.h"
#include "titlelogo.h"
#include "sky.h"
#include "sound.h"
#include "player.h"
#include "titleUI.h"
#include "tutorialAI.h"

//===========================================================
//�R���X�g���N�^
//===========================================================
CTitle::CTitle()
{
	for (int nCount = 0; nCount < MAX_TITLEOBJ; nCount++)
	{
		m_apObject2D[nCount] = NULL;
		m_apObject3D[nCount] = NULL;
	}
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CTitle::~CTitle()
{

}

//===========================================================
//����
//===========================================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTitle;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//����������
//===========================================================
HRESULT CTitle::Init(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�t�B�[���h�𐶐�
	CField::Create();

	//�`���[�g���A���擱��AI
	CTutorialAI::Create({ 150.0f, 0.0f, 50.0f }, { 0.0f, D3DX_PI, 0.0f });

	CPlayer::Create({ -150.0f, 0.0f, 50.0f });

	//��𐶐�
	CSky::Create({ 0.0f,0.0f,0.0f });

	//�^�C�g�����S�𐶐�
	CTitlelogo::Create({ SCREEN_WIDTH * 0.5f, 200.0f, 0.0f });

	CTitleUI::Create({ SCREEN_WIDTH * 0.5f, 600.0f, 0.0f });

	pSound->Play(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTitle::Uninit(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	CObject::ReleaseAll();
}

//===========================================================
//�X�V����
//===========================================================
void CTitle::Update(void)
{
	//���ׂẴI�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\n�V�[���F�^�C�g��");
}

//===========================================================
//�`�揈��
//===========================================================
void CTitle::Draw(void)
{
	
}