//===============================================================
//
//チュートリアルUI処理[tutorialUI.cpp]
// Author 大原怜将
//
//===============================================================
#include "tutorialUI.h"
#include "tutorial.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"

//===============================================================
//静的メンバ変数
//===============================================================
CTutorialUI *CTutorialUI::m_TutorialUI = NULL;

//===============================================================
//コンストラクタ
//===============================================================
CTutorialUI::CTutorialUI()
{
	m_nIdxTexture = -1;
}

//===============================================================
//デストラクタ
//===============================================================
CTutorialUI::~CTutorialUI()
{

}

//===============================================================
//クリエイト
//===============================================================
CTutorialUI *CTutorialUI::Create(D3DXVECTOR3 pos, TYPE type)
{
	if (m_TutorialUI == NULL)
	{
		m_TutorialUI = new CTutorialUI;

		m_TutorialUI->SetPos(&pos);

		m_TutorialUI->m_type = type;

		m_TutorialUI->Init();
	}

	return m_TutorialUI;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CTutorialUI::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	switch (m_type)
	{
	case CTutorialUI::TYPE_NONE:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutplogo.png"));
		break;

	case CTutorialUI::TYPE_AIM00:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_000.png"));
		break;

	case CTutorialUI::TYPE_AIM01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_001.png"));
		break;

	case CTutorialUI::TYPE_AIM02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_002.png"));
		break;

	case CTutorialUI::TYPE_AIM03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_0002.png"));
		break;

	case CTutorialUI::TYPE_AIM04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutoaim_0003.png"));
		break;

	case CTutorialUI::TYPE_AIM05:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_005.png"));
		break;

	case CTutorialUI::TYPE_LESSON01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_001.png"));
		break;

	case CTutorialUI::TYPE_LESSON02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CTutorialUI::TYPE_LESSON03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_005.png"));
		break;

	case CTutorialUI::TYPE_LESSON04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CTutorialUI::TYPE_LESSON05:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CTutorialUI::TYPE_MAX:

		break;

	default:
		break;
	}
	

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===============================================================
//終了処理
//===============================================================
void CTutorialUI::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	if (m_TutorialUI != NULL)
	{
		m_TutorialUI = NULL;
	}
}

//===============================================================
//更新処理
//===============================================================
void CTutorialUI::Update(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//更新処理
	CObject2D::Update();

	if (m_TutorialUI != NULL)
	{
		D3DXVECTOR3 pos = m_TutorialUI->Getpos();

		if (m_type == TYPE_LESSON01 || m_type == TYPE_LESSON02 || m_type == TYPE_LESSON03 || m_type == TYPE_LESSON04 || m_type == TYPE_LESSON05)
		{
			m_TutorialUI->SetVtxUI(pos, 400.0f, 75.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
		else if (m_type == TYPE_NONE)
		{
			m_TutorialUI->SetVtxUI(pos, 100.0f, 50.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
		else
		{
			m_TutorialUI->SetVtxUI(pos, 640.0f, 360.0f, { 1.0f,1.0f,1.0f,1.0f });
		}
	}
}

//===============================================================
//描画処理
//===============================================================
void CTutorialUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CObject2D::Draw();
}