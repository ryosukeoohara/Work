//===========================================================
//
//�|���S�����o�����[field.cpp]
//Author �匴�叫
//
//===========================================================
#include "wall.h"
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//===========================================================
//�R���X�g���N�^
//===========================================================
CWall::CWall()
{
	m_nIdxTexture = 0;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CWall::~CWall()
{

}

//===========================================================
//�N���G�C�g
//===========================================================
CWall *CWall::Create(void)
{
	//�n�ʂ̃|�C���^
	CWall *pWall = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pWall == NULL)
		{//�g�p����Ă��Ȃ�������

			//�I�u�W�F�N�g�𐶐�
			pWall = new CWall;

			pWall->Init();
		}
	}

	return pWall;
}

//===========================================================
//����������
//===========================================================
HRESULT CWall::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tora.png");

	/*for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		if (m_Object3D[nCount] != NULL)
		{
			m_Object3D[nCount]->Create()
		}
	}*/

	//����������
	CObject3D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CWall::Uninit(void)
{
	//�I������
	CObject3D::Uninit();
}

//===========================================================
//�X�V����
//===========================================================
void CWall::Update(void)
{
	//�X�V����
	CObject3D::Update();
	CObject3D::SetVtxField();
}

//===========================================================
//�`�揈��
//===========================================================
void CWall::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`�揈��
	CObject3D::Draw();
}