//===========================================================
//
//プレイヤー処理[player.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "character.h"
#include "bullet.h"
#include "effect.h"
#include "particl.h"
#include "map.h"
#include "collision.h"
#include "enemy.h"
#include "UImanager.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
//マクロ定義
//================================================================
#define MAX_LIFECHIBI (10)                                        //チビの体力
#define MAX_LIFEFOOT  (6)                                         //デブの体力
#define REST_BULLET   (30)                                        //保持できる弾の数
#define BULLETWAIT    (15)                                        //射撃の間隔
#define MUTEKITIME    (30)                                        //無敵時間
#define PLAYER_X      (40.0f)                                     //プレイヤーのX軸の幅
#define PLAYER_Z      (10.0f)                                     //プレイヤーのZ軸の幅
#define CHIBISPEED    (0.9f)                                      //チビデブの走る速さ
#define FOOTSPEED     (1.1f)                                      //クソデブの走る速さ
#define CHIBIJUMP     (20.0f)                                     //チビデブのジャンプ力
#define FOOTJUMP      (22.0f)                                     //クソデブのジャンプ力
#define CHIBIGRAVITY  (0.7f)                                      //チビデブの重力
#define FOOTGRAVITY   (0.9f)                                      //クソデブの重力
#define FRIST         (21)                                        //攻撃判定発生開始
#define FINISH        (31)                                        //攻撃判定終了
#define PLAYER01_TEXT ("data\\TEXT\\motion_set_player.txt")       //プレイヤーのテキストファイル
#define PLAYER02_TEXT ("data\\TEXT\\motion_set_player2.txt")      //プレイヤーのテキストファイル

//================================================================
//静的メンバ変数宣言
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
//コンストラクタ
//================================================================
CPlayer::CPlayer()
{
	/*ZeroMemory(m_Chibi, sizeof(CChibi));
	ZeroMemory(m_Foot, sizeof(CFoot));*/
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	//m_rot = { 0.0f, 0.0f, 0.0f };
	
	m_nCnterMotion = 0;
	m_nCntMotion = 0;
	m_nCntEff = 0;
	m_nCntDuration = 0;
	m_nCntDie = 0;
	m_nCntSound = 0;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nLifeGage = -1;
	m_RestBullet = 0;
	m_ApprCharcter = 0;
	
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
	m_bJump = false;
	m_bAction = false;
	m_bEncounter = false;
	m_bIconDisp = false;
	m_bAcFir = false;
	m_bAcSec = false;
	m_bAcThr = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CPlayer::CPlayer(D3DXVECTOR3 pos)
{
	/*ZeroMemory(m_Chibi, sizeof(CChibi));
	ZeroMemory(m_Foot, sizeof(CFoot));*/
	SetPos(&pos);  //位置
	SetRot(&D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	m_move = {0.0f, 0.0f, 0.0f};  //移動量
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	m_nCnterMotion = 0;
	m_nCntMotion = 0;
	m_nCntEff = 0;
	m_nCntDuration = 0;
	m_nCntDie = 0;
	m_nCntSound = 0;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nLifeGage = -1;
	m_RestBullet = 0;
	m_ApprCharcter = 0;
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
	m_bJump = false;
	m_bAction = false;
	/*m_bDisp = false;
	m_bAppr = false;*/
	m_bEncounter = false;
	m_bIconDisp = false;
	m_bAcFir = false;
	m_bAcSec = false;
	m_bAcThr = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//デストラクタ
//================================================================
CPlayer::~CPlayer()
{

}

//================================================================
//生成処理
//================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CPlayer *pPlayer = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == NULL)
		{
			//オブジェクト2Dの生成
			pPlayer = new CPlayer(pos);

			//初期化処理
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
//プレイヤーの初期化処理
//================================================================
HRESULT CPlayer::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//影の情報を取得
	//CShadow *pShadow = CGame::GetShadow();

	D3DXVECTOR3 pos = Getpos();

	//種類設定
	SetType(TYPE_PLAYER);

	//if (m_pShadow == NULL)
	//{
	//	m_pShadow = new CShadow(pos);

	//	//初期化処理
	//	m_pShadow->Init();
	//}

	m_RestBullet = REST_BULLET;

	m_fDest = 1.57f;

	return S_OK;
}

//================================================================
//プレイヤーの終了処理
//================================================================
void CPlayer::Uninit(void)
{
	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンドストップ
	pSound->Stop();

	CObject::Release();
}

//================================================================
//プレイヤーの更新処理
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

	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	if (pChibi != nullptr && pFoot != nullptr)
	{
		if ((InputKeyboard->GetTrigger(DIK_F) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
			&& pFoot->GetState() != CFoot::STATE_APPR && pChibi->GetState() != CChibi::STATE_APPR
			&& pFoot->GetState() != CFoot::STATE_JUMP && pChibi->GetState() != CChibi::STATE_JUMP
			&& pFoot->GetState() != CFoot::STATE_ATTACK && pChibi->GetState() != CChibi::STATE_ATTACK
			&& pFoot->GetState() != CFoot::STATE_DEATH && pChibi->GetState() != CChibi::STATE_DEATH
			&& pChibi->GetState() != CChibi::STATE_RELOAD
			&& pChibi->GetState() != CChibi::STATE_DAMAGE && pFoot->GetState() != CFoot::STATE_DAMAGE)
		{//SPACEキーが押された

			//サウンドストップ
			pSound->Play(CSound::SOUND_LABEL_CHANGE);

			if (pChibi->GetbAppr() == false)
			{
				pChibi->SetbDisp(true);
				pChibi->SetbAppr(true);

				pFoot->SetbDisp(false);
				pFoot->SetbAppr(false);

				pChibi->SetPos(&pFoot->Getpos());
				pChibi->SetRot(&pFoot->GetRot());

				CParticl::Create({ pChibi->Getpos().x, pChibi->Getpos().y, pChibi->Getpos().z }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 10.0f, CParticl::TYPEPAR_CIRCLE);
			}

			else if (pFoot->GetbAppr() == false)
			{
				pFoot->SetbDisp(true);
				pFoot->SetbAppr(true);

				pChibi->SetbDisp(false);
				pChibi->SetbAppr(false);

				pFoot->SetPos(&pChibi->Getpos());
				pFoot->SetRot(&pChibi->GetRot());

				CParticl::Create({ pFoot->Getpos().x, pFoot->Getpos().y, pFoot->Getpos().z }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 10.0f, CParticl::TYPEPAR_CIRCLE);
			}

			pChibi->SetState(CChibi::STATE_APPR);
			pFoot->SetState(CFoot::STATE_APPR);
		}
	}

	if (pChibi->GetState() == CChibi::STATE_DEATH && pFoot->GetState() == CFoot::STATE_DEATH)
	{
		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをタイトルに遷移
			pFade->Set(CScene::MODE_RESULT);
		}
	}
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	D3DXVECTOR3 pos = Getpos();
	D3DXVECTOR3 rot = GetRot();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//================================================================
//プレイヤーの制御処理
//================================================================
void CPlayer::ControlPlayer(void)
{
	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	if (pChibi->GetbAppr() == true)
	{
		//チビデブの制御
		pChibi->Control();
	}

	if (pFoot->GetbAppr() == true)
	{
		//クソデブの制御
		pFoot->Control();
	}
}

//================================================================
//攻撃くらった時の処理
//================================================================
void CChibi::Hit(void)
{
	if (m_bDamage != true)
	{
		int life = GetLife();

		life--;

		SetLife(life);

		m_State = STATE_DAMAGE;

		m_bDamage = true;

		m_nCntDamage = 80;
	}
}

//================================================================
//プレイヤーの制御処理(チビデブ)
//================================================================
void CChibi::Control(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

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

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//位置と向きを取得
	D3DXVECTOR3 m_pos = pChibi->Getpos();
	D3DXVECTOR3 PlayerRot = pChibi->GetRot();

	if (m_State != STATE_DEATH)
	{
		m_posOld = m_pos;  //位置を代入

						   //float fHeight;

		if ((m_State != STATE_ATTACK || (m_State == STATE_ATTACK && m_bJump == true) || m_bRand == false) && m_State != STATE_APPR)
		{
			//重力
			m_move.y -= CHIBIGRAVITY;
		}
		 
		//走っていない状態
		m_bDash = false;

		if (m_State != STATE_APPR && m_State != STATE_ATTACK)
		{
			if (InputKeyboard->GetPress(DIK_W) == true)
			{//Wキーが押された

				m_nLife--;
			}

			if (InputKeyboard->GetPress(DIK_S) == true)
			{//Wキーが押された

				m_nLife++;
			}

			////上に移動----------------------------------------------
			//if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LY, 0) > 0)
			//{//Wキーが押された

			//}
			////下に移動----------------------------------------------
			//else if (InputKeyboard->GetPress(DIK_S) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LY, 0) < 0)
			//{//Sキーが押された

			//}

			//右に移動----------------------------------------------
			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LX, 0) > 0 && m_bAction != true)
			{//Dキーだけ押した

			 //移動量
				m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * CHIBISPEED;

				//向き
				m_fDest = D3DX_PI * -0.5f;

				//走っている状態にする
				m_bDash = true;
			}
			//左に移動----------------------------------------------
			if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LX, 0) < 0 && m_bAction != true)
			{//Aキーだけ押した

			 //移動量
				m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * CHIBISPEED;

				//向き
				m_fDest = D3DX_PI * 0.5f;

				//走っている状態にする
				m_bDash = true;
			}

			//向き代入
			PlayerRot.y = m_fDest;
		}

		if (m_State != STATE_APPR)
		{
			//ジャンプ---------------
			if ((InputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true) && m_bJump == false)
			{//SPACEキーが押された

				m_bJump = true;

				m_move.y += CHIBIJUMP;

				//サウンドストップ
				pSound->Play(CSound::SOUND_LABEL_SEJUMP00);
			}

			//攻撃-------------------
			if ((InputKeyboard->GetPress(DIK_K) == true || pInputJoyPad->GetPress(CInputJoyPad::BUTTON_RB, 0) == true) && m_RestBullet > 0)
			{//Kキーが押された

				m_bAction = true;

				if (m_nCntBullet == 0)
				{
					D3DXMATRIX Matrix = m_apModel[5]->GetMtxWorld();

					//弾生成
					CBullet::Create(D3DXVECTOR3(Matrix._41, Matrix._42, Matrix._43), D3DXVECTOR3(0.0f, m_fDest, 0.0f), CBullet::TYPE_PLAYER);

					//サウンドストップ
					pSound->Play(CSound::SOUND_LABEL_SEMAGIC);

					m_RestBullet--;
				}

				if (m_bDash == true)
				{
					m_bDash = false;
				}

				m_nCntBullet++;
			}

			if (m_bDash == true && m_State != STATE_MOVE && m_State != STATE_ATTACK)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_MOVE);

				m_State = STATE_MOVE;

				m_bAction = false;
			}

			if (m_bDash == false && m_State != STATE_NEUTRAL && m_State != STATE_ATTACK && m_State != STATE_APPR && m_State != STATE_RELOAD)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_NEUTRAL);

				m_State = STATE_NEUTRAL;

				m_bAction = false;
			}

			if (m_bJump == true && m_State != STATE_JUMP)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_JUMP);

				m_State = STATE_JUMP;
			}

			if ((InputKeyboard->GetPress(DIK_R) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_LB, 0) == true) && m_bJump != true && m_bAction != true && m_State != STATE_RELOAD)
			{
				m_State = STATE_RELOAD;

				m_motion->Set(MOTIONTYPE_RELOAD);

				pSound->Play(CSound::SOUND_LABEL_SEMAGICPOWER);
			}

			if (m_bAction == true && m_bDash != true && m_State != STATE_ATTACK)
			{
				//モーションをセット(攻撃)
				m_motion->Set(MOTIONTYPE_ATTACK);

				m_State = STATE_ATTACK;
			}

			if (m_nCntBullet >= BULLETWAIT)
			{
				m_nCntBullet = 0;
			}
		}

		//位置に移動量加算----------------------------------------------------
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;

		//m_pos.y = fHeight + 18.0f;

		//移動量を更新(減衰させる)--------------------------------------------
		m_move.x += (0.0f - m_move.x) * 0.1f;

		if (m_State == STATE_APPR && m_WaitApper == false)
		{
			//モーションをセット(出現待ち)
			m_motion->Set(MOTIONTYPE_APPR);

			PlayerRot.y = 0.0f;

			m_WaitApper = true;
		}

		if (m_motion->IsFinish() == true)
		{
			m_nCntEff = 0;
			m_nCntColi = 0;
			m_bAction = false;

			if (m_State == STATE_APPR)
			{
				m_WaitApper = false;

				pChibi->SetState(STATE_NONE);
				pFoot->SetState(CFoot::STATE_NONE);
			}
			else if (m_State == STATE_RELOAD)
			{
				m_RestBullet = REST_BULLET;

				m_State = STATE_NONE;
			}
			else
			{
				m_State = STATE_NONE;

				m_nCntBullet = 0;
			}
		}

		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;

			m_move.y = 0.0f;

			m_bJump = false;
		}

		if (m_RestBullet <= 0)
		{
			pDebugProc->Print("\n球切れだよ～～\n");
		}

		if (m_bDash == true && m_nCntSound == 0)
		{
			m_nCntSound = 35;

			pSound->Play(CSound::SOUND_LABEL_SEASIOTO);
		}

		if (m_nCntSound > 0)
		{
			m_nCntSound--;
		}

		if (m_bDamage == true)
		{
			m_nCntDamage--;

			if (m_nCntDamage <= 0)
			{
				m_bDamage = false;
			}
		}
	}
	
	SetPos(&m_pos);
	SetRot(&PlayerRot);

	pFoot->SetPos(&m_pos);

	pDebugProc->Print("\nプレイヤーの位置：%f,%f,%f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("プレイヤーの向き：%f,%f,%f\n", PlayerRot.x, PlayerRot.y, PlayerRot.z);
	pDebugProc->Print("プレイヤーの移動量：%f,%f,%f\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("残りの弾数：%d", m_RestBullet);
}

//================================================================
//攻撃くらった時の処理
//================================================================
void CFoot::Hit(void)
{
	if (m_bDamage != true)
	{
		m_nLife--;

		m_State = STATE_DAMAGE;

		m_bDamage = true;

		m_nCntDamage = 80;
	}
}

//================================================================
//プレイヤーの制御処理(クソデブ)
//================================================================
void CFoot::Control(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

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

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//プレイヤー(チビデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	//位置と向きを取得
	D3DXVECTOR3 m_pos = pFoot->Getpos();
	D3DXVECTOR3 PlayerRot = pFoot->GetRot();

	if (m_State != STATE_DEATH)
	{
		m_posOld = m_pos;  //位置を代入

						   //float fHeight;

		m_bRand = false;

		if ((m_bRand != true || m_bJump == true) && m_State != STATE_APPR)
		{
			//重力
			m_move.y -= FOOTGRAVITY;
		}
		
		//走っていない状態
		m_bDash = false;

		if (m_State != STATE_APPR)
		{
			////上に移動----------------------------------------------
			//if (InputKeyboard->GetPress(DIK_W) == true)
			//{//Wキーが押された

			//}
			////下に移動----------------------------------------------
			//else if (InputKeyboard->GetPress(DIK_S) == true)
			//{//Sキーが押された

			//}
			//右に移動----------------------------------------------
			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LX, 0) > 0 && m_bAttack != true)
			{//Dキーだけ押した

			 //移動量
				m_move.x += sinf((D3DX_PI * 0.5f)) * FOOTSPEED;
				m_move.z += cosf((D3DX_PI * 0.5f)) * FOOTSPEED;

				//向き
				m_fDest = ((D3DX_PI * -0.5f));

				//走っている状態にする
				m_bDash = true;
			}
			//左に移動----------------------------------------------
			if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetXStick(CInputJoyPad::STICK_LX, 0) < 0 && m_bAttack != true)
			{//Aキーだけ押した

			 //移動量
				m_move.x -= sinf((D3DX_PI * 0.5f)) * FOOTSPEED;
				m_move.z -= cosf((D3DX_PI * 0.5f)) * FOOTSPEED;

				//向き
				m_fDest = ((D3DX_PI * 0.5f));

				//走っている状態にする
				m_bDash = true;
			}

			PlayerRot.y = m_fDest;


			//ジャンプ------------
			if ((InputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true) && m_bJump == false && m_bAttack != true)
			{//SPACEキーが押された

				m_bJump = true;

				m_move.y += FOOTJUMP;

				//サウンドストップ
				pSound->Play(CSound::SOUND_LABEL_SEJUMP01);
			}

			//攻撃----------------
			if (InputKeyboard->GetTrigger(DIK_K) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_RB, 0) == true && m_bAttack == false)
			{//Kキーが押された

				m_bAttack = true;

				//サウンドストップ
				pSound->Play(CSound::SOUND_LABEL_SESWORD);

				//m_State = STATE_ATTACK;
			}

			if (m_bAttack == true)
			{
				m_nCntColi++;

				if (m_nCntColi >= 10 && 30 >= m_nCntColi)
				{
					if (pCollision != NULL)
					{
						if (pCollision->Sword(m_apModel[28]->GetMtxWorld(), m_apModel[28]->GetMtxWorld(), 100.0f, pEnemy) == true)
						{
							int n = 0;
						}
					}
				}
			}

			if (m_bDash == true && m_bAttack == false
				&& m_State != STATE_MOVE && m_State != STATE_ATTACK)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_MOVE);

				m_State = STATE_MOVE;
			}

			if (m_bDash == false && m_bAttack == false
				&& m_State != STATE_NEUTRAL && m_State != STATE_ATTACK && m_State != STATE_APPR)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_NEUTRAL);

				m_State = STATE_NEUTRAL;
			}

			if (m_bJump == true && m_bAttack == false && m_State != STATE_JUMP)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_JUMP);

				m_State = STATE_JUMP;
			}

			if (m_bAttack == true && m_bDash != true && m_State != STATE_ATTACK)
			{
				//モーションをセット(攻撃)
				m_motion->Set(MOTIONTYPE_ATTACK);

				m_State = STATE_ATTACK;
			}
		}

		//位置に移動量加算----------------------------------------------------
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;

		//m_pos.y = fHeight + 18.0f;

		//移動量を更新(減衰させる)--------------------------------------------
		m_move.x += (0.0f - m_move.x) * 0.1f;

		if (m_State == STATE_APPR && m_WaitApper == false)
		{
			//モーションをセット(出現待ち)
			m_motion->Set(MOTIONTYPE_APPR);

			PlayerRot.y = 0.0f;

			m_WaitApper = true;
		}

		if (m_motion->IsFinish() == true)
		{
			m_nCntEff = 0;
			m_nCntColi = 0;
			m_bAttack = false;

			if (m_State == STATE_APPR)
			{
				m_WaitApper = false;

				pChibi->SetState(CChibi::STATE_NONE);
				pFoot->SetState(STATE_NONE);
			}
			else
			{
				m_State = STATE_NONE;
			}
		}

		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;

			m_move.y = 0.0f;

			m_bJump = false;
		}

		if (m_bDash == true && m_nCntSound == 0)
		{
			m_nCntSound = 35;

			pSound->Play(CSound::SOUND_LABEL_SEASIOTO);
		}

		if (m_nCntSound > 0)
		{
			m_nCntSound--;
		}

		if (m_bDamage == true)
		{
			m_nCntDamage--;

			if (m_nCntDamage <= 0)
			{
				m_bDamage = false;
			}
		}
	}

	SetPos(&m_pos);
	SetRot(&PlayerRot);

	pChibi->SetPos(&m_pos);

	pDebugProc->Print("\nプレイヤーの位置：%f,%f,%f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("プレイヤーの向き：%f,%f,%f\n", PlayerRot.x, PlayerRot.y, PlayerRot.z);
	pDebugProc->Print("プレイヤーの移動量：%f,%f,%f", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("\n判定 : %d", m_nCntColi);
}

//================================================================
//出現処理
//================================================================
void CPlayer::Appear(void)
{
	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	//それぞれの位置取得
	D3DXVECTOR3 Chibipos = pChibi->Getpos();
	D3DXVECTOR3 Footpos = pFoot->Getpos();

	if (pChibi->GetState() == CChibi::STATE_APPR && pChibi->GetbAppr() == true)
	{
		pChibi->SetMove({ -0.1f, 0.0f , 0.0f });
	}
	else if (pChibi->GetState() == CChibi::STATE_APPR && pChibi->GetbAppr() == false)
	{
		pChibi->SetMove({ 0.1f, 0.0f , 0.0f });
	}

	if (pFoot->GetState() == CFoot::STATE_APPR && pFoot->GetbAppr() == false)
	{
		pFoot->SetMove({ 0.1f, 0.0f , 0.0f });
	}
	else if (pFoot->GetState() == CFoot::STATE_APPR && pFoot->GetbAppr() == true)
	{
		pFoot->SetMove({ -0.1f, 0.0f , 0.0f });
	}

	Chibipos.x += pChibi->GetMove().x;
	Footpos.x += pFoot->GetMove().x;

	pChibi->SetPos(&Chibipos);
	pFoot->SetPos(&Footpos);
}

//================================================================
//チュートリアルのプレイヤーの制御処理
//================================================================
void CPlayer::ControlTutorial(void)
{
	
}

//================================================================
//攻撃くらった時の処理
//================================================================
void CPlayer::Hit(void)
{
	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(チビデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	if (pFoot->GetbAppr() == true)
	{
		pFoot->Hit();
	}

	if (pChibi->GetbAppr() == true)
	{
		pChibi->Hit();
	}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CFoot::ReadText(const char *fliename)
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

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //モデルの名前

					m_apModel[nCntModel] = CCharacter::Create(m_filename);
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
										m_apModel[nCntParts2]->SetParent(m_apModel[m_nParent]);
									}
									else
									{
										m_apModel[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.z);  //モデルの総数

									m_apModel[nCntParts2]->SetRotOrigin(m_Readrot);

									m_apModel[nCntParts2]->SetRot(m_Readrot);
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

	if (m_motion != NULL)
	{
		//モデルの設定
		m_motion->SetModel(&m_apModel[0], m_nNumModel);

		//初期化処理
		m_motion->ReadText(fliename);
	}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CChibi::ReadText(const char *fliename)
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

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //モデルの名前

					m_apModel[nCntModel] = CCharacter::Create(m_filename);
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
										m_apModel[nCntParts2]->SetParent(m_apModel[m_nParent]);
									}
									else
									{
										m_apModel[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.z);  //モデルの総数

									m_apModel[nCntParts2]->SetRotOrigin(m_Readrot);

									m_apModel[nCntParts2]->SetRot(m_Readrot);
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

	if (m_motion != NULL)
	{
		//モデルの設定
		m_motion->SetModel(&m_apModel[0], m_nNumModel);

		//初期化処理
		m_motion->ReadText(fliename);
	}
}

//******************************************************************************************************************************************************
//チビデブ
//******************************************************************************************************************************************************
//=======================================================
//コンストラクタ
//=======================================================
CChibi::CChibi()
{
	SetLife(MAX_LIFECHIBI);
	m_State = STATE_NONE;
	m_TitleState = TITLE_STATE_NONE;
	m_move = { 0.0f,0.0f,0.0f };
	m_nCntBullet = 0;
	m_nLife = 0;
	m_nCntDamage = 0;
	m_bRand = false;
	m_bDamage = false;
	m_motion = NULL;
}

//=======================================================
//コンストラクタ
//=======================================================
CChibi::CChibi(D3DXVECTOR3 pos)
{
	CObject::SetPos(&pos);  //位置
	SetLife(MAX_LIFECHIBI);
	m_pos = pos;
	SetRot(&D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	m_move = { 0.0f,0.0f,0.0f };
	m_State = STATE_NONE;
	m_TitleState = TITLE_STATE_NONE;
	m_nCntBullet = 0;
	m_nLife = 0;
	m_nCntDamage = 0;
	m_bRand = false;
	m_bDamage = false;
	m_motion = NULL;
}

//=======================================================
//デストラクタ
//=======================================================
CChibi::~CChibi()
{

}

//=======================================================
//初期化処理
//=======================================================
HRESULT CChibi::Init(void)
{
	CPlayer::Init();

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//弾の最大数設定
	m_RestBullet = REST_BULLET;

	//テキストファイル読み込み
	ReadText(PLAYER02_TEXT);

	//体力設定
	m_nLife = MAX_LIFECHIBI;

	

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		//体力ゲージのUI
		CUIManager::Create({ 125.0f, 50.0f, 0.0f }, CUIManager::TYPE_LIFECHIBI);

		//アイコン
		CUIManager::Create({ 25.0f, 50.0f, 0.0f }, CUIManager::TYPE_ICONCHIBI);

		//残弾表示UI
		CUIManager::Create({ 100.0f, 150.0f, 0.0f }, CUIManager::TYPE_GUNGAGE);

		//魔法UI
		CUIManager::Create({ 50.0f, 150.0f, 0.0f }, CUIManager::TYPE_MAGIC);

		m_fDest = -1.57f;
	}

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		//描画しない
		SetbDisp(false);

		//出現しない
		SetbAppr(false);
	}
	else
	{
		//描画しない
		SetbDisp(true);

		//出現しない
		SetbAppr(true);

		SetRot(&D3DXVECTOR3( 0.0f , (D3DX_PI * -0.5f) , 0.0f ));
	}


	return S_OK;
}

//=======================================================
//終了処理
//=======================================================
void CChibi::Uninit(void)
{
	if (m_motion != NULL)
	{
		//終了処理
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
	}

	//if (m_pShadow != NULL)
	//{
	//	//終了処理
	//	m_pShadow->Uninit();

	//	m_pShadow = NULL;
	//}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			m_apModel[nCount]->Uninit();  //終了処理
										  //delete m_apModel[nCount];  //メモリを開放
			m_apModel[nCount] = NULL;  //使用していない状態にする
		}
	}

	CPlayer::Uninit();
}

//=======================================================
//更新処理
//=======================================================
void CChibi::Update(void)
{
	//マップモデルの情報を取得
	CMap *pmap = CGame::GetMap();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		CPlayer::Update();
	}

	if (m_nLife > 0)
	{
		if (m_bAppr == true)
		{
			m_bRand = false;

			if (CScene::GetMode() == CScene::MODE_GAME)
			{
				Control();
			}
			else
			{
				D3DXVECTOR3 pos = Getpos();

				if (m_TitleState != TITLE_STATE_NEUTRAL && m_TitleState != TITLE_STATE_MOVE)
				{
					m_motion->Set(MOTIONTYPE_TITLE);

					m_TitleState = TITLE_STATE_NEUTRAL;
				}

				if (m_TitleState == TITLE_STATE_MOVE && m_bDash != true)
				{
					m_motion->Set(MOTIONTYPE_MOVE);

					m_bDash = true;
				}

				if (m_TitleState == TITLE_STATE_MOVE && m_bDash == true)
				{
					//移動量
					m_move.x += sinf((D3DX_PI * 0.5f)) * CHIBISPEED;
				}

				pos.x += m_move.x;

				//移動量を更新(減衰させる)--------------------------------------------
				m_move.x += (0.0f - m_move.x) * 0.1f;

				SetPos(&pos);
			}

			if (pmap != nullptr)
			{
				if (pCollision != nullptr && pmap->GetX() != nullptr)
				{
					(pCollision->Map(&Getpos(), &m_posOld, pmap->GetX()));
				}

				if (pCollision != nullptr)
				{
					if (pCollision->Enemy(&Getpos(), &m_posOld, 30.0f, 30.0f, pEnemy) == true)
					{
						Hit();
					}
				}
			}
		}

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_apModel[nCount]->Update();
		}

		if (m_motion != nullptr)
		{
			//初期化処理
			m_motion->Update();
		}
	}
	else
	{
		//終了処理
		//Uninit();

		m_State = STATE_DEATH;

		//プレイヤー(クソデブ)の情報を取得
		CFoot *pFoot = CGame::GetPlayerFoot();

		if (pFoot != nullptr)
		{
			if (pFoot->GetbAppr() == false && pFoot->GetState() != CChibi::STATE_DEATH)
			{
				pFoot->SetState(CFoot::STATE_APPR);

				pFoot->SetbDisp(true);
				pFoot->SetbAppr(true);

				SetbDisp(false);
				SetbAppr(false);
			}
		}
	}
}

//=======================================================
//描画処理
//=======================================================
void CChibi::Draw(void)
{
	if (m_bDisp == true)
	{
		CPlayer::Draw();

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			//描画処理
			m_apModel[nCount]->Draw();
		}
	}
}
CChibi * CChibi::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CChibi *pPlayer = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == NULL)
		{
			//オブジェクト2Dの生成
			pPlayer = new CChibi(pos);

			//初期化処理
			pPlayer->Init();
		}
	}

	return pPlayer;
}
//******************************************************************************************************************************************************
//クソデブ
//******************************************************************************************************************************************************
//=======================================================
//コンストラクタ
//=======================================================
CFoot::CFoot()
{
	SetLife(MAX_LIFEFOOT);
	m_move = { 0.0f,0.0f,0.0f };
	m_State = STATE_NONE;
	m_TitleState = TITLE_STATE_NONE;
	m_nLife = 0;
	m_nCntDamage = 0;
	m_bRand = false;
	m_motion = NULL;
}

//=======================================================
//コンストラクタ
//=======================================================
CFoot::CFoot(D3DXVECTOR3 pos)
{
	CObject::SetPos(&pos);  //位置]
	SetLife(MAX_LIFEFOOT);
	m_pos = pos;
	SetRot(&D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	m_move = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_nCntDamage = 0;
	m_State = STATE_NONE;
	m_TitleState = TITLE_STATE_NONE;
	m_bRand = false;
	m_motion = NULL;
}

//=======================================================
//デストラクタ
//=======================================================
CFoot::~CFoot()
{

}

//=======================================================
//初期化処理
//=======================================================
HRESULT CFoot::Init(void)
{
	CPlayer::Init();

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//テキストファイル読み込み
	ReadText(PLAYER01_TEXT);

	//体力設定
	m_nLife = MAX_LIFEFOOT;

	SetLife(MAX_LIFEFOOT);

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		//体力ゲージのUI
		CUIManager::Create({ 350.0f, 50.0f, 0.0f }, CUIManager::TYPE_LIFEFOOT);

		//アイコン
		CUIManager::Create({ 250.0f, 50.0f, 0.0f }, CUIManager::TYPE_ICONFOOT);

		m_fDest = -1.57f;
	}
	else
	{
		SetRot(&D3DXVECTOR3(0.0f, (D3DX_PI * -0.5f), 0.0f));
	}

	//描画する
	SetbDisp(true);

	//出現状態にする
	SetbAppr(true);
	
	return S_OK;
}

//=======================================================
//終了処理
//=======================================================
void CFoot::Uninit(void)
{
	if (m_motion != NULL)
	{
		//終了処理
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
	}

	//if (m_pShadow != NULL)
	//{
	//	//終了処理
	//	m_pShadow->Uninit();

	//	m_pShadow = NULL;
	//}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			m_apModel[nCount]->Uninit();  //終了処理
										  //delete m_apModel[nCount];  //メモリを開放
			m_apModel[nCount] = NULL;  //使用していない状態にする
		}
	}

	CPlayer::Uninit();
}

//=======================================================
//更新処理
//=======================================================
void CFoot::Update(void)
{
	CMap *pmap = CGame::GetMap();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		CPlayer::Update();
	}
	
	if (m_nLife > 0)
	{
		if (m_bAppr == true)
		{
			m_bRand = false;

			if (CScene::GetMode() == CScene::MODE_GAME)
			{
				Control();

				
			}
			else
			{
				D3DXVECTOR3 pos = Getpos();

				if (m_TitleState != TITLE_STATE_NEUTRAL && m_TitleState != TITLE_STATE_MOVE)
				{
					m_motion->Set(MOTIONTYPE_TITLE);

					m_TitleState = TITLE_STATE_NEUTRAL;
				}

				if (m_TitleState == TITLE_STATE_MOVE && m_bDash != true)
				{
					m_motion->Set(MOTIONTYPE_MOVE);

					m_bDash = true;
				}

				if (m_TitleState == TITLE_STATE_MOVE && m_bDash == true)
				{
					//移動量
					m_move.x += sinf((D3DX_PI * 0.5f)) * CHIBISPEED;
				}

				pos.x += m_move.x;

				//移動量を更新(減衰させる)--------------------------------------------
				m_move.x += (0.0f - m_move.x) * 0.1f;

				SetPos(&pos);
			}

			if (pmap != NULL)
			{
				//マップモデルの情報を取得
				//CObjectX **pMap = CMap::GetX();

				if (pCollision != NULL && pmap->GetX() != NULL)
				{
					(pCollision->Map(&Getpos(), &m_posOld, pmap->GetX()));
				}

				if (pCollision != nullptr)
				{
					if (pCollision->Enemy(&Getpos(), &m_posOld, 30.0f, 30.0f, pEnemy) == true)
					{
						Hit();
					}
				}
			}
		}

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_apModel[nCount]->Update();
		}

		if (m_motion != NULL)
		{
			//初期化処理
			m_motion->Update();
		}
	}
	else
	{
		//終了処理
		//Uninit();

		m_State = STATE_DEATH;

		//プレイヤー(クソデブ)の情報を取得
		CChibi *pChibi = CGame::GetPlayerChibi();

		if (pChibi != nullptr)
		{
			if (pChibi->GetbAppr() == false && pChibi->GetState() != CChibi::STATE_DEATH)
			{
				pChibi->SetState(CChibi::STATE_APPR);

				pChibi->SetbDisp(true);
				pChibi->SetbAppr(true);

				SetbDisp(false);
				SetbAppr(false);
			}
		}
	}
}

//=======================================================
//描画処理
//=======================================================
void CFoot::Draw(void)
{
	if (m_bDisp == true)
	{
		CPlayer::Draw();

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			//描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

CFoot * CFoot::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CFoot *pPlayer = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == NULL)
		{
			//オブジェクト2Dの生成
			pPlayer = new CFoot(pos);

			//初期化処理
			pPlayer->Init();
		}
	}

	return pPlayer;
}
