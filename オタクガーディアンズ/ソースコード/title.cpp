//===========================================================
//
//タイトル処理[title.cpp]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "UImanager.h"
#include "camera.h"
#include "sky.h"
#include "player.h"
#include "field.h"
#include "map.h"
#include "input.h"
#include "fade.h"

//*==========================================================
//静的メンバ変数
//*==========================================================
CChibi* CTitle::m_PlayerChibi = nullptr;
CFoot* CTitle::m_PlayerFoot = nullptr;

//*==========================================================
//定数定義
//*==========================================================
namespace
{
	const D3DXVECTOR3 CHIBI_POS = D3DXVECTOR3(-650.0f, 30.0f, 0.0f);   // プレイヤーチビの位置
	const D3DXVECTOR3 FOOT_POS = D3DXVECTOR3(-675.0f, 30.0f, -50.0f);  // プレイヤーデブの位置
	const D3DXVECTOR3 TITLE_UI = D3DXVECTOR3(100.0f, 180.0f, 0.0f);    // タイトルロゴ
	const D3DXVECTOR3 START_UI = D3DXVECTOR3(100.0f, 500.0f, 0.0f);    // スタートボタンのUI
}

//===========================================================
//コンストラクタ
//===========================================================
CTitle::CTitle()
{

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
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = NULL;

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
	//カメラ取得
	CCamera* pCamera = CManager::Getinstance()->GetCamera();

	pCamera->SetType(CCamera::TYPE_TITLE);

	//CSky::Create({ 0.0f,0.0f,0.0f });

	CMap::Create();

	if (m_PlayerChibi == nullptr)
	{
		m_PlayerChibi = new CChibi(CHIBI_POS);

		m_PlayerChibi->Init();
	}

	if (m_PlayerFoot == nullptr)
	{
		m_PlayerFoot = new CFoot(FOOT_POS);

		m_PlayerFoot->Init();
	}

	//タイトルのロゴ生成
	CUIManager::Create(TITLE_UI, CUIManager::TYPE_TITLE);

	//スタートorエンター
	CUIManager::Create(START_UI, CUIManager::TYPE_TITLESELECT);

	//サウンドを取得
	CSound* pSound = CManager::Getinstance()->GetSound();

	if(pSound != nullptr)
	   pSound->Play(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTitle::Uninit(void)
{
	//サウンドを取得
	CSound* pSound = CManager::Getinstance()->GetSound();

	//サウンド停止
	pSound->Stop();

	if (m_PlayerChibi != nullptr)
	{
		m_PlayerChibi->Uninit();

		m_PlayerChibi = nullptr;
	}

	if (m_PlayerFoot != nullptr)
	{
		m_PlayerFoot->Uninit();

		m_PlayerFoot = nullptr;
	}

	//すべてのオブジェクト破棄
	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CTitle::Update(void)
{
	//キーボードを取得
	CInputKeyboard* InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse* pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad* pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//フェードの情報を取得
	CFade* pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{//ENTERキーを押したかつシーンがタイトルのとき

		m_PlayerFoot->SetTState(CFoot::TITLE_STATE_MOVE);

		m_PlayerChibi->SetTState(CChibi::TITLE_STATE_MOVE);

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをゲームに遷移
			pFade->Set(CScene::MODE_TUTORIAL);
		}
	}

	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();

	CDebugProc* pDebugProc = CManager::Getinstance()->Getinstance()->GetDebugProc();
	pDebugProc->Print("\nシーン：タイトル");
}

//===========================================================
//描画処理
//===========================================================
void CTitle::Draw(void)
{

}