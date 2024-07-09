//===========================================================
//
// �Ռ��g����[impact.cpp]
// Author �匴�叫
//
//===========================================================
#include "impact.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//�}�N����`
#define HEIGHT   (20.0f)
#define WIDHT    (20.0f)

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CImpact::m_pTexture = NULL;

//===========================================================
//�R���X�g���N�^
//===========================================================
CImpact::CImpact()
{
	m_SizeX = 0.0f;
	m_SizeZ = 0.0f;
	m_nIdxTexture = -1;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CImpact::CImpact(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_SizeX = 0.0f;
	m_SizeZ = 0.0f;
	m_nIdxTexture = -1;
	m_type = type;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CImpact::~CImpact()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CImpact *CImpact::Create(D3DXVECTOR3 pos, TYPE type)
{
	CImpact *pItemSlot = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CImpact(pos, type);

		switch (type)
		{
		case TYPE_NONE:

			pItemSlot->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\impact.png");
			break;
		
		default:
			break;
		}

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//����������
//===========================================================
HRESULT CImpact::Init(void)
{
	CObject3D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CImpact::Uninit(void)
{
	CObject3D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CImpact::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject3D::Update();

	CObject3D::SetVtxCircle(WIDHT + m_SizeX, HEIGHT + m_SizeZ, { 1.0f,1.0f,1.0f,1.0f });

	if (m_SizeX < 100.0f && m_SizeZ < 100.0f)
	{
		m_SizeX += 5.0f;
		m_SizeZ += 5.0f;
	}
	else
	{
		Uninit();

		return;
	}
}

//===========================================================
//�`�揈��
//===========================================================
void CImpact::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}