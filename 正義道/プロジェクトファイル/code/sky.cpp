//=============================================================================
//
// スカイボックス処理 [sky.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "sky.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "enemyweak.h"

//================================================================
//コンストラクタ
//================================================================
CSky::CSky()
{
	m_nIdxTexture = -1;
}

//================================================================
//コンストラクタ
//================================================================
CSky::CSky(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CSky::~CSky()
{

}

//================================================================
//デストラクタ
//================================================================
CSky *CSky::Create(D3DXVECTOR3 pos)
{
	CSky *pSky = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pSky == NULL)
		{
			//空の生成
			pSky = new CSky(pos);

			//初期化処理
			pSky->Init();
		}
	}

	return pSky;
}

//================================================================
//空の初期化処理
//================================================================
HRESULT CSky::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	D3DXVECTOR3 pos = Getpos();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\sky101.jpg");

	//生成
	CObjectX::Create(pos, { 0.0f,0.0f,0.0f }, "data\\MODEL\\sky.x");

	//初期化処理
	//CObjectX::Init();

	return S_OK;
}

//================================================================
//空の終了処理
//================================================================
void CSky::Uninit(void)
{
	//終了処理
	CObjectX::Uninit();
}

//================================================================
//空の更新処理
//================================================================
void CSky::Update(void)
{
	//更新処理
	CObjectX::Update();
}

//================================================================
//空の描画処理
//================================================================
void CSky::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	//CObjectX::Draw();
}