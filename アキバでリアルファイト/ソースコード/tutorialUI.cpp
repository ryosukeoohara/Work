//===========================================================
//
// �`���[�g���A����UI����[tutorialUI.cpp]
// Author �匴�叫
//
//===========================================================
#include "tutorialUI.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const char *TEXTURENAME[CTutorialUI::TYPE_MAX] =
	{
		"data\\TEXTURE\\10_tutorial.png",  // ���o��
		"data\\TEXTURE\\00_tutorial.png",  // �ړ�
		"data\\TEXTURE\\01_tutorial.png",  // ���_�ړ�
		"data\\TEXTURE\\02_tutorial.png",  // �U��
		"data\\TEXTURE\\03_tutorial.png",  // ���
		"data\\TEXTURE\\04_tutorial.png",  // �͂�
		"data\\TEXTURE\\05_tutorial.png",  // ���A�c
	};  // �g�p����e�N�X�`��
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CTutorialUI::CTutorialUI()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_apObject2D[nCount] = nullptr;
	}
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CTutorialUI::~CTutorialUI()
{
}

//===========================================================
// ����������
//===========================================================
HRESULT CTutorialUI::Init(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apObject2D[nCount] == nullptr)
		{// �g�p���Ă��Ȃ�������

			// �������āA�ʒu�A�T�C�Y�A�e�N�X�`���A�`�悷�邩�ݒ�
			m_apObject2D[nCount] = CObject2D::Create(7);
			m_apObject2D[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.85f, 150.0f + nCount * 40, 0.0f));
			m_apObject2D[nCount]->SetSize(150.0f, 20.0f);
			m_apObject2D[nCount]->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[nCount]));
			m_apObject2D[nCount]->SetDraw();
		}
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CTutorialUI::Uninit(void)
{
}

//===========================================================
// �X�V����
//===========================================================
void CTutorialUI::Update(void)
{
}

//===========================================================
// �`�揈��
//===========================================================
void CTutorialUI::Draw(void)
{
}

//===========================================================
// ��������
//===========================================================
CTutorialUI * CTutorialUI::Create(void)
{
	CTutorialUI *pUI = nullptr;
	pUI = new CTutorialUI;

	if (pUI != nullptr)
	{
		pUI->Init();
	}

	return pUI;
}
