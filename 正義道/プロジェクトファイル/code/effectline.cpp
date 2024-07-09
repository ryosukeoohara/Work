//===========================================================
//
// 注目線の処理[bg.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "effectline.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "texture.h"

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CEffectLine::m_pTexture = NULL;

//================================================================
//コンストラクタ
//================================================================
CEffectLine::CEffectLine()
{
	m_nCounter = 0;
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CEffectLine::~CEffectLine()
{

}

//================================================================
//生成処理
//================================================================
CEffectLine *CEffectLine::Create(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//オブジェクト2Dのポインタ
	CEffectLine *pEffectLine = NULL;

	if (pEffectLine == NULL)
	{
		//オブジェクト2Dの生成
		pEffectLine = new CEffectLine;

		//初期化処理
		pEffectLine->Init();
	}

	return pEffectLine;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CEffectLine::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\syutyu.png"));

	CObject2D::Init();

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CEffectLine::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CEffectLine::Update(void)
{
	CObject2D::Update();

	SetVtxEffectLine();

	m_nCounter++;

	if (m_nCounter >= 120)
	{
		Uninit();
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CEffectLine::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();
}