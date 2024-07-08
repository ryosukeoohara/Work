//===========================================================
//
//�|���S�����o�����[bg.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "frame.h"
#include "texture.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "tutorial.h"

//�}�N����`
#define HEIGHT   (50.0f)  //����
#define WIDHT    (50.0f)  //��
#define MOVE     (100.0f) //�ړ�

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
CFrame *CFrame::m_Frame = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CFrame::CFrame()
{
	m_nIdxTexture = 0;
}

//================================================================
//�R���X�g���N�^
//================================================================
CFrame::CFrame(D3DXVECTOR3 pos)
{
	m_nIdxTexture = 0;
	SetPos(&pos);
}

//================================================================
//�f�X�g���N�^
//================================================================
CFrame::~CFrame()
{

}

//================================================================
//��������
//================================================================
CFrame *CFrame::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CFrame *pFrame = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pFrame == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pFrame = new CFrame({ 350.0f, 650.0f, 0.0f });

			//����������
			pFrame->Init();

			m_Frame = pFrame;
		}
	}

	return pFrame;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CFrame::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\waku.png"));

	CObject2D::Init();

	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CFrame::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CFrame::Update(void)
{
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//�V�[���̏����擾
	CScene *pScene = CManager::GetScene();

	//�v���C���[�̏����擾
	CPlayer *pPlayer = CTutorial::GetPlayer();

	float MouseWheel = pInputMouse->GetMouseWheel();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxFrame(pos, WIDHT, HEIGHT);

	if (pScene->GetMode() == CScene::MODE_GAME)
	{
		if (MouseWheel > 0)
		{
			pos.x -= MOVE;
		}

		if (MouseWheel < 0)
		{
			pos.x += MOVE;
		}

		if (pos.x <= 349.0f)
		{
			pos.x = 450.0f;
		}
		else if (pos.x >= 451.0f)
		{
			pos.x = 350.0f;
		}
	}

	if (pScene->GetMode() == CScene::MODE_TUTORIAL && pPlayer->GetbAttack() == true)
	{
		if (MouseWheel > 0)
		{
			pos.x -= MOVE;
		}

		if (MouseWheel < 0)
		{
			pos.x += MOVE;
		}

		if (pos.x <= 349.0f)
		{
			pos.x = 450.0f;
		}
		else if (pos.x >= 451.0f)
		{
			pos.x = 350.0f;
		}
	}

	SetPos(&pos);
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CFrame::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject2D::Draw();
}