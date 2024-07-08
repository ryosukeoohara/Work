//===========================================================
//
// �����ȃQ�[�W����[gage.cpp]
// Author �匴�叫
//
//===========================================================
#include "gage.h"
#include "game.h"
#include "player.h"
#include "manager.h"
#include "texture.h"

namespace
{
	const D3DXCOLOR GAGECOL[CGage2D::TYPE_MAX] =
	{
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
		D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
	};
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CGage2D::CGage2D(int nPriority)
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_Type = TYPE_NONE;
	m_pObject2D = nullptr; 
	m_pObjGage = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CGage2D::~CGage2D()
{

}

//===========================================================
// ��������
//===========================================================
CGage2D * CGage2D::Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type)
{
	CGage2D *pGage = nullptr;
	pGage = new CGage2D;

	if (pGage != nullptr)
	{
		pGage->Init(pos, fHei, fWid, type);
		pGage->SetCol();
	}

	return pGage;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage2D::Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type)
{
	m_Type = type;

	if (m_pObjGage == nullptr)
	{
		m_pObjGage = CObject2D::Create();
		m_pObjGage->SetPosition(D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f , pos.z));
		m_pObjGage->SetEdgeCenter(fWid * 10.4f, fHei * 1.4f);
		m_pObjGage->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\lifegage.png"));
		m_pObjGage->SetDraw(true);
	}

	if (m_pObject2D == nullptr)
	{
		m_pObject2D = CObject2D::Create();
		m_pObject2D->SetPosition(pos);
		m_pObject2D->SetEdgeCenter(fWid, fHei);
		m_pObject2D->SetDraw(true);
	}

	return S_OK;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage2D::Init(void)
{
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CGage2D::Uninit(void)
{
	CObject::Release();
}

//===========================================================
// �X�V����
//===========================================================
void CGage2D::Update(void)
{

}

//===========================================================
// �`�揈��
//===========================================================
void CGage2D::Draw(void)
{

}

//===========================================================
// ��ނ��Ƃ̐F�ݒ�
//===========================================================
void CGage2D::SetCol(void)
{
	switch (m_Type)
	{
	case CGage2D::TYPE_NONE:
		m_pObject2D->SetColor(GAGECOL[TYPE_NONE]);
		break;

	case CGage2D::TYPE_LIFE:
		m_pObject2D->SetColor(GAGECOL[TYPE_LIFE]);
		break;

	case CGage2D::TYPE_STAMINA:
		m_pObject2D->SetColor(GAGECOL[TYPE_STAMINA]);
		break;

	case CGage2D::TYPE_MAX:

		break;

	default:
		break;
	}
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CGage3D::CGage3D(int nPriority)
{
	// �l���N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_Type = TYPE_NONE;
	m_pBillBoard = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CGage3D::~CGage3D()
{

}

//===========================================================
// ��������
//===========================================================
CGage3D * CGage3D::Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type)
{
	CGage3D *pGage = nullptr;
	pGage = new CGage3D(5);

	if (pGage != nullptr)
	{
		pGage->Init(pos, fHei, fWid, type);
		pGage->SetCol();
	}

	return pGage;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage3D::Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type)
{
	m_Type = type;

	if (m_pBillBoard == nullptr)
	{
		m_pBillBoard = CBillBoard::Create(6);
		m_pBillBoard->SetPosition(pos);
		m_pBillBoard->SetSize(fHei, fWid);
		m_pBillBoard->SetDraw(true);
	}

	return S_OK;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage3D::Init(void)
{
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CGage3D::Uninit(void)
{
	if (m_pBillBoard != nullptr)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = nullptr;
	}

	CObject::Release();
}

//===========================================================
// �X�V����
//===========================================================
void CGage3D::Update(void)
{
	SetMixPos();
}

//===========================================================
// �`�揈��
//===========================================================
void CGage3D::Draw(void)
{

}

//===========================================================
// ��ނ��Ƃ̐F�ݒ�
//===========================================================
void CGage3D::SetCol(void)
{
	switch (m_Type)
	{
	case CGage3D::TYPE_NONE:
		m_pBillBoard->SetColor(GAGECOL[TYPE_NONE]);
		break;

	case CGage3D::TYPE_STAMINA:
		m_pBillBoard->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		break;

	case CGage3D::TYPE_LIFE:
		m_pBillBoard->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f));
		break;

	case CGage3D::TYPE_MAX:

		break;

	default:
		break;
	}
}

void CGage3D::SetMixPos(void)
{
	if (m_pPos == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = *m_pPos;

	pos.y += m_UpHeight;

	if (m_pBillBoard != nullptr)
	{
		m_pBillBoard->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}
}