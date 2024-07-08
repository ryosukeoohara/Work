//===========================================================
//
// �X�R�A����[score.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "input.h"
#include "input.h"
#include "texture.h"
#include "game.h"
#include "time.h"

namespace
{
	const int NUM_SCORE = 8;  // �X�R�A�̌���
}

//===========================================================
// �ÓI�����o�ϐ��錾
//===========================================================
CNumber *CScore::m_apNumber[NUM_SCORE] = {};
int CScore::m_nScore = 0;

//===========================================================
// �R���X�g���N�^
//===========================================================
CScore::CScore()
{
	m_nScore = 0;  //�X�R�A
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CScore::CScore(D3DXVECTOR3 pos)
{
	m_pos = pos;  //�ʒu
	SetPosition(pos);
	m_nScore = 0;  //�X�R�A
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CScore::~CScore()
{

}

//===========================================================
// ��������
//===========================================================
CScore *CScore::Create(void)
{
	// �X�R�A�̃|�C���^
	CScore *pScore = nullptr;

	if (pScore == nullptr)
	{
		// ����
		pScore = new CScore();

		//����������
		pScore->Init();
	}
	
	return pScore;
}

//===========================================================
// ����������
//===========================================================
HRESULT CScore::Init(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 800.0f + 50.0f * nCount, 50.0f, 0.0f });

			m_apNumber[nCount]->SetNumberType(TYPENUMBER_SCORE);

			//����������
			m_apNumber[nCount]->Init();
		}
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		// �I������
		if (m_apNumber[nCount] != nullptr)
		{
			m_apNumber[nCount]->Uninit();
			m_apNumber[nCount] = nullptr;
		}
	}

	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		// �X�V����
		if (m_apNumber[nCount] != nullptr)
			m_apNumber[nCount]->Update();
		
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CScore::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		// �`�揈��
		if (m_apNumber[nCount] != nullptr)
			m_apNumber[nCount]->Draw();
	}
}

//===========================================================
// �X�R�A���Z����
//===========================================================
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;

	m_apNumber[0]->m_Number = m_nScore % 100000000 / 10000000;
	m_apNumber[1]->m_Number = m_nScore % 10000000 / 1000000;
	m_apNumber[2]->m_Number = m_nScore % 1000000 / 100000;
	m_apNumber[3]->m_Number = m_nScore % 100000 / 10000;
	m_apNumber[4]->m_Number = m_nScore % 10000 / 1000;
	m_apNumber[5]->m_Number = m_nScore % 1000 / 100;
	m_apNumber[6]->m_Number = m_nScore % 100 / 10;
	m_apNumber[7]->m_Number = m_nScore % 10 / 1;
	
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if(m_apNumber[nCount] != nullptr)
		m_apNumber[nCount]->SetNumber(m_apNumber[nCount]->m_Number);
	}
}