//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "icon.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CIcon::m_pTexture = NULL;

//===========================================================
//�R���X�g���N�^
//===========================================================
CIcon::CIcon()
{

}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CIcon::CIcon(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_type = type;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CIcon::~CIcon()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CIcon *CIcon::Create(D3DXVECTOR3 pos, TYPE type)
{
	CIcon *pItemSlot = NULL;

	if (pItemSlot == NULL)
	{
		pItemSlot = new CIcon(pos, type);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//����������
//===========================================================
HRESULT CIcon::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	CObject2D::Init();

	switch (m_type)
	{
	case TYPE_NONE:

		break;

	case TYPE_PLAYER:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\face.png"));
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CIcon::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CIcon::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxIcon(pos, 50.0f, 50.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CIcon::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject2D::Draw();
}