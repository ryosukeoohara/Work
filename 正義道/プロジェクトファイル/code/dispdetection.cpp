//===========================================================
//
//�|���S�����o�����[bg.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "dispdetection.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//�}�N����`
#define HEIGHT   (100.0f)  //����
#define WIDHT    (100.0f)  //��
#define MOVE     (100.0f) //�ړ�

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
CDISPDETECTION *CDISPDETECTION::m_DispDetection = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CDISPDETECTION::CDISPDETECTION()
{
	m_nIdxTexture = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
//�R���X�g���N�^
//================================================================
CDISPDETECTION::CDISPDETECTION(D3DXVECTOR3 pos)
{
	m_nIdxTexture = 0;
	SetPos(&pos);
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
//�f�X�g���N�^
//================================================================
CDISPDETECTION::~CDISPDETECTION()
{

}

//================================================================
//��������
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

			pFrame->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\redcircle.png");

			//����������
			pFrame->Init();

			m_DispDetection = pFrame;
		}
	}

	return pFrame;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CDISPDETECTION::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	CObject3D::Init();

	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CDISPDETECTION::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CDISPDETECTION::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	m_col.a = 0.5f;

	CObject3D::SetVtxCircle(WIDHT, HEIGHT, m_col);

	CObject3D::Update();
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CDISPDETECTION::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}