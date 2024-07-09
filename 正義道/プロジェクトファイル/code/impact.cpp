//===========================================================
//
// 衝撃波処理[impact.cpp]
// Author 大原怜将
//
//===========================================================
#include "impact.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//マクロ定義
#define HEIGHT   (20.0f)
#define WIDHT    (20.0f)

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CImpact::m_pTexture = NULL;

//===========================================================
//コンストラクタ
//===========================================================
CImpact::CImpact()
{
	m_SizeX = 0.0f;
	m_SizeZ = 0.0f;
	m_nIdxTexture = -1;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CImpact::CImpact(D3DXVECTOR3 pos, TYPE type)
{
	SetPos(&pos);
	m_SizeX = 0.0f;
	m_SizeZ = 0.0f;
	m_nIdxTexture = -1;
	m_type = type;
}

//===========================================================
//デストラクタ
//===========================================================
CImpact::~CImpact()
{

}

//===========================================================
//クリエイト
//===========================================================
CImpact *CImpact::Create(D3DXVECTOR3 pos, TYPE type)
{
	CImpact *pItemSlot = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pItemSlot == NULL)
	{
		pItemSlot = new CImpact(pos, type);

		switch (type)
		{
		case TYPE_NONE:

			pItemSlot->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\impact.png");
			break;
		
		default:
			break;
		}

		pItemSlot->Init();
	}

	return pItemSlot;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CImpact::Init(void)
{
	CObject3D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CImpact::Uninit(void)
{
	CObject3D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CImpact::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	CObject3D::Update();

	CObject3D::SetVtxCircle(WIDHT + m_SizeX, HEIGHT + m_SizeZ, { 1.0f,1.0f,1.0f,1.0f });

	if (m_SizeX < 100.0f && m_SizeZ < 100.0f)
	{
		m_SizeX += 5.0f;
		m_SizeZ += 5.0f;
	}
	else
	{
		Uninit();

		return;
	}
}

//===========================================================
//描画処理
//===========================================================
void CImpact::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}