//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "bulletUI.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "frame.h"
#include "game.h"
#include "target.h"
#include "player.h"

//===========================================================
//�ÓI�����o�ϐ�
//===========================================================
CNumber *CBulletUI::m_apNumber[MAX_NUMBER] = {};

//===========================================================
//�R���X�g���N�^
//===========================================================
CBulletUI::CBulletUI()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CBulletUI::CBulletUI(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CBulletUI::~CBulletUI()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CBulletUI *CBulletUI::Create(D3DXVECTOR3 pos)
{
	CBulletUI *pTitlelogo = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CBulletUI(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//����������
//===========================================================
HRESULT CBulletUI::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\bullet.png"));

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 1090.0f + 50.0f * nCount, 400.0f, 0.0f });

			m_apNumber[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			//����������
			m_apNumber[nCount]->Init();

			m_apNumber[nCount]->m_Number = 0;
		}
	}

	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CBulletUI::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//�I������
			m_apNumber[nCount]->Uninit();

			m_apNumber[nCount] = NULL;
		}
	}
}

//===========================================================
//�X�V����
//===========================================================
void CBulletUI::Update(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	int n = pPlayer->GetRestBullet();

	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 100.0f, 25.0f);

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[0]->m_Number = 0;
			m_apNumber[1]->m_Number = n;

			//�X�V����
			m_apNumber[nCount]->SetVtxCounter({ 200.0f + 30.0f * nCount, 400.0f, 0.0f }, 15.0f, 20.0f);
		}
	}
}

//===========================================================
//�`�揈��
//===========================================================
void CBulletUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}