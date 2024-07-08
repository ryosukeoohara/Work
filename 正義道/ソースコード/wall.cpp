//===========================================================
//
//ポリゴンを出すやつ[field.cpp]
//Author 大原怜将
//
//===========================================================
#include "wall.h"
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//===========================================================
//コンストラクタ
//===========================================================
CWall::CWall()
{
	m_nIdxTexture = 0;
}

//===========================================================
//デストラクタ
//===========================================================
CWall::~CWall()
{

}

//===========================================================
//クリエイト
//===========================================================
CWall *CWall::Create(void)
{
	//地面のポインタ
	CWall *pWall = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pWall == NULL)
		{//使用されていなかったら

			//オブジェクトを生成
			pWall = new CWall;

			pWall->Init();
		}
	}

	return pWall;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CWall::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tora.png");

	/*for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{
		if (m_Object3D[nCount] != NULL)
		{
			m_Object3D[nCount]->Create()
		}
	}*/

	//初期化処理
	CObject3D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CWall::Uninit(void)
{
	//終了処理
	CObject3D::Uninit();
}

//===========================================================
//更新処理
//===========================================================
void CWall::Update(void)
{
	//更新処理
	CObject3D::Update();
	CObject3D::SetVtxField();
}

//===========================================================
//描画処理
//===========================================================
void CWall::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CObject3D::Draw();
}