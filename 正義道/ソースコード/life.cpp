//=============================================================================
//
// �V���h�E���� [shadow.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "life.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "enemyweak.h"
#include "enemy.h"

//�ÓI�����o�ϐ�
CBillBoard *CLife::m_Life[MAX_SHADOW] = {};

//================================================================
//�R���X�g���N�^
//================================================================
CLife::CLife()
{
	m_nIdxTexture = -1;
}

//================================================================
//�R���X�g���N�^
//================================================================
CLife::CLife(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nIdxTexture = -1;
}

//================================================================
//�f�X�g���N�^
//================================================================
CLife::~CLife()
{

}

//================================================================
//�f�X�g���N�^
//================================================================
CLife *CLife::Create(D3DXVECTOR3 pos)
{
	CLife *pLife = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pLife == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pLife = new CLife(pos);

			//����������
			pLife->Init();
		}
	}

	return pLife;
}

//================================================================
//���C�t�̏���������
//================================================================
HRESULT CLife::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = -1;

	CBillBoard::Init();

	return S_OK;
}

//================================================================
//���C�t�̏I������
//================================================================
void CLife::Uninit(void)
{
	CBillBoard::Uninit();
}

//================================================================
//���C�t�̍X�V����
//================================================================
void CLife::Update(void)
{
	//�G�̏��擾
	CEnemy **pEnemy = CEnemy::GetEnemy();

	D3DXVECTOR3 pos = Getpos();

	int nNumEnemy = CEnemyManager::GetNumAll();

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		if (pEnemy[nCount] != NULL)
		{
			float life = (float)pEnemy[nCount]->GetLife();

			CBillBoard::SetVtxLife(pos, 20.0f, 5.0f, life);
		}
	}

	

	CBillBoard::Update();

	
}

//================================================================
//���C�t�̕`�揈��
//================================================================
void CLife::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CBillBoard::Draw();
}

//================================================================
//���C�t�̐ݒ菈��
//================================================================
int CLife::Set(D3DXVECTOR3 pos)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (m_Life[nCount] == NULL)
		{
			m_Life[nCount] = Create(pos);

			nCntShadow = nCount;

			break;
		}
	}

	return nCntShadow;
}

//================================================================
//�ʒu�X�V
//================================================================
void CLife::SetPosition(int nIdxShadow, D3DXVECTOR3 pos)
{
	CLife::SetPos(&pos);
}