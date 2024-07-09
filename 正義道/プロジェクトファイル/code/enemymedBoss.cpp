//===========================================================
//
// 中ボスの処理[enemymedBoss.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "bullet.h"
#include "motion.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "enemymedBoss.h"
#include "game.h"
#include "texture.h"
#include "score.h"
#include "enemyweak.h"
#include "enemy.h"
#include "effectsord.h"
#include "dispdetection.h"
#include "particl.h"
#include "impact.h"
#include "effect.h"

//================================================================
//マクロ定義
//================================================================
#define ENEMY_WIDTH     (10.0f)                         //幅
#define ENEMY_HEIGHT    (10.0f)                         //高さ
#define ENEMY_LIFE      (50)                            //体力
#define FRIST           (15)                            //攻撃判定発生開始
#define FINISH          (25)                            //攻撃判定終了
#define MAX_LIFE        (7)                             //体力
#define ENEMY001_TEXT   ("data\\TEXT\\yanki001.txt")    //敵のテキストファイル
#define ENEMY002_TEXT   ("data\\TEXT\\yanki002.txt")    //敵のテキストファイル
#define ENEMY003_TEXT   ("data\\TEXT\\yanki003.txt")    //敵のテキストファイル

//================================================================
//静的メンバ変数宣言
//================================================================
CEnemyMedBoss *CEnemyMedBoss::m_EnemyMedBoss = NULL;

//================================================================
//コンストラクタ
//================================================================
CEnemyMedBoss::CEnemyMedBoss()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_JumpPoint = { 0.0f,0.0f,0.0f };
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nIdxTexture = 0;
	m_nCntColli = 0;
	m_Tracking = false;
	m_bAction = false;
	m_ACKTYpe = ATTACKTYPE_NONE;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CEnemyMedBoss::CEnemyMedBoss(D3DXVECTOR3 pos, CEnemyMedBoss::TYPEENE type)
{
	SetPos(&pos);  //位置設定
	SetPosOld(pos);
	m_typeEne = type;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_rot = { 0.0f, 0.0f, 0.0f };   //向き
	m_JumpPoint = { 0.0f,0.0f,0.0f };
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nIdxTexture = 0;
	m_nCntColli = 0;
	m_Tracking = false;
	m_bAction = false;
	m_ACKTYpe = ATTACKTYPE_NONE;
}

//================================================================
//デストラクタ
//================================================================
CEnemyMedBoss::~CEnemyMedBoss()
{

}

//================================================================
//生成処理
//================================================================
CEnemyMedBoss *CEnemyMedBoss::Create(D3DXVECTOR3 pos, TYPEENE type)
{
	//オブジェクト2Dのポインタ
	CEnemyMedBoss *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//オブジェクト2Dの生成
			pEnemy = new CEnemyMedBoss(pos, type);

			//初期化処理
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_BOSS);

					m_Enemy[nCount]->SetNumber(nCount);

					m_EnemyMedBoss = pEnemy;

					int nCountBoss = CEnemyManager::GetNumEneMedBoss();

					nCountBoss++;

					CEnemyManager::SetNumEneMedBoss(nCountBoss);

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
//敵の初期化処理
//================================================================
HRESULT CEnemyMedBoss::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	//種類の設定
	m_type = TYPE_MEDBOSS;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	//体力
	SetLife(MAX_LIFE);

	CEnemy::Init();

	//テキストファイル読み込み
	ReadText(m_typeEne);

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//敵の終了処理
//================================================================
void CEnemyMedBoss::Uninit(void)
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

	CEnemy::Uninit();

	m_EnemyMedBoss = NULL;
}

//================================================================
//敵の更新処理
//================================================================
void CEnemyMedBoss::Update(void)
{
	//敵の操作
	Control();

	//更新処理
	CEnemy::Update();
}

//================================================================
//敵の描画処理
//================================================================
void CEnemyMedBoss::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, Getpos().x, Getpos().y, Getpos().z);

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
void CEnemyMedBoss::Control(void)
{
	//デバッグプロックの情報取得
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	CDISPDETECTION *pDispDetection = CDISPDETECTION::GetFrame();

	D3DXVECTOR3 pos = Getpos();

	D3DXVECTOR3 posOld = GetPosOld();

	D3DXVECTOR3 posplayer = pPlayer->Getpos();

	if (m_state != STATE_DEATH && m_state != STATE_END)
	{
		if ((pCollision->CollisionCircle(&pos, 300.0f, pPlayer) == true))
		{//円の中にプレイヤーが入ったまたは、状態がダメージのとき

			posOld = pos;

			D3DXVECTOR3 fDest;

			float fDiffmove, fDestmove;

			fDest = pos - posplayer;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - m_rot.y;

			//角度の値を修正する--------------------------------------------------
			if (fDiffmove >= D3DX_PI)
			{
				fDiffmove = -D3DX_PI;
			}
			else if (fDiffmove <= -D3DX_PI)
			{
				fDiffmove = D3DX_PI;
			}

			m_rot.y += fDiffmove * 0.05f;

			//角度の値を修正する--------------------------------------------------
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y = -D3DX_PI;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y = D3DX_PI;
			}

			//移動量を更新(減衰させる)
			m_move.x = sinf(m_rot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(m_rot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 100.0f && fDest.x >= -100.0f && fDest.z <= 100.0f && fDest.z >= -100.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					pos.x -= m_move.x * 0.5f;
					pos.z -= m_move.z * 0.5f;

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

						m_nCntColli = 0;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{//状態が戦闘体制のとき

						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_bAction = false;
					}

					if (m_nCntAction >= 40)
					{//行動可能になった

						m_nCntAction = 0;

						//乱数の種を設定
						srand((unsigned int)time(0));

						int AttackType = rand() % ATTACKTYPE_MAX;  //攻撃の種類抽選

						switch (AttackType)
						{
						case ATTACKTYPE_NONE:   //通常攻撃

							m_ACKTYpe = ATTACKTYPE_NONE;

							break;

						case ATTACKTYPE_JUMP:   //ジャンプ攻撃

							if (m_state != STATE_ACTION)
							{//状態が攻撃以外の時
								m_JumpPoint = posplayer;
								m_JumpPoint.y = m_JumpPoint.y + 50.0f;
								pDispDetection->Create({ pos.x, 1.0f, pos.z });
								m_state = STATE_ACTION;
								m_ACKTYpe = ATTACKTYPE_JUMP;
								m_motion->Set(MOTIONTYPE_JUMP);
								pSound->Play(CSound::SOUND_LABEL_SE08);
								m_bAction = true;
							}

							break;

						case ATTACKTYPE_AROUND:   //範囲攻撃

							if (m_state != STATE_ACTION)
							{//状態が攻撃以外の時

								//モーションをセット(攻撃)
								m_motion->Set(MOTIONTYPE_ACTION);

								pSound->Play(CSound::SOUND_LABEL_SE00);

								m_state = STATE_ACTION;

								m_bAction = true;
							}

							m_ACKTYpe = ATTACKTYPE_AROUND;

							break;

						case ATTACKTYPE_BOM:

							if (m_state != STATE_ACTION)
							{//状態が攻撃以外の時

								//モーションをセット(攻撃)
								m_motion->Set(MOTIONTYPE_BOM);

								m_state = STATE_ACTION;

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y + 0.25f, 0.0f), CBullet::TYPE_BOM);

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y, 0.0f), CBullet::TYPE_BOM);

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y - 0.25f, 0.0f), CBullet::TYPE_BOM);

								m_bAction = true;
							}

							m_ACKTYpe = ATTACKTYPE_BOM;

							break;
						}

						if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
						{
							//モーションをセット(ニュートラル)
							m_motion->Set(MOTIONTYPE_DAMEGE);

							m_state = STATE_STAGGER;
						}

						if (m_state == STATE_STAGGER)
						{
							pos.x -= m_move.x;
							pos.z -= m_move.z;
						}
					}
				}
			}
			else
			{
				if (m_state != STATE_ACTION && m_ACKTYpe != ATTACKTYPE_JUMP && m_state != STATE_GETUP && m_state != STATE_DAMEGE && m_state != STATE_STAGGER && m_ACKTYpe != ATTACKTYPE_BOM)
				{//状態が攻撃以外かつ攻撃の種類がジャンプ攻撃以外の時

					pos.x += m_move.x * 1.3f;
					pos.z += m_move.z * 1.3f;

					if (m_state != STATE_MOVE)
					{//状態が移動以外の時

						m_nFrame = 0;

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
			if (m_state != STATE_DAMEGE && m_state != STATE_STAGGER)
			{
				if (m_state != STATE_NONE && m_ACKTYpe != ATTACKTYPE_JUMP && m_bAction == false)
				{//状態がNONE以外かつ攻撃の種類がジャンプ攻撃以外の時

					m_nFrame = 0;

					//モーションをセット(ニュートラル)
					m_motion->Set(MOTIONTYPE_NONE);

					m_state = STATE_NONE;
				}
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_AROUND)
		{
			m_nCntColli++;

			if (m_nCntColli >= FRIST && m_nCntColli <= FINISH)
			{
				if ((pCollision->CollisionCircle(&pos, 200.0f, pPlayer) == true))
				{//円の中にプレイヤーが入った

					pPlayer->Hit();
				}
			}
		}

		if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
		{
			//モーションをセット(ニュートラル)
			m_motion->Set(MOTIONTYPE_DAMEGE);

			m_state = STATE_STAGGER;
		}

		if (m_state == STATE_ACTION && m_ACKTYpe != ATTACKTYPE_JUMP && m_state != STATE_GETUP&& m_state != STATE_DAMEGE && m_state != STATE_STAGGER)
		{//状態が攻撃以外かつ攻撃の種類がジャンプ攻撃以外の時

			m_nFrame++;

			if (m_nFrame == 15)
			{
				CEffectSword::Create({ pos.x, pos.y + 20.0f, pos.z }, { 0.0f, m_rot.y, 0.0f });
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_JUMP && m_state != STATE_JUMP && m_state != STATE_GETUP)
		{//攻撃の種類がジャンプ攻撃かつ状態がジャンプ以外のとき

			m_move.y += ENEMYMOVE * 0.1f;

			pos.y += m_move.y;

			if (pos.y >= 100.0f)
			{
				m_state = STATE_JUMP;
				m_move = { 0.0f, 0.0f, 0.0f };
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_JUMP  && m_state == STATE_JUMP)
		{//攻撃の種類がジャンプ攻撃かつ状態がジャンプの時

			m_move.y += ENEMYMOVE * 0.8f;

			pos.y -= m_move.y;

			if (pos.y <= 0.0f)
			{
				pos.y = 0.0f;

				CParticl::Create(pos, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 5.0f, TYPEPAR_GROUND);
				CImpact::Create({ pos.x, 15.0f, pos.z }, CImpact::TYPE_NONE);

				pSound->Play(CSound::SOUND_LABEL_SE06);

				m_ACKTYpe = ATTACKTYPE_NONE;
				m_state = STATE_GETUP;
				m_motion->Set(MOTIONTYPE_GETUP);

				if ((pCollision->CollisionCircle(&pos, 300.0f, pPlayer) == true))
				{//円の中にプレイヤーが入った

					pPlayer->Hit();
				}

				if (pDispDetection != NULL)
				{
					pDispDetection->Uninit();
					pDispDetection = NULL;
				}
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_BOM)
		{//攻撃の種類が爆弾攻撃

			D3DXMATRIX Matrix = m_apModel[6]->GetMtxWorld();

			CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);
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

	if (m_motion->IsFinish() == true && m_state != STATE_DEATH)
	{//モーションが終了した

		m_move = { 0.0f, 0.0f, 0.0f };
		m_nFrame = 0;
		m_nCntColli = 0;
		//m_state = TATE_NONE;
		m_ACKTYpe = ATTACKTYPE_NONE;
		m_bAction = false;
	}

	//位置設定
	SetPos(&pos);
	SetPosOld(posOld);
}

//================================================================
//外部ファイル読み込み
//================================================================
void CEnemyMedBoss::ReadText(TYPEENE type)
{
	char aString[128] = {};
	char aComment[128] = {};
	const char *aText[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;
	int nCntPatrol = 0;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	switch (m_typeEne)
	{
	case TYPE_NONE:

		break;

	case TYPE_001:

		aText[0] = ENEMY001_TEXT;
		break;

	case TYPE_002:

		aText[0] = ENEMY002_TEXT;
		break;

	case TYPE_003:

		aText[0] = ENEMY003_TEXT;
		break;
	}

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(aText[0], "r");

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
		switch (m_typeEne)
		{
		case TYPE_NONE:

			break;

		case TYPE_001:

			//初期化処理
			m_motion->ReadText(ENEMY001_TEXT);
			break;

		case TYPE_002:

			//初期化処理
			m_motion->ReadText(ENEMY002_TEXT);
			break;

		case TYPE_003:

			//初期化処理
			m_motion->ReadText(ENEMY003_TEXT);
			break;
		}
		
	}
}