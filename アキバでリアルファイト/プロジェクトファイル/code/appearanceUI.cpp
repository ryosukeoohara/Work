//===========================================================
//
// �G�o�ꎞ��UI[appearanceUI.cpp]
// Author �匴�叫
//
//===========================================================
#include "appearanceUI.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "number.h"
#include "utility.h"
#include "sound.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const char *TEXTURENAME[CAppearanceUI::TYPE_MAX] =
	{
		"",
		"data\\TEXTURE\\underling.png", // �U�R
		"data\\TEXTURE\\ishii.png",     // �{�X
		"data\\TEXTURE\\number002.png", // ����
	};  // �e�N�X�`���̖��O
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAppearanceUI::CAppearanceUI()
{
	// ������
	m_type = TYPE_NONE;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
	m_pNumber = nullptr;
	m_bSound = false;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAppearanceUI::CAppearanceUI(TYPE type, int nPriority) : CObject(nPriority)
{
	// ������
	m_type = type;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
	m_pNumber = nullptr;
	m_bSound = false;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CAppearanceUI::~CAppearanceUI()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CAppearanceUI::Init(void)
{
	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		// ���ꂼ�ꐶ�����āA�ʒu�A�T�C�Y�A�e�N�X�`���A�`���Ԃ�ݒ�
		if (m_pBackObj2D == nullptr)
		{
			m_pBackObj2D = CObject2D::Create();
			m_pBackObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pBackObj2D->SetSize(0.0f, 0.0f);
			m_pBackObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
			m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pBackObj2D->SetDraw(false);
		}

		if (m_pFrontObj2D == nullptr)
		{
			m_pFrontObj2D = CObject2D::Create();
			m_pFrontObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pFrontObj2D->SetSize(1200.0f, 600.0f);
			m_pFrontObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
			m_pFrontObj2D->SetDraw();
		}
	}
	
	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_RESULT)
	{
		// ���ꂼ�ꐶ�����āA�ʒu�A�T�C�Y�A�e�N�X�`���A�`���Ԃ�ݒ�
		if (m_pBackObj2D == nullptr)
		{
			m_pBackObj2D = CObject2D::Create();
			m_pBackObj2D->SetPosition(D3DXVECTOR3(750.0f, 225.0f, 0.0f));
			m_pBackObj2D->SetSize(0.0f, 0.0f);
			m_pBackObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
			m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pBackObj2D->SetTex((float)CManager::Getinstance()->GetDefeat());
			m_pBackObj2D->SetDraw(false);
		}

		if (m_pNumber == nullptr)
		{
			m_pNumber = CObject2D::Create();
			m_pNumber->SetPosition(D3DXVECTOR3(750.0f, 225.0f, 0.0f));
			m_pNumber->SetSize(200.0f, 200.0f);
			m_pNumber->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
			m_pNumber->SetTex((float)CManager::Getinstance()->GetDefeat());
			m_pNumber->SetDraw();
		}
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CAppearanceUI::Uninit(void)
{
	// �j��
	if (m_pFrontObj2D != nullptr)
	{
		m_pFrontObj2D->Uninit();
		m_pFrontObj2D = nullptr;
	}

	if (m_pBackObj2D != nullptr)
	{
		m_pBackObj2D->Uninit();
		m_pBackObj2D = nullptr;
	}

	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}

	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CAppearanceUI::Update(void)
{
	if (m_pFrontObj2D != nullptr && m_pBackObj2D != nullptr)
	{// �O�ƌ�뗼���g�p���Ă�����

		// ���ƍ����擾
		float fHeight = m_pFrontObj2D->GetHeight();
		float fWidth = m_pFrontObj2D->GetWidth();

		if (m_pFrontObj2D->GetHeight() >= 100.0f && m_pFrontObj2D->GetWidth() >= 30.0f)
		{// ���̐��l�ȉ��ɂȂ�܂ŏ���������

			// �|���S��������������
			CManager::Getinstance()->GetUtility()->Shrink(m_pFrontObj2D, 25.0f, 50.0f);

		}
		else
		{// �������Ȃ���

			if (m_bSound == false)
			{
				CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_IMPACT);
				m_bSound = true;
			}

			// �|���S����傫������
			CManager::Getinstance()->GetUtility()->Enlarge(m_pBackObj2D, 5.0f, 10.0f);

			// �|���S���𓧖��ɂ���
			CManager::Getinstance()->GetUtility()->Color_A2D(m_pBackObj2D, -0.03f);
		}

		if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
		{
			D3DXVECTOR3 pos = m_pFrontObj2D->GetPosition();

			pos.x = pos.x + 60.0f;

			m_pFrontObj2D->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));

			// �T�C�Y�ݒ�
			m_pFrontObj2D->SetSize(fWidth, fHeight);

			if (pos.x >= 1500.0f)
			{
				Uninit();
			}
		}
	}

	if (m_pNumber != nullptr && m_pBackObj2D != nullptr)
	{
		// ���ƍ����擾
		float fHeight = m_pNumber->GetHeight();
		float fWidth = m_pNumber->GetWidth();

		if (m_pNumber->GetHeight() >= 50.0f && m_pNumber->GetWidth() >= 50.0f)
		{// ���̐��l�ȉ��ɂȂ�܂ŏ���������

			// �|���S��������������
			CManager::Getinstance()->GetUtility()->Shrink(m_pNumber, 10.0f, 10.0f);
		}
		else
		{// �������Ȃ���

			// �|���S����傫������
			CManager::Getinstance()->GetUtility()->Enlarge(m_pBackObj2D, 5.0f, 10.0f);

			// �|���S���𓧖��ɂ���
			CManager::Getinstance()->GetUtility()->Color_A2D(m_pBackObj2D, -0.03f);
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CAppearanceUI::Draw(void)
{

}

//===========================================================
// ��������
//===========================================================
CAppearanceUI * CAppearanceUI::Create(TYPE type, int nPriority)
{
	CAppearanceUI *pAppearUI = nullptr;
	pAppearUI = new CAppearanceUI(type, nPriority);

	if (pAppearUI != nullptr)
	{
		pAppearUI->Init();
	}

	return pAppearUI;
}
