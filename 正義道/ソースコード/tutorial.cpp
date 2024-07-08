//===============================================================
//
//チュートリアル処理[tutorial.cpp]
// Author 大原怜将
//
//===============================================================
#include "tutorial.h"
#include "player.h"
#include "field.h"
#include "sky.h"
#include "map.h"
#include "collision.h"
#include "debugproc.h"
#include "slot.h"
#include "itemicon.h"
#include "tutorialUI.h"
#include "fade.h"
#include "tutorialAI.h"
#include "input.h"
#include "sound.h"
#include "tutoriallogo.h"

//===============================================================
//静的メンバ変数
//===============================================================
CPlayer *CTutorial::m_Player = NULL;
CTutorial::TYPE CTutorial::m_type = TYPE_NONE;
bool CTutorial::m_bEndlesson = false;

//===============================================================
//コンストラクタ
//===============================================================
CTutorial::CTutorial()
{
	m_bCrateUI = false;
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
	CSound *pSound = CManager::GetSound();

	m_type = TYPE_LESSON01;

	CField::Create();

	//空を生成
	CSky::Create({ 0.0f,0.0f,0.0f });

	if (m_Player == NULL)
	{//使用されていなかったら

		//プレイヤーの生成
		m_Player = new CPlayer({ 780.0f, 0.0f, -800.0f });

		//初期化処理
		m_Player->Init();
	}

	//チュートリアル先導役AI
	CTutorialAI::Create({ 780.0f, 0.0f, -1300.0f }, {0.0f, D3DX_PI, 0.0f});

	//アイテムスロット
	CSlot::Create();

	//アイテムアイコン
	CItemIcon::Create({ 350.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROXIMITY);
	CItemIcon::Create({ 450.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROJECTILE);

	//フレーム
	CFrame::Create();

	CTutoriallogo::Create({ 1100.0f, 650.0f, 0.0f });

	pSound->Play(CSound::SOUND_LABEL_BGM003);

	return S_OK;
}

//===============================================================
//終了処理
//===============================================================
void CTutorial::Uninit(void)
{
	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	//プレイヤーの破棄
	if (m_Player != NULL)
	{
		//プレイヤーの終了処理
		m_Player->Uninit();

		//メモリを開放
		//delete m_Player;

		//使用していない状態にする
		m_Player = NULL;
	}

	CObject::ReleaseAll();
}

//===============================================================
//更新処理
//===============================================================
void CTutorial::Update(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//シーンの情報を取得
	CScene *pScene = CManager::GetScene();

	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	//チュートリアルUIの情報を取得
	CTutorialUI *pTutoUI = CTutorialUI::GetUI();

	//すべてのオブジェクトの更新処理
	CObject::UpdateAll();

	if (m_Player->GetTutostate() == CPlayer::TUTOSTATE_STOP && m_bCrateUI == false)
	{
		CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM00);

		m_bCrateUI = true;
	}
	
	if (pTutoUI != NULL)
	{
		if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM00 || CTutorialUI::TYPE_AIM01 || CTutorialUI::TYPE_AIM02 || CTutorialUI::TYPE_AIM03 || CTutorialUI::TYPE_AIM04 || CTutorialUI::TYPE_AIM05)
		{
			if (InputKeyboard->GetTrigger(DIK_SPACE) == true)
			{//ENTERキーが押された

				//一つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM00)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON01);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//二つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM01)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON02);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//三つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM02)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON03);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//4つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM03)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON04);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//5つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM04)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, 400.0f, 0.0f }, CTutorialUI::TYPE_LESSON05);

					m_Player->SetTutostate(CPlayer::TUTOSTATE_NONE);

					return;
				}

				//四つ目の目標
				if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_AIM05)
				{
					pTutoUI->Uninit();

					pTutoUI = NULL;

					if (pFade->Get() != pFade->FADE_OUT)
					{
						pFade->Set(CScene::MODE_GAME);
					}

					return;
				}
			}
		}

		//移動のチュートリアル--------------------------------------------------------------------------------------------------------------
 		if (m_bEndlesson == true && m_type == TYPE_LESSON01)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON01)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM01);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON02;

			m_bEndlesson = false;
		}

		//攻撃のチュートリアル--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON02)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON02)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM02);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON03;

			m_bEndlesson = false;
		}

		//ホイールのチュートリアル--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON03)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON03)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM03);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON04;

			m_bEndlesson = false;
		}

		//射撃のチュートリアル--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON04)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON04)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM04);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_type = TYPE_LESSON05;

			m_bEndlesson = false;
		}

		//回避のチュートリアル--------------------------------------------------------------------------------------------------------------
		if (m_bEndlesson == true && m_type == TYPE_LESSON05)
		{
			if (pTutoUI->GetTypeUI() == CTutorialUI::TYPE_LESSON05)
			{
				pTutoUI->Uninit();

				pTutoUI = NULL;

				CTutorialUI::Create({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CTutorialUI::TYPE_AIM05);

				m_Player->SetTutostate(CPlayer::TUTOSTATE_STOP);
			}

			m_bEndlesson = false;
		}
	}

	if (pDebugProc != NULL)
	{
		pDebugProc->Print("\nシーン：チュートリアル");
	}
}

//===============================================================
//描画処理
//===============================================================
void CTutorial::Draw(void)
{
	CTutorialUI *pTutorial = CTutorialUI::GetUI();

	if (pTutorial != NULL)
	{
		pTutorial->Draw();
	}
}

//===============================================================
//チュートリアルのプレイヤーを取得
//===============================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_Player;
}