//===========================================================
//
// ����Ō��Ă���l�̊Ǘ�[audiencemanager.cpp]
// Author �匴�叫
//
//===========================================================
#include "audiencemanager.h"
#include "audience.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int FRONT_AUDIENCE = 50;  // ���ʂ̌��Ă���l�̐�
	const int BACK_AUDIENCE = 45;   // �w�ʂ̌��Ă���l�̐�
	const int LIFT_AUDIENCE = 20;   // ���̌��Ă���l�̐�

	const char* MODELNAME[CAudience::TYPE_MAX] =
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
CAudienceManager::CAudienceManager()
{

}

//================================================================
// �f�X�g���N�^
//================================================================
CAudienceManager::~CAudienceManager()
{

}

//================================================================
// ����������
//================================================================
HRESULT CAudienceManager::Init(void)
{
	// ����
	for (int i = 0; i < FRONT_AUDIENCE; i++)
	{
		int nModelFileIdx = rand() % TYPE_MAX;
		float fPosX = rand() % 21;
		float fPosZ = rand() % 101;
		
		CAudience* pAudience = CAudience::Create(D3DXVECTOR3((800.0f - i * 35.0f) + fPosX, 0.0f, -1000.0f + fPosZ), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODELNAME[nModelFileIdx]);
	}

	// �w��
	for (int i = 0; i < BACK_AUDIENCE; i++)
	{
		int nModelFileIdx = rand() % TYPE_MAX;
		float fPosX = rand() % 21;
		float fPosZ = rand() % 101;

		CAudience* pAudience = CAudience::Create(D3DXVECTOR3((-800.0f + i * 35.0f) + fPosX, 0.0f, 1050.0f + fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELNAME[nModelFileIdx]);
	}

	// ��
	for (int i = 0; i < LIFT_AUDIENCE; i++)
	{
		int nModelFileIdx = rand() % TYPE_MAX;
		float fPosX = rand() % 21;
		float fPosZ = rand() % 101;

		CAudience* pAudience = CAudience::Create(D3DXVECTOR3(850.0f + fPosX, 0.0f, (900.0f - i * 35.0f) + fPosZ), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), MODELNAME[nModelFileIdx]);
	}

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CAudienceManager::Uninit(void)
{

}

//================================================================
// �X�V����
//================================================================
void CAudienceManager::Update(void)
{

}

//================================================================
// ��������
//================================================================
CAudienceManager* CAudienceManager::Create(void)
{
	CAudienceManager* pAudienceManager = nullptr;
	pAudienceManager = new CAudienceManager;

	if (pAudienceManager != nullptr)
	{
		pAudienceManager->Init();
	}

	return pAudienceManager;
}
