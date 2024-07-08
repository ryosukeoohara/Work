//===============================================================
//
//�`���[�g���A��UI����[tutorialUI.cpp]
// Author �匴�叫
//
//===============================================================
#include "tutorialUI.h"
#include "tutorial.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"

//===============================================================
//�ÓI�����o�ϐ�
//===============================================================
CTutorialUI *CTutorialUI::m_TutorialUI = NULL;

//===============================================================
//�R���X�g���N�^
//===============================================================
CTutorialUI::CTutorialUI()
{
	m_nIdxTexture = -1;
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CTutorialUI::~CTutorialUI()
{

}

//===============================================================
//�N���G�C�g
//===============================================================
CTutorialUI *CTutorialUI::Create(D3DXVECTOR3 pos, TYPE type)
{
	if (m_TutorialUI == NULL)
	{
		m_TutorialUI = new CTutorialUI;

		m_TutorialUI->SetPos(&pos);

		m_TutorialUI->m_type = type;

		m_TutorialUI->Init();
	}

	return m_TutorialUI;
}

//===============================================================
//����������
//===============================================================
HRESULT CTutorialUI::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	switch (m_type)
	{
	case CTutorialUI::TYPE_NONE:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutplogo.png"));
		break;

	case CTutorialUI::TYPE_AIM00:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_000.png"));
		break;

	case CTutorialUI::TYPE_AIM01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_001.png"));
		break;

	case CTutorialUI::TYPE_AIM02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_002.png"));
		break;

	case CTutorialUI::TYPE_AIM03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_0002.png"));
		break;

	case CTutorialUI::TYPE_AIM04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_0003.png"));
		break;

	case CTutorialUI::TYPE_AIM05:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_005.png"));
		break;

	case CTutorialUI::TYPE_LESSON01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_001.png"));
		break;

	case CTutorialUI::TYPE_LESSON02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CTutorialUI::TYPE_LESSON03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_005.png"));
		break;

	case CTutorialUI::TYPE_LESSON04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CTutorialUI::TYPE_LESSON05:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CTutorialUI::TYPE_MAX:

		break;

	default:
		break;
	}
	

	//����������
	CObject2D::Init();

	return S_OK;
}

//===============================================================
//�I������
//===============================================================
void CTutorialUI::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	if (m_TutorialUI != NULL)
	{
		m_TutorialUI = NULL;
	}
}

//===============================================================
//�X�V����
//===============================================================
void CTutorialUI::Update(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//�X�V����
	CObject2D::Update();

	if (m_TutorialUI != NULL)
	{
		D3DXVECTOR3 pos = m_TutorialUI->Getpos();

		if (m_type == TYPE_LESSON01 || m_type == TYPE_LESSON02 || m_type == TYPE_LESSON03 || m_type == TYPE_LESSON04 || m_type == TYPE_LESSON05)
		{
			m_TutorialUI->SetVtxUI(pos, 400.0f, 75.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
		else if (m_type == TYPE_NONE)
		{
			m_TutorialUI->SetVtxUI(pos, 100.0f, 50.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
		else
		{
			m_TutorialUI->SetVtxUI(pos, 640.0f, 360.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
	}
}

//===============================================================
//�`�揈��
//===============================================================
void CTutorialUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`�揈��
	CObject2D::Draw();
}