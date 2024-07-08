//===========================================================
//
//ポリゴンを出すやつ[map.cpp]
//Author 大原怜将
//
//===========================================================
#include "map.h"
#include "model.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//マクロ定義
#define MAPMODEL  ("data\\TEXT\\model.txt")  //テキストファイル名

//静的メンバ変数
CObjectX *CMap::m_apModel[MAX_MODEL] = {};

//===========================================================
//コンストラクタ
//===========================================================
CMap::CMap()
{
	m_nIdxModel = -1;
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
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			//終了処理
			m_apModel[nCount]->Uninit();

			//使用していない状態にする
			m_apModel[nCount] = NULL;
		}
	}

	Release();
}

//================================================================
//プレイヤーの更新処理
//================================================================
void CMap::Update(void)
{
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			//更新処理
			m_apModel[nCount]->Update();
		}
	}
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CMap::Draw(void)
{
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用していたら

			//描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

//================================================================
//外部ファイル読み込み
//================================================================
void CMap::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntModel = 0;
	int nIdx = 0;

	//モデルのポインタ取得
	CModel *pModel = CManager::GetModel();

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
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumAll);  //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
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
							fscanf(pFile, "%s", &aString);  //=
							fscanf(pFile, "%d", &m_nIdx);     //種類
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &pos.x);  //位置
							fscanf(pFile, "%f", &pos.y);  //位置
							fscanf(pFile, "%f", &pos.z);  //位置
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &rot.x);  //位置
							fscanf(pFile, "%f", &rot.y);  //位置
							fscanf(pFile, "%f", &rot.z);  //位置
						}
					}

					if (m_apModel[nIdx] == NULL)
					{//使用していなかったら

						//m_nIdxModel = pModel->Regist(m_aModel[nIdx].m_pos, m_aModel[nIdx].m_rot, m_aModel[m_nIdx].m_filename);

						//オブジェクトXを生成
						//m_apModel[nIdx] = &pModel->GetAddress(m_nIdxModel);

						m_apModel[nIdx] = CObjectX::Create(pos, rot, m_filename[m_nIdx]);
					}
					
					nIdx++;  //カウントアップ

				}  //NUM_MODELのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}