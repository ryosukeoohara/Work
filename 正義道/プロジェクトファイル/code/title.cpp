//===========================================================
//
//ポリゴンを出すやつ[title.cpp]
//Author 大原怜将
//
//===========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "field.h"
#include "debugproc.h"
#include "renderer.h"
#include "titlelogo.h"
#include "sky.h"
#include "sound.h"
#include "player.h"
#include "titleUI.h"
#include "tutorialAI.h"

//===========================================================
//コンストラクタ
//===========================================================
CTitle::CTitle()
{
	for (int nCount = 0; nCount < MAX_TITLEOBJ; nCount++)
	{
		m_apObject2D[nCount] = NULL;
		m_apObject3D[nCount] = NULL;
	}
}

//===========================================================
//デストラクタ
//===========================================================
CTitle::~CTitle()
{

}

//===========================================================
//生成
//===========================================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTitle;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CTitle::Init(void)
{
	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	//フィールドを生成
	CField::Create();

	//チュートリアル先導役AI
	CTutorialAI::Create({ 150.0f, 0.0f, 50.0f }, { 0.0f, D3DX_PI, 0.0f });

	CPlayer::Create({ -150.0f, 0.0f, 50.0f });

	//空を生成
	CSky::Create({ 0.0f,0.0f,0.0f });

	//タイトルロゴを生成
	CTitlelogo::Create({ SCREEN_WIDTH * 0.5f, 200.0f, 0.0f });

	CTitleUI::Create({ SCREEN_WIDTH * 0.5f, 600.0f, 0.0f });

	pSound->Play(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTitle::Uninit(void)
{
	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CTitle::Update(void)
{
	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\nシーン：タイトル");
}

//===========================================================
//描画処理
//===========================================================
void CTitle::Draw(void)
{
	
}