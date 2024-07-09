//===========================================================
//
// アイテムアイコン処理[itemicon.cpp]
// Author 大原怜将
//
//===========================================================
#include "itemicon.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CItemIcon::m_pTexture = NULL;

//===========================================================
//コンストラクタ
//===========================================================
CItemIcon::CItemIcon()
{

}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CItemIcon::CItemIcon(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_type = type;
}

//===========================================================
//デストラクタ
//===========================================================
CItemIcon::~CItemIcon()
{

}

//===========================================================
//クリエイト
//===========================================================
CItemIcon *CItemIcon::Create(D3DXVECTOR3 pos, TYPE type)
{
	CItemIcon *pItemSlot = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CItemIcon(pos, type);

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CItemIcon::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	switch (m_type)
	{
	case CItemIcon::TYPE_PROXIMITY:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\punch.png"));
		break;

	case CItemIcon::TYPE_PROJECTILE:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\gun.png"));
		break;

	case CItemIcon::TYPE_KUGIBAT:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\kugibat.png"));
		break;

	case CItemIcon::TYPE_BOM:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\bom.png"));
		break;

	default:
		break;
	}

	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CItemIcon::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CItemIcon::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxItemSlot(pos, 40.0f, 40.0f);
}

//===========================================================
//描画処理
//===========================================================
void CItemIcon::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();
}