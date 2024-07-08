//===========================================================
//
//ポリゴンを出すやつ[bg.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "dispdetection.h"
#include "texture.h"
#include "input.h"
#include "game.h"

//マクロ定義
#define HEIGHT   (100.0f)  //高さ
#define WIDHT    (100.0f)  //横
#define MOVE     (100.0f) //移動

//================================================================
//静的メンバ変数宣言
//================================================================
CDISPDETECTION *CDISPDETECTION::m_DispDetection = NULL;

//================================================================
//コンストラクタ
//================================================================
CDISPDETECTION::CDISPDETECTION()
{
	m_nIdxTexture = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
//コンストラクタ
//================================================================
CDISPDETECTION::CDISPDETECTION(D3DXVECTOR3 pos)
{
	m_nIdxTexture = 0;
	SetPos(&pos);
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
}

//================================================================
//デストラクタ
//================================================================
CDISPDETECTION::~CDISPDETECTION()
{

}

//================================================================
//生成処理
//================================================================
CDISPDETECTION *CDISPDETECTION::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CDISPDETECTION *pFrame = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pFrame == NULL)
		{
			//オブジェクト2Dの生成
			pFrame = new CDISPDETECTION(pos);

			pFrame->m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\redcircle.png");

			//初期化処理
			pFrame->Init();

			m_DispDetection = pFrame;
		}
	}

	return pFrame;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CDISPDETECTION::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	CObject3D::Init();

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CDISPDETECTION::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CDISPDETECTION::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	m_col.a = 0.5f;

	CObject3D::SetVtxCircle(WIDHT, HEIGHT, m_col);

	CObject3D::Update();
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CDISPDETECTION::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();
}