//===========================================================
//
// タイトルロゴ処理[titlelogo.cpp]
// Author 大原怜将
//
//===========================================================
#include "titlelogo.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "frame.h"
#include "game.h"

//===========================================================
//コンストラクタ
//===========================================================
CTitlelogo::CTitlelogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CTitlelogo::CTitlelogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CTitlelogo::~CTitlelogo()
{

}

//===========================================================
//クリエイト
//===========================================================
CTitlelogo *CTitlelogo::Create(D3DXVECTOR3 pos)
{
	CTitlelogo *pTitlelogo = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CTitlelogo(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CTitlelogo::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\titlelogo.png"));

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTitlelogo::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CTitlelogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 400.0f, 150.0f);
}

//===========================================================
//描画処理
//===========================================================
void CTitlelogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}