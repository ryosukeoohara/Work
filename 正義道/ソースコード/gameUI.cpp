//===============================================================
//
//�`���[�g���A��UI����[tutorialUI.cpp]
// Author �匴�叫
//
//===============================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "gameUI.h"
#include "fade.h"

//===============================================================
//�ÓI�����o�ϐ�
//===============================================================
CGameUI *CGameUI::m_pGameUI = NULL;

//===============================================================
//�R���X�g���N�^
//===============================================================
CGameUI::CGameUI()
{
	m_nCntMove = 0;
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CGameUI::~CGameUI()
{
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CGameUI * CGameUI::Create(D3DXVECTOR3 pos, TYPE type)
{
	CGameUI *pGameUI = NULL;

	if (pGameUI == NULL)
	{
		pGameUI = new CGameUI;

		pGameUI->SetPos(&pos);

		pGameUI->m_type = type;

		pGameUI->Init();

		m_pGameUI = pGameUI;
	}

	return pGameUI;
}

//===============================================================
//����������
//===============================================================
HRESULT CGameUI::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_state = STATE_MOVE;

	switch (m_type)
	{
	case CGameUI::TYPE_NONE:

		break;

	case CGameUI::TYPE_AIM00:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\0001.png"));
		break;

	case CGameUI::TYPE_AIM01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_001.png"));
		break;

	case CGameUI::TYPE_AIM02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_100.png"));
		break;

	case CGameUI::TYPE_AIM03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_005.png"));
		break;

	case CGameUI::TYPE_LESSON01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_001.png"));
		break;

	case CGameUI::TYPE_LESSON02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CGameUI::TYPE_LESSON03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CGameUI::TYPE_LESSON04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CGameUI::TYPE_MAX:

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
void CGameUI::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	if (m_pGameUI != NULL)
	{
		m_pGameUI = NULL;
	}
}

//===============================================================
//�X�V����
//===============================================================
void CGameUI::Update(void)
{
	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	SetVtxUI(pos, 400.0f, 200.0f, { 1.0f,1.0f,1.0f,1.0f });

	if (pFade->Get() != pFade->FADE_OUT)
	{
		if (m_state != STATE_NONE)
		{
			if (m_state == STATE_MOVE)
			{
				pos.x -= 20.0f;
			}

			if (pos.x <= 700.0f && m_state != STATE_STOP)
			{
				m_state = STATE_STOP;
			}

			if (m_state == STATE_STOP)
			{
				m_nCntMove++;

				pos.x -= 0.5f;
			}

			if (m_nCntMove >= 120)
			{
				m_state = STATE_MOVE;
			}

			if (pos.x <= -SCREEN_WIDTH)
			{
				Uninit();
			}
		}
	}

	SetPos(&pos);
}

//===============================================================
//�`�揈��
//===============================================================
void CGameUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}