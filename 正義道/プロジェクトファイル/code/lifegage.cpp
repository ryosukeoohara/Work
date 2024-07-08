//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "lifegage.h"
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
CLifegage::CLifegage()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CLifegage::CLifegage(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CLifegage::~CLifegage()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CLifegage *CLifegage::Create(D3DXVECTOR3 pos)
{
	CLifegage *pTitlelogo = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CLifegage(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//����������
//===========================================================
HRESULT CLifegage::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\Lifegage.png"));

	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CLifegage::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CLifegage::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxLifeGage(pos, 200.0f, 50.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CLifegage::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}