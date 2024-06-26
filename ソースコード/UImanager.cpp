//===========================================================
//
// UI�}�l�[�W��[UImanager.cpp]
// Author �匴�叫
//
//===========================================================

//*==========================================================
// �C���N���[�h�t�@�C��
//*==========================================================
#include "UImanager.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "camera.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{

}

//===========================================================
// �R���X�g���N�^
//===========================================================
CUIManager::CUIManager()
{
	// ������
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.type = TYPE_NONE;
	m_nIdxTexture = -1;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CUIManager::CUIManager(D3DXVECTOR3 pos, TYPE type) : CObject2D::CObject2D(pos)
{
	// ������
	m_Info.pos = pos;
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.type = type;
	m_nIdxTexture = -1;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CUIManager::~CUIManager()
{

}

//===========================================================
// ��������
//===========================================================
CUIManager * CUIManager::Create(D3DXVECTOR3 pos, TYPE type)
{
	// UI�}�l�[�W���ւ̃|�C���^
	CUIManager *pUI = nullptr;

	// ����
	pUI = new CUIManager(pos, type);

	if (pUI != nullptr)
	{
		// ����������
		pUI->Init();
	}

	return pUI;
}

//===========================================================
// ���̈ړ�
//===========================================================
void CUIManager::LineMove(void)
{
	m_Info.move.x = 10.0f;
	m_Info.pos.x += m_Info.move.x;

	CObject2D::SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	CObject2D::SetSize(640.0f, 10.0f);
}

//===========================================================
// �������Ⴍ�Ȃ���I
//===========================================================
void CUIManager::ShrinkSize(void)
{
	float fHeight = CObject2D::GetHeight();
	float fWidth = CObject2D::GetWidth();

	if (CObject2D::GetHeight() >= 100.0f && CObject2D::GetWidth() >= 30.0f)
	{
		fHeight = fHeight - 25.0f;
		fWidth = fWidth - 50.0f;
	}
	else
	{

	}
	
	CObject2D::SetSize(fWidth, fHeight);

	if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
	{
		Uninit();
	}
}

//===========================================================
// ����������
//===========================================================
HRESULT CUIManager::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//����������
	CObject2D::Init();

	// �e�N�X�`���A�T�C�Y�A�ʒu�A�`�悷�邩�ǂ����ݒ�
	switch (m_Info.type)
	{
	case TYPE_NONE:     //�Ȃ���Ȃ�
		break;

	case TYPE_TITLE:    //�^�C�g��

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\title.png"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(500.0f, 400.0f);
		CObject2D::SetDraw();
		break;

	case TYPE_TUTORIAL: //�`���[�g���A��

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial.jpg"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(500.0f, 400.0f);
		CObject2D::SetDraw();
		break;

	case TYPE_RESULT:   //���U���g

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\res.jpg"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(500.0f, 400.0f);
		CObject2D::SetDraw();
		break;

	case TYPE_WEAKNAME:

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\underling.png"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(1200.0f, 600.0f);
		CObject2D::SetDraw();
		break;

	case TYPE_BOSSNAME:

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\ishii.png"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(1200.0f, 600.0f);
		CObject2D::SetDraw();
		break;

	case TYPE_LINE:

		CObject2D::SetIdxTex(pTexture->Regist("data\\TEXTURE\\line.png"));
		CObject2D::SetPosition(m_Info.pos);
		CObject2D::SetSize(640.0f, 10.0f);
		CObject2D::SetDraw(true);
		break;

	case TYPE_MAX:
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CUIManager::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	//���g�̔j��
	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CUIManager::Update(void)
{
	//�X�V����
	CObject2D::Update();

	// �傫���Ƃ��ݒ�
	switch (m_Info.type)
	{
	case TYPE_NONE:      //�Ȃ���Ȃ�

		break;

	case TYPE_TITLE:     //�^�C�g��

		break;

	case TYPE_TUTORIAL:  //�`���[�g���A��

		break;

	case TYPE_RESULT:    //���U���g

		break;

	case TYPE_WEAKNAME:  // �G���̖��O
		ShrinkSize();
		
		break;

	case TYPE_BOSSNAME:  // �{�X�̖��O
		ShrinkSize();
		
		break;

	case TYPE_LINE:      // ���̈ړ�
		LineMove();
		
		break;

	case TYPE_MAX:
		break;

	default:
		break;
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CUIManager::Draw(void)
{
	//�e�N�X�`���̏����擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//�����_���[�̏����擾
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	//�f�o�C�X�̏����擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`�揈��
	CObject2D::Draw();
}