//===========================================================
//
// プレイヤー処理[player.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"
#include "camera.h"
#include "object.h"
#include "gage.h"
#include "billboard.h"
#include "enemymanager.h"
#include "utility.h"
#include "item.h"
#include "itemmanager.h"
#include "particle.h"
#include "effect2D.h"
#include "animation.h"
#include "heataction.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//===========================================================
// 静的メンバ変数
//===========================================================
CPlayer *CPlayer::m_pPlayer = nullptr;

//===========================================================
// 定数定義
//===========================================================
namespace
{
	const int DAMAGE_COUNT = 15;                              // ダメージ状態でいる時間
	const int MICROWAVE = 3600;                              // 電子レンジを使用したヒートアクションを再び使用可能になるまでの時間
	const float GRAP_MOVE_SPEED = 0.7f;                        // 掴み状態の移動の速さ
	const float MOVE_SPEED = 1.0f;                            // 通常状態の移動の速さ
	const float MAX_STAMINA = 40.0f;                          // スタミナの最大値
	const float BOOST_STAMINA = 0.1f;                         // スタミナの回復値
	const float LOST_STMINA = 10.0f;                          // 回避のスタミナ消費量
	const float GRAP_LOST_STMINA = 0.1f;                       // 敵を掴んでいる時のスタミナ消費量
	const char* PLAYER_TEXT = "data\\TEXT\\player_info.txt";  // プレイヤーのテキストファイル

	const D3DXVECTOR3 CAMERA_ROT[CPlayer::HEAT_MAX] = 
	{ 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI * -0.38f),

	};  // ヒートアクション時のカメラ位置

	const float CAMERA_DISTNCE[CPlayer::HEAT_MAX] =
	{
		300.0f,
		300.0f,
		200.0f,

	};  // ヒートアクション時のカメラの距離

	const D3DXVECTOR3 ENEMY_GRAP_POS[CEnemy::MAX] =
	{
		D3DXVECTOR3(-10.0f, -10.0f, 60.0f),  // 雑魚敵
		D3DXVECTOR3(-15.0f, -10.0f, 80.0f),  // ボス敵
	};

	const D3DXVECTOR3 MAP_LIMIT_MAX = D3DXVECTOR3(800.0f, 0.0f, 1000.0f);   // マップの制限
	const D3DXVECTOR3 MAP_LIMIT_MIN = D3DXVECTOR3(-850.0f, 0.0f, -670.0f);  // マップの制限
	const float TUTORIAL_MAP_LIMITZ = 30.0f;                                // チュートリアルマップのZ軸の制限

	const D3DXVECTOR3 STICK_ENEMY = D3DXVECTOR3(100.0f, 0.0f, 100.0f);      // 
	const D3DXVECTOR2 HEATACT_BUTTON_SIZE = D3DXVECTOR2(25.0f, 25.0f);      // ヒートアクション可能時に出るテクスチャのサイズ
}

//===========================================================
// コンストラクタ
//===========================================================
CPlayer::CPlayer()
{
	// 初期化
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_Grap.pItem = nullptr;
	m_Grap.pEnemy = nullptr;

	m_HeatAct = HEAT_NONE;
	m_Mobility = Immobile;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_nUseCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItemMicro = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pItem = nullptr;
	m_pBotton = nullptr;
	m_pGekiatu = nullptr;
	m_pHeatAct = nullptr;
	m_nIdxEne = -1;
	m_nIdxItem = -1;
	m_nDefeat = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nCntSound = 0;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	m_bInvi = false;
	m_bHeatActFlag = false;
	
	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;

	m_pPlayer = this;
}

//===========================================================
// コンストラクタ
//===========================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, int nPriority) : CObject(nPriority)
{
	// 初期化
	m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_HeatAct = HEAT_NONE;
	m_Mobility = Immobile;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_nUseCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItemMicro = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pItem = nullptr;
	m_pBotton = nullptr;
	m_pGekiatu = nullptr;
	m_pHeatAct = nullptr;
	m_nIdxEne = -1;
	m_nIdxItem = -1;
	m_nDefeat = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nCntSound = 0;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	m_bInvi = false;
	m_bHeatActFlag = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;

	m_pPlayer = this;
}

//===========================================================
// デストラクタ
//===========================================================
CPlayer::~CPlayer()
{

}

//===========================================================
// 生成処理
//===========================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nPriority)
{
	// プレイヤーのポインタ
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		// 生成
		pPlayer = new CPlayer(pos, nPriority);

		// 初期化処理
		pPlayer->Init();
	}
	
	return pPlayer;
}

//===========================================================
// 生成処理
//===========================================================
CPlayer * CPlayer::Create(void)
{
	// プレイヤーのポインタ
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		// 生成
		pPlayer = new CPlayer();

		// 初期化処理
		pPlayer->Init();
	}
	
	return pPlayer;
}

//===========================================================
// ダメージ
//===========================================================
void CPlayer::Damage(int nDamage, float fKnockBack)
{
	if (m_Info.state != STATE_DAMEGE && m_bInvi == false)
	{
		m_Info.state = STATE_DAMEGE;
		m_pMotion->Set(TYPE_DAMAGE);
		CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
		CAnimation::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 60.0f, m_Info.pos.z), 30.0f, CBillBoard::TYPE_HIT);
		m_Info.nLife -= nDamage;
		m_Info.move = D3DXVECTOR3(sinf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack, fKnockBack, cosf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack);
	}
}

//===========================================================
// タイトルで歩く
//===========================================================
void CPlayer::TitleWalk(void)
{
	// パーツごとの更新
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	if (m_Info.state != STATE_OTA)
	{
		m_Info.state = STATE_OTA;
		m_pMotion->Set(TYPE_OTA);
	}

	//位置に移動量加算----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//m_pos.y = fHeight + 18.0f;

	//移動量を更新(減衰させる)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	CManager::Getinstance()->GetDebugProc()->Print("\nプレイヤーの位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("プレイヤーの向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
}

//===========================================================
// 初期化処理
//===========================================================
HRESULT CPlayer::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//種類設定
	SetType(TYPE_PLAYER);

	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;

		//初期化処理
		m_pMotion->Init();

		m_pMotion->Set(TYPE_NEUTRAL);
	}

	m_fGrapRot = 1.0f;
	m_fStamina = 40.0f;
	m_Info.nLife = 200;
	m_Info.fRadius = 20.0f;
	m_nCntSound = 35;
	m_nDamegeCounter = DAMAGE_COUNT;

	ReadText(PLAYER_TEXT);

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME || CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		m_pLife = CGage2D::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 42.0f, (float)((m_Info.nLife * 0.01f) * 20.0f), CGage2D::TYPE_LIFE);
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.01f) * 20));
		m_pStamina = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, m_fStamina, CGage3D::TYPE_STAMINA);
		m_pStamina->SetPos(&m_Info.pos);
		m_pStamina->GetBill()->SetTex(m_fStamina);
	}
	
	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CPlayer::Uninit(void)
{
	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンドストップ
	pSound->Stop();

	if (m_pMotion != nullptr)
	{
		//終了処理
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppCharacter != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_ppCharacter[nCount] != nullptr)
			{
				m_ppCharacter[nCount]->Uninit();
				m_ppCharacter[nCount] = nullptr;
			}
		}

		delete m_ppCharacter;
		m_ppCharacter = nullptr;
	}

	if (m_pStamina != nullptr)
	{
		m_pStamina->Uninit();
		m_pStamina = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	CObject::Release();
}

//================================================================
// 更新処理
//================================================================
void CPlayer::Update(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMAGE_COUNT;
		}
	}
	else
	{
		if (m_Mobility == Mobile)
		{
			// 制御処理
			Control();
		}
	}
	
	// パーツごとの更新
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	// スタミナ
	if (m_fStamina < MAX_STAMINA && m_bGrap == false)
	{
		m_fStamina += BOOST_STAMINA;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	if (m_nUseCounter > 0)
	{
		m_nUseCounter--;

		if (m_nUseCounter % 20 == 0)
		{
			if (m_pItemMicro != nullptr)
			{
				CParticle::Create(m_pItemMicro->GetPosition(), CParticle::TYPE_SMOOK);
			}
		}
	}

	// 体力
	if (m_pLife != nullptr)
	{
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.1f) * 20.0f));
	}

	if (m_Info.nLife <= 0)
	{
		Uninit();

		//フェードの情報を取得
		CFade *pFade = CManager::Getinstance()->GetFade();

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをゲームに遷移
			pFade->Set(CScene::MODE_RESULT);
		}
	}

	if (m_pHeatAct != nullptr)
	{
		m_pHeatAct->Updata();

		if (m_bHeatActFlag == false)
			m_pHeatAct = nullptr;
	}

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// マップの制限
		if (m_Info.pos.x >= MAP_LIMIT_MAX.x)
		{
			m_Info.pos.x = MAP_LIMIT_MAX.x;
		}
		if (m_Info.pos.x <= MAP_LIMIT_MIN.x)
		{
			m_Info.pos.x = MAP_LIMIT_MIN.x;
		}
		if (m_Info.pos.z >= MAP_LIMIT_MAX.z)
		{
			m_Info.pos.z = MAP_LIMIT_MAX.z;
		}
		if (m_Info.pos.z <= TUTORIAL_MAP_LIMITZ)
		{
			m_Info.pos.z = TUTORIAL_MAP_LIMITZ;
		}
	}

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		// マップの制限
		if (m_Info.pos.x >= MAP_LIMIT_MAX.x)
		{
			m_Info.pos.x = MAP_LIMIT_MAX.x;
		}
		if (m_Info.pos.x <= MAP_LIMIT_MIN.x)
		{
			m_Info.pos.x = MAP_LIMIT_MIN.x;
		}
		if (m_Info.pos.z >= MAP_LIMIT_MAX.z)
		{
			m_Info.pos.z = MAP_LIMIT_MAX.z;
		}
		if (m_Info.pos.z <= MAP_LIMIT_MIN.z)
		{
			m_Info.pos.z = MAP_LIMIT_MIN.z;
		}
	}
}

//================================================================
// 描画処理
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Draw();
		}
	}
}

//================================================================
// 制御処理
//================================================================
void CPlayer::Control(void)
{
	if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME || CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_TUTORIAL)
	{
		Move();     // 移動
	}

	// 敵との当たり判定
	CEnemy *pEnemy = CEnemy::GetTop();
	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();
		if (m_nIdxEne != pEnemy->GetIdxID())
		{
			m_Info.pos = *CGame::GetCollision()->CheckEnemy(&m_Info.pos, &m_Info.posOld, &pEnemy->GetPosition(), m_Info.fRadius);
		}
		pEnemy = pEnemyNext;
	}

	// アイテムとの当たり判定
	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		CItem* pItem = CItem::GetTop();

		while (pItem != nullptr)
		{
			CItem* pItemNext = pItem->GetNext();

			pItem->Collision(&m_Info.pos, &m_Info.posOld, 20.0f);

			pItem = pItemNext;
		}
	}
	
	//マウスを取得
	CInputMouse* pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad* pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	if (pInputMouse == nullptr)
		return;

	if (pInputJoyPad == nullptr)
		return;

	// 通常攻撃
	if (pInputMouse->GetLButton() == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_B, 0) == true)
	{
		if (m_Info.state != STATE_GRAP && m_Info.state != STATE_HEAT && m_bGrap == false)
		{
			// 攻撃
			Attack();
		}
	}

	// 投げ
	Grap();

	// 回避
	Avoid();

	// ヒートアクション
	Heat();

	// 状態
	State();   

	CManager::Getinstance()->GetDebugProc()->Print("\nプレイヤーの位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("プレイヤーの向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	CManager::Getinstance()->GetDebugProc()->Print("掴んでいる敵の番号:%d", m_nIdxEne);
	CManager::Getinstance()->GetDebugProc()->Print("倒した数：%d\n", m_nDefeat);
}

//================================================================
// 移動処理
//================================================================
void CPlayer::Move(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//マウスの位置を取得
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_bDesh = false;

	m_Info.posOld = m_Info.pos;
	
	float fSpeed = 0.0f;

	if (m_bGrap == true)
	{
		fSpeed = GRAP_MOVE_SPEED;
	}
	else
	{
		fSpeed = MOVE_SPEED;
	}

	if (m_Info.state != STATE_GRAP && m_Info.state != STATE_AVOID && m_Info.state != STATE_ATTACK && m_Info.state != STATE_HEAT && m_Info.state != STATE_DAMEGE)
	{
		//上に移動----------------------------------------------
		if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
		{//Wキーが押された

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//Dキーも押した 右上に移動

				// 移動量
				m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左上に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
			}
			else
			{//Wキーだけ押した	真上に移動

				// 移動量
				m_Info.move.x -= sinf(CameraRot.y) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
			}

			m_bDesh = true;

			// チュートリアル判別
			m_bPushW = true;
		}
		//下に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_S) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
		{//Sキーが押された

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//Dキーも押した 右下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
			}
			else
			{//Sキーだけ押した 真下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI));
			}

			m_bDesh = true;

			// チュートリアル判別
			m_bPushS = true;
		}
		//右に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーだけ押した

			// 移動量
			m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// チュートリアル判別
			m_bPushD = true;

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
		}
		//左に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーだけ押した

			// 移動量
			m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// チュートリアル判別
			m_bPushA = true;

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
		}

		m_fDiff = m_fDest - m_Info.rot.y;

		//角度の値を修正する
		if (m_fDiff >= D3DX_PI)
		{
			m_fDiff -= D3DX_PI * 2;
		}
		else if (m_fDiff <= -D3DX_PI)
		{
			m_fDiff += D3DX_PI * 2;
		}

		//移動方向(角度)の補正------------------------------------------------
		m_Info.rot.y += m_fDiff * 0.15f;

		//角度の値を修正する--------------------------------------------------
		if (m_Info.rot.y > D3DX_PI)
		{
			m_Info.rot.y = -D3DX_PI;
		}
		else if (m_Info.rot.y < -D3DX_PI)
		{
			m_Info.rot.y = D3DX_PI;
		}
	}
	else if(m_Info.state == STATE_GRAP)
	{
		GrapRotition();
	}
	
	//位置に移動量加算----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//移動量を更新(減衰させる)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	if(CCollision::GetColl() != nullptr)
	CCollision::GetColl()->Map(&m_Info.pos, &m_Info.posOld, 40.0f);
}

//================================================================
// アクション
//================================================================
void CPlayer::Attack(void)
{
	// 攻撃一段目
	if (m_Info.state != STATE_ATTACK)
	{
		m_Info.state = STATE_ATTACK;
		m_Info.Atc = TYPE_ATTACK1;
		m_pMotion->Set(TYPE_ATTACK01);
	}

	// 攻撃二段目
	if (m_Info.Atc == TYPE_ATTACK1 
	&& (m_pMotion->GetCancellFrame() <= m_pMotion->GetNumFrame() 
	&&  m_pMotion->GetCancellFrameEnd() >= m_pMotion->GetNumFrame()))
	{// 攻撃が一段目かつ現在のフレームがキャンセル可能フレーム

		m_Info.Atc = TYPE_ATTACK2;
		m_pMotion->Set(TYPE_ATTACK02);
	}

	// 攻撃三段目
	if (m_Info.Atc == TYPE_ATTACK2 
	&& (m_pMotion->GetCancellFrame() <= m_pMotion->GetNumFrame()
	&&  m_pMotion->GetCancellFrameEnd() >= m_pMotion->GetNumFrame()))
	{// 攻撃が二段目かつ現在のフレームがキャンセル可能フレーム

		m_Info.Atc = TYPE_ATTACK3;
		m_pMotion->Set(TYPE_ATTACK03);
	}

	float fLenght = EnemyDistance();

	if (fLenght <= 100.0f)
	{
		float fDiffmove = 0.0f;

		// 追尾
		fDiffmove = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, m_pEnemy->GetPosition(), m_Info.rot.y);

		// 角度補正
		m_fDest = fDiffmove;
		m_Info.rot.y += fDiffmove;

		// 角度補正
		m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

		//移動量を更新(減衰させる)
		m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * MOVE_SPEED;
		m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * MOVE_SPEED;
	}
}

//================================================================
// 投げる時の角度処理
//================================================================
void CPlayer::GrapRotition(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_fDestOld = m_fDest;

	//上に移動----------------------------------------------
	if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
	{//Wキーが押された

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーも押した 右上に移動

			//向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーも押した 左上に移動

			//向き
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
		}
		else
		{//Wキーだけ押した	真上に移動

			//向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
		}

	}
	//下に移動----------------------------------------------
	else if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
	{//Sキーが押された

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーも押した 右下に移動

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーも押した 左下に移動

			// 向き
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
		}
		else
		{//Sキーだけ押した 真下に移動

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * m_fGrapRot));
		}

	}
	//右に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//Dキーだけ押した

		// 向き
		m_fDest += (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//左に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//Aキーだけ押した

		// 向き
		m_fDest -= (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//右に移動----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
	{//Dキーだけ押した

		// 向き
		m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
	}
	//左に移動----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
	{//Aキーだけ押した

		// 向き
		m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
	}

	if (m_fDest > 0.0f && m_fDestOld < 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}
	else if (m_fDest < 0.0f && m_fDestOld > 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}

	m_fDiff = m_fDest - m_Info.rot.y;

	//角度の値を修正する
	if (m_fDiff >= D3DX_PI)
	{
		m_fDiff -= D3DX_PI * 2;
	}
	else if (m_fDiff <= -D3DX_PI)
	{
		m_fDiff += D3DX_PI * 2;
	}

	//移動方向(角度)の補正------------------------------------------------
	m_Info.rot.y += m_fDiff * (0.15f * m_fGrapRot);

	//角度の値を修正する--------------------------------------------------
	if (m_Info.rot.y > D3DX_PI)
	{
		m_Info.rot.y = -D3DX_PI;
	}
	else if (m_Info.rot.y < -D3DX_PI)
	{
		m_Info.rot.y = D3DX_PI;
	}
}

//================================================================
// 投げる処理
//================================================================
void CPlayer::Grap(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	// 敵を掴む
	if (InputKeyboard->GetTrigger(DIK_E) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
	{
		if (m_Info.state != STATE_THROW && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_AVOID && m_Info.state != STATE_HEAT)
		{
			if (m_Grap.pEnemy == nullptr && m_Grap.pItem == nullptr)
			{
				m_Info.state = STATE_GRAP;
				m_pMotion->Set(TYPE_GRAP);
			}
			else
			{
				if (m_Grap.pEnemy != nullptr)
				{
					m_Grap.pEnemy->SetCurrent(nullptr);
					m_Grap.pEnemy->SetPosition(m_Info.pos);
					m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_Grap.pEnemy->SetState(CEnemy::STATE_NEUTRAL);
					m_Grap.pEnemy->SetChase(CEnemy::CHASE_ON);
					m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_NEUTRAL);
					m_Grap.pEnemy = nullptr;
					m_nIdxEne = -1;
					m_Info.state = STATE_NEUTRAL;
					m_pMotion->Set(TYPE_NEUTRAL);
					m_bGrap = false;
				}

				if (m_Grap.pItem != nullptr)
				{
					m_Grap.pItem->SetCurrent(nullptr);
					m_Grap.pItem->SetPosition(m_Info.pos);
					m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_Grap.pItem = nullptr;
					m_Info.state = STATE_NEUTRAL;
					m_pMotion->Set(TYPE_NEUTRAL);
					m_bLift = false;
				}
			}
		}
	}

	if (m_fStamina > 0.0f && m_bGrap == true && m_Info.state != STATE_HEAT)
	{// 敵を掴んでいたらスタミナを減らす

		m_fStamina -= GRAP_LOST_STMINA;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	if (m_fStamina < 0.0f && m_bGrap == true)
	{// スタミナがなくなったかつ敵を掴んでいたら

		// 敵を離す
		if (m_Grap.pEnemy != nullptr)
		{
			m_Grap.pEnemy->SetCurrent(nullptr);
			m_Grap.pEnemy->SetPosition(m_Info.pos);
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_Grap.pEnemy->SetState(CEnemy::STATE_NEUTRAL);
			m_Grap.pEnemy->SetChase(CEnemy::CHASE_ON);
			m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_NEUTRAL);
			m_Grap.pEnemy = nullptr;
			m_nIdxEne = -1;
			m_Info.state = STATE_NEUTRAL;
			m_pMotion->Set(TYPE_NEUTRAL);
			m_bGrap = false;
		}
	}

	// 敵またはアイテムを掴む
	{
		if (m_Info.state == STATE_GRAP && m_bGrap == false && m_bLift == false)
		{
			float f = EnemyDistance();
			float g = ItemDistance();
			if (f >= g)
			{// 範囲内

				if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
				{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

					if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pItem->GetPosition(), 40.0f, 40.0f) == true)
					{// 範囲内

						m_Grap.pItem = m_pItem;

						// 親、位置、向き、状態、追尾、モーションを設定し、掴んでいることにする
						m_Grap.pItem->SetCurrent(m_ppCharacter[9]->GetMtxWorld());
						m_Grap.pItem->SetPosition(D3DXVECTOR3(50.0f, 5.0f, -15.0f));
						m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
						m_Grap.pEnemy = nullptr;
						m_nIdxEne = -1;
						m_bLift = true;
					}
				}
			}
			else
			{
				if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
				{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

					if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pEnemy->GetPosition(), 40.0f, 40.0f) == true
						/*&& m_pEnemy->GetState() == CEnemy::STATE_PAINFULDAMAGE || m_pEnemy->GetState() == CEnemy::STATE_GETUP*/)
					{// 範囲内かつ敵がコケている

						m_Grap.pEnemy = m_pEnemy; 

						// 親、位置、向き、状態、追尾、モーションを設定し、掴んでいることにする
						m_Grap.pEnemy->SetCurrent(m_ppCharacter[9]->GetMtxWorld());
						m_Grap.pEnemy->SetPosition(ENEMY_GRAP_POS[m_Grap.pEnemy->GetType()]);
						m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
						m_Grap.pEnemy->SetState(CEnemy::STATE_GRAP);
						m_Grap.pEnemy->SetChase(CEnemy::CHASE_OFF);
						m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_GRAP);
						m_nIdxEne = m_Grap.pEnemy->GetIdxID();
						m_Grap.pItem = nullptr;
						m_bGrap = true;
					}
				}
			}
		}
	}
	
}

//================================================================
// 回避処理
//================================================================
void CPlayer::Avoid(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	if ((InputKeyboard->GetTrigger(DIK_LSHIFT) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true))
	{
		if (m_Info.state != STATE_AVOID && m_Info.state != STATE_LIFT &&
			m_Info.state != STATE_THROW && m_Info.state != STATE_GRAP && 
			m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_GRAPWALK && 
			m_Info.state != STATE_HEAT)
		{
			if (m_fStamina >= LOST_STMINA)
			{// 消費量より多かったら

				// スタミナ減らして回避状態に
				m_bAvoid = true;
				m_fStamina -= LOST_STMINA;
				m_Info.state = STATE_AVOID;
				m_pMotion->Set(TYPE_AVOID);

				if (m_pStamina != nullptr)
				{
					m_pStamina->GetBill()->SetTex(m_fStamina);
				}
			}
		}
	}
}

//================================================================
// 状態処理
//================================================================
void CPlayer::State(void)
{
	// 敵を掴む
	if (m_bLift == true && m_bDesh == true && m_Info.state != STATE_HEAT)
	{
		if (m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_THROW)
		{
			m_Info.state = STATE_GRAPDASH;
			m_pMotion->Set(TYPE_GRAPDASH);
		}
	}

	if (m_bGrap == true && m_bDesh == true && m_Info.state != STATE_HEAT)
	{
		if (m_Info.state != STATE_GRAPWALK)
		{
			m_Info.state = STATE_GRAPWALK;
			m_pMotion->Set(TYPE_GRAPWALK);
		}
	}

	// 通常攻撃・こぶしorアイテム
	if (m_Info.state == STATE_ATTACK && m_Info.state != STATE_HEAT)
	{
		// アイテム
		if (m_Grap.pItem != nullptr)
		{
			D3DXMATRIX *mtx = m_Grap.pItem->GetMtxWorld();

			D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Objpos.x = mtx->_41;
			Objpos.y = mtx->_42;
			Objpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				CGame::GetCollision()->AttackCircle(&Objpos, 50.0f, 50.0f, 100.0f);
			}
		}
		else // こぶし
		{
			D3DXMATRIX *mtx = m_ppCharacter[9]->GetMtxWorld();

			D3DXVECTOR3 Handpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Handpos.x = mtx->_41;
			Handpos.y = mtx->_42;
			Handpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				CGame::GetCollision()->AttackCircle(&Handpos, 25.0f, 50.0f, 100.0f);
			}
		}
	}

	// アイテムを持った
	if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW &&m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_HEAT && m_bLift == true)
	{
		m_Info.state = STATE_LIFT;
		m_pMotion->Set(TYPE_LIFT);
	}

	// 回避
	if (m_Info.state == STATE_AVOID)
	{
		m_bDesh = false;
		m_Info.move.x += sinf(m_Info.rot.y + D3DX_PI) * 0.5f;
		m_Info.move.z += cosf(m_Info.rot.y + D3DX_PI) * 0.5f;

		if (m_pMotion->GetInvincibleStrat() <= m_pMotion->GetNowFrame() && m_pMotion->GetInvincibleEnd() >= m_pMotion->GetNowFrame())
		{// 時間内だったら完全無敵にする

			m_bInvi = true;
		}
		else
		{// 完全無敵終了

			m_bInvi = false;
		}
	}

	// 持っているアイテムで攻撃した
	if (m_Info.state == STATE_THROW && m_Grap.pItem != nullptr)
	{
		m_Grap.pItem->SetPosition(D3DXVECTOR3(50.0f, -30.0f, -15.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI, -D3DX_PI * 0.5f));
		CGame::GetCollision()->ItemAttack(m_Grap.pItem);
	}

	// 持っているアイテムとの親子関係を切る
	if (m_pMotion->GetNumFrame() >= m_pMotion->GetAttackEnd() && m_Grap.pItem != nullptr && (m_Info.state == STATE_THROW || m_Info.state == STATE_HEAT))
	{
		m_Grap.pItem->SetCurrent(nullptr);
		m_Grap.pItem->SetPosition(D3DXVECTOR3(m_Info.pos.x + sinf(m_Info.rot.y) * -60.0f, m_Info.pos.y, m_Info.pos.z + cosf(m_Info.rot.y) * -60.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
		m_Grap.pItem = nullptr;
	}
	
	// モーションを移動モーションにする
	if (m_Info.state != STATE_MOVE && m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH 
		&& m_Info.state != STATE_GRAPWALK && m_Info.state != STATE_THROW && m_Info.state != STATE_HEAT
		&& m_bDesh == true && m_bAttack == false && m_bAvoi == false)
	{
		m_Info.state = STATE_MOVE;

		//モーションをセット(移動)
		m_pMotion->Set(TYPE_MOVE);
	}

	// モーションが終了かつヒートアクション中
	if (m_pMotion->IsFinish() == true && m_Info.state == STATE_HEAT)
	{
		// カメラをもとの位置に戻す
		CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
	}

	// モーションが終了かつ敵を投げるモーション
	if (m_pMotion->IsFinish() == false && m_pMotion->GetType() == STATE_ENEMYGRAP)
	{
		if (m_Grap.pEnemy != nullptr)
		{
			m_Grap.pEnemy->SetCurrent(m_ppCharacter[6]->GetMtxWorld());
			m_Grap.pEnemy->SetPosition(D3DXVECTOR3(-15.0f, 0.0f, 80.0f));
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
		}
	}

	// 待機モーションにする
	if (m_pMotion->IsFinish() == true || (m_bDesh == false && m_bLift == true && m_Info.state == STATE_GRAPDASH)
		|| (m_bDesh == false && m_bGrap == true && m_Info.state == STATE_GRAPWALK)
		|| (m_bDesh == false && m_bGrap == false && m_bLift == false 
		 && m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_AVOID
		 && m_Info.state != STATE_LIFT && m_Info.state != STATE_HEAT && m_Info.state != STATE_THROW
		 && m_Info.state != STATE_AVOID && m_Info.state != STATE_GRAP))
	{
		//モーションをセット(待機)
		m_pMotion->Set(TYPE_NEUTRAL);
		m_Info.state = STATE_NEUTRAL;
		m_bLift = false;
		m_bAttack = false;
		m_nCntColi = 0;

		if (CGame::GetCollision() != nullptr)
		{
			CGame::GetCollision()->SetbColli(false);
		}
		
		if (m_Grap.pItem != nullptr)
		{
			m_Info.state = STATE_LIFT;
			m_pMotion->Set(TYPE_LIFT);
			m_bLift = true;
		}

		if (m_Grap.pEnemy != nullptr)
		{
			m_Info.state = STATE_GRAPNEUTRAL;
			m_pMotion->Set(TYPE_GRAPNEUTRAL);
			m_bGrap = true;
		}
	}
}

//================================================================
// ダメージ
//================================================================
void CPlayer::Damege(void)
{
	if (m_Info.state == STATE_HEAT)
	{
		if (m_Info.state != STATE_DAMEGE)
		{
			m_Info.state = STATE_DAMEGE;
			m_nDamegeCounter = 10;
		}

		m_Info.nLife--;

		m_nDamegeCounter--;
	}
}

//================================================================
// ヒートアクション
//================================================================
void CPlayer::Heat(void)
{
	// アイテムを持っているときまたはアイテムを持って走っているとき
	if (m_Info.state == STATE_LIFT || m_Info.state == STATE_GRAPDASH)
	{
		// 距離を測って一番近くの敵を覚える
		EnemyDistance();
			
		if (m_pEnemy != nullptr)
		{
			if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pEnemy->GetPosition(), 50.0f, 50.0f) == true)
			{// 範囲内に入ったらYボタンが出てくる

				m_HeatAct = HEAT_SMASH;

				// Xボタンが出てくる
				{
					if (m_pBotton == nullptr)
					{
						m_pBotton = CObject2D::Create();
						m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
						m_pBotton->SetSize(HEATACT_BUTTON_SIZE.x, HEATACT_BUTTON_SIZE.y);
						m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Xbutton.png"));
						m_pBotton->SetDraw(true);
					}

					if (m_pBotton != nullptr)
					{
						//CEffect2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.7f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30.0f, 30, CEffect2D::TYPE_SMOOK);
					}
				}

				if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true)
				{// ヒートアクションする

					m_pHeatAct = new CHeatAction;
					if (m_pHeatAct != nullptr)
					{
						m_pHeatAct->SetAction(m_HeatAct, this, m_pEnemy);
					}

					if(CGame::GetEnemyManager() != nullptr)
					CGame::GetEnemyManager()->SetTarget(m_pEnemy->GetIdxID());

					m_Info.state = STATE_HEAT;

					// ヒートアクションしている
					m_bHeatActFlag = true;

					if (m_pBotton != nullptr)
					{
						m_pBotton->Uninit();
						m_pBotton = nullptr;
					}
				}
			}
			else
			{
				if (m_pBotton != nullptr)
				{
					m_pBotton->Uninit();
					m_pBotton = nullptr;
				}
			}
		}
	}

	// 電子レンジ
	if (m_bGrap == true && m_nUseCounter == 0)
	{// 敵を掴んでいる

		CItem *pItem = CItem::GetTop();

		while (pItem != nullptr)
		{
			CItem *pItemNext = pItem->GetNext();

			if (pItem->GetType() == CItem::TYPE_MICROWAVE)
			{
				m_pItemMicro = pItem;
			}

			pItem = pItemNext;
		}

		if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pItemMicro->GetPosition(), 30.0f, 40.0f))
		{// 範囲内

			m_HeatAct = HEAT_FIRE;

			// Xボタンが出てくる
			{
				if (m_pBotton == nullptr)
				{
					m_pBotton = CObject2D::Create();
					m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
					m_pBotton->SetSize(HEATACT_BUTTON_SIZE.x, HEATACT_BUTTON_SIZE.y);
					m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Xbutton.png"));
					m_pBotton->SetDraw(true);
				}
			}

			if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true)
			{// ヒートアクションする

				m_pHeatAct = new CHeatAction;
				if (m_pHeatAct != nullptr)
				{
					m_pHeatAct->SetAction(m_HeatAct, this, m_pEnemy);
				}

				if (CGame::GetEnemyManager() != nullptr)
					CGame::GetEnemyManager()->SetTarget(m_pEnemy->GetIdxID());

				m_pMotion->Set(TYPE_ENEMYGRAP);

				m_Info.state = STATE_HEAT;

				// ヒートアクションしている
				m_bHeatActFlag = true;

				// 敵を離す
				m_bGrap = false;

				if (m_pBotton != nullptr)
				{
					m_pBotton->Uninit();
					m_pBotton = nullptr;
				}
			}
		}
		else
		{
			if (m_pBotton != nullptr)
			{
				m_pBotton->Uninit();
				m_pBotton = nullptr;
			}
		}
	}
}

//================================================================
// 外部ファイル読み込み
//================================================================
void CPlayer::ReadText(const char *fliename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(fliename, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_MODEL", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumModel);  //モデルの総数

					m_ppCharacter = new CCharacter*[m_nNumModel];

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //モデルの名前

					m_ppCharacter[nCntModel] = CCharacter::Create(m_filename);
					nCntModel++;

					nCntParts++;

				}  //MODEL_LILENAMEのかっこ

				if (strcmp("CHARACTERSET", aString) == 0)
				{
					while (strcmp("END_CHARACTERSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("PARTSSET", aString) == 0)
						{
							while (strcmp("END_PARTSSET", aString) != 0)
							{
								fscanf(pFile, "%s", &aString);

								if (strcmp("INDEX", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nIdx);  //モデルの番号
								}

								if (strcmp("PARENT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nParent);  //親モデルの番号

									if (m_nParent > -1 && m_nNumModel > m_nParent)
									{
										m_ppCharacter[nCntParts2]->SetParent(m_ppCharacter[m_nParent]);
									}
									else
									{
										m_ppCharacter[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_ppCharacter[nCntParts2]->SetPositionOri(m_Readpos);

									m_ppCharacter[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.z);  //モデルの総数

									m_ppCharacter[nCntParts2]->SetRotOrigin(m_Readrot);

									m_ppCharacter[nCntParts2]->SetRot(m_Readrot);
								}

							}//END_PARTSSETのかっこ

							nCntParts2++;

						}//PARTSSETのかっこ

					}//END_CHARACTERSETのかっこ 

				}//CHARACTERSETのかっこ 
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}

	if (m_pMotion != nullptr)
	{
		// モデルの設定
		m_pMotion->SetModel(m_ppCharacter, m_nNumModel);

		// 初期化処理
		m_pMotion->ReadText(fliename);

		// セット(待機)
		m_pMotion->Set(TYPE_NEUTRAL);
	}
}

//================================================================
// 敵との距離算出
//================================================================
float CPlayer::EnemyDistance(void)
{
	float fLenght = 10000.0f;
	float fLenghtDiff = 0.0f;  // 比較用

	CEnemy *pEnemy = CEnemy::GetTop();

	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();

		// 自分と敵の距離を取得
		if (CManager::Getinstance()->GetUtility() != nullptr)
			fLenghtDiff = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, pEnemy->GetPosition());

		// 距離を比較
		if (fLenght >= fLenghtDiff)
		{
			fLenght = fLenghtDiff;
			
			// 一番近くの敵を覚える
			m_pEnemy = pEnemy;
		}
			
		pEnemy = pEnemyNext;
	}

	return fLenght;
}

//================================================================
// アイテムとの距離算出
//================================================================
float CPlayer::ItemDistance(void)
{
	float fLenght = 10000.0f;
	float fLenghtDiff = 0.0f;  // 比較用

	CItem *pItem = CItem::GetTop();

	while (pItem != nullptr)
	{
		CItem *pItemNext = pItem->GetNext();

		if (pItem->GetType() == CItem::TYPE_BIKE)
		{
			// 自分とアイテムの距離を取得
			if (CManager::Getinstance()->GetUtility() != nullptr)
				fLenghtDiff = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, pItem->GetPosition());

			// 距離を比較
			if (fLenght >= fLenghtDiff)
			{
				fLenght = fLenghtDiff;

				// 一番近くの敵を覚える
				m_pItem = pItem;
			}
		}
		
		pItem = pItemNext;
	}

	return fLenght;
}