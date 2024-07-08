//===========================================================
//
//ポリゴンを出すやつ[enemy.cpp]
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
#include "enemyweak.h"
#include "number.h"
#include "texture.h"
#include "motion.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "message.h"
#include "game.h"
#include "enemymanager.h"
#include "score.h"
#include "effect.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//マクロ定義
#define ENEMY_WIDTH     (40.0f)    //幅
#define ENEMY_HEIGHT    (100.0f)   //高さ
#define ENEMY_LIFE      (3)        //体力
#define ENEMYNEAR_TEXT     ("data\\TEXT\\yankinear.txt")  //敵のテキストファイル
#define ENEMYFAR_TEXT      ("data\\TEXT\\enemyfar.txt")  //敵のテキストファイル

//================================================================
//静的メンバ変数宣言
//================================================================
//LPDIRECT3DTEXTURE9 CEnemyWeak::m_pTexture = NULL;
CEnemyWeak *CEnemyWeak::m_EnemyWeak[128] = {};

CEnemyWeak::TYPE CEnemyWeak::m_type = TYPE_NONE;

//================================================================
//コンストラクタ
//================================================================
CEnemyWeak::CEnemyWeak()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CEnemyWeak::CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //位置設定
				   //SetType(type);     //種類取得
	//m_pos = pos;
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//デストラクタ
//================================================================
CEnemyWeak::~CEnemyWeak()
{

}

//================================================================
//生成処理
//================================================================
CEnemyWeak *CEnemyWeak::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//オブジェクト2Dのポインタ
	CEnemyWeak *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//オブジェクト2Dの生成
			pEnemy = new CEnemyWeak(pos, rot);

			//初期化処理
			pEnemy->Init();

			for (int nCount = 0; nCount < 128; nCount++)
			{
				if (m_EnemyWeak[nCount] == NULL)
				{
					m_EnemyWeak[nCount] = pEnemy;

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					//m_nNumAll++;

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//敵の初期化処理
//================================================================
HRESULT CEnemyWeak::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	//種類の設定
	//SetType(TYPE_ENEMY);

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\yanki.jpg");

	//体力
	SetLife(ENEMY_LIFE);

	m_move.x = sinf(m_rot.y + (D3DX_PI * 0.5f)) * ENEMYMOVE;
	//m_move.z = cosf(m_rot.y + (D3DX_PI * 0.5f)) * ENEMYMOVE;

	//テキストファイル読み込み
	//ReadText();

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	//m_pos = GetPosition();

	return S_OK;
}

//================================================================
//敵の終了処理
//================================================================
void CEnemyWeak::Uninit(void)
{
	if (m_motion != NULL)
	{
		//終了処理
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
	}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			m_apModel[nCount]->Uninit();  //終了処理
			delete m_apModel[nCount];     //メモリを開放
			m_apModel[nCount] = NULL;     //使用していない状態にする
		}
	}

	CObject::Release();
}

//================================================================
//敵の更新処理
//================================================================
void CEnemyWeak::Update(void)
{
	
}

//================================================================
//敵の描画処理
//================================================================
void CEnemyWeak::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			//描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

//================================================================
//敵の動き
//================================================================
void CEnemyWeak::Control(void)
{
	

	
}

//================================================================
//死亡処理
//================================================================
void CEnemyWeak::Death(int nCntEnemy)
{
	//終了処理
	m_Enemy[nCntEnemy]->Uninit();

	//使用していない状態にする
	m_Enemy[nCntEnemy] = NULL;
}

//================================================================
//外部ファイル読み込み
//================================================================
void CEnemyWeak::ReadText(char *Filename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;
	int nCntPatrol = 0;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(Filename, "r");
	
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
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumModel);  //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);        //=
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
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);  //=
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

				 //if (strcmp("SET_PATROL", aString) == 0)   //巡回地点設定
				 //{
				 //	while (strcmp("END_PATROL", aString) != 0)
				 //	{
				 //		fscanf(pFile, "%s", &aString);

				 //		if (strcmp("NUM_PATROL", aString) == 0)
				 //		{
				 //			fscanf(pFile, "%s", &aString);  //=
				 //			fscanf(pFile, "%d", &m_nNumPatrol);  //巡回する地点の数
				 //		}
				 //		
				 //		if (strcmp("PATROLPOS", aString) == 0)
				 //		{
				 //			fscanf(pFile, "%s", &aString);  //=
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.x);  //巡回地点
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.y);  //巡回地点
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.z);  //巡回地点

				 //			nCntPatrol++;
				 //		}

				 //	}
				 //}
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
		switch (m_type)
		{
		case TYPE_NONE:
			break;

		case TYPE_NEAR:		//近距離

			//テキストファイル読み込み
			m_motion->ReadText(ENEMYNEAR_TEXT);

			break;

		case TYPE_FAR:		//遠距離

			//テキストファイル読み込み
			m_motion->ReadText(ENEMYFAR_TEXT);

			break;
		}
	}
}

//================================================================
//ザコ敵全員の終了処理
//================================================================
void CEnemyWeak::UninitWeak(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (m_Enemy[nCount] != NULL)
		{
			m_Enemy[nCount]->Uninit();

			m_Enemy[nCount] = NULL;
		}
	}

	////敵の総数リセット
	//CEnemyManager::SetNumEneWeak(0);
	//CEnemyManager::SetNumEneMedBoss(0);
	//CEnemyManager::SetNumEneBoss(0);
	//CEnemyManager::SetNumAll(0);
}

//***************************************************************************************************
//近距離ざこ敵
//***************************************************************************************************

//================================================================
//コンストラクタ
//================================================================
CEnemyNear::CEnemyNear()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_nCntRush = 0;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CEnemyNear::CEnemyNear(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //位置設定
	SetRot(&rot);  //向き設定
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_nCntRush = 0;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//デストラクタ
//================================================================
CEnemyNear::~CEnemyNear()
{

}

//================================================================
//生成処理
//================================================================
CEnemyNear *CEnemyNear::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//オブジェクト2Dのポインタ
	CEnemyNear *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//オブジェクト2Dの生成
			pEnemy = new CEnemyNear(pos, rot);

			//初期化処理
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_NEAR);

					m_Enemy[nCount]->SetNumber(nCount);

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					int nNumAll = CEnemyManager::GetNumAll();

					nNumAll++;

					CEnemyManager::SetNumAll(nNumAll);

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//初期化処理
//================================================================
HRESULT CEnemyNear::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	D3DXVECTOR3 pos = Getpos();

	//影の情報を取得
	CShadow *pShadow = CGame::GetShadow();

	//m_nIdxShaadow = pShadow->Set(pos);

	m_type = TYPE_NEAR;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//体力
	SetLife(ENEMY_LIFE);

	CEnemy::Init();

	//テキストファイル読み込み
	CEnemy::ReadText(ENEMYNEAR_TEXT);

	//テキストファイル読み込み
	m_motion->ReadText(ENEMYNEAR_TEXT);

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CEnemyNear::Uninit(void)
{
	//終了処理
	CEnemy::Uninit();
}

//================================================================
//更新処理
//================================================================
void CEnemyNear::Update(void)
{
	Control();

	CEnemy::Update();
}

//================================================================
//描画処理
//================================================================
void CEnemyNear::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();

	//向き取得
	D3DXVECTOR3 EnemyRot = GetRot();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, EnemyRot.y, EnemyRot.x, EnemyRot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

		    //描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

//================================================================
//動き
//================================================================
void CEnemyNear::Control(void)
{
	//デバッグプロックの情報取得
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//当たり判定の情報取得
	CCollision *pCollision = CManager::GetCollsion();

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();

	//向き取得
	D3DXVECTOR3 EnemyRot = GetRot();

	if (GetState() != STATE_DEATH && GetState() != STATE_END)
	{
		if ((pCollision->CollisionCircle(&EnemyPos, 300.0f, pPlayer) == true))
		{//円の中にプレイヤーが入ったまたは、状態がダメージのとき

			D3DXVECTOR3 fDest, pos = pPlayer->Getpos();
			float fDiffmove, fDestmove;

			fDest = EnemyPos - pos;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - EnemyRot.y;

			if (m_state != STATE_RUSH)
			{
				//角度の値を修正する--------------------------------------------------
				if (fDiffmove >= D3DX_PI)
				{
					fDiffmove = -D3DX_PI;
				}
				else if (fDiffmove <= -D3DX_PI)
				{
					fDiffmove = D3DX_PI;
				}

				EnemyRot.y += fDiffmove * 0.05f;

				//角度の値を修正する--------------------------------------------------
				if (EnemyRot.y > D3DX_PI)
				{
					EnemyRot.y = -D3DX_PI;
				}
				else if (EnemyRot.y < -D3DX_PI)
				{
					EnemyRot.y = D3DX_PI;
				}
			}

			//移動量を更新(減衰させる)
			m_move.x = sinf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 100.0f && fDest.x >= -100.0f && fDest.z <= 100.0f && fDest.z >= -100.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					EnemyPos.x -= m_move.x * 0.5f;
					EnemyPos.z -= m_move.z * 0.5f;

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
				else
				{
					if (m_state != STATE_ACTIONNEUTRAL && m_bAction == false)
					{
						//モーションをセット(移動)
						m_motion->Set(MOTIONTYPE_ACTIONNEUTRAL);

						m_state = STATE_ACTIONNEUTRAL;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{
						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_bAction = false;
					}

					if (m_nCntAction % 60 == 0)
					{
						if (m_state != STATE_ACTION && m_state != STATE_RUSH)
						{
							//モーションをセット(攻撃)
							m_motion->Set(MOTIONTYPE_ACTION);

							m_state = STATE_ACTION;

							pSound->Play(CSound::SOUND_LABEL_SE07);

							m_bAction = true;

							m_nCntRush++;
						}
					}

					if (m_bAction == true)
					{
						D3DXMATRIX Matrix = m_apModel[15]->GetMtxWorld();

						D3DXVECTOR3 kugipos = { Matrix._41, Matrix._42, Matrix._43 };

						CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);

						if (pCollision->kugibat(&kugipos, pPlayer))
						{
							int n = 0;
						}
					}

					if (m_nCntRush > 3)
					{
						if (m_state != STATE_RUSH)
						{
							//モーションをセット(攻撃)
							m_motion->Set(MOTIONTYPE_RUSH);

							m_state = STATE_RUSH;

							m_bAction = true;

							m_nCntRush = 0;
						}
					}

					if (m_state == STATE_RUSH)
					{
						EnemyPos.x += m_move.x * 1.2f;
						EnemyPos.z += m_move.z * 1.2f;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_state == STATE_STAGGER)
					{
						EnemyPos.x -= m_move.x;
						EnemyPos.z -= m_move.z;
					}
				}
			}
			else
			{
				if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE)
				{
					EnemyPos.x += m_move.x;
					EnemyPos.z += m_move.z;

					if (m_state != STATE_MOVE)
					{
						//モーションをセット(移動)
						m_motion->Set(MOTIONTYPE_MOVE);

						m_state = STATE_MOVE;

						m_bAction = false;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}
				}
				else
				{
					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
			}
		}
		else
		{
			if (m_state != STATE_NONE)
			{
				//モーションをセット(ニュートラル)
				m_motion->Set(MOTIONTYPE_NONE);

				m_state = STATE_NONE;
			}
		}
	}

	if (m_state == STATE_DEATH && m_state != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//モーションをセット(死亡)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->IsFinish() == true && m_state == STATE_DEATH)
	{
		m_state = STATE_END;

		m_bAction = false;
	}

	//位置設定
	SetPos(&EnemyPos);

	//向き設定
	SetRot(&EnemyRot);
}


//***************************************************************************************************
//遠距離ざこ敵
//***************************************************************************************************

//================================================================
//コンストラクタ
//================================================================
CEnemyFar::CEnemyFar()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_nCntReload = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
	m_bBom = false;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CEnemyFar::CEnemyFar(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //位置設定
	SetRot(&rot);  //向き設定
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_nCntReload = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
	m_bBom = false;
}

//================================================================
//デストラクタ
//================================================================
CEnemyFar::~CEnemyFar()
{

}

//================================================================
//生成処理
//================================================================
CEnemyFar *CEnemyFar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//オブジェクト2Dのポインタ
	CEnemyFar *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//オブジェクト2Dの生成
			pEnemy = new CEnemyFar(pos, rot);

			//初期化処理
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_FAR);

					m_Enemy[nCount]->SetNumber(nCount);

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					int nNumAll = CEnemyManager::GetNumAll();

					nNumAll++;

					CEnemyManager::SetNumAll(nNumAll);

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//初期化処理
//================================================================
HRESULT CEnemyFar::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	D3DXVECTOR3 pos = Getpos();

	//影の情報を取得
	CShadow *pShadow = CGame::GetShadow();

	//m_nIdxShaadow = pShadow->Set(pos);

	m_type = TYPE_FAR;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//体力
	SetLife(ENEMY_LIFE);

	CEnemy::Init();

	//テキストファイル読み込み
	CEnemy::ReadText(ENEMYFAR_TEXT);

	//テキストファイル読み込み
	m_motion->ReadText(ENEMYFAR_TEXT);

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CEnemyFar::Uninit(void)
{
	CEnemy::Uninit();

	//CObject::Release();
}

//================================================================
//更新処理
//================================================================
void CEnemyFar::Update(void)
{
	Control();

	CEnemy::Update();
}

//================================================================
//描画処理
//================================================================
void CEnemyFar::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();

	//向き取得
	D3DXVECTOR3 EnemyRot = GetRot();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, EnemyRot.y, EnemyRot.x, EnemyRot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bBom != true)
	{//攻撃していないとき

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_apModel[nCount] != NULL)
			{//使用していたら

				//描画処理
				m_apModel[nCount]->Draw();
			}
		}
	}
	else
	{
		for (int nCount = 0; nCount < m_nNumModel - 1; nCount++)
		{
			if (m_apModel[nCount] != NULL)
			{//使用していたら

				//描画処理
				m_apModel[nCount]->Draw();
			}
		}
	}
}

//================================================================
//動き
//================================================================
void CEnemyFar::Control(void)
{
	//デバッグプロックの情報取得
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//当たり判定の情報取得
	CCollision *pCollision = CManager::GetCollsion();

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();
	D3DXVECTOR3 EnemyRot = GetRot();

	m_state = GetState();

	if (GetState() != STATE_DEATH && GetState() != STATE_END)
	{
		if ((pCollision->CollisionCircle(&EnemyPos, 400.0f, pPlayer) == true))
		{//円の中にプレイヤーが入ったまたは、状態がダメージのとき

			D3DXVECTOR3 fDest, pos = pPlayer->Getpos();

			float fDiffmove, fDestmove;

			fDest = EnemyPos - pos;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - EnemyRot.y;

			//角度の値を修正する--------------------------------------------------
			if (fDiffmove >= D3DX_PI)
			{
				fDiffmove = -D3DX_PI;
			}
			else if (fDiffmove <= -D3DX_PI)
			{
				fDiffmove = D3DX_PI;
			}

			EnemyRot.y += fDiffmove * 0.05f;

			//角度の値を修正する--------------------------------------------------
			if (EnemyRot.y > D3DX_PI)
			{
				EnemyRot.y = -D3DX_PI;
			}
			else if (EnemyRot.y < -D3DX_PI)
			{
				EnemyRot.y = D3DX_PI;
			}
			
			//移動量を更新(減衰させる)
			m_move.x = sinf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 200.0f && fDest.x >= -200.0f && fDest.z <= 200.0f && fDest.z >= -200.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					EnemyPos.x -= m_move.x * 0.5f;
					EnemyPos.z -= m_move.z * 0.5f;

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
				else
				{
					if (m_state != STATE_ACTIONNEUTRAL && m_bAction == false)
					{
						//モーションをセット(移動)
						m_motion->Set(MOTIONTYPE_ACTIONNEUTRAL);

						m_state = STATE_ACTIONNEUTRAL;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{
						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}

					if (m_nCntAction % 120 == 0)
					{
						if (m_state != STATE_ACTION && m_bBom == false)
						{
							//モーションをセット(攻撃)
							m_motion->Set(MOTIONTYPE_ACTION);

							m_state = STATE_ACTION;

							CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + 60.0f, EnemyPos.z), D3DXVECTOR3(0.0f, EnemyRot.y, 0.0f), CBullet::TYPE_ENEMY);

							pSound->Play(CSound::SOUND_LABEL_SE07);

							m_bAction = true;
							m_bBom = true;
						}
					}

					if (m_bBom == true)
					{
						m_nCntReload++;
					}

					if (m_nCntReload % 150 == 0)
					{
						if (m_bBom == true)
						{
							//モーションをセット(攻撃)
							m_motion->Set(MOTIONTYPE_REROAD);

							m_bBom = false;
							m_nCntReload = 0;
						}
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_state == STATE_STAGGER)
					{
						EnemyPos.x -= m_move.x;
						EnemyPos.z -= m_move.z;
					}
				}

				if (fDest.x <= 50.0f && fDest.x >= -50.0f && fDest.z <= 50.0f && fDest.z >= -50.0f)
				{

				}
			}
			else
			{
				if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE)
				{
					EnemyPos.x += m_move.x;
					EnemyPos.z += m_move.z;

					if (m_state != STATE_MOVE)
					{
						//モーションをセット(移動)
						m_motion->Set(MOTIONTYPE_MOVE);
						
						m_state = STATE_MOVE;

						m_bAction = false;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//モーションをセット(ニュートラル)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}
				}
				else
				{
					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
			}
		}
		else
		{
			if (m_state != STATE_NONE)
			{
				//モーションをセット(ニュートラル)
				m_motion->Set(MOTIONTYPE_NONE);

				m_state = STATE_NONE;
			}
		}

		if (m_state == STATE_NONE)
		{
			EnemyPos.y = -10.0f;
		}
		else
		{
			EnemyPos.y = 0.0f;
		}
	}

	if (m_state != STATE_DEATH || m_state != STATE_END)
	{
		if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
		{
			EnemyPos.x -= m_move.x * 0.5f;
			EnemyPos.z -= m_move.z * 0.5f;

			if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
			{
				//モーションをセット(ニュートラル)
				m_motion->Set(MOTIONTYPE_DAMEGE);

				m_state = STATE_STAGGER;
			}

			if (m_motion->IsFinish() == true)
			{
				m_state = STATE_NONE;

				m_bAction = false;
			}
		}
	}
	

	if (m_state == STATE_DEATH && m_state != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//モーションをセット(死亡)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->IsFinish() == true && m_state != STATE_DEATH)
	{
		m_state = STATE_NONE;

		m_bAction = false;
	}

	if (m_motion->IsFinish() == true && m_state == STATE_DEATH)
	{
		m_state = STATE_END;

		m_bAction = false;
	}

	//位置設定
	SetPos(&EnemyPos);
	SetRot(&EnemyRot);
}