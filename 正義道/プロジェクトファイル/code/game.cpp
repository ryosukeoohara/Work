//===========================================================
//
// ゲーム処理[game.cpp]
// Author 大原怜将
//
//===========================================================
#include "game.h"
#include "enemyweak.h"
#include "enemyBoss.h"
#include "time.h"
#include "score.h"
#include "slot.h"
#include "itemicon.h"
#include "frame.h"
#include "player.h"
#include "collision.h"
#include "field.h"
#include "map.h"
#include "debugproc.h"
#include "enemymanager.h"
#include "effectline.h"
#include "effectsord.h"
#include "lifegage.h"
#include "icon.h"
#include "displife.h"
#include "target.h"
#include "pause.h"
#include "sky.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "objectMesh.h"
#include "gameUI.h"
#include "bulletUI.h"

//================================================================
//静的メンバ変数
//================================================================
CPlayer *CGame::m_Player = NULL;
CEnemy *CGame::m_Enemy = NULL;
CEnemyManager *CGame::m_EnemyManager = NULL;
CCollision *CGame::m_Collision = NULL;
CMap *CGame::m_Map = NULL;
CDispLife *CGame::m_DispLife = NULL;
CShadow *CGame::m_Shadow = NULL;
CLife *CGame::m_Life = NULL;
CPause *CGame::m_Pause = NULL;
bool CGame::m_bPause = false;

//===========================================================
//コンストラクタ
//===========================================================
CGame::CGame()
{
	
}

//===========================================================
//コンストラクタ
//===========================================================
CGame::CGame(CScene::MODE mode)
{
	
}

//===========================================================
//デストラクタ
//===========================================================
CGame::~CGame()
{

}

//===========================================================
//デストラクタ
//===========================================================
CGame *CGame::Create(void)
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;

		pGame->Init();
	}

	return pGame;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CGame::Init(void)
{
	//カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	pCamera->SetType(CCamera::TYPE_GAME);

	//フィールドを生成
	CField::Create();

	//CObjectMesh::Create();

	//空を生成
	CSky::Create({ 0.0f,0.0f,0.0f });

	if (m_Map == NULL)
	{//使用されていなかったら

		//マップを生成
		m_Map = new CMap;

		//初期化処理
		m_Map->Init();
	}

	if (m_Collision == NULL)
	{//使用されていなかったら

		//当たり判定を生成
		m_Collision = new CCollision;

		//初期化処理
		m_Collision->Init();
	}

	if (m_Player == NULL)
	{//使用されていなかったら

		//プレイヤーの生成
		m_Player = new CPlayer({ 780.0f, 0.0f, -1140.0f });

		//初期化処理
		m_Player->Init();
	}

	if (m_EnemyManager == NULL)
	{//使用されていなかったら

		//敵マネージャの生成
		m_EnemyManager = new CEnemyManager;

		//初期化処理
		m_EnemyManager->Init();
	}

	//時間
	CTime::Create();

	//スコア
	CScore::Create();

	//アイテムスロット
	CSlot::Create();

	//アイテムアイコン
	CItemIcon::Create({ 350.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROXIMITY);
	CItemIcon::Create({ 450.0f, 650.0f, 0.0f }, CItemIcon::TYPE_PROJECTILE);

	//フレーム
	CFrame::Create();

	CLifegage::Create({200.0f, 50.0f, 0.0f});

	CDispLife::Create({ 65.0f, 50.0f, 0.0f });

	CIcon::Create({ 50.0f,50.0f,0.0f }, CIcon::TYPE_PLAYER);

	CBulletUI::Create({80.0f, 400.0f, 0.0f});

	CTarget::Create(CTarget::TYPE_FIRST, { 200.0f, 200.0f, 0.0f });

	CSound *pSound = CManager::GetSound();

	CGameUI::Create({ SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.5f, 0.0f }, CGameUI::TYPE_AIM00);

	pSound->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	pSound->Stop();

	//当たり判定の破棄
	if (m_Collision != NULL)
	{
		//マップの終了処理
		m_Collision->Uninit();

		//メモリを開放
		delete m_Collision;

		//使用していない状態にする
		m_Collision = NULL;
	}

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

	//敵マネージャの破棄
	if (m_EnemyManager != NULL)
	{
		//敵マネージャの終了処理
		m_EnemyManager->Uninit();

		//メモリを開放
		delete m_EnemyManager;

		//使用していない状態にする
		m_EnemyManager = NULL;
	}

	//影の破棄
	if (m_Shadow != NULL)
	{//使用されているとき

		//影の終了処理
		//m_Shadow->Uninit();

		//メモリを開放
		//delete m_Shadow;

		//使用していない状態にする
		m_Shadow = NULL;
	}

	if (m_Life != NULL)
	{
		m_Life = NULL;
	}

	//マップの破棄
	if (m_Map != NULL)
	{//使用されていなかったら

		////マップの終了処理
		//m_Map->Uninit();

		////メモリを開放
		//delete m_Map;

		//使用していない状態にする
		m_Map = NULL;
	}

	//ポーズの破棄
	if (m_Pause != NULL)
	{
		//終了処理
		m_Pause->Uninit();

		//使用していない状態にする
		m_Pause = NULL;
	}

	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CGame::Update(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	if (m_EnemyManager != NULL)
	{
		m_EnemyManager->Update();
	}

	//if (InputKeyboard->GetTrigger(DIK_P) == true)
	//{//Wキーが押された

	//	m_bPause = m_bPause ? false : true;
	//}

	//if (m_bPause == true)
	//{
	//	if (m_Pause == NULL)
	//	{//使用されていなかったら

	//		//ポーズを生成
	//		m_Pause = new CPause;

	//		//初期化処理
	//		m_Pause->Init();
	//	}

	//	if (m_Pause != NULL)
	//	{
	//		m_Pause->Update();
	//	}
	//}
	//else
	//{
	//	//ポーズの破棄
	//	if (m_Pause != NULL)
	//	{
	//		//終了処理
	//		m_Pause->Uninit();

	//		//使用していない状態にする
	//		m_Pause = NULL;
	//	}

	//	CObject::UpdateAll();
	//}

	CObject::UpdateAll();

	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\nシーン：ゲーム");
}

//===========================================================
//描画処理
//===========================================================
void CGame::Draw(void)
{
	
}

//================================================================
//プレイヤーの取得
//================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_Player;
}

//================================================================
//敵の取得
//================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_Enemy;
}

//================================================================
//敵の取得
//================================================================
CEnemyManager *CGame::GetEnemyManager(void)
{
	return m_EnemyManager;
}

//================================================================
//当たり判定の取得
//================================================================
CCollision *CGame::GetCollsion(void)
{
	return m_Collision;
}

//================================================================
//マップの取得
//================================================================
CMap *CGame::GetMap(void)
{
	return m_Map;
}

//================================================================
//2D表示のライフの取得
//================================================================
CDispLife *CGame::GetDispLife(void)
{
	return m_DispLife;
}

//================================================================
//影表示の取得
//================================================================
CShadow *CGame::GetShadow(void)
{
	return m_Shadow;
}

//================================================================
//3D表示のライフの取得
//================================================================
CLife *CGame::GetLife(void)
{
	return m_Life;
}

//================================================================
//ポーズの取得
//================================================================
CPause *CGame::GetPause(void)
{
	return m_Pause;
}