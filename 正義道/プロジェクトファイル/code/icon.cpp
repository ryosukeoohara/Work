//===========================================================
//
//ポリゴンを出すやつ[itemslot.cpp]
//Author 大原怜将
//
//===========================================================
#include "icon.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CIcon::m_pTexture = NULL;

//===========================================================
//コンストラクタ
//===========================================================
CIcon::CIcon()
{

}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CIcon::CIcon(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_type = type;
}

//===========================================================
//デストラクタ
//===========================================================
CIcon::~CIcon()
{

}

//===========================================================
//クリエイト
//===========================================================
CIcon *CIcon::Create(D3DXVECTOR3 pos, TYPE type)
{
	CIcon *pItemSlot = NULL;

	if (pItemSlot == NULL)
	{
		pItemSlot = new CIcon(pos, type);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CIcon::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	CObject2D::Init();

	switch (m_type)
	{
	case TYPE_NONE:

		break;

	case TYPE_PLAYER:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\face.png"));
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CIcon::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CIcon::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxIcon(pos, 50.0f, 50.0f);
}

//===========================================================
//描画処理
//===========================================================
void CIcon::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject2D::Draw();
}