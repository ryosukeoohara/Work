//===========================================================
//
// �A�C�e���A�C�R������[itemicon.cpp]
// Author �匴�叫
//
//===========================================================
#include "itemicon.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CItemIcon::m_pTexture = NULL;

//===========================================================
//�R���X�g���N�^
//===========================================================
CItemIcon::CItemIcon()
{

}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CItemIcon::CItemIcon(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_type = type;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CItemIcon::~CItemIcon()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CItemIcon *CItemIcon::Create(D3DXVECTOR3 pos, TYPE type)
{
	CItemIcon *pItemSlot = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CItemIcon(pos, type);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//����������
//===========================================================
HRESULT CItemIcon::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	switch (m_type)
	{
	case CItemIcon::TYPE_PROXIMITY:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\punch.png"));
		break;

	case CItemIcon::TYPE_PROJECTILE:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\gun.png"));
		break;

	case CItemIcon::TYPE_KUGIBAT:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\kugibat.png"));
		break;

	case CItemIcon::TYPE_BOM:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\bom.png"));
		break;

	default:
		break;
	}

	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CItemIcon::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CItemIcon::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxItemSlot(pos, 40.0f, 40.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CItemIcon::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();
}