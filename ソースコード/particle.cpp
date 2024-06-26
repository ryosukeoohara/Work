//===========================================================
//
// �p�[�e�B�N������[particl.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect.h"
#include "effect3D.h"
#include "particle.h"
#include <time.h>

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int BLOOD = 1;        // ���t�̃p�[�e�B�N��
	const int GROUND = 20;      // �y���̃p�[�e�B�N��
	const int CIRCLE = 314;     // �~�`�̃p�[�e�B�N��
	const float SPEED = 10.0f;  // �ړ���
}

//===========================================================
//�ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = nullptr;

//===========================================================
// �R���X�g���N�^
//===========================================================
CParticle::CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 0;
	m_nLife = 0;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CParticle::CParticle(D3DXVECTOR3 pos, TYPE type)
{
	m_pos = pos;
	m_fRadius = 0;
	m_nLife = 0;
	m_type = type;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CParticle::~CParticle()
{

}

//===========================================================
// ��������
//===========================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, TYPE type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CParticle *pParticl = NULL;

	if (pParticl == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pParticl = new CParticle(pos, type);

		//����������
		pParticl->Init();
	}
	
	return pParticl;
}

//===========================================================
// ����������
//===========================================================
HRESULT CParticle::Init(void)
{
	switch (m_type)
	{
	case TYPE_GROUND:
		Ground();
		break;

	case TYPE_BLOOD:
		Blood();
		break;

	case TYPE_SMOOK:
		Smook();
		break;

	case TYPE_CIRCLE:
		Circle();
		break;

	case TYPE_GLASS:
		Glass();
		break;
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CParticle::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//===========================================================
// �X�V����
//===========================================================
void CParticle::Update(void)
{
	
}

//===========================================================
// �`�揈��
//===========================================================
void CParticle::Draw(void)
{
	
}

//===========================================================
// �`�揈��
//===========================================================
void CParticle::Move(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		//CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 0.8f, 1.0f, 1.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_NONE);
	}
}

//===========================================================
// ���t
//===========================================================
void CParticle::Blood(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < BLOOD; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

 		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BIKE, "data\\MODEL\\bike\\tier.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BIKE, "data\\MODEL\\bike\\basket.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BIKE, "data\\MODEL\\bike\\handle.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BIKE, "data\\MODEL\\bike\\pedal.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BIKE, "data\\MODEL\\bike\\tier.x");
	}
}

//===========================================================
// �y��
//===========================================================
void CParticle::Ground(void)
{
	float fRot = 0.0f;

	for (int nCnt = 0; nCnt < GROUND; nCnt++)
	{
		// �����ݒ�
		fRot = ((float)nCnt / (D3DX_PI * 1.0f));

		// �ړ��ʐݒ�
		m_move.x = sinf(fRot) * SPEED;
		m_move.z = cosf(fRot) * SPEED;

		CEffect::Create({ m_pos.x, 0.0f, m_pos.z }, { m_move.x, 0.0f, m_move.z }, { 1.0f, 1.0f, 1.0f, 0.8f }, 50.0f, 30, CEffect::TYPE_GROUND);
	}
}

//===========================================================
// �� 
//===========================================================
void CParticle::Smook(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		int nLife = 0;
		float fRadius = 0;
		D3DXVECTOR3 move = {};
		D3DXCOLOR col = {};

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * 0.09f;
		move.y = 20.0f * 0.05f;
		move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * 0.09f;

		//�F�̐ݒ�
		col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//���a�̐ݒ�
		fRadius = 10.0f;

		//�����̐ݒ�
		nLife = 500;

		CEffect::Create(m_pos, move, col, fRadius, nLife, CEffect::TYPE_SMOOK);
	}
}

//===========================================================
// �~�`
//===========================================================
void CParticle::Circle(void)
{
	
}

//===========================================================
// �K���X�̔j��
//===========================================================
void CParticle::Glass(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		int nLife = 0;
		float fRadius = 0;
		D3DXVECTOR3 move = {};
		D3DXVECTOR3 rot = {};

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 50) / 100.0f * 8.0f) * 5.0f;
		move.y = 10.0f;
		move.z = cosf((float)(rand() % 50) / 100.0f * 8.0f);

		if (move.x < 0.0f)
		{
			move.x *= -1.0f;
		}

		//�����̐ݒ�
		nLife = 25;

		CEffect3D::Create(D3DXVECTOR3(m_pos.x + 30.0f, m_pos.y, m_pos.z), move, rot, nLife, CEffect3D::TYPE_GLASS, "data\\MODEL\\glass.x");
	}
}