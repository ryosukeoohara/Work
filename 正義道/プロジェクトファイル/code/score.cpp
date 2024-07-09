//===========================================================
//
// スコア処理[score.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "input.h"
#include "input.h"
#include "texture.h"
#include "game.h"

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;
CNumber *CScore::m_apNumber[SETSCORE] = {};
int CScore::m_nScore = 0;

//================================================================
//コンストラクタ
//================================================================
CScore::CScore()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nScore = 0;  //スコア
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CScore::CScore(D3DXVECTOR3 pos)
{
	m_pos = pos;  //位置
	SetPosition(pos);
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nScore = 0;  //スコア
}

//================================================================
//デストラクタ
//================================================================
CScore::~CScore()
{

}

//================================================================
//生成処理
//================================================================
CScore *CScore::Create(void)
{
	//オブジェクト2Dのポインタ
	CScore *pScore = NULL;

	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pScore == NULL)
		{
			//オブジェクト2Dの生成
			pScore = new CScore();

			//初期化処理
			pScore->Init();
		}
	}

	return pScore;
}

//================================================================
//プレイヤーの初期化処理
//================================================================
HRESULT CScore::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < SETSCORE; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 800.0f + 50.0f * nCount, 50.0f, 0.0f });

			//テクスチャをバインド
			//m_apNumber[nCount]->BindTexture(pTexture->GetAddress(m_nIdxTexture));

			m_apNumber[nCount]->SetNumberType(TYPENUMBER_SCORE);

			//初期化処理
			m_apNumber[nCount]->Init();
		}
	}

	return S_OK;
}

//================================================================
//プレイヤーの終了処理
//================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < SETSCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//終了処理
			m_apNumber[nCount]->Uninit();

			m_apNumber[nCount] = NULL;
		}
	}

	Release();
}

//================================================================
//プレイヤーの更新処理
//================================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < SETSCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//更新処理
			m_apNumber[nCount]->Update();
		}
	}
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CScore::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < SETSCORE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//描画処理
			m_apNumber[nCount]->Draw();
		}
	}
}

//================================================================
//スコア加算処理
//================================================================
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;

	m_apNumber[0]->m_Number = m_nScore % 100000000 / 10000000;
	m_apNumber[1]->m_Number = m_nScore % 10000000 / 1000000;
	m_apNumber[2]->m_Number = m_nScore % 1000000 / 100000;
	m_apNumber[3]->m_Number = m_nScore % 100000 / 10000;
	m_apNumber[4]->m_Number = m_nScore % 10000 / 1000;
	m_apNumber[5]->m_Number = m_nScore % 1000 / 100;
	m_apNumber[6]->m_Number = m_nScore % 100 / 10;
	m_apNumber[7]->m_Number = m_nScore % 10 / 1;
	
	for (int nCount = 0; nCount < SETSCORE; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_apNumber[nCount]->m_Number);
	}
}

////================================================================
////テクスチャの生成(読み込み)
////================================================================
//HRESULT CScore::Load(void)
//{
//	CRenderer *pRenderer;
//	pRenderer = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\number000.png",
//		&m_pTexture
//	);
//
//	return S_OK;
//}
//
////================================================================
////テクスチャの破棄
////================================================================
//void CScore::UnLoad(void)
//{
//	//テクスチャの処理
//	if (m_pTexture != NULL)
//	{//使用されていたら
//
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}