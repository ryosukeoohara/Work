//===========================================================
//
// �|���S�����o�����[dispdetection.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "dispdetection.h"
#include "texture.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const float HEIGHT = 100.0f;  // ����
	const float WIDHT = 100.0f;   // ����
	const char* TEX_NAME = "data\\TEXTURE\\redcircle.png";
}

//================================================================
// �ÓI�����o�ϐ��錾
//================================================================
CDISPDETECTION *CDISPDETECTION::m_DispDetection = NULL;

//================================================================
// �R���X�g���N�^
//================================================================
CDISPDETECTION::CDISPDETECTION()
{
	m_nIdxTexture = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
// �R���X�g���N�^
//================================================================
CDISPDETECTION::CDISPDETECTION(D3DXVECTOR3 pos)
{
	m_nIdxTexture = 0;
	SetPos(&pos);
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
// �f�X�g���N�^
//================================================================
CDISPDETECTION::~CDISPDETECTION()
{

}

//================================================================
// ��������
//================================================================
CDISPDETECTION *CDISPDETECTION::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CDISPDETECTION *pFrame = NULL;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pFrame == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pFrame = new CDISPDETECTION(pos);

			//����������
			pFrame->Init();

			m_DispDetection = pFrame;
		}
	}

	return pFrame;
}

//================================================================
// ����������
//================================================================
HRESULT CDISPDETECTION::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist(TEX_NAME);

	CObject3D::Init();

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CDISPDETECTION::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================================
// �X�V����
//================================================================
void CDISPDETECTION::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	m_col.a = 0.5f;

	CObject3D::SetVtxCircle(WIDHT, HEIGHT, m_col);

	CObject3D::Update();
}

//================================================================
// �`�揈��
//================================================================
void CDISPDETECTION::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (pTexture == nullptr || pRenderer == nullptr || pDevice == nullptr)
		return;

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}