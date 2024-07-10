//==============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 大原　怜将
//
//==============================================================================

//*=============================================================================
//インクルードファイル
//*=============================================================================
#include "enemy.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "sound.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "debugproc.h"
#include "score.h"
#include "player.h"
#include <assert.h>

//*=============================================================================
//マクロ定義
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\enemy00.txt")   //敵のテキストファイル
#define ENEMYMOVE    (2.0f)                        //移動量

//*=============================================================================
//静的メンバ変数
//*=============================================================================
CEnemy *CEnemy::m_pEnemy[64] = {};
int CEnemy::m_nNumAll = 0;

//==============================================================================
//コンストラクタ
//==============================================================================
CEnemy::CEnemy()
{
	m_state = (STATE)0;
	m_nidxID = -1;
	m_nLife = 0;
}

//==============================================================================
//コンストラクタ
//==============================================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	SetPos(&pos);
	SetRot(&rot);
	SetLife(nlife);
	m_state = (STATE)0;
	m_nidxID = -1;
}

//==============================================================================
//デストラクタ
//==============================================================================
CEnemy::~CEnemy()
{

}

//==============================================================================
//生成処理
//==============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy(pos, rot, nlife);

		pEnemy->Init();
	}

	for (int nCount = 0; nCount < 64; nCount++)
	{
		if (m_pEnemy[nCount] == NULL)
		{
			m_pEnemy[nCount] = pEnemy;

			m_pEnemy[nCount]->SetIdx(nCount);

			m_nNumAll++;

			break;
		}
	}

	return pEnemy;
}

//==============================================================================
//初期化処理
//==============================================================================
HRESULT CEnemy::Init(void)
{
	if (m_motion == NULL)
	{//使用されていなかったら

		//生成
		m_motion = new CMotion;

		//初期化処理
		m_motion->Init();
	}

	ReadText(ENEMY_TEXT);

	return S_OK;
}

//==============================================================================
//終了処理
//==============================================================================
void CEnemy::Uninit(void)
{
	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンドストップ
	//pSound->Stop();

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
			m_apModel[nCount] = NULL;  //使用していない状態にする
		}
	}

	if (m_pEnemy[m_nidxID] != NULL)
	{
		m_pEnemy[m_nidxID] = NULL;

		m_nNumAll--;
	}
	
	CObject::Release();
}

//==============================================================================
//更新処理
//==============================================================================
void CEnemy::Update(void)
{
	CMap *pmap = CGame::GetMap();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	CFoot *pPlayerFoot = CGame::GetPlayerFoot();
	CChibi *pPlayerChibi = CGame::GetPlayerChibi();

	int life = GetLife();

	if (life <= 0)
	{
		int n = CGame::GetCounter();

		n++;

		CGame::SetCounter(n);

		CScore::AddScore(500);

		Uninit();
	}
	else
	{
		if (pPlayerFoot->GetState() != CFoot::STATE_APPR && pPlayerChibi->GetState() != CChibi::STATE_APPR)
		{
			for (int nCount = 0; nCount < m_nNumModel; nCount++)
			{
				m_apModel[nCount]->Update();
			}

			if (m_motion != NULL)
			{
				//初期化処理
				m_motion->Update();
			}

			//制御処理
			Controll();

			if (pCollision != NULL && pmap->GetX() != NULL)
			{
				//位置と向き取得
				D3DXVECTOR3 EnemyPos = Getpos();

				pCollision->MapEnemy(&EnemyPos, &m_posOld, pmap->GetX(), m_pEnemy[m_nidxID]);
			}
		}
	}
}

//==============================================================================
//描画処理
//==============================================================================
void CEnemy::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//描画処理
		m_apModel[nCount]->Draw();
	}
}

//==============================================================================
//制御処理
//==============================================================================
void CEnemy::Controll(void)
{
	CMap *pmap = CGame::GetMap();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	//位置と向き取得
	D3DXVECTOR3 EnemyPos = Getpos();
	D3DXVECTOR3 EnemyRot = GetRot();

	m_posOld = EnemyPos;  //位置を代入

	m_move.y -= 0.9f;

	EnemyPos.y += m_move.y;

	if ((pCollision->Circle(&EnemyPos, 400.0f, pPlayer) == true))
	{//円の中にプレイヤーが入ったまたは、状態がダメージのとき

		D3DXVECTOR3 fDest, pos = pPlayer->Getpos();

		float fDiffmove, fDestmove;

		fDest = EnemyPos - pos;

		fDestmove = atan2f(fDest.x, fDest.y);
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
		//m_move.z = cosf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;

		//移動量を位置に加算
		EnemyPos.x += m_move.x;
		

		if (m_state != STATE_MOVE)
		{
			//モーションをセット(移動)
			m_motion->Set(MOTIONTYPE_MOVE);

			m_state = STATE_MOVE;

			//m_bAction = false;
		}
	}
	else
	{
		if (m_state != STATE_NEUTRAL)
		{
			m_motion->Set(MOTIONTYPE_NEUTRAL);

			m_state = STATE_NEUTRAL;
		}

	}
	
	if (m_motion->IsFinish() == true)
	{
		m_state = STATE_NEUTRAL;
	}

	if (EnemyPos.y <= 0.0f)
	{
		EnemyPos.y = 0.0f;

		m_move.y = 0.0f;
	}

	//位置設定
	SetPos(&EnemyPos);
	SetRot(&EnemyRot);

	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n敵の位置：%f,%f,%f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
	pDebugProc->Print("敵の向き：%f,%f,%f\n", EnemyRot.x, EnemyRot.y, EnemyRot.z);
	pDebugProc->Print("敵の移動量：%f,%f,%f", m_move.x, m_move.y, m_move.z);
}

//==============================================================================
//テキストファイル読み込み
//==============================================================================
void CEnemy::ReadText(char *fliename)
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


