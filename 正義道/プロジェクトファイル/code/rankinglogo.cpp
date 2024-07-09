//===========================================================
//
// ランキングのロゴ処理[itemslot.cpp]
// Author 大原怜将
//
//===========================================================
#include "rankinglogo.h"
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
CRankinglogo::CRankinglogo()
{
	m_nIdxTexture = 0;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CRankinglogo::CRankinglogo(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CRankinglogo::~CRankinglogo()
{

}

//===========================================================
//クリエイト
//===========================================================
CRankinglogo *CRankinglogo::Create(D3DXVECTOR3 pos)
{
	CRankinglogo *pTitlelogo = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CRankinglogo(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CRankinglogo::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\ranking.png"));

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CRankinglogo::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CRankinglogo::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 200.0f, 50.0f);
}

//===========================================================
//描画処理
//===========================================================
void CRankinglogo::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}