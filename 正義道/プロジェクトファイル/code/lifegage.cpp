//===========================================================
//
//ポリゴンを出すやつ[itemslot.cpp]
//Author 大原怜将
//
//===========================================================
#include "lifegage.h"
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
CLifegage::CLifegage()
{
	m_nIdxTexture = 0;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CLifegage::CLifegage(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CLifegage::~CLifegage()
{

}

//===========================================================
//クリエイト
//===========================================================
CLifegage *CLifegage::Create(D3DXVECTOR3 pos)
{
	CLifegage *pTitlelogo = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CLifegage(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CLifegage::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\Lifegage.png"));

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CLifegage::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CLifegage::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxLifeGage(pos, 200.0f, 50.0f);
}

//===========================================================
//描画処理
//===========================================================
void CLifegage::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}