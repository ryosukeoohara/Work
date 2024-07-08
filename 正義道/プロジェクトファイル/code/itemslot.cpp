//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "itemslot.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CItemSlot::m_pTexture = NULL;

//===========================================================
//�R���X�g���N�^
//===========================================================
CItemSlot::CItemSlot()
{

}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CItemSlot::CItemSlot(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CItemSlot::~CItemSlot()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CItemSlot *CItemSlot::Create(D3DXVECTOR3 pos)
{
	CItemSlot *pItemSlot = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CItemSlot(pos);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//����������
//===========================================================
HRESULT CItemSlot::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	CObject2D::Init();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\Itemslot001.png"));

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CItemSlot::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CItemSlot::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxItemSlot(pos, 50.0f, 50.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CItemSlot::Draw(void)
{
	CObject2D::Draw();
}