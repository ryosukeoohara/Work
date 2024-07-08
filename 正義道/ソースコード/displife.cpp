//===========================================================
//
//�|���S�����o�����[itemslot.cpp]
//Author �匴�叫
//
//===========================================================
#include "displife.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"
#include "player.h"

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CDispLife::m_pTexture = NULL;
CObject2D *CDispLife::m_apObject2D[MAX_DISPLIFE] = {};

//===========================================================
//�R���X�g���N�^
//===========================================================
CDispLife::CDispLife()
{
	m_nIdxTexture = -1;
	m_nMaxLife = 0;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CDispLife::CDispLife(D3DXVECTOR3 pos)
{
	m_nIdxTexture = -1;
	m_nMaxLife = 0;
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CDispLife::~CDispLife()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CDispLife *CDispLife::Create(D3DXVECTOR3 pos)
{
	CDispLife *pDispLife = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pDispLife == NULL)
	{
		pDispLife = new CDispLife(pos);

		pDispLife->Init();

		//m_pDispLife = pDispLife;
	}

	return pDispLife;
}

//===========================================================
//����������
//===========================================================
HRESULT CDispLife::Init(void)
{
	m_nIdxTexture = -1;

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	CObject2D::Init();
	
	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CDispLife::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CDispLife::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	float nLife = (float)pPlayer->GetLife();

	nLife = nLife * 33.0f;

	CObject2D::Update();

	CObject2D::SetVtxLife(pos, 300.0f, 45.0f, nLife);
}

//===========================================================
//�`�揈��
//===========================================================
void CDispLife::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject2D::Draw();
}

//===========================================================
//���C�t���ݒ�
//===========================================================
//int CDispLife::SetDispLife(void)
//{
//	int nCntDispLife = -1;
//
//	for (int nCount = 0; nCount < MAX_DISPLIFE; nCount++)
//	{
//		if (m_apObject2D[nCount] == NULL)
//		{
//			m_apObject2D[nCount] = CDispLife::Create({ 250.0f,70.0f,0.0f });
//
//			nCntDispLife = nCount;
//			break;
//		}
//	}
//
//	return nCntDispLife;
//}