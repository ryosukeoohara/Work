//===========================================================
//
//ポリゴンを出すやつ[time.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "time.h"
#include "texture.h"
#include "game.h"
#include "fade.h"

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CTime::m_pTexture = NULL;
CNumber *CTime::m_apNumber[SETTIME] = {};
int CTime::m_nTime = 0;
int CTime::m_nTimerCount = 0;

//================================================================
//コンストラクタ
//================================================================
CTime::CTime()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nTime = 0;  //時間
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CTime::CTime(D3DXVECTOR3 pos)
{
	m_pos = pos;  //位置
	SetPosition(pos);
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_nTime = 0;  //時間
}

//================================================================
//デストラクタ
//================================================================
CTime::~CTime()
{

}

//================================================================
//生成処理
//================================================================
CTime *CTime::Create(void)
{
	//オブジェクト2Dのポインタ
	CTime *pTime = NULL;

	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pTime == NULL)
		{
			//オブジェクト2Dの生成
			pTime = new CTime();

			//初期化処理
			pTime->Init();
		}
	}

	return pTime;
}

//================================================================
//プレイヤーの初期化処理
//================================================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < SETTIME; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 600.0f + 50.0f * nCount, 50.0f, 0.0f });

			//テクスチャをバインド
			//m_apNumber[nCount]->BindTexture(pTexture->GetAddress(m_nIdxTexture));

			m_apNumber[nCount]->SetNumberType(TYPENUMBER_TIME);

			//初期化処理
			//m_apNumber[nCount]->Init();

			m_apNumber[nCount]->m_Number = INITTIME;
		}
	}

	m_nTime = TIME;  //時間

	return S_OK;
}

//================================================================
//プレイヤーの終了処理
//================================================================
void CTime::Uninit(void)
{
	for (int nCount = 0; nCount < SETTIME; nCount++)
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
void CTime::Update(void)
{
	for (int nCount = 0; nCount < SETTIME; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//更新処理
			m_apNumber[nCount]->Update();
		}
	}

	TimeCounter();
}

//================================================================
//プレイヤーの描画処理
//================================================================
void CTime::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < SETTIME; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//描画処理
			m_apNumber[nCount]->Draw();
		}
	}
}

//================================================================
//タイム
//================================================================
void CTime::TimeCounter(void)
{
	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	m_nTimerCount++;

	if (m_nTimerCount % 60 == 0)
	{
		m_nTime--;

		m_apNumber[0]->m_Number = m_nTime % 100 / 10;
		m_apNumber[1]->m_Number = m_nTime % 10 / 1;
	}

	for (int nCount = 0; nCount < SETTIME; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_apNumber[nCount]->m_Number);
	}

	if (m_nTime <= 0)
	{
		if (pFade->Get() != pFade->FADE_OUT)
		{
			pFade->Set(CScene::MODE_RESULT);
		}
	}
}

////================================================================
////テクスチャの生成(読み込み)
////================================================================
//HRESULT CTime::Load(void)
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
//void CTime::UnLoad(void)
//{
//	//テクスチャの処理
//	if (m_pTexture != NULL)
//	{//使用されていたら
//
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}