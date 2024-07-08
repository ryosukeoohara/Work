//===========================================================
//
//ポリゴンを出すやつ[itemslot.cpp]
//Author 大原怜将
//
//===========================================================
#include "bulletUI.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "frame.h"
#include "game.h"
#include "target.h"
#include "player.h"

//===========================================================
//静的メンバ変数
//===========================================================
CNumber *CBulletUI::m_apNumber[MAX_NUMBER] = {};

//===========================================================
//コンストラクタ
//===========================================================
CBulletUI::CBulletUI()
{
	m_nIdxTexture = 0;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CBulletUI::CBulletUI(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CBulletUI::~CBulletUI()
{

}

//===========================================================
//クリエイト
//===========================================================
CBulletUI *CBulletUI::Create(D3DXVECTOR3 pos)
{
	CBulletUI *pTitlelogo = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pTitlelogo == NULL)
	{
		pTitlelogo = new CBulletUI(pos);

		pTitlelogo->Init();
	}

	return pTitlelogo;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CBulletUI::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\bullet.png"));

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 1090.0f + 50.0f * nCount, 400.0f, 0.0f });

			m_apNumber[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			//初期化処理
			m_apNumber[nCount]->Init();

			m_apNumber[nCount]->m_Number = 0;
		}
	}

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CBulletUI::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//終了処理
			m_apNumber[nCount]->Uninit();

			m_apNumber[nCount] = NULL;
		}
	}
}

//===========================================================
//更新処理
//===========================================================
void CBulletUI::Update(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	int n = pPlayer->GetRestBullet();

	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxTitleLogo(pos, 100.0f, 25.0f);

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[0]->m_Number = 0;
			m_apNumber[1]->m_Number = n;

			//更新処理
			m_apNumber[nCount]->SetVtxCounter({ 200.0f + 30.0f * nCount, 400.0f, 0.0f }, 15.0f, 20.0f);
		}
	}
}

//===========================================================
//描画処理
//===========================================================
void CBulletUI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//描画処理
	CObject2D::Draw();
}