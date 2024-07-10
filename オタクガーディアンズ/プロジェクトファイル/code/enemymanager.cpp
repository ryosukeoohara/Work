//=============================================================================
//
// 敵の管理 [enemymanager.cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
//インクルードファイル
//*============================================================================
#include "enemymanager.h"

//*============================================================================
//マクロ定義
//*============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\enemyinformation.txt")    //敵の最大数

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemyManager::CEnemyManager()
{
	//初期化
	ZeroMemory(m_pEnemy, sizeof(CEnemy));
	m_nEnemyAll = 0;
	m_Readpos = { 0.0f,0.0f,0.0f };
	m_Readrot = { 0.0f,0.0f,0.0f };
}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemyManager::~CEnemyManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CEnemyManager::Init(void)
{
	//テキストファイル読み込み
	//ReadText();

	/*CEnemy::Create({ 0.0f,10.0f,0.0f }, { 0.0f,0.0f,0.0f }, 90);
	CEnemy::Create({ 3600.0f,115.0f,0.0f }, { 0.0f,0.0f,0.0f }, 80);
	CEnemy::Create({ 3000.0f,455.0f,0.0f }, { 0.0f,0.0f,0.0f }, 50);
	CEnemy::Create({ 4800.0f,310.0f,0.0f }, { 0.0f,0.0f,0.0f }, 100);
	CEnemy::Create({ 4300.0f,650.0f,0.0f }, { 0.0f,0.0f,0.0f }, 90);

	CEnemy::Create({ 5600.0f,620.0f,0.0f }, { 0.0f,0.0f,0.0f }, 250);*/

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CEnemyManager::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (m_pEnemy[nCount] != NULL)
		{//使用されていたら

			////終了処理
			m_pEnemy[nCount]->Uninit();

			//使用していない状態にする
			m_pEnemy[nCount] = NULL;
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CEnemyManager::Update(void)
{
	//for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	//{
	//	if (m_pEnemy[nCount] != NULL)
	//	{//使用されていたら

	//		//更新処理
	//		m_pEnemy[nCount]->Update();
	//	}
	//}
}

void CEnemyManager::Draw(void)
{
	//for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	//{
	//	if (m_pEnemy[nCount] != NULL)
	//	{//使用されていたら

	//		//更新処理
	//		m_pEnemy[nCount]->Draw();
	//	}
	//}
}

//=============================================================================
//テキストファイル読み込み
//=============================================================================
void CEnemyManager::ReadText(void)
{
	int nLife = 0;
	char aString[128] = {};

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(ENEMY_TEXT, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp("ALL_ENEMY", aString) == 0)
			{
				fscanf(pFile, "%s", &aString);          //=
				fscanf(pFile, "%d", &m_nEnemyAll);  //モデルの総数

			}  //NUM_MODELのかっこ

			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("ENEMYSET", aString) == 0)
				{
					while (strcmp("ENEMYSET_END", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readpos.x);  //敵の位置
							fscanf(pFile, "%f", &m_Readpos.y);  //敵の位置
							fscanf(pFile, "%f", &m_Readpos.z);  //敵の位置
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readrot.x);  //敵の向き
							fscanf(pFile, "%f", &m_Readrot.y);  //敵の向き
							fscanf(pFile, "%f", &m_Readrot.z);  //敵の向き
						}

						if (strcmp("LIFE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);       //=
							fscanf(pFile, "%d", &nLife);       //敵の体力
						}

					}//ENEMYSET_ENDのかっこ 

					for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
					{
						if (m_pEnemy[nCount] == NULL)
						{//使用されていなかったら

							//CEnemy *pEnemy = new CEnemy(m_Readpos, m_Readrot, nLife);

							//m_pEnemy[nCount] = CEnemy::Create(m_Readpos, m_Readrot, nLife);

							//m_pEnemy[nCount]->Init();

							break;
						}
					}

				}//ENEMYSETのかっこ 

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
