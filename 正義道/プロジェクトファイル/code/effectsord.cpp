//===========================================================
//
// �a���G�t�F�N�g����[effectsord.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "effectsord.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "texture.h"
#include "enemyBoss.h"
#include "debugproc.h"
#include "enemymanager.h"

//================================================================
//�R���X�g���N�^
//================================================================
CEffectSword::CEffectSword()
{
	m_DispCounter = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nIdxTexture = -1;
}

//================================================================
//�R���X�g���N�^
//================================================================
CEffectSword::CEffectSword(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);
	SetRot(&rot);
	m_DispCounter = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nIdxTexture = -1;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEffectSword::~CEffectSword()
{

}

//================================================================
//��������
//================================================================
CEffectSword *CEffectSword::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//�I�u�W�F�N�g2D�̃|�C���^
	CEffectSword *pEffectSword = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEffectSword == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pEffectSword = new CEffectSword(pos, rot);

			//����������
			pEffectSword->Init();
		}
	}

	return pEffectSword;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CEffectSword::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\zangeki.png");

	CObject3D::Init();

	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CEffectSword::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CEffectSword::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_col.a < 1.0f)
	{
		m_col.a += 0.1f;
	}
	else
	{
		int n = 0;
	}
	
	SetVtxEffectSword(150.0f, 150.0f, m_col);

	CObject3D::Update();

	m_DispCounter++;

	if (m_DispCounter >= 20)
	{
		Uninit();
	}
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CEffectSword::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////���u�����f�B���O�����Z���v�ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();

	////���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}