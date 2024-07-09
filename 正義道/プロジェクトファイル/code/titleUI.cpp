//===============================================================
//
// タイトルUI処理[titleUI.cpp]
// Author 大原怜将
//
//===============================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "titleUI.h"
#include "fade.h"

//===============================================================
//コンストラクタ
//===============================================================
CTitleUI::CTitleUI()
{
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_colA = 0.0f;
}

//===============================================================
//デストラクタ
//===============================================================
CTitleUI::~CTitleUI()
{
}

//===============================================================
//デストラクタ
//===============================================================
CTitleUI * CTitleUI::Create(D3DXVECTOR3 pos)
{
	CTitleUI *pGameUI = NULL;

	if (pGameUI == NULL)
	{
		pGameUI = new CTitleUI;

		pGameUI->SetPos(&pos);
		pGameUI->Init();
	}

	return pGameUI;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CTitleUI::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//初期化処理
	CObject2D::Init();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\press.png"));

	m_colA = 0.007f;

	return S_OK;
}

//===============================================================
//終了処理
//===============================================================
void CTitleUI::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();
}

//===============================================================
//更新処理
//===============================================================
void CTitleUI::Update(void)
{
	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	if (m_col.a >= 1.0f)
	{
		m_colA *= -1.0f;
	}
	
	if (m_col.a <= 0.0f)
	{
		m_colA *= -1.0f;
	}

	m_col.a += m_colA;

	SetVtxUI(pos, 200.0f, 50.0f, m_col);
}

//===============================================================
//描画処理
//===============================================================
void CTitleUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}