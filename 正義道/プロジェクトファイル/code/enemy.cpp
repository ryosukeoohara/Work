//===========================================================
//
// 敵の処理[enemy.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "object.h"
#include "enemy.h"
#include "texture.h"
#include "manager.h"
#include "character.h"
#include "enemymanager.h"
#include "game.h"
#include "score.h"
#include "debugproc.h"
#include "particl.h"
#include "enemyweak.h"
#include "fade.h"
#include "life.h"
#include "item.h"
#include "player.h"

//静的メンバ変数
int CEnemy::m_nNumAll = 0;
CEnemy *CEnemy::m_Enemy[MAX_ENEMY] = {};
//CEnemy::TYPE CEnemy::m_type = TYPE_NONE;

//マクロ定義
#define ENEMYNEAR_TEXT     ("data\\TEXT\\yanki001.txt")  //敵のテキストファイル
#define ENEMYFAR_TEXT      ("data\\TEXT\\enemyfar.txt")  //敵のテキストファイル

//================================================================
//コンストラクタ
//================================================================
CEnemy::CEnemy()
{
	m_nNumber = 0;
	m_pShadow = NULL;
	m_Life = NULL;
}

//================================================================
//デストラクタ
//================================================================
CEnemy::~CEnemy()
{

}

//================================================================
//敵の初期化処理
//================================================================
HRESULT CEnemy::Init(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow(pos);

		//初期化処理
		m_pShadow->Init();
	}

	/*if (m_Life == NULL)
	{
		m_Life = new CLife(pos);

		m_Life->Init();
	}*/

	//CLife::Set({pos.x, pos.y + 50.0f, pos.z});

	return S_OK;
}

//================================================================
//敵の終了処理
//================================================================
void CEnemy::Uninit(void)
{
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

		//delete m_pShadow;

		m_pShadow = NULL;
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

	if (m_Enemy[m_nNumber] != NULL)
	{
		m_Enemy[m_nNumber] = NULL;
	}

	CObject::Release();
}

//================================================================
//敵の更新処理
//================================================================
void CEnemy::Update(void)
{
	//影の情報を取得
	CShadow *pShadow = CGame::GetShadow();

	CLife *pLife = CGame::GetLife();

	//位置取得
	D3DXVECTOR3 EnemyPos = Getpos();

	//敵マネージャの情報取得
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();

	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	//プレイヤーの情報を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	//敵の総数取得
	int nNumEnemy = CEnemyManager::GetNumAll();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//更新処理
		m_apModel[nCount]->Update();
	}

	if (m_motion != NULL)
	{//使用されていたら

		//初期化処理
		m_motion->Update();
	}

	//デバッグ表示用体力取得
	int nLife = GetLife();

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		if (m_Enemy[nCount] != NULL)
		{
			int life = m_Enemy[nCount]->GetLife();

			if (life <= 0 && m_Enemy[nCount]->GetState() != STATE_DEATH && m_Enemy[nCount]->GetState() != STATE_END)
			{//体力がなくなったら

				if (m_Enemy[nCount]->m_type == TYPE_NEAR)
				{
					
				}

				/*if (m_Enemy[nCount]->m_type == TYPE_FAR)
				{
					CItem::Create(m_Enemy[nCount]->Getpos(), CItem::TYPE_BOM, "data\\MODEL\\bom.x");
				}*/

				m_Enemy[nCount]->SetState(STATE_DEATH);
			}

			if (m_Enemy[nCount]->GetState() == STATE_END)
			{
				//CItem::Create(m_Enemy[nCount]->Getpos(), CItem::TYPE_NAILBAT, "data\\MODEL\\kugibat.x");



				//終了処理
				m_Enemy[nCount]->Uninit();

				//使用していない状態にする
				m_Enemy[nCount] = NULL;

				CScore::AddScore(500);

				int DeathCounter = pEnemyManager->GetCounter();

				DeathCounter++;

				pEnemyManager->SetCounter(DeathCounter);

				pPlayer->SetBullet(6);

				

				return;
			}
		}
	}

	m_pShadow->SetPosition(m_nIdxShaadow, { EnemyPos.x, 2.0f, EnemyPos.z });

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\n敵の体力：<<%d>>", nLife);
	pDebugProc->Print("\n敵の位置：<<X軸:%f,Y軸:%f,Z軸:%f>>", EnemyPos.x, EnemyPos.y, EnemyPos.z);
	pDebugProc->Print("\n敵の向き：<<X軸:%f,Y軸:%f,Z軸:%f>>", m_rot.x, m_rot.y, m_rot.z);
}

//================================================================
//敵の描画処理
//================================================================
void CEnemy::Draw(void)
{
	
}

//================================================================
//ヒット処理
//================================================================
void CEnemy::Hit(void)
{
	if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE &&  m_state != STATE_JUMP && m_state != STATE_END && m_state != STATE_DEATH)
	{
		int Life = GetLife();

		Life -= 1;

		SetLife(Life);

		SetState(CEnemy::STATE_DAMEGE);

		D3DXVECTOR3 pos = Getpos();

		D3DXVECTOR3 rot = GetRot();
	}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CEnemy::ReadText(char *Filename)
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