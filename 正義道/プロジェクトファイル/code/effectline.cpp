//===========================================================
//
// ���ڐ��̏���[bg.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "effectline.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "texture.h"

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 CEffectLine::m_pTexture = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CEffectLine::CEffectLine()
{
	m_nCounter = 0;
	m_nIdxTexture = -1;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEffectLine::~CEffectLine()
{

}

//================================================================
//��������
//================================================================
CEffectLine *CEffectLine::Create(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//�I�u�W�F�N�g2D�̃|�C���^
	CEffectLine *pEffectLine = NULL;

	if (pEffectLine == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pEffectLine = new CEffectLine;

		//����������
		pEffectLine->Init();
	}

	return pEffectLine;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CEffectLine::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\syutyu.png"));

	CObject2D::Init();

	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CEffectLine::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CEffectLine::Update(void)
{
	CObject2D::Update();

	SetVtxEffectLine();

	m_nCounter++;

	if (m_nCounter >= 120)
	{
		Uninit();
	}
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CEffectLine::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();
}