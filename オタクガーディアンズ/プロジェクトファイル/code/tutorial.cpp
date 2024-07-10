//===============================================================
//
//チュートリアル処理[tutorial.cpp]
// Author 大原怜将
//
//===============================================================
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "UImanager.h"
#include "fade.h"

//===============================================================
//コンストラクタ
//===============================================================
CTutorial::CTutorial()
{
	
}

//===============================================================
//デストラクタ
//===============================================================
CTutorial::~CTutorial()
{

}

//===============================================================
//クリエイト
//===============================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;

		pTutorial->Init();
	}

	return pTutorial;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CTutorial::Init(void)
{
	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//タイトルのロゴ生成
	CUIManager::Create({ 0.0f, SCREEN_HEIGHT * 0.5f, 0.0f }, CUIManager::TYPE_TUTORIAL);

	pSound->Play(CSound::SOUND_LABEL_BGM003);

	return S_OK;
}

//===============================================================
//終了処理
//===============================================================
void CTutorial::Uninit(void)
{
	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	pSound->Stop();

	//すべてのオブジェクト破棄
	CObject::ReleaseAll();
}

//===============================================================
//更新処理
//===============================================================
void CTutorial::Update(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{//ENTERキーを押したかつシーンがタイトルのとき

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをゲームに遷移
			pFade->Set(CScene::MODE_GAME);
		}
	}

	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();
}

//===============================================================
//描画処理
//===============================================================
void CTutorial::Draw(void)
{
	
}