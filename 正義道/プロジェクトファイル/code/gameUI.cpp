//===============================================================
//
//チュートリアルUI処理[tutorialUI.cpp]
// Author 大原怜将
//
//===============================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "gameUI.h"
#include "fade.h"

//===============================================================
//静的メンバ変数
//===============================================================
CGameUI *CGameUI::m_pGameUI = NULL;

//===============================================================
//コンストラクタ
//===============================================================
CGameUI::CGameUI()
{
	m_nCntMove = 0;
}

//===============================================================
//デストラクタ
//===============================================================
CGameUI::~CGameUI()
{
}

//===============================================================
//デストラクタ
//===============================================================
CGameUI * CGameUI::Create(D3DXVECTOR3 pos, TYPE type)
{
	CGameUI *pGameUI = NULL;

	if (pGameUI == NULL)
	{
		pGameUI = new CGameUI;

		pGameUI->SetPos(&pos);

		pGameUI->m_type = type;

		pGameUI->Init();

		m_pGameUI = pGameUI;
	}

	return pGameUI;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CGameUI::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_state = STATE_MOVE;

	switch (m_type)
	{
	case CGameUI::TYPE_NONE:

		break;

	case CGameUI::TYPE_AIM00:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\0001.png"));
		break;

	case CGameUI::TYPE_AIM01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_001.png"));
		break;

	case CGameUI::TYPE_AIM02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_100.png"));
		break;

	case CGameUI::TYPE_AIM03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorialaim_005.png"));
		break;

	case CGameUI::TYPE_LESSON01:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_001.png"));
		break;

	case CGameUI::TYPE_LESSON02:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_002.png"));
		break;

	case CGameUI::TYPE_LESSON03:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CGameUI::TYPE_LESSON04:

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\tutorial_003.png"));
		break;

	case CGameUI::TYPE_MAX:

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
void CGameUI::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	if (m_pGameUI != NULL)
	{
		m_pGameUI = NULL;
	}
}

//===============================================================
//更新処理
//===============================================================
void CGameUI::Update(void)
{
	//フェードの情報を取得
	CFade *pFade = CManager::GetFade();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	SetVtxUI(pos, 400.0f, 200.0f, { 1.0f,1.0f,1.0f,1.0f });

	if (pFade->Get() != pFade->FADE_OUT)
	{
		if (m_state != STATE_NONE)
		{
			if (m_state == STATE_MOVE)
			{
				pos.x -= 20.0f;
			}

			if (pos.x <= 700.0f && m_state != STATE_STOP)
			{
				m_state = STATE_STOP;
			}

			if (m_state == STATE_STOP)
			{
				m_nCntMove++;

				pos.x -= 0.5f;
			}

			if (m_nCntMove >= 120)
			{
				m_state = STATE_MOVE;
			}

			if (pos.x <= -SCREEN_WIDTH)
			{
				Uninit();
			}
		}
	}

	SetPos(&pos);
}

//===============================================================
//描画処理
//===============================================================
void CGameUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}