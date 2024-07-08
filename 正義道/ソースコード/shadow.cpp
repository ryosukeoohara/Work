//=============================================================================
//
// �V���h�E���� [shadow.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "shadow.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "enemyweak.h"

//�ÓI�����o�ϐ�
CObject3D *CShadow::m_Shadow[MAX_SHADOW] = {};

//================================================================
//�R���X�g���N�^
//================================================================
CShadow::CShadow()
{
	m_nIdxTexture = -1;
}

//================================================================
//�R���X�g���N�^
//================================================================
CShadow::CShadow(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nIdxTexture = -1;
}

//================================================================
//�f�X�g���N�^
//================================================================
CShadow::~CShadow()
{

}

//================================================================
//�f�X�g���N�^
//================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow *pShadow = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pShadow == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pShadow = new CShadow(pos);

			//����������
			pShadow->Init();
		}
	}

	return pShadow;
}

//================================================================
//�V���h�E�̏���������
//================================================================
HRESULT CShadow::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\shadow000.jpg");

	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//����������
	//		m_Shadow[nCount]->Init();
	//	}
	//}
	
	CObject3D::Init();

	return S_OK;
}

//================================================================
//�V���h�E�̏I������
//================================================================
void CShadow::Uninit(void)
{
	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//�I������
	//		m_Shadow[nCount]->Uninit();
	//	}
	//}

	CObject3D::Uninit();
}

//================================================================
//�V���h�E�̍X�V����
//================================================================
void CShadow::Update(void)
{
	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//�X�V����
	//		m_Shadow[nCount]->Update();

	//		m_Shadow[nCount]->SetShadowPosition({ 0.0f,0.0f,0.0f }, 20.0f, 20.0f);
	//	}
	//}

	CObject3D::Update();

	CObject3D::SetShadowPosition({ 0.0f,0.0f,0.0f }, 20.0f, 20.0f);
}

//================================================================
//�V���h�E�̕`�揈��
//================================================================
void CShadow::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================
//�V���h�E�̐ݒ菈��
//================================================================
int CShadow::Set(D3DXVECTOR3 pos)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (m_Shadow[nCount] == NULL)
		{
			m_Shadow[nCount] = Create(pos);

			nCntShadow = nCount;

			break;
		}
	}

	return nCntShadow;
}

//================================================================
//�ʒu�X�V
//================================================================
void CShadow::SetPosition(int nIdxShadow, D3DXVECTOR3 pos)
{
	CShadow::SetPos(&pos);
}