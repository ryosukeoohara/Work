//===========================================================
//
//ポリゴンを出すやつ[itemslot.cpp]
//Author 大原怜将
//
//===========================================================
#include "itemslot.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CItemSlot::m_pTexture = NULL;

//===========================================================
//コンストラクタ
//===========================================================
CItemSlot::CItemSlot()
{

}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CItemSlot::CItemSlot(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CItemSlot::~CItemSlot()
{

}

//===========================================================
//クリエイト
//===========================================================
CItemSlot *CItemSlot::Create(D3DXVECTOR3 pos)
{
	CItemSlot *pItemSlot = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CItemSlot(pos);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CItemSlot::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	CObject2D::Init();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\Itemslot001.png"));

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CItemSlot::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CItemSlot::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxItemSlot(pos, 50.0f, 50.0f);
}

//===========================================================
//描画処理
//===========================================================
void CItemSlot::Draw(void)
{
	CObject2D::Draw();
}