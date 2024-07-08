//===========================================================
//
//ポリゴンを出すやつ[ranking.cpp]
//Author 大原怜将
//
//===========================================================
#include "ranking.h"
#include "texture.h"
#include "manager.h"
#include "time.h"

//===========================================================
//静的メンバ変数
//===========================================================
int CRanking::m_nScore[MAX_RANK] = {};

//===========================================================
//コンストラクタ
//===========================================================
CRanking::CRanking()
{
	m_nIdxTexture = 0;
}

//===========================================================
//デストラクタ
//===========================================================
CRanking::~CRanking()
{

}

//===========================================================
//生成処理
//===========================================================
CRanking *CRanking::Create(void)
{
	//ランキングのポインタ
	CRanking *pRanking = NULL;

	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	if (pRanking == NULL)
	{//使用されていない場合

		//生成
		pRanking = new CRanking;

		//初期化処理
		pRanking->Init();
	}

	return pRanking;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CRanking::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			if (m_apObject2D[nCntRank] != NULL)
			{//使用されていない場合

				//生成
				m_apObject2D[nCntRank][nCntScore] = CObject2D::Create({ 500.0f + nCntScore * 50.0f, 180.0f + nCntRank * 100.0f, 0.0f });

				//テクスチャ読み込み
				m_apObject2D[nCntRank][nCntScore]->SetIdxTex(pTexture->Regist("data\\TEXTURE\\number000.png"));
			}
		}
	}

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			if (m_apObject2D[nCntRank][nCntScore] != NULL)
			{//使用されいる状態のとき

				//終了処理
				m_apObject2D[nCntRank][nCntScore]->Uninit();

				//使用していない状態にする
				m_apObject2D[nCntRank][nCntScore] = NULL;
			}
		}
	}

	Release();
}

//===========================================================
//更新処理
//===========================================================
void CRanking::Update(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			if (m_apObject2D[nCntRank][nCntScore] != NULL)
			{//使用されている状態のとき

				//更新処理
				m_apObject2D[nCntRank][nCntScore]->Update();
			}
		}
	}

	int aTexU[MAX_RANK][MAX_SCORE];    //各桁の数字を格納

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		aTexU[nCntRank][0] = m_nScore[nCntRank] % 100000000 / 10000000;
		aTexU[nCntRank][1] = m_nScore[nCntRank] % 10000000 / 1000000;
		aTexU[nCntRank][2] = m_nScore[nCntRank] % 1000000 / 100000;
		aTexU[nCntRank][3] = m_nScore[nCntRank] % 100000 / 10000;
		aTexU[nCntRank][4] = m_nScore[nCntRank] % 10000 / 1000;
		aTexU[nCntRank][5] = m_nScore[nCntRank] % 1000 / 100;
		aTexU[nCntRank][6] = m_nScore[nCntRank] % 100 / 10;
		aTexU[nCntRank][7] = m_nScore[nCntRank] % 10;
	}

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			m_apObject2D[nCntRank][nCntScore]->SetVtxRanking(aTexU[nCntRank][nCntScore]);
		}
	}
}

//===========================================================
//描画処理
//===========================================================
void CRanking::Draw(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			if (m_apObject2D[nCntRank][nCntScore] != NULL)
			{//使用されている状態のとき

			 //描画処理
				m_apObject2D[nCntRank][nCntScore]->Draw();
			}
		}
	}
}

//===========================================================
//ランキングリセット処理
//===========================================================
void CRanking::ResetRanking(void)
{

}

//===========================================================
//ランキング設定処理
//===========================================================
void CRanking::SetRanking(int nScore)
{
	FILE *pFile;

	pFile = fopen("ranking.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		for (int nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &m_nScore[nCount]);
		}

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルが開けませんでした***");
	}

	if (m_nScore[MAX_RANK - 1] < nScore)
	{
		m_nScore[MAX_RANK - 1] = nScore;
	}

	//ソート開始
	for (int nCount = 0; nCount < MAX_RANK - 1; nCount++)
	{
		for (int nCntRank = 1 + nCount; nCntRank < MAX_RANK; nCntRank++)
		{
			//大きかったら入れ替え
			if (m_nScore[nCount] < m_nScore[nCntRank])
			{//入れ替え

				int nTmp = m_nScore[nCntRank];
				m_nScore[nCntRank] = m_nScore[nCount];
				m_nScore[nCount] = nTmp;
			}
		}
	}

	pFile = fopen("ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", m_nScore[nCount]);
		}

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルが開けませんでした***");
	}
}