//===========================================================
//
//リザルト処理[result.cpp]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "result.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "UImanager.h"
#include "ranking.h"
#include "score.h"
#include "camera.h"
#include "sky.h"
#include "map.h"

//===========================================================
//コンストラクタ
//===========================================================
CResult::CResult()
{
	
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
	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	pCamera->SetType(CCamera::TYPE_TITLE);

	//空生成
	CSky::Create({ 0.0f,0.0f,0.0f });

	//マップ生成
	CMap::Create();

	//ランキング上の見出し
	CUIManager::Create({ 400.0f, 100.0f, 0.0f }, CUIManager::TYPE_SCORE);

	//ランク表示
	CUIManager::Create({ 300.0f, 380.0f, 0.0f }, CUIManager::TYPE_RANK);

	

	//ランキングの生成
	CRanking::Create();

	//ランキング設定
	CRanking::SetRanking(CScore::Getscore());

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンド再生
	pSound->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CResult::Uninit(void)
{
	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンド停止
	pSound->Stop();

	//すべてのオブジェクト破棄
	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CResult::Update(void)
{
	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\nシーン：リザルト");
}

//===========================================================
//描画処理
//===========================================================
void CResult::Draw(void)
{
	
}