//===========================================================
//
// �����L���O�̃��S����[itemslot.cpp]
// Author �匴�叫
//
//===========================================================
#include "rankinglogo.h"
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
CRankinglogo::CRankinglogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CRankinglogo::CRankinglogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CRankinglogo::~CRankinglogo()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CRankinglogo *CRankinglogo::Create(D3DXVECTOR3 pos)
{
	CRankinglogo *pTitlelogo = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CRankinglogo(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//����������
//===========================================================
HRESULT CRankinglogo::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\ranking.png"));

	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CRankinglogo::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CRankinglogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 200.0f, 50.0f);
}

//===========================================================
//�`�揈��
//===========================================================
void CRankinglogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}