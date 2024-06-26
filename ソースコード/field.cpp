//===========================================================
//
// �t�B�[���h����[field.cpp]
// Author �匴�叫
//
//===========================================================
#include "field.h"
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CField::CField()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CField::~CField()
{
	
}

//===========================================================
// ��������
//===========================================================
CField *CField::Create(void)
{
	//�n�ʂ̃|�C���^
	CField *pField = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	if (pField == NULL)
	{//�g�p����Ă��Ȃ�������

		//�I�u�W�F�N�g�𐶐�
		pField = new CField;

		pField->Init();
	}
	
	return pField;
}

//===========================================================
// ����������
//===========================================================
HRESULT CField::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//����������
	CObject3D::Init();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CField::Uninit(void)
{
	//�I������
	CObject3D::Uninit();
}

//===========================================================
// �X�V����
//===========================================================
void CField::Update(void)
{
	//�X�V����
	CObject3D::Update();
}

//===========================================================
// �`�揈��
//===========================================================
void CField::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`�揈��
	CObject3D::Draw();
}