//===========================================================
//
//ポリゴンを出すやつ[manager.cpp]
//Author 大原怜将
//
//===========================================================
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "enemyBoss.h"
#include "enemyweak.h"
#include "input.h"
#include "multiplexbg.h"
#include "effect.h"
#include "time.h"
#include "score.h"
#include "block.h"
#include "debugproc.h"
#include "item.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "billboard.h"
#include "texture.h"
#include "field.h"
#include "collision.h"
#include "edit.h"
#include "map.h"
#include "model.h"
#include "frame.h"
#include "itemslot.h"
#include "slot.h"
#include "itemicon.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "gameUI.h"

//================================================================
//静的メンバ変数
//================================================================
CRenderer *CManager::m_Renderer = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CSound *CManager::m_Sound = NULL;
CPlayer *CManager::m_Player = NULL;
CDebugProc *CManager::m_DebugProc = NULL;
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CTexture *CManager::m_Texture = NULL;
CModel *CManager::m_Model = NULL;
CObject3D *CManager::m_Object3D = NULL;
CEnemy *CManager::m_Enemy = NULL;
CCollision *CManager::m_Collision = NULL;
CEdit *CManager::m_Edit = NULL;
CMap *CManager::m_Map = NULL;
CScene *CManager::m_pScene = NULL;
CFade *CManager::m_Fade = NULL;
CPause *CManager::m_Pause = NULL;

CGame  *CScene::m_Game = NULL;
CTutorial *CScene::m_Tutorial = NULL;
CTitle *CScene::m_Title = NULL;
CResult *CScene::m_Result = NULL;
CScene::MODE CScene::m_mode = CScene::MODE_TITLE;
bool CManager::m_bPause = NULL;

//================================================================
//コンストラクタ
//================================================================
CManager::CManager()
{
	m_ResetCounter = 0;
	m_bPause = false;
}

//================================================================
//デストラクタ
//================================================================
CManager::~CManager()
{

}

//================================================================
//初期化処理
//================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_Renderer == NULL)
	{//使用されていなかったら

		//レンダラーの生成
		m_Renderer = new CRenderer;

		//初期化処理
		m_Renderer->Init(hWnd, TRUE);
	}

	if (m_InputKeyboard == NULL)
	{//使用されていなかったら

		//キーボードの生成
		m_InputKeyboard = new CInputKeyboard;

		//初期化処理
		m_InputKeyboard->Init(hInstance, hWnd);
	}

	if (m_InputMouse == NULL)
	{//使用されていなかったら

		//マウス生成
		m_InputMouse = new CInputMouse;

		//初期化処理
		m_InputMouse->Init(hInstance, hWnd);
	}

	if (m_Sound == NULL)
	{//使用されていなかったら

		//サウンドの生成
		m_Sound = new CSound;

		//初期化処理
		m_Sound->Init(hWnd);
	}

	if (m_DebugProc == NULL)
	{//使用されていなかったら

	 //デバッグプロックの生成
		m_DebugProc = new CDebugProc;

		//初期化処理
		m_DebugProc->Init();
	}

	if (m_Camera == NULL)
	{//使用されていなかったら

		//カメラを生成
		m_Camera = new CCamera;

		//初期化処理
		m_Camera->Init();
	}

	if (m_Light == NULL)
	{//使用されていなかったら

	 //ライトを生成
		m_Light = new CLight;

		//初期化処理
		m_Light->Init();
	}

	if (m_Texture == NULL)
	{//使用されていなかったら

		//テクスチャを生成
		m_Texture = new CTexture;

		//初期化処理
		m_Texture->Load();
	}

	if (m_Collision == NULL)
	{//使用されていなかったら

	 //当たり判定を生成
		m_Collision = new CCollision;

		//初期化処理
		m_Collision->Init();
	}

	if (m_Model == NULL)
	{//使用されていなかったら

		//モデルを生成
		m_Model = new CModel;

		//初期化処理
		m_Model->Load();
	}

	if (m_pScene == NULL)
	{//使用されていなかったら

		//シーンの生成
		m_pScene = CScene::Create(CScene::MODE_GAME);

		//初期化処理
		m_pScene->Init();
	}

	//if (m_Enemy == NULL)
	//{//使用されていなかったら

	//	//敵を生成
	//	m_Enemy = new CEnemy;

	//	//初期化処理
	//	m_Enemy->Init();
	//}

	if (m_Fade == NULL)
	{//使用されていなかったら

		//フェードを生成
		m_Fade = new CFade;

		//初期化処理
		m_Fade->Init();
	}

	
	
	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CManager::Uninit(void)
{
	m_Sound->Stop();

	//シーンの破棄
	if (m_pScene != NULL)
	{
		//シーンの終了処理
		m_pScene->Uninit();

		//メモリを開放
		delete m_pScene;

		//使用していない状態にする
		m_pScene = NULL;
	}

	//レンダラーの破棄
	if (m_Renderer != NULL)
	{
		//レンダラーの終了処理
		m_Renderer->Uninit();

		//メモリを開放
		delete m_Renderer;

		//使用していない状態にする
		m_Renderer = NULL;
	}

	//キーボードの破棄
	if (m_InputKeyboard != NULL)
	{
		//キーボードの終了処理
		m_InputKeyboard->Uninit();

		//メモリを開放
		delete m_InputKeyboard;

		//使用していない状態にする
		m_InputKeyboard = NULL;
	}

	//マウスの破棄
	if (m_InputMouse != NULL)
	{
		//マウスの終了処理
		m_InputMouse->Uninit();

		//メモリを開放
		delete m_InputMouse;

		//使用していない状態にする
		m_InputMouse = NULL;
	}

	//サウンドの破棄
	if (m_Sound != NULL)
	{
		//サウンドの終了処理
		m_Sound->Uninit();
	
		//メモリを開放
		delete m_Sound;

		//使用していない状態にする
		m_Sound = NULL;
	}

	//デバッグプロックの破棄
	if (m_DebugProc != NULL)
	{
		//デバッグプロックの終了処理
		m_DebugProc->Uninit();

		//メモリを開放
		delete m_DebugProc;

		//使用していない状態にする
		m_DebugProc = NULL;
	}

	//カメラの破棄
	if (m_Camera != NULL)
	{
		//デバッグプロックの終了処理
		m_Camera->Uninit();

		//メモリを開放
		delete m_Camera;

		//使用していない状態にする
		m_Camera = NULL;
	}

	//ライトの破棄
	if (m_Light != NULL)
	{
		//デバッグプロックの終了処理
		m_Light->Uninit();

		//メモリを開放
		delete m_Light;

		//使用していない状態にする
		m_Light = NULL;
	}

	//テクスチャの破棄
	if (m_Texture != NULL)
	{
		//テクスチャの終了処理
		m_Texture->UnLoad();

		//メモリを開放
		delete m_Texture;

		//使用していない状態にする
		m_Texture = NULL;
	}

	//モデルの破棄
	if (m_Model != NULL)
	{
		//テクスチャの終了処理
		m_Model->UnLoad();

		//メモリを開放
		delete m_Model;

		//使用していない状態にする
		m_Model = NULL;
	}

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

	////敵の破棄
	//if (m_Enemy != NULL)
	//{
	//	//使用していない状態にする
	//	m_Enemy = NULL;
	//}

	//フェードの破棄
	if (m_Fade != NULL)
	{
		//フェードの終了処理
		m_Fade->Uninit();

		//メモリを開放
		delete m_Fade;

		//使用していない状態にする
		m_Fade = NULL;
	}

	//if (m_Pause != NULL)
	//{
	//	//ポーズの終了処理
	//	m_Pause->Uninit();

	//	//使用していない状態にする
	//	m_Pause = NULL;
	//}

	//CObject::ReleaseAll();

	////サウンドの破棄
	//if (m_Sound != NULL)
	//{
	//	//キーボードの終了処理
	//	m_Sound->Uninit();

	//	//メモリを開放
	//	delete m_Sound;

	//	//使用していない状態にする
	//	m_Sound = NULL;
	//}
}

//================================================================
//更新処理
//================================================================
void CManager::Update(void)
{
	//レンダラーの更新処理
	m_Renderer->Update();

	//キーボードの更新処理
	m_InputKeyboard->Update();

	//マウスの更新処理
	m_InputMouse->Update();

	//ポーズの情報を取得
	CPause *pPause = CGame::GetPause();

	m_Enemy = GetEnemy();

	if (m_InputKeyboard->GetTrigger(DIK_P) == true && m_pScene->GetMode() == CScene::MODE_GAME)
	{//ENTERキーを推した
		
		if (m_Fade->Get() != m_Fade->FADE_OUT)
		{
			m_bPause = m_bPause ? false : true;
		}
	}

	if (m_bPause == true)
	{
		if (m_Pause == NULL)
		{//使用されていなかったら

			//ポーズを生成
			m_Pause = new CPause;

			//初期化処理
			m_Pause->Init();
		}

		if (m_Pause != NULL)
		{
			m_Pause->Update();
		}
	}
	else
	{
		if (m_Pause != NULL)
		{
			//ポーズの終了処理
			m_Pause->Uninit();

			//使用していない状態にする
			m_Pause = NULL;
		}

		if (m_Camera != NULL)
		{
			//カメラの更新処理
			m_Camera->Update();
		}

		if (m_pScene != NULL)
		{
			m_pScene->Update();
		}
	}

	if (m_InputKeyboard->GetTrigger(DIK_RETURN) == true && m_pScene->GetMode() == CScene::MODE_RESULT)
	{//ENTERキーを推した

		if (m_Fade->Get() != m_Fade->FADE_OUT)
		{
			m_Fade->Set(CScene::MODE_TITLE);
		}

		//SetMode(CScene::MODE_TITLE);

		//CFade::Create(CScene::MODE_TITLE);
	}
	else if (m_InputKeyboard->GetTrigger(DIK_RETURN) == true && m_pScene->GetMode() == CScene::MODE_TITLE)
	{//ENTERキーを推した

		if (m_Fade->Get() != m_Fade->FADE_OUT)
		{
			m_Fade->Set(CScene::MODE_TUTORIAL);
		}

		//SetMode(CScene::MODE_GAME);

		//CFade::Create(CScene::MODE_GAME);
	}
	else if (m_InputKeyboard->GetTrigger(DIK_RETURN) == true && m_pScene->GetMode() == CScene::MODE_TUTORIAL)
	{//ENTERキーを推した

		if (m_Fade->Get() != m_Fade->FADE_OUT)
		{
			m_Fade->Set(CScene::MODE_GAME);
		}

		//SetMode(CScene::MODE_GAME);

		//CFade::Create(CScene::MODE_GAME);
	}
	//else if (m_InputKeyboard->GetTrigger(DIK_RETURN) == true && m_pScene->GetMode() == CScene::MODE_GAME)
	//{//ENTERキーを推した

	//	if (m_Fade->Get() != m_Fade->FADE_OUT)
	//	{
	//		m_Fade->Set(CScene::MODE_RESULT);
	//	}

	//	CEnemyWeak::UninitWeak();
	//	
	//	//SetMode(CScene::MODE_RESULT);

	//	//CFade::Create(CScene::MODE_RESULT);
	//}

	int nTexAll = m_Texture->GetNumTexture();

	m_DebugProc->Print("\n<<テクスチャの総数 : %d>>", nTexAll);
	m_DebugProc->Print("\n<<ENTERで次のシーンに遷移>>");
}

//================================================================
//描画処理
//================================================================
void CManager::Draw(void)
{
	//ポーズの情報を取得
	CPause *pPause = CGame::GetPause();

	//レンダラーの描画処理
	m_Renderer->Draw();

	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}

	if (m_bPause == true)
	{
		if (pPause != NULL)
		{
			pPause->Draw();
		}
	}
}

//================================================================
//コンストラクタ
//================================================================
CScene::CScene()
{
	//m_mode = MODE_TITLE;
}

//================================================================
//コンストラクタ
//================================================================
CScene::CScene(MODE mode)
{
	m_mode = mode;
}

//================================================================
//デストラクタ
//================================================================
CScene::~CScene()
{

}

//================================================================
//生成
//================================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	if (pScene == NULL)
	{
		pScene = new CScene(mode);

		pScene->Init();
	}

	return pScene;
}

//================================================================
//初期化処理
//================================================================
HRESULT CScene::Init(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_Title == NULL)
		{
			m_Title = new CTitle;

			m_Title->Init();
		}

		break;

	case MODE_TUTORIAL:

		if (m_Tutorial == NULL)
		{
			m_Tutorial = new CTutorial;

			m_Tutorial->Init();
		}

		break;

	case MODE_GAME:

		if (m_Game == NULL)
		{
			m_Game = new CGame;

			m_Game->Init();
		}

		break;

	case MODE_RESULT:

		if (m_Result == NULL)
		{
			m_Result = new CResult;

			m_Result->Init();
		}

		break;
	}

	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CScene::Uninit(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_Title != NULL)
		{
			m_Title->Uninit();

			delete m_Title;

			m_Title = NULL;
		}

		break;

	case MODE_TUTORIAL:

		if (m_Tutorial != NULL)
		{
			m_Tutorial->Uninit();

			delete m_Tutorial;

			m_Tutorial = NULL;
		}

		break;

	case MODE_GAME:

		if (m_Game != NULL)
		{
			m_Game->Uninit();

			delete m_Game;

			m_Game = NULL;
		}

		break;

	case MODE_RESULT:

		if (m_Result != NULL)
		{
			m_Result->Uninit();

			delete m_Result;

			m_Result = NULL;
		}

		break;
	}
}

//================================================================
//更新処理
//================================================================
void CScene::Update(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_Title != NULL)
		{
			m_Title->Update();
		}

		break;

	case MODE_TUTORIAL:

		if (m_Tutorial != NULL)
		{
			m_Tutorial->Update();
		}

		break;

	case MODE_GAME:

		if (m_Game != NULL)
		{
			m_Game->Update();
		}

		break;

	case MODE_RESULT:

		if (m_Result != NULL)
		{
			m_Result->Update();
		}

		break;
	}
}

//================================================================
//描画
//================================================================
void CScene::Draw(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_Title != NULL)
		{
			m_Title->Draw();
		}

		break;

	case MODE_TUTORIAL:

		if (m_Tutorial != NULL)
		{
			m_Tutorial->Draw();
		}

		break;

	case MODE_GAME:

		if (m_Game != NULL)
		{
			m_Game->Draw();
		}

		break;

	case MODE_RESULT:

		if (m_Result != NULL)
		{
			m_Result->Draw();
		}

		break;
	}
}

//================================================================
//レンダラーの取得
//================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_Renderer;
}

//================================================================
//キーボードの取得
//================================================================
CInputKeyboard *CManager::GetKeyBoard(void)
{
	return m_InputKeyboard;
}

//================================================================
//マウス取得
//================================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_InputMouse;
}

//================================================================
//サウンドの取得
//================================================================
CSound *CManager::GetSound(void)
{
	return m_Sound;
}

//================================================================
//プレイヤーの取得
//================================================================
CPlayer *CManager::GetPlayer(void)
{
	return m_Player;
}

//================================================================
//デバッグプロックの取得
//================================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_DebugProc;
}

//================================================================
//カメラの取得
//================================================================
CCamera *CManager::GetCamera(void)
{
	return m_Camera;
}

//================================================================
//ライトの取得
//================================================================
CLight *CManager::GetLight(void)
{
	return m_Light;
}

//================================================================
//テクスチャの取得
//================================================================
CTexture *CManager::GetTexture(void)
{
	return m_Texture;
}

//================================================================
//モデルの取得
//================================================================
CModel *CManager::GetModel(void)
{
	return m_Model;
}

//================================================================
//オブジェクト3Dの取得
//================================================================
CObject3D *CManager::GetObject3D(void)
{
	return m_Object3D;
}

//================================================================
//敵の取得
//================================================================
CEnemy *CManager::GetEnemy(void)
{
	return m_Enemy;
}
//================================================================
//当たり判定の取得
//================================================================
CCollision *CManager::GetCollsion(void)
{
	return m_Collision;
}

//================================================================
//エディットの取得
//================================================================
CEdit *CManager::GetEdit(void)
{
	return m_Edit;
}

//================================================================
//マップの取得
//================================================================
CMap *CManager::GetMap(void)
{
	return m_Map;
}

//================================================================
//マップの取得
//================================================================
CScene *CManager::GetScene(void)
{
	return m_pScene;
}

//================================================================
//マップの取得
//================================================================
CFade *CManager::GetFade(void)
{
	return m_Fade;
}

//================================================================
//ポーズの取得
//================================================================
CPause *CManager::GetPause(void)
{
	return m_Pause;
}

//================================================================
//モード設定
//================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//m_Sound->Stop();

	//CObject::ReleaseAll();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		delete m_pScene;

		m_pScene = NULL;
	}

	if (m_pScene == NULL)
	{
		m_pScene = new CScene(mode);

		m_pScene->Init();
	}
}

//================================================================
//モードの取得
//================================================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}