//===========================================================
//
//�|���S�����o�����[multiplexbg.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "bg.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "multiplexbg.h"

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 CMultiplexBg::m_pTexture[TYPETEX_MAX] = {};
CObject2D *CMultiplexBg::m_apObject2D[TYPETEX_MAX] = {};
float CMultiplexBg::m_fTexU = 0.0f;
float CMultiplexBg::m_fTexV = 0.0f;

//================================================================
//�R���X�g���N�^
//================================================================
CMultiplexBg::CMultiplexBg()
{
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
}

//================================================================
//�f�X�g���N�^
//================================================================
CMultiplexBg::~CMultiplexBg()
{

}

//================================================================
//��������
//================================================================
CMultiplexBg *CMultiplexBg::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CMultiplexBg *pMultiplexBg = NULL;

	if (pMultiplexBg == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMultiplexBg = new CMultiplexBg;

		//����������
		pMultiplexBg->Init();

		for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
		{
			if (m_pTexture[nCount] != NULL)
			{
				m_apObject2D[nCount]->BindTexture(m_pTexture[nCount]);
			}
		}
	}

	return pMultiplexBg;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CMultiplexBg::Init(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] == NULL)
		{//�g�p���Ă��Ȃ�������

			//����
			m_apObject2D[nCount] = CObject2D::Create({ 0.0f,0.0f,0.0f });

			//����������
			m_apObject2D[nCount]->Init();
		}
	}

	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CMultiplexBg::Uninit(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Uninit();

			m_apObject2D[nCount] = NULL;
		}
	}

	Release();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CMultiplexBg::Update(void)
{
	m_fTexU += 0.001f;

	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Update();
		}
	}
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CMultiplexBg::Draw(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Draw();
		}
	}
}

//================================================================
//�e�N�X�`���̐���(�ǂݍ���)
//================================================================
HRESULT CMultiplexBg::Load(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_pTexture[nCount] == NULL)
		{
			if (nCount == TYPETEX_00)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg100.png",
					&m_pTexture[nCount]);
			}

			if (nCount == TYPETEX_01)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg101.png",
					&m_pTexture[nCount]);
			}

			if (nCount == TYPETEX_02)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg102.png",
					&m_pTexture[nCount]);
			}
		}
	}

	return S_OK;
}

//================================================================
//�e�N�X�`���̔j��
//================================================================
void CMultiplexBg::UnLoad(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		//�e�N�X�`���̏���
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}