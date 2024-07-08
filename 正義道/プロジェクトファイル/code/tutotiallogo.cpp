//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "tutoriallogo.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "frame.h"
#include "game.h"

//===========================================================
//�R���X�g���N�^
//===========================================================
CTutoriallogo::CTutoriallogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CTutoriallogo::CTutoriallogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CTutoriallogo::~CTutoriallogo()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CTutoriallogo *CTutoriallogo::Create(D3DXVECTOR3 pos)
{
	CTutoriallogo *pTitlelogo = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CTutoriallogo(pos);

		//pTitlelogo->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Itemslot001.png");

		//�e�N�X�`�����o�C���h
		//pTitlelogo->BindTexture(pTexture->GetAddress(pTitlelogo->m_nIdxTexture));

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//����������
//===========================================================
HRESULT CTutoriallogo::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutologo.png"));

	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTutoriallogo::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CTutoriallogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 200.0f, 50.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CTutoriallogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}