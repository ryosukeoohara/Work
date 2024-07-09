//===========================================================
//
// �^�C�g�����S����[titlelogo.cpp]
// Author �匴�叫
//
//===========================================================
#include "titlelogo.h"
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
CTitlelogo::CTitlelogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CTitlelogo::CTitlelogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CTitlelogo::~CTitlelogo()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CTitlelogo *CTitlelogo::Create(D3DXVECTOR3 pos)
{
	CTitlelogo *pTitlelogo = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CTitlelogo(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//����������
//===========================================================
HRESULT CTitlelogo::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\titlelogo.png"));

	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTitlelogo::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CTitlelogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 400.0f, 150.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CTitlelogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}