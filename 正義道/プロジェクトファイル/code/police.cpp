//===========================================================
//
//ポリゴンを出すやつ[enemy.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "object.h"
#include "police.h"
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

//================================================================
//静的メンバ変数
//================================================================
int CPolice::m_nNumAll = 0;
CPolice *CPolice::m_Police[MAX_ENEMY] = {};
//CPolice::TYPE CPolice::m_type = TYPE_NONE;

//================================================================
//マクロ定義
//================================================================
#define POLICE_TEXT      ("data\\TEXT\\police.txt")      //警察のテキストファイル

//================================================================
//コンストラクタ
//================================================================
CPolice::CPolice()
{
	m_nNumber = 0;
	m_pShadow = NULL;
	m_Life = NULL;
}

//================================================================
//コンストラクタ
//================================================================
CPolice::CPolice(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nNumber = 0;
	m_pShadow = NULL;
	m_Life = NULL;
}

//================================================================
//デストラクタ
//================================================================
CPolice::~CPolice()
{

}

//================================================================
//敵の初期化処理
//================================================================
HRESULT CPolice::Init(void)
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
void CPolice::Uninit(void)
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

	if (m_Police[m_nNumber] != NULL)
	{
		m_Police[m_nNumber] = NULL;
	}

	CObject::Release();
}

//================================================================
//敵の更新処理
//================================================================
void CPolice::Update(void)
{
	//影の情報を取得
	CShadow *pShadow = CGame::GetShadow();

	CLife *pLife = CGame::GetLife();

	//位置取得
	D3DXVECTOR3 PolicePos = Getpos();

	//敵マネージャの情報取得
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();

	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

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
	//int nLife = GetLife();

	//for (int nCount = 0; nCount < nNumEnemy; nCount++)
	//{
	//	if (m_Police[nCount] != NULL)
	//	{
	//		int life = m_Police[nCount]->GetLife();

	//		if (life <= 0)
	//		{//体力がなくなったら

	//			int DeathCounter = pEnemyManager->GetCounter();

	//			DeathCounter++;

	//			pEnemyManager->SetCounter(DeathCounter);

	//			if (m_Police[nCount]->m_type == TYPE_NEAR)
	//			{
	//				CItem::Create(m_Police[nCount]->Getpos(), CItem::TYPE_NAILBAT, "data\\MODEL\\kugibat.x");
	//			}

	//			/*if (m_Police[nCount]->m_type == TYPE_FAR)
	//			{
	//			CItem::Create(m_Police[nCount]->Getpos(), CItem::TYPE_BOM, "data\\MODEL\\bom.x");
	//			}*/

	//			CScore::AddScore(500);

	//			//終了処理
	//			m_Police[nCount]->Uninit();

	//			//使用していない状態にする
	//			m_Police[nCount] = NULL;

	//			return;
	//		}
	//	}
	//}

	m_pShadow->SetPosition(m_nIdxShaadow, { PolicePos.x, 2.0f, PolicePos.z });

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	//pDebugProc->Print("\n敵の体力：<<%d>>", nLife);
	pDebugProc->Print("\n敵の位置：<<X軸:%f,Y軸:%f,Z軸:%f>>", PolicePos.x, PolicePos.y, PolicePos.z);
	//pDebugProc->Print("\n敵の向き：<<X軸:%f,Y軸:%f,Z軸:%f>>", m_rot.x, m_rot.y, m_rot.z);
}

//================================================================
//敵の描画処理
//================================================================
void CPolice::Draw(void)
{

}

//================================================================
//動き制御処理
//================================================================
void CPolice::Controll(void)
{
	D3DXVECTOR3 PolicePos = Getpos();


}

//================================================================
//外部ファイル読み込み
//================================================================
void CPolice::ReadText(char *Filename)
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

				 if (strcmp("SET_PATROL", aString) == 0)   //巡回地点設定
				 {
				 	while (strcmp("END_PATROL", aString) != 0)
				 	{
				 		fscanf(pFile, "%s", &aString);

				 		if (strcmp("NUM_PATROL", aString) == 0)
				 		{
				 			fscanf(pFile, "%s", &aString);  //=
				 			fscanf(pFile, "%d", &m_nNumPatrol);  //巡回する地点の数
				 		}
				 		
				 		if (strcmp("PATROLPOS", aString) == 0)
				 		{
				 			fscanf(pFile, "%s", &aString);  //=
				 			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.x);  //巡回地点
				 			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.y);  //巡回地点
				 			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.z);  //巡回地点

				 			nCntPatrol++;
				 		}

				 	}
				 }
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
		//テキストファイル読み込み
		m_motion->ReadText(POLICE_TEXT);
	}
}