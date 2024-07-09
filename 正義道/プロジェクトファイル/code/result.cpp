//===========================================================
//
// リザルト処理[result.cpp]
// Author 大原怜将
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
//コンストラクタ
//===========================================================
CResult::CResult()
{
	m_apObject2D = NULL;
}

//===========================================================
//デストラクタ
//===========================================================
CResult::~CResult()
{

}

//===========================================================
//生成
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
//初期化処理
//===========================================================
HRESULT CResult::Init(void)
{
	//テクスチャの情報を取得
	CTexture *pTexture = CManager::GetTexture();

	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	//フィールドを生成
	CField::Create();

	//空を生成
	CSky::Create({ 0.0f,0.0f,0.0f });

	//チュートリアル先導役AI
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
//終了処理
//===========================================================
void CResult::Uninit(void)
{
	//サウンドを取得
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
//更新処理
//===========================================================
void CResult::Update(void)
{
	if (m_apObject2D != NULL)
	{
		D3DXVECTOR3 pos = m_apObject2D->Getpos();
		m_apObject2D->Update();

		m_apObject2D->SetVtxItemSlot(pos, 80.0f, 250.0f);
	}

	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\nシーン：リザルト");
}

//===========================================================
//描画処理
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