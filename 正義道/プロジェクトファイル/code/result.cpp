//===========================================================
//
// ���U���g����[result.cpp]
// Author �匴�叫
//
//===========================================================
#include "result.h"
#include "texture.h"
#include "game.h"
#include "field.h"
#include "debugproc.h"
#include "renderer.h"
#include "sky.h"
#include "input.h"
#include "ranking.h"
#include "score.h"
#include "rankinglogo.h"
#include "sound.h"
#include "player.h"
#include "tutorialAI.h"

//===========================================================
//�R���X�g���N�^
//===========================================================
CResult::CResult()
{
	m_apObject2D = NULL;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CResult::~CResult()
{

}

//===========================================================
//����
//===========================================================
CResult *CResult::Create(void)
{
	CResult *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CResult;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//����������
//===========================================================
HRESULT CResult::Init(void)
{
	//�e�N�X�`���̏����擾
	CTexture *pTexture = CManager::GetTexture();

	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�t�B�[���h�𐶐�
	CField::Create();

	//��𐶐�
	CSky::Create({ 0.0f,0.0f,0.0f });

	//�`���[�g���A���擱��AI
	CTutorialAI::Create({ 780.0f, 0.0f, -1300.0f }, { 0.0f, D3DX_PI, 0.0f });

	CPlayer::Create({ -150.0f, 0.0f, 50.0f });

	CRankinglogo::Create({SCREEN_WIDTH * 0.5f, 50.0f, 0.0f});

	CRanking::Create();

	CRanking::SetRanking(CScore::Getscore());

	if (m_apObject2D == NULL)
	{
		m_apObject2D = new CObject2D({ 250.0f, 380.0f, 0.0f });

		m_apObject2D->SetIdxTex(pTexture->Regist("data\\TEXTURE\\rank.png"));

		m_apObject2D->Init();
	}

	pSound->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CResult::Uninit(void)
{
	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	if (m_apObject2D != NULL)
	{
		m_apObject2D->Uninit();

		m_apObject2D = NULL;
	}

	CObject::ReleaseAll();
}

//===========================================================
//�X�V����
//===========================================================
void CResult::Update(void)
{
	if (m_apObject2D != NULL)
	{
		D3DXVECTOR3 pos = m_apObject2D->Getpos();
		m_apObject2D->Update();

		m_apObject2D->SetVtxItemSlot(pos, 80.0f, 250.0f);
	}

	//���ׂẴI�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\n�V�[���F���U���g");
}

//===========================================================
//�`�揈��
//===========================================================
void CResult::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_apObject2D != NULL)
	{
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		m_apObject2D->Draw();
	}
}