//===========================================================
//
//マップ処理[map.cpp]
//Author 大原怜将
//
//===========================================================
#include "map.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"

//マクロ定義
#define MAPMODEL  ("data\\TEXT\\map.txt")  //テキストファイル名

//静的メンバ変数
//CObjectX *CMap::m_apModel[MAX_MODEL] = {};

//===========================================================
//コンストラクタ
//===========================================================
CMap::CMap()
{
	m_nNumAll = 0;
	m_nIdx = -1;
	ZeroMemory(m_filename, sizeof(char));
}

//================================================================
//デストラクタ
//================================================================
CMap::~CMap()
{

}

//================================================================
//プレイヤーの初期化処理
//================================================================
HRESULT CMap::Init(void)
{
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//終了処理
			m_apModel[nCount] = NULL;
		}
	}

	//外部ファイル読み込み
	ReadText();

	return S_OK;
}

//================================================================
//プレイヤーの終了処理
//================================================================
void CMap::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			//終了処理
			m_apModel[nCount]->Uninit();

			//使用していない状態にする
			m_apModel[nCount] = NULL;
		}
	}

	m_nNumAll = 0;

	//Release();
}

//================================================================
//プレイヤーの更新処理
//================================================================
void CMap::Update(void)
{
	//for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{//使用していたら

	//		//更新処理
	//		m_apModel[nCount]->Update();
	//	}
	//}
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CMap::Draw(void)
{
	//for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{//使用していたら

	//		//描画処理
	//		m_apModel[nCount]->Draw();
	//	}
	//}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CMap::ReadText(void)
{
	char aString[MAX_CHAR] = {};
	int nCntModel = 0;
	int nIdx = 0;

	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(MAPMODEL, "r");

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
					fscanf(pFile, "%s", &aString);                   //=
					fscanf(pFile, "%d", &m_nNumAll);                 //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);                   //=
					fscanf(pFile, "%s", &m_filename[nCntModel][0]);  //モデルの名前

					nCntModel++;

				}  //MODEL_LILENAMEのかっこ

				if (strcmp("MODELSET", aString) == 0)
				{
					while (strcmp("END_MODELSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);         //=
							fscanf(pFile, "%d", &m_nIdx);          //種類
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &pos.x);            //位置
							fscanf(pFile, "%f", &pos.y);            //位置
							fscanf(pFile, "%f", &pos.z);            //位置
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &rot.x);            //位置
							fscanf(pFile, "%f", &rot.y);            //位置
							fscanf(pFile, "%f", &rot.z);            //位置
						}
					}

					if (m_apModel[nIdx] == NULL)
					{//使用していなかったら

						//m_apModel[nIdx] = CObjectX::Create(pos, rot, m_filename[m_nIdx]);

						m_apModel[nIdx] = new CObjectX(pos, rot, m_filename[m_nIdx]);

						m_apModel[nIdx]->Init();
					}
					
					nIdx++;  //カウントアップ

				}  //NUM_MODELのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}
}

CMap * CMap::Create(void)
{
	CMap *pMap = nullptr;

	if (pMap == nullptr)
	{
		pMap = new CMap;

		pMap->Init();
	}

	return pMap;
}
