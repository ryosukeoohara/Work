//===========================================================
//
// �|�[�Y����[pause.cpp]
// Author �匴�叫
//
//===========================================================
#include "pause.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"
#include "fade.h"
#include "game.h"

//===========================================================
// �萔��`
//===========================================================
namespace 
{
	const D3DXVECTOR3 TEXPOS[3] =   // �ʒu
	{
		D3DXVECTOR3(640.0f, 350.0f, 0.0f),
		D3DXVECTOR3(640.0f, 500.0f, 0.0f),
		D3DXVECTOR3(640.0f, 650.0f, 0.0f),
	};

	const D3DXVECTOR2 TEX_SIZE = { 140.0f, 45.0f };  // �T�C�Y
}

//===========================================================
// �e�N�X�`���l�[��
//===========================================================
const char *CPause::m_apTexName[TYPE_MAX] =
{
	"data\\TEXTURE\\pause000.png",     // ������
	"data\\TEXTURE\\pause001.png",     // ��蒼��
	"data\\TEXTURE\\pause002.png",     // �^�C�g����ʂɖ߂�
	"data\\TEXTURE\\iron000.jpg",      // �����w�i
	"data\\TEXTURE\\fream.png",		   // �g
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CPause::CPause()
{
	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		m_aMenu[nCount].Object2D = nullptr;
		m_aMenu[nCount].col = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	}

	m_pBg = nullptr;
	m_pFrame = nullptr;
	m_nSelect = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CPause::~CPause()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CPause::Init(void)
{
	if (m_pFrame == nullptr)
	{
		m_pFrame = CObject2D::Create();
		m_pFrame->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[TYPE_FRAME]));
		m_pFrame->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pFrame->SetSize(270.0f, 270.0f);
		m_pFrame->SetDraw(false);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D == nullptr)
		{
			m_aMenu[nCount].Object2D = CObject2D::Create();
			m_aMenu[nCount].Object2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[nCount]));
			m_aMenu[nCount].Object2D->SetPosition(D3DXVECTOR3(640.0f, 250.0f + nCount * 150.0f, 0.0f));
			m_aMenu[nCount].Object2D->SetSize(TEX_SIZE.x, TEX_SIZE.y);
			m_aMenu[nCount].Object2D->SetDraw(false);
		}
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CPause::Uninit(void)
{
	
}

//===========================================================
// �X�V����
//===========================================================
void CPause::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	//��Ɉړ�----------------------------------------------
	if (InputKeyboard->GetTrigger(DIK_S) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_DOWN, 0) == true)
	{//W�L�[�������ꂽ

		m_nSelect = (m_nSelect + 1) % MENU_MAX;
		SetCol();
	}
	else if (InputKeyboard->GetTrigger(DIK_W) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_UP, 0) == true)
	{
		m_nSelect = (m_nSelect - 1 + MENU_MAX) % MENU_MAX;
		SetCol();
	}

	//��Ɉړ�----------------------------------------------
	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{//W�L�[�������ꂽ

		switch (m_nSelect)
		{
		case MENU_COUTINUE:
			CGame::SetbPause(false);
			break;

		case MENU_RETRY:

			if (pFade->Get() != pFade->FADE_OUT)
			{
				//�V�[�����Q�[���ɑJ��
				pFade->Set(CScene::MODE_GAME);
			}
			break;

		case MENU_QUIT:

			if (pFade->Get() != pFade->FADE_OUT)
			{
				//�V�[�����^�C�g���J��
				pFade->Set(CScene::MODE_TITLE);
			}
			break;

		default:
			break;
		}
	}

	SetCol();
}

//===========================================================
// �`�揈��
//===========================================================
void CPause::Draw(void)
{
	
}

//===========================================================
// ��������
//===========================================================
CPause * CPause::Create(void)
{
	// �|�[�Y�̃|�C���^
	CPause *pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{//	�g�p����Ă�����

		// ����������
		pPause->Init();
	}
	else
	{// �g�p����Ă��Ȃ�������null��Ԃ�

		return nullptr;
	}

	return pPause;
}

//===========================================================
// �`�悷�邩�ǂ���
//===========================================================
void CPause::SetDraw(bool bPause)
{
	if (m_pBg != nullptr)
	{
		m_pBg->SetDraw(bPause);
	}

	if (m_pFrame != nullptr)
	{
		m_pFrame->SetDraw(bPause);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D != nullptr)
		{
			m_aMenu[nCount].Object2D->SetDraw(bPause);
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CPause::SetCol(void)
{
	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_nSelect != nCount)
		{
			m_aMenu[nCount].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else
		{
			m_aMenu[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_aMenu[nCount].Object2D != nullptr)
		{
			m_aMenu[nCount].Object2D->SetColor(m_aMenu[nCount].col);
		}
	}
}