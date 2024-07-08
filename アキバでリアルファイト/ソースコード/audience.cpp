//===========================================================
//
// ����Ō��Ă�l[audience.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "audience.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"

//================================================================
// �ÓI�����o�ϐ�
//================================================================
CAudience* CAudience::m_pTop = nullptr;
CAudience* CAudience::m_pCur = nullptr;

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int JUMPWAITTIME = 60;  // �ĂуW�����v�ł���悤�ɂȂ�܂ł̎���
	const float JUMP = 8.0f;      // �W�����v�̍���
	const float GRAVITY = -1.0f;  // �d��

	const char *MODELNAME[CAudience::TYPE_MAX] =
	{
		"data\\MODEL\\crowd_02.x",
		"data\\MODEL\\crowd_02.x",
		"data\\MODEL\\crowd_03.x",
		"data\\MODEL\\crowd_04.x",
	};  // ���f���̃t�@�C���l�[��
}

//================================================================
// �R���X�g���N�^
//================================================================
CAudience::CAudience()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nJumpWaitTime = 0;
	m_bJump = false;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;
		m_pCur = this;
	}
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CAudience::CAudience(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename) : CObjectX(filename)
{
	SetPosition(pos);
	SetRotition(rot);

	m_pos = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nJumpWaitTime = 0;
	m_bJump = false;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;
		m_pCur = this;
	}
}

//================================================================
// �f�X�g���N�^
//================================================================
CAudience::~CAudience()
{

}

//================================================================
// ��������
//================================================================
CAudience *CAudience::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CAudience *pAudience = nullptr;

	if (pAudience == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pAudience = new CAudience();

		//����������
		pAudience->Init();
	}
	
	return pAudience;
}

//================================================================
// ��������
//================================================================
CAudience* CAudience::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CAudience* pAudience = nullptr;

	if (pAudience == nullptr)
	{
		// ����
		pAudience = new CAudience(pos, rot, filename);

		// ����������
		pAudience->Init();
	}
	
	return pAudience;
}

//================================================================
// ����������
//================================================================
HRESULT CAudience::Init(void)
{
	CObjectX::Init();

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CAudience::Uninit(void)
{
	CAudience* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CAudience* pObjectNext = pObject->m_pNext;

		CObjectX::Uninit();
		pObject = nullptr;

		pObject = pObjectNext;
	}
}

//================================================================
// �X�V����
//================================================================
void CAudience::Update(void)
{
	CObjectX::Update();

	// �d�͂�^����
	m_move.y += GRAVITY;

	if (m_bJump == false)
	{// �W�����v���Ă��Ȃ��Ƃ�

		int i = rand() % 3;
		

		if (i == 1)
		{
			float fjump = (rand() % 31 - 10) * 0.1f;
			// �W�����v�����čĂуW�����v�ł���܂ł̎��Ԃ�ݒ�
			m_bJump = true;
			m_move.y = JUMP + fjump;
			m_nJumpWaitTime = JUMPWAITTIME;
		}
	}

	m_pos += m_move;
	
	// �n�ʂɂ߂荞�܂Ȃ��悤��
	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
	}

	// �ĂуW�����v�ł���悤�ɂȂ�܂ŃJ�E���g
	if (m_bJump == true)
	{
		m_nJumpWaitTime--;
	}

	// 0�ɂȂ�����ĂуW�����v�ł���悤�ɂ���
	if (m_nJumpWaitTime <= 0)
	{
		m_bJump = false;
	}

	// �ʒu�ݒ�
	SetPosition(m_pos);
}

//================================================================
// �`�揈��
//================================================================
void CAudience::Draw(void)
{
	CObjectX::Draw();
}