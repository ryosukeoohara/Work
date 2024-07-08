//===========================================================
//
//ポリゴンを出すやつ[player.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyBoss.h"
#include "enemyweak.h"
#include "effect.h"
#include "debugproc.h"
#include "block.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "collision.h"
#include "particl.h"
#include "frame.h"
#include "game.h"
#include "effectsord.h"
#include "displife.h"
#include "map.h"
#include "shadow.h"
#include "fade.h"
#include "tutorial.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
//マクロ定義
//================================================================
#define MAX_LIFE    (10)                            //プレイヤーの体力
#define REST_BULLET (6)                             //保持できる弾の数
#define MUTEKITIME  (30)                            //無敵時間
#define PLAYER_X    (40.0f)                         //プレイヤーのX軸の幅
#define PLAYER_Z    (10.0f)                         //プレイヤーのZ軸の幅
#define FRIST       (21)                            //攻撃判定発生開始
#define FINISH      (31)                            //攻撃判定終了
#define PLAYER_TEXT ("data\\TEXT\\player.txt")      //プレイヤーのテキストファイル

//================================================================
//静的メンバ変数宣言
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
//コンストラクタ
//================================================================
CPlayer::CPlayer()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	//m_rot = { 0.0f, 0.0f, 0.0f };
	m_State = STATE_NONE;
	m_AcType = ACTIONTYPE_NEAR;
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
	m_motion = NULL;
	m_pShadow = NULL;
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
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
	SetPos(&pos);  //位置
	SetRot(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_move = {0.0f, 0.0f, 0.0f};  //移動量
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	m_State = STATE_NONE;
	m_AcType = ACTIONTYPE_NEAR;
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
	m_motion = NULL;
	m_pShadow = NULL;
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
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
	CTexture *pTexture = CManager::GetTexture();

	//ライフ表示の情報取得
	CDispLife *pDispLife = CGame::GetDispLife();

	//シーンの情報を取得
	CScene *pScene = CManager::GetScene();

	if (pScene->GetMode() == CScene::MODE_TUTORIAL)
	{
		m_Tutostate = TUTOSTATE_MOVE;
	}

	//影の情報を取得
	//CShadow *pShadow = CGame::GetShadow();

	D3DXVECTOR3 pos = Getpos();

	//種類設定
	SetType(TYPE_PLAYER);

	if(m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow(pos);

		//初期化処理
		m_pShadow->Init();
	}

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\yanki.jpg");

	ReadText();

	SetLife(MAX_LIFE);

	m_RestBullet = REST_BULLET;

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//プレイヤーの終了処理
//================================================================
void CPlayer::Uninit(void)
{
	//サウンドの情報を取得
	CSound *pSound = CManager::GetSound();

	//サウンドストップ
	pSound->Stop();

	if (m_motion != NULL)
	{
		//終了処理
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
	}

	if (m_pShadow != NULL)
	{
		//終了処理
		m_pShadow->Uninit();

		m_pShadow = NULL;
	}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			m_apModel[nCount]->Uninit();  //終了処理
			delete m_apModel[nCount];  //メモリを開放
			m_apModel[nCount] = NULL;  //使用していない状態にする
		}
	}

	CObject::Release();
}

//================================================================
//プレイヤーの更新処理
//================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *InputKeyboard;

	InputKeyboard = CManager::GetKeyBoard();

	CSound *pSound;

	pSound = CManager::GetSound();

	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	//シーンの情報を取得
	CScene *pScene = CManager::GetScene();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Update();
	}

	if (m_motion != NULL)
	{
		//初期化処理
		m_motion->Update();
	}

	int nLife = GetLife();

	if (pScene->GetMode() == CScene::MODE_GAME)
	{
		//プレイヤーの制御
		ControlPlayer();
	}
	else if (pScene->GetMode() == CScene::MODE_TUTORIAL || pScene->GetMode() == CScene::MODE_TITLE)
	{
		//チュートリアルのプレイヤーの制御
		ControlTutorial();
	}
	
	SetLife(nLife);

	if (nLife <= 0 && m_State != STATE_DEATH && m_State != STATE_END)
	{
		m_State = STATE_DEATH;

		CEnemyWeak::UninitWeak();
	}

	if (m_State == STATE_END)
	{
		if (pFade->Get() != pFade->FADE_OUT)
		{
			pFade->Set(CScene::MODE_RESULT);
		}
	}
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
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

	if (m_State != STATE_END)
	{
		if (m_AcType == ACTIONTYPE_NEAR)
		{
			for (int nCount = 0; nCount < m_nNumModel - 1; nCount++)
			{
				//描画処理
				m_apModel[nCount]->Draw();
			}
		}
		else if (m_AcType == ACTIONTYPE_BAT)
		{
			for (int nCount = 0; nCount < m_nNumModel; nCount++)
			{
				if (nCount != 15)
				{
					//描画処理
					m_apModel[nCount]->Draw();
				}
			}
		}
		else
		{
			for (int nCount = 0; nCount < m_nNumModel - 2; nCount++)
			{
				//描画処理
				m_apModel[nCount]->Draw();
			}
		}
	}
}

//================================================================
//プレイヤーの制御処理
//================================================================
void CPlayer::ControlPlayer(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//マウスの位置を取得
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	//カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	CObject3D *pObject3D = CManager::GetObject3D();

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//敵の情報取得
	CEnemyBoss *pEnemyBoss = CEnemyBoss::GetEnemy();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//当たり判定の情報取得
	CCollision *pCollision = CManager::GetCollsion();

	//フレームの情報を取得
	CFrame *pFrame = CFrame::GetFrame();

	//マップモデルの情報を取得
	CObjectX **pMap = CMap::GetX();

	//影の情報を取得
	CShadow *pShadow = CGame::GetShadow();

	D3DXVECTOR3 Playerpos = Getpos();
	D3DXVECTOR3 PlayerRot = GetRot();

	m_posOld = Playerpos;  //位置を代入
	m_move = GetMove();

	if (Playerpos.x >= 3000.0f)
	{
		Playerpos.x = 3000.0f;
	}

	if (Playerpos.x <= -3000.0f)
	{
		Playerpos.x = -3000.0f;
	}

	if (Playerpos.z >= 3000.0f)
	{
		Playerpos.z = 3000.0f;
	}

	if (Playerpos.z <= -3000.0f)
	{
		Playerpos.z = -3000.0f;
	}

	//走っていない状態
	m_bDash = false;

	//float fHeight;

	if (m_State != STATE_DEATH && m_State != STATE_END)
	{
		if (m_State != STATE_STAGGER && m_State != STATE_DAMEGE)
		{
			if (m_State != STATE_AVOI)
			{
				//上に移動----------------------------------------------
				if (InputKeyboard->GetPress(DIK_W) == true)
				{//Wキーが押された

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//Dキーも押した 右上に移動

					 //移動量
						m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
					}

					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//Aキーも押した 左上に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
					}

					else
					{//Wキーだけ押した	真上に移動

					 //移動量
						m_move.x -= sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
					}

					//走っている状態にする
					m_bDash = true;

					//パーティクルを生成
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}

				//下に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_S) == true)
				{//Sキーが押された

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//Dキーも押した 右下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
					}
					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//Aキーも押した 左下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
					}
					else
					{//Sキーだけ押した 真下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI));
					}

					//走っている状態にする
					m_bDash = true;

					//パーティクルを生成
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}

				//右に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_D) == true)
				{//Dキーだけ押した

				 //移動量
					m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//向き
					m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));

					//走っている状態にする
					m_bDash = true;

					//パーティクルを生成
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}
				//左に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_A) == true)
				{//Aキーだけ押した

				 //移動量
					m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//向き
					m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));

					//走っている状態にする
					m_bDash = true;

					//パーティクルを生成
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}
			}

			if (pCamera->GetType() == CCamera::TYPE_SCOPE || m_AcType == ACTIONTYPE_FAR)
			{
				PlayerRot.y = CameraRot.y;
			}
			else
			{
				m_fDiff = m_fDest - PlayerRot.y;

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
				PlayerRot.y += m_fDiff * 0.15f;

				//角度の値を修正する--------------------------------------------------
				if (PlayerRot.y > D3DX_PI)
				{
					PlayerRot.y = -D3DX_PI;
				}
				else if (PlayerRot.y < -D3DX_PI)
				{
					PlayerRot.y = D3DX_PI;
				}
			}
			
			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
			 && m_AcType == ACTIONTYPE_NEAR && m_State != STATE_AVOI)
			{
				//if (m_bAcFir == false)
				//{
				//	//モーションをセット(近接攻撃)
				//	m_motion->Set(MOTIONTYPE_ACFRIST);

				//	m_State = STATE_CONSECAC;

				//	m_bAcFir = true;

				//	m_nCntDuration = 0;
				//}
				//else if (m_bAcFir == true && m_bAcSec == false)
				//{
				//	//モーションをセット(近接攻撃)
				//	m_motion->Set(MOTIONTYPE_ACSECOND);

				//	m_State = STATE_CONSECACSEC;

				//	m_bAcSec = true;

				//	m_nCntDuration = 0;
				//}
				//else if (m_bAcSec == true && m_bAcThr == false)
				//{
				//	//モーションをセット(近接攻撃)
				//	m_motion->Set(MOTIONTYPE_ACTHIRD);

				//	m_State = STATE_CONSECACTHI;

				//	m_bAcThr = false;
				//}

				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_KNIFEAC);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE00);

				m_bAction = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_SNP && m_AcType == ACTIONTYPE_FAR && m_RestBullet >= 1 && m_State != STATE_AVOI)
			{
				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_SNP);

				m_State = STATE_SNP;

				CBullet::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y + 60.0f, Playerpos.z), D3DXVECTOR3(0.0f, CameraRot.y, 0.0f), CBullet::TYPE_PLAYER);

				m_RestBullet--;

				pSound->Play(CSound::SOUND_LABEL_SE03);

				m_bAction = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC && m_AcType == ACTIONTYPE_BAT)
			{
				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_BATACTION);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE07);

				m_bAction = true;
			}

			if (pInputMouse->GetRButton() == true && m_State != STATE_AVOI)
			{
				//モーションをセット(回避)
				m_motion->Set(MOTIONTYPE_AVOI);

				m_State = STATE_AVOI;

				pSound->Play(CSound::SOUND_LABEL_SE10);
			}

			if (m_State == STATE_KNIFEAC)
			{
				m_nCntColi++;

				if (m_nCntColi >= FRIST && m_nCntColi <= FINISH)
				{
					if (m_apModel[m_nNumModel - 1] != NULL)
					{
						D3DXMATRIX Matrix = m_apModel[m_nNumModel - 1]->GetMtxWorld();

						CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);
					}

					if (pCollision->Knife(&Playerpos, { PlayerRot.x, PlayerRot.y, PlayerRot.z }, 50.0f, pEnemy) == true)
					{
						pDebugProc->Print("\nクソイヤホン馬鹿野郎specialバージョン1.2血まみれ～～");
					}
				}
			}

			//fHeight = pObject3D->GetHeight(m_pos);

			//m_move.y -= 0.8f;

			Playerpos.x += m_move.x;
			Playerpos.y += m_move.y;
			//m_pos.y = fHeight + 18.0f;
			Playerpos.z += m_move.z;

			if (m_bDash == true && m_State != STATE_MOVE && m_State != STATE_AVOI)
			{
				//モーションをセット(移動)
				m_motion->Set(MOTIONTYPE_MOVE);

				m_State = STATE_MOVE;

				m_nCntColi = 0;

				m_bAction = false;
			}

			if (m_bAcFir == true || m_bAcSec == true || m_bAcThr == true)
			{
				m_nCntDuration++;

				if (m_nCntDuration >= 120)
				{
					m_bAcFir = false;
					m_bAcSec = false;
					m_bAcThr = false;

					m_nCntDuration = 0;
				}
			}

			if (pFrame != NULL)
			{
				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_NEAR && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					//モーションをセット(移動)
					m_motion->Set(MOTIONTYPE_KNIFESTAN);

					m_State = STATE_KNIFESTAN;
				}

				if (m_State != STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					m_motion->Set(MOTIONTYPE_SNPSTAN);

					m_State = STATE_SNPSTAN;
				}

				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_BAT && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					//モーションをセット(移動)
					m_motion->Set(MOTIONTYPE_BATNEUTAL);

					m_State = STATE_KNIFESTAN;
				}
			}

			if (m_State == STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR)
			{
				if (InputKeyboard->GetTrigger(DIK_E) == true)
				{//Eキーが押された

					if (pCamera->GetType() == CCamera::TYPE_GAME)
					{
						pCamera->SetType(CCamera::TYPE_SCOPE);
					}
					else if (pCamera->GetType() == CCamera::TYPE_SCOPE)
					{
						pCamera->SetType(CCamera::TYPE_GAME);
					}
				}
			}

			if (m_motion->IsFinish() == true)
			{
				m_nCntEff = 0;
				m_nCntColi = 0;
				m_bAction = false;

				m_State = STATE_NONE;
			}

			if (m_State == STATE_NEUTRAL)
			{
				Playerpos.y = -17.0f;
			}
			else
			{
				Playerpos.y = 0.0f;
			}

			//移動量を更新(減衰させる)--------------------------------------------
			m_move.x += (0.0f - m_move.x) * 0.1f;
			m_move.z += (0.0f - m_move.z) * 0.1f;

			if (pEnemy != NULL)
			{
				//敵との当たり判定
				if (pCollision->CollsionEnemy(&Playerpos, &m_posOld, PLAYER_X, PLAYER_Z, *pEnemy) == true)
				{

				}
			}
		}
	}

	if (pFrame != NULL)
	{
		if (pFrame->GetACType() == CFrame::TYPE_NEAR)
		{
			m_AcType = ACTIONTYPE_NEAR;
		}

		if (pFrame->GetACType() == CFrame::TYPE_FAR)
		{
			m_AcType = ACTIONTYPE_FAR;
		}

		if (pFrame->GetACType() == CFrame::TYPE_BAT)
		{
			m_AcType = ACTIONTYPE_BAT;
		}
	}
	else
	{
		m_AcType = ACTIONTYPE_NEAR;
	}
	
	if (m_State == STATE_DAMEGE)
	{
		m_State = STATE_STAGGER;

		m_motion->Set(MOTIONTYPE_DAMEGE);

		m_nCntInvincible = MUTEKITIME;
	}

	if (m_State == STATE_STAGGER)
	{
		m_nCntInvincible--;

		Playerpos.x -= m_move.x * 0.5f;
		Playerpos.z -= m_move.z * 0.5f;

		if (m_nCntInvincible <= 0)
		{
			m_State = STATE_NONE;
		}
	}

	if (m_State == STATE_AVOI)
	{
		m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
		m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;

		Playerpos.x += m_move.x * 0.05f;
		Playerpos.z += m_move.z * 0.05f;
	}

	if (m_State == STATE_DEATH && m_State != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//モーションをセット(死亡)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->GetType() == MOTIONTYPE_DEATH)
	{
		m_nCntDie++;

		if (m_nCntDie == 50)
		{
			pSound->Play(CSound::SOUND_LABEL_SE05);
		}
	}
	
	if (m_motion->IsFinish() == true && m_State == STATE_DEATH)
	{
		m_State = STATE_END;

		m_bAction = false;
	}

	if (m_bDash == true && m_nCntSound == 0)
	{
		m_nCntSound = 35;

		pSound->Play(CSound::SOUND_LABEL_SE09);
	}

	if (m_nCntSound > 0)
	{
		m_nCntSound--;
	}

	if (pCollision->Map(&Playerpos, &m_posOld, pMap) == true)
	{
		int n = 0;
	}

	if (m_bEncounter == true)
	{

	}

	SetPos(&Playerpos);
	SetRot(&PlayerRot);

	m_pShadow->SetPosition(m_nIdxShaadow, { Playerpos.x, 2.0f, Playerpos.z });

	pDebugProc->Print("プレイヤーの位置：%f,%f,%f\n", Playerpos.x, Playerpos.y, Playerpos.z);
	pDebugProc->Print("プレイヤーの向き：%f,%f,%f\n", PlayerRot.x, PlayerRot.y, PlayerRot.z);
	pDebugProc->Print("プレイヤーの移動量：%f,%f,%f", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("\n弾発射：左クリック");
}

//================================================================
//チュートリアルのプレイヤーの制御処理
//================================================================
void CPlayer::ControlTutorial(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//シーンの情報を取得
	CScene *pScene = CManager::GetScene();

	//フレームの情報を取得
	CFrame *pFrame = CFrame::GetFrame();

	//サウンドを取得
	CSound *pSound = CManager::GetSound();

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	D3DXVECTOR3 Playerpos = Getpos();
	D3DXVECTOR3 PlayerRot = GetRot();

	//走っていない状態
	m_bDash = false;

	if (pScene->GetMode() != CScene::MODE_TITLE)
	{
		if (Playerpos.z >= -1100.0f && m_Tutostate == TUTOSTATE_MOVE)
		{
			//走っている状態にする
			m_bDash = true;

			m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
			m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
		}

		if (Playerpos.z < -1150.0f && m_Tutostate == TUTOSTATE_MOVE)
		{
			//m_State = PLAYERSTATE_KNIFESTAN;

			m_Tutostate = TUTOSTATE_STOP;
		}

		if (GetTutostate() == TUTOSTATE_NONE)
		{
			if (m_State != STATE_AVOI)
			{
				//上に移動----------------------------------------------
				if (InputKeyboard->GetPress(DIK_W) == true)
				{//Wキーが押された

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//Dキーも押した 右上に移動

					 //移動量
						m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
					}

					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//Aキーも押した 左上に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
					}

					else
					{//Wキーだけ押した	真上に移動

					 //移動量
						m_move.x -= sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
					}

					//走っている状態にする
					m_bDash = true;

					m_bPushW = true;
				}

				//下に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_S) == true)
				{//Sキーが押された

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//Dキーも押した 右下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
					}
					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//Aキーも押した 左下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
					}
					else
					{//Sキーだけ押した 真下に移動

					 //移動量
						m_move.x += sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y) * PLAYERMOVE;

						//向き
						m_fDest = (CameraRot.y + (D3DX_PI));
					}

					//走っている状態にする
					m_bDash = true;

					m_bPushS = true;
				}

				//右に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_D) == true)
				{//Dキーだけ押した

				 //移動量
					m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//向き
					m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));

					//走っている状態にする
					m_bDash = true;

					m_bPushD = true;
				}
				//左に移動----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_A) == true)
				{//Aキーだけ押した

				 //移動量
					m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//向き
					m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));

					//走っている状態にする
					m_bDash = true;

					m_bPushA = true;
				}
			}

			m_fDiff = m_fDest - PlayerRot.y;

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
			PlayerRot.y += m_fDiff * 0.15f;

			//角度の値を修正する--------------------------------------------------
			if (PlayerRot.y > D3DX_PI)
			{
				PlayerRot.y = -D3DX_PI;
			}
			else if (PlayerRot.y < -D3DX_PI)
			{
				PlayerRot.y = D3DX_PI;
			}

			if (m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON01)
			{
				CTutorial::SetEndlesson(true);
			}

			if (pInputMouse->GetRButton() == true && m_State != STATE_AVOI
				&& m_bWhee == true)
			{
				//モーションをセット(回避)
				m_motion->Set(MOTIONTYPE_AVOI);

				m_State = STATE_AVOI;

				pSound->Play(CSound::SOUND_LABEL_SE10);

				m_bAvoi = true;
			}

			if (m_bAvoi == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON05)
			{
				CTutorial::SetEndlesson(true);
			}

			//===============================================================================================================================
			//攻撃
			//===============================================================================================================================
			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
				&& m_AcType == ACTIONTYPE_NEAR && m_State != STATE_AVOI && m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true)
			{
				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_KNIFEAC);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE00);

				m_bAction = true;

				m_bAttack = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_SNP
				&& m_AcType == ACTIONTYPE_FAR && m_RestBullet >= 0 && m_State != STATE_AVOI  && m_bWhee == true)
			{
				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_SNP);

				CBullet::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y + 60.0f, Playerpos.z), D3DXVECTOR3(0.0f, m_fDest, 0.0f), CBullet::TYPE_PLAYER);

				m_State = STATE_SNP;

				pSound->Play(CSound::SOUND_LABEL_SE03);

				//m_RestBullet--;

				m_bAction = true;

				m_bAttack = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
				&& m_AcType == ACTIONTYPE_BAT  && m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true)
			{
				//モーションをセット(近接攻撃)
				m_motion->Set(MOTIONTYPE_BATACTION);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				m_bAction = true;

				m_bAttack = true;
			}

			//===============================================================================================================================

			if (m_bAttack == true && (CTutorial::GetLesson() == CTutorial::TYPE_LESSON02 || CTutorial::GetLesson() == CTutorial::TYPE_LESSON04))
			{
				CTutorial::SetEndlesson(true);
			}

			if (pFrame != NULL)
			{
				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_NEAR
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI && m_bAvoi == true)
				{
					//モーションをセット(移動)
					m_motion->Set(MOTIONTYPE_KNIFESTAN);

					m_State = STATE_KNIFESTAN;
				}

				if (m_State != STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI && m_bAvoi == true)
				{
					m_motion->Set(MOTIONTYPE_SNPSTAN);

					m_State = STATE_SNPSTAN;
				}

				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_BAT
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI  && m_bAvoi == true)
				{
					//モーションをセット(移動)
					m_motion->Set(MOTIONTYPE_BATNEUTAL);

					m_State = STATE_KNIFESTAN;
				}
			}

			if (pFrame != NULL)
			{
				if (pFrame->GetACType() == CFrame::TYPE_NEAR)
				{
					m_AcType = ACTIONTYPE_NEAR;
				}

				if (pFrame->GetACType() == CFrame::TYPE_FAR)
				{
					m_AcType = ACTIONTYPE_FAR;

					m_bWhee = true;
				}

				if (pFrame->GetACType() == CFrame::TYPE_BAT)
				{
					m_AcType = ACTIONTYPE_BAT;
				}
			}
			else
			{
				m_AcType = ACTIONTYPE_NEAR;
			}

			if (m_bWhee == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON03)
			{
				CTutorial::SetEndlesson(true);

				m_bAttack = false;
			}
		}

		Playerpos.x += m_move.x;
		Playerpos.y += m_move.y;
		//m_pos.y = fHeight + 18.0f;
		Playerpos.z += m_move.z;

		//移動量を更新(減衰させる)--------------------------------------------
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		//移動---------------------------------------------------------------------------------------------
		if (m_bDash == true && m_State != STATE_MOVE && m_State != STATE_AVOI)
		{
			//モーションをセット(移動)
			m_motion->Set(MOTIONTYPE_MOVE);

			m_State = STATE_MOVE;

			m_nCntColi = 0;

			m_bAction = false;
		}

		//攻撃ニュートラル---------------------------------------------------------------------------------------------
		if (m_State != STATE_KNIFESTAN && m_bDash == false
			&& m_bAction == false && m_State != STATE_AVOI)
		{
			//モーションをセット(移動)
			m_motion->Set(MOTIONTYPE_KNIFESTAN);

			m_State = STATE_KNIFESTAN;
		}

		//回避---------------------------------------------------------------------------------------------
		if (m_State == STATE_AVOI)
		{
			m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
			m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;

			Playerpos.x += m_move.x * 0.05f;
			Playerpos.z += m_move.z * 0.05f;
		}

		if (m_bDash == true && m_nCntSound == 0)
		{
			m_nCntSound = 35;

			pSound->Play(CSound::SOUND_LABEL_SE09);
		}

		if (m_nCntSound > 0)
		{
			m_nCntSound--;
		}

		if (m_motion->IsFinish() == true)
		{
			m_nCntEff = 0;
			m_nCntColi = 0;
			m_bAction = false;
			m_State = STATE_NONE;
		}

		SetPos(&Playerpos);
		SetRot(&PlayerRot);
	}

	m_pShadow->SetPosition(m_nIdxShaadow, { Playerpos.x, 2.0f, Playerpos.z });
}

//================================================================
//攻撃くらった時の処理
//================================================================
void CPlayer::Hit(void)
{
	if (m_State != STATE_DAMEGE && m_State != STATE_STAGGER && m_State != STATE_AVOI)
	{
		int nLife = GetLife();

		nLife--;

		SetLife(nLife);

		m_State = STATE_DAMEGE;
	}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CPlayer::ReadText(void)
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
	CTexture *pTexture = CManager::GetTexture();

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(PLAYER_TEXT, "r");

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
					//m_apModel[nCntModel]->BindTexture(pTexture->GetAddress(m_nIdxTexture));
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
		//初期化処理
		m_motion->ReadText(PLAYER_TEXT);
	}
}