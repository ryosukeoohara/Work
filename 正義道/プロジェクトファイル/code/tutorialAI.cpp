//===============================================================
//
// チュートリアルAI処理[tutorialAI.cpp]
// Author 大原怜将
//
//===============================================================
#include "tutorialAI.h"
#include "motion.h"
#include "shadow.h"
#include "manager.h"
#include "renderer.h"

//================================================================
//マクロ定義
//================================================================
#define PLAYER_TEXT ("data\\TEXT\\yankinear.txt")      //プレイヤーのテキストファイル

//===============================================================
//コンストラクタ
//===============================================================
CTutorialAI::CTutorialAI()
{

}

//===============================================================
//コンストラクタ
//===============================================================
CTutorialAI::CTutorialAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);
	SetRot(&rot);
}

//===============================================================
//デストラクタ
//===============================================================
CTutorialAI::~CTutorialAI()
{
	
}

//===============================================================
//クリエイト
//===============================================================
CTutorialAI * CTutorialAI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//オブジェクト2Dのポインタ
	CTutorialAI *pTutorialAI = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pTutorialAI == NULL)
		{
			//オブジェクト2Dの生成
			pTutorialAI = new CTutorialAI(pos, rot);

			//初期化処理
			pTutorialAI->Init();
		}
	}

	return pTutorialAI;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CTutorialAI::Init(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_motion == NULL)
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

	ReadText();

	//モデルの設定
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return E_NOTIMPL;
}

//===============================================================
//終了処理
//===============================================================
void CTutorialAI::Uninit(void)
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

//===============================================================
//更新処理
//===============================================================
void CTutorialAI::Update(void)
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
}

//===============================================================
//描画処理
//===============================================================
void CTutorialAI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

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

//===============================================================
//テキストファイル読み込み処理
//===============================================================
void CTutorialAI::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

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
