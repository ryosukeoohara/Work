//===========================================================
//
//ポリゴンを出すやつ[itemslot.cpp]
//Author 大原怜将
//
//===========================================================
#include "tutoriallogo.h"
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
CTutoriallogo::CTutoriallogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CTutoriallogo::CTutoriallogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CTutoriallogo::~CTutoriallogo()
{

}

//===========================================================
//クリエイト
//===========================================================
CTutoriallogo *CTutoriallogo::Create(D3DXVECTOR3 pos)
{
	CTutoriallogo *pTitlelogo = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CTutoriallogo(pos);

		//pTitlelogo->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Itemslot001.png");

		//テクスチャをバインド
		//pTitlelogo->BindTexture(pTexture->GetAddress(pTitlelogo->m_nIdxTexture));

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CTutoriallogo::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutologo.png"));

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTutoriallogo::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CTutoriallogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 200.0f, 50.0f);
}

//===========================================================
//描画処理
//===========================================================
void CTutoriallogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}