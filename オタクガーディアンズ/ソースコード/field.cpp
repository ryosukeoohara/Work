//===========================================================
//
//フィールド処理[field.cpp]
//Author 大原怜将
//
//===========================================================
#include "field.h"
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//===========================================================
//コンストラクタ
//===========================================================
CField::CField()
{
	m_nIdxTexture = 0;
}

//===========================================================
//デストラクタ
//===========================================================
CField::~CField()
{
	
}

//===========================================================
//クリエイト
//===========================================================
CField *CField::Create(void)
{
	//地面のポインタ
	CField *pField = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pField == NULL)
		{//使用されていなかったら

			//オブジェクトを生成
			pField = new CField;

			pField->Init();
		}
	}

	return pField;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CField::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\field001.jpg");

	//初期化処理
	CObject3D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CField::Uninit(void)
{
	//終了処理
	CObject3D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CField::Update(void)
{
	//更新処理
	CObject3D::Update();
	//CObject3D::SetVtxField();
}

//===========================================================
//描画処理
//===========================================================
void CField::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CObject3D::Draw();
}