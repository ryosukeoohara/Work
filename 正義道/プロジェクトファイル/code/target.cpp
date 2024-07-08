//===========================================================
//
//�|���S�����o�����[title.cpp]
//Author �匴�叫
//
//===========================================================
#include "target.h"
#include "texture.h"
#include "game.h"
#include "field.h"
#include "debugproc.h"
#include "renderer.h"
#include "titlelogo.h"
#include "camera.h"
#include "player.h"

//===========================================================
//�ÓI�����o�ϐ�
//===========================================================
CNumber *CTarget::m_apNumber[MAX_NUMBER] = {};
CNumber *CTarget::m_apNumCount[MAX_NUMBER] = {};
CTarget::TYPE CTarget::m_type = TYPE_NONE;

//===========================================================
//�R���X�g���N�^
//===========================================================
CTarget::CTarget()
{
	m_nIdxTexture = -1;
}

//===========================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CTarget::CTarget(TYPE type, D3DXVECTOR3 pos)
{
	m_nIdxTexture = -1;
	m_type = type;
	SetPos(&pos);
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CTarget::~CTarget()
{

}

//===========================================================
//����
//===========================================================
CTarget *CTarget::Create(TYPE type, D3DXVECTOR3 pos)
{
	CTarget *Target = NULL;

	if (Target == NULL)
	{
		Target = new CTarget(type, pos);

		Target->Init();
	}

	return Target;
}

//===========================================================
//����������
//===========================================================
HRESULT CTarget::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//����������
	CObject2D::Init();

	switch (m_type)
	{
	case CTarget::TYPE_NONE:    //�Ȃ�
		break;

	case CTarget::TYPE_FIRST:   //�ŏ��̖ڕW

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim000.png"));
		break;

	case CTarget::TYPE_SECOND:  //��ڂ̖ڕW

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim001.png"));
		break;

	case CTarget::TYPE_MAX:
		break;

	default:
		break;
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 1090.0f + 50.0f * nCount, 235.0f, 0.0f });

			m_apNumber[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			//����������
			m_apNumber[nCount]->Init();

			m_apNumber[nCount]->m_Number = 0;
		}
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumCount[nCount] == NULL)
		{
			m_apNumCount[nCount] = CNumber::Create({ 1220.0f + 50.0f * nCount, 235.0f, 0.0f });

			m_apNumCount[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			m_apNumCount[nCount]->m_Number = 0;
		}
	}
	
	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTarget::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//�I������
			m_apNumber[nCount]->Uninit();

			m_apNumber[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumCount[nCount] != NULL)
		{
			//�I������
			m_apNumCount[nCount]->Uninit();

			m_apNumCount[nCount] = NULL;
		}
	}
}

//===========================================================
//�X�V����
//===========================================================
void CTarget::Update(void)
{
	//�G�̎��񂾐����擾
	int EnemyDieCount = CEnemyManager::GetCounter();

	//�����G�̑������擾
	int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

	//�����̑������擾
	int nNumBoss = CEnemyManager::GetNumEneMedBoss();

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//�v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();

	//�ʒu���
	D3DXVECTOR3 pos = Getpos();

	//�X�V����
	CObject2D::Update();

	CObject2D::SetVtxTarget(pos, 180.0f, 70.0f);

	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_apNumber[nCount] != NULL)
			{
				m_apNumber[0]->m_Number = 0;
				m_apNumber[1]->m_Number = EnemyDieCount;

				//�X�V����
				m_apNumber[nCount]->SetVtxCounter({ 260.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
			}
		}

		switch (m_type)
		{
		case CTarget::TYPE_NONE:    //�Ȃ�
			break;

		case CTarget::TYPE_FIRST:   //�ŏ��̖ڕW

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					m_apNumCount[0]->m_Number = 0;
					m_apNumCount[1]->m_Number = nNumEnemyWeak;

					//�X�V����
					m_apNumCount[nCount]->SetVtxCounter({ 350.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
				}
			}

			break;

		case CTarget::TYPE_SECOND:  //��ڂ̖ڕW

			SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim001.png"));

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					m_apNumCount[0]->m_Number = 0;
					m_apNumCount[1]->m_Number = nNumBoss;

					//�X�V����
					m_apNumCount[nCount]->SetVtxCounter({ 350.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
				}
			}

			break;

		case CTarget::TYPE_FINAL:  //�Ō�̖ڕW

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumber[nCount] != NULL)
				{
					//�I������
					m_apNumber[nCount]->Uninit();

					m_apNumber[nCount] = NULL;
				}
			}

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					//�I������
					m_apNumCount[nCount]->Uninit();

					m_apNumCount[nCount] = NULL;
				}
			}

			SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim002.png"));

			break;

		case CTarget::TYPE_MAX:
			break;

		default:
			break;
		}
	}
}

//===========================================================
//�`�揈��
//===========================================================
void CTarget::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CCamera *pCamera = CManager::GetCamera();

	//�v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		//�`�揈��
		CObject2D::Draw();

		if (m_type != TYPE_FINAL)
		{
			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumber[nCount] != NULL)
				{
					//�`�揈��
					//m_apNumber[nCount]->Draw();
				}
			}
		}
	}
}