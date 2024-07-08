//=============================================================================
//
// シャドウ処理 [shadow.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "shadow.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "enemyweak.h"

//静的メンバ変数
CObject3D *CShadow::m_Shadow[MAX_SHADOW] = {};

//================================================================
//コンストラクタ
//================================================================
CShadow::CShadow()
{
	m_nIdxTexture = -1;
}

//================================================================
//コンストラクタ
//================================================================
CShadow::CShadow(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CShadow::~CShadow()
{

}

//================================================================
//デストラクタ
//================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow *pShadow = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pShadow == NULL)
		{
			//オブジェクト2Dの生成
			pShadow = new CShadow(pos);

			//初期化処理
			pShadow->Init();
		}
	}

	return pShadow;
}

//================================================================
//シャドウの初期化処理
//================================================================
HRESULT CShadow::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\shadow000.jpg");

	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//初期化処理
	//		m_Shadow[nCount]->Init();
	//	}
	//}
	
	CObject3D::Init();

	return S_OK;
}

//================================================================
//シャドウの終了処理
//================================================================
void CShadow::Uninit(void)
{
	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//終了処理
	//		m_Shadow[nCount]->Uninit();
	//	}
	//}

	CObject3D::Uninit();
}

//================================================================
//シャドウの更新処理
//================================================================
void CShadow::Update(void)
{
	//for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	//{
	//	if (m_Shadow[nCount] != NULL)
	//	{
	//		//更新処理
	//		m_Shadow[nCount]->Update();

	//		m_Shadow[nCount]->SetShadowPosition({ 0.0f,0.0f,0.0f }, 20.0f, 20.0f);
	//	}
	//}

	CObject3D::Update();

	CObject3D::SetShadowPosition({ 0.0f,0.0f,0.0f }, 20.0f, 20.0f);
}

//================================================================
//シャドウの描画処理
//================================================================
void CShadow::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================
//シャドウの設定処理
//================================================================
int CShadow::Set(D3DXVECTOR3 pos)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (m_Shadow[nCount] == NULL)
		{
			m_Shadow[nCount] = Create(pos);

			nCntShadow = nCount;

			break;
		}
	}

	return nCntShadow;
}

//================================================================
//位置更新
//================================================================
void CShadow::SetPosition(int nIdxShadow, D3DXVECTOR3 pos)
{
	CShadow::SetPos(&pos);
}