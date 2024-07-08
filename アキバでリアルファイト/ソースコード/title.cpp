//===========================================================
//
// �^�C�g������[title.cpp]
// Author �匴�叫
//
//===========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "field.h"
#include "map.h"
#include "player.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const D3DXVECTOR3 TEXPOS[3] =   // �ʒu
	{
		D3DXVECTOR3(640.0f, 0.0f, 350.0f),
		D3DXVECTOR3(640.0f, 0.0f, 550.0f),
		D3DXVECTOR3(640.0f, 0.0f, 750.0f),
	};

	const D3DXVECTOR3 CAMERAPOS[3] =   // �ʒu
	{
		D3DXVECTOR3(640.0f, 0.0f, -350.0f),
		D3DXVECTOR3(640.0f, 0.0f, -550.0f),
		D3DXVECTOR3(640.0f, 0.0f, -750.0f),
	};
}

//===========================================================
//�@�ÓI�����o�ϐ�
//===========================================================
CPlayer *CTitle::m_pPlayer = nullptr;

//===========================================================
//�R���X�g���N�^
//===========================================================
CTitle::CTitle()
{
	m_pField = nullptr;
	m_pBg = nullptr;
	m_pMap = nullptr;
	m_pStart = nullptr;
	m_nCnt = 0;
	m_nCntPos = 0;
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
	CTitle *pTitle = nullptr;

	if (pTitle == nullptr)
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

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
		m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pPlayer->SetRotition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	if (m_pStart == nullptr)
	{
		m_pStart = CObject2D::Create();
		m_pStart->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\any.png"));
		m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f));
		m_pStart->SetSize(200.0f, 50.0f);
		m_pStart->SetDraw(true);
	}

	if (m_pBg == nullptr)
	{
		m_pBg = CObject2D::Create();
		m_pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\aaa.png"));
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f));
		m_pBg->SetSize(300.0f, 200.0f);
		m_pBg->SetDraw(true);
	}

	CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);
	
	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTitle::Uninit(void)
{
	CManager::Getinstance()->GetSound()->Stop();

	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// �}�b�v�̔j��
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	if (m_pStart != nullptr)
	{
		m_pStart->Uninit();
		m_pStart = nullptr;
	}

	// �v���C���[�̔j��
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	
	CObject::ReleaseAll();
}

//===========================================================
//�X�V����
//===========================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true)
	{//ENTER�L�[�����������V�[�����^�C�g���̂Ƃ�

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_TUTORIAL);
		}
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->TitleWalk();
	}

	CManager::Getinstance()->GetDebugProc()->Print("���݂̃V�[���F�^�C�g��");
}

//===========================================================
//�`�揈��
//===========================================================
void CTitle::Draw(void)
{
	
}