//===========================================================
//
// �G�o�ꎞ��UI[appearanceUI.cpp]
// Author �匴�叫
//
//===========================================================
#include "userrankUI.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "number.h"
#include "utility.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const char *TEXTURENAME[CUserRankUI::TYPE_MAX] =
	{
		"",                             // �Ȃ���Ȃ�
		"data\\TEXTURE\\00_Result.png",	// �ō�
		"data\\TEXTURE\\01_Result.png", // ����
		"data\\TEXTURE\\02_Result.png", // �����[
		"data\\TEXTURE\\03_Result.png", // �Ŏ�
	};  // �e�N�X�`���̖��O
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CUserRankUI::CUserRankUI()
{
	// ������
	m_type = TYPE_NOEN;
	m_pObject = nullptr;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CUserRankUI::CUserRankUI(TYPE type, int nPriority)
{
	// ������
	m_type = type;
	m_pObject = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CUserRankUI::~CUserRankUI()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CUserRankUI::Init(void)
{
	if (m_pObject == nullptr)
	{// �g�p���Ă��Ȃ��Ƃ�

		// �������āA�ʒu�A�T�C�Y�A�e�N�X�`���A�`�悷�邩�ݒ�
		m_pObject = CObject2D::Create();
		m_pObject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f));
		m_pObject->SetSize(600.0f, 150.0f);
		m_pObject->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
		m_pObject->SetDraw();
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CUserRankUI::Uninit(void)
{
	// �j��
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}

	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CUserRankUI::Update(void)
{
	if (m_pObject != nullptr)
	{
		// ���ƍ����擾
		float fHeight = m_pObject->GetHeight();
		float fWidth = m_pObject->GetWidth();

		if (m_pObject->GetHeight() >= 100.0f && m_pObject->GetWidth() >= 30.0f)
		{// ���̐��l�ȉ��ɂȂ�܂ŏ���������

			// �|���S��������������
			CManager::Getinstance()->GetUtility()->Shrink(m_pObject, 25.0f, 50.0f);
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CUserRankUI::Draw(void)
{

}

//===========================================================
// ��������
//===========================================================
CUserRankUI * CUserRankUI::Create(TYPE type)
{
	CUserRankUI *pAppearUI = nullptr;
	pAppearUI = new CUserRankUI(type);

	if (pAppearUI != nullptr)
	{
		pAppearUI->Init();
	}

	return pAppearUI;
}