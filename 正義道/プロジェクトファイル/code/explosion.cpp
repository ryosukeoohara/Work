//===========================================================
//
// �|���S�����o�����[explosion.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "explosion.h"

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CExplosion::CExplosion()
{
	m_nLife = 0;       //����
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CExplosion::CExplosion(D3DXVECTOR3 pos)
{
	SetPos(&pos);  //�ʒu�ݒ�
	m_nLife = 0;       //����
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
}

//================================================================
//�f�X�g���N�^
//================================================================
CExplosion::~CExplosion()
{

}

//================================================================
//��������
//================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pExplosion = new CExplosion(pos);

		//�e�N�X�`�����o�C���h
		pExplosion->BindTexture(m_pTexture);

		//����������
		pExplosion->Init();
	}

	return pExplosion;
}

//================================================================
//�����̏���������
//================================================================
HRESULT CExplosion::Init(void)
{
	//����������
	CObject2D::Init();

	//��ނ̐ݒ�
	SetType(TYPE_EXPLOSION);

	//�����̎���
	m_nLife = EXPLOSIONLIFE;

	return S_OK;
}

//================================================================
//�����̏I������
//================================================================
void CExplosion::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//================================================================
//�����̍X�V����
//================================================================
void CExplosion::Update(void)
{
	//�X�V����
	CObject2D::Update();

	//���������炷
	m_nLife--;

	if (m_nLife < 0)
	{//�������Ȃ��Ȃ�����

	    //�I������
		Uninit();
	}
}

//================================================================
//�����̕`�揈��
//================================================================
void CExplosion::Draw(void)
{
	//�`�揈��
	CObject2D::Draw();
}

//================================================================
//�e�N�X�`���̐���(�ǂݍ���)
//================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture
	);

	return S_OK;
}

//================================================================
//�e�N�X�`���̔j��
//================================================================
void CExplosion::UnLoad(void)
{
	//�e�N�X�`���̏���
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}