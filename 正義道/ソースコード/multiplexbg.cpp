//===========================================================
//
//ポリゴンを出すやつ[multiplexbg.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "bg.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "multiplexbg.h"

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CMultiplexBg::m_pTexture[TYPETEX_MAX] = {};
CObject2D *CMultiplexBg::m_apObject2D[TYPETEX_MAX] = {};
float CMultiplexBg::m_fTexU = 0.0f;
float CMultiplexBg::m_fTexV = 0.0f;

//================================================================
//コンストラクタ
//================================================================
CMultiplexBg::CMultiplexBg()
{
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
}

//================================================================
//デストラクタ
//================================================================
CMultiplexBg::~CMultiplexBg()
{

}

//================================================================
//生成処理
//================================================================
CMultiplexBg *CMultiplexBg::Create(void)
{
	//オブジェクト2Dのポインタ
	CMultiplexBg *pMultiplexBg = NULL;

	if (pMultiplexBg == NULL)
	{
		//オブジェクト2Dの生成
		pMultiplexBg = new CMultiplexBg;

		//初期化処理
		pMultiplexBg->Init();

		for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
		{
			if (m_pTexture[nCount] != NULL)
			{
				m_apObject2D[nCount]->BindTexture(m_pTexture[nCount]);
			}
		}
	}

	return pMultiplexBg;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CMultiplexBg::Init(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] == NULL)
		{//使用していなかったら

			//生成
			m_apObject2D[nCount] = CObject2D::Create({ 0.0f,0.0f,0.0f });

			//初期化処理
			m_apObject2D[nCount]->Init();
		}
	}

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CMultiplexBg::Uninit(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Uninit();

			m_apObject2D[nCount] = NULL;
		}
	}

	Release();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CMultiplexBg::Update(void)
{
	m_fTexU += 0.001f;

	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Update();
		}
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CMultiplexBg::Draw(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_apObject2D[nCount] != NULL)
		{
			m_apObject2D[nCount]->Draw();
		}
	}
}

//================================================================
//テクスチャの生成(読み込み)
//================================================================
HRESULT CMultiplexBg::Load(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		if (m_pTexture[nCount] == NULL)
		{
			if (nCount == TYPETEX_00)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg100.png",
					&m_pTexture[nCount]);
			}

			if (nCount == TYPETEX_01)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg101.png",
					&m_pTexture[nCount]);
			}

			if (nCount == TYPETEX_02)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					"data\\TEXTURE\\bg102.png",
					&m_pTexture[nCount]);
			}
		}
	}

	return S_OK;
}

//================================================================
//テクスチャの破棄
//================================================================
void CMultiplexBg::UnLoad(void)
{
	for (int nCount = 0; nCount < TYPETEX_MAX; nCount++)
	{
		//テクスチャの処理
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}