//===============================================================
//
// �^�C�g��UI����[titleUI.cpp]
// Author �匴�叫
//
//===============================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "titleUI.h"
#include "fade.h"

//===============================================================
//�R���X�g���N�^
//===============================================================
CTitleUI::CTitleUI()
{
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_colA = 0.0f;
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CTitleUI::~CTitleUI()
{
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CTitleUI * CTitleUI::Create(D3DXVECTOR3 pos)
{
	CTitleUI *pGameUI = NULL;

	if (pGameUI == NULL)
	{
		pGameUI = new CTitleUI;

		pGameUI->SetPos(&pos);
		pGameUI->Init();
	}

	return pGameUI;
}

//===============================================================
//����������
//===============================================================
HRESULT CTitleUI::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//����������
	CObject2D::Init();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\press.png"));

	m_colA = 0.007f;

	return S_OK;
}

//===============================================================
//�I������
//===============================================================
void CTitleUI::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===============================================================
//�X�V����
//===============================================================
void CTitleUI::Update(void)
{
	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	if (m_col.a >= 1.0f)
	{
		m_colA *= -1.0f;
	}
	
	if (m_col.a <= 0.0f)
	{
		m_colA *= -1.0f;
	}

	m_col.a += m_colA;

	SetVtxUI(pos, 200.0f, 50.0f, m_col);
}

//===============================================================
//�`�揈��
//===============================================================
void CTitleUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�`�揈��
	CObject2D::Draw();
}