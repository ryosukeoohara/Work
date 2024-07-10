//===========================================================
//
//UIマネージャ[UImanager.h]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "UImanager.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"

//===========================================================
//コンストラクタ
//===========================================================
CUIManager::CUIManager()
{
	//初期化
	m_type = TYPE_NONE;
	m_nIdxTexture = -1;
}

//===========================================================
//コンストラクタ
//===========================================================
CUIManager::CUIManager(D3DXVECTOR3 pos, TYPE type)
{
	//初期化
	SetPos(&pos);
	m_type = type;
	m_nIdxTexture = -1;
}

//===========================================================
//デストラクタ
//===========================================================
CUIManager::~CUIManager()
{

}

//===========================================================
//生成処理
//===========================================================
CUIManager * CUIManager::Create(D3DXVECTOR3 pos, TYPE type)
{
	//UIマネージャへのポインタ
	CUIManager *pUI = NULL;

	if (pUI == NULL)
	{//使用されていなかったら

		//生成
		pUI = new CUIManager(pos, type);

		//初期化処理
		pUI->Init();
	}

	return pUI;
}


//===========================================================
//初期化処理
//===========================================================
HRESULT CUIManager::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//初期化処理
	CObject2D::Init();

	switch (m_type)
	{
	case CUIManager::TYPE_NONE:     //なんもない
		break;

	case CUIManager::TYPE_TITLE:    //タイトル

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\title.png");
		break;

	case CUIManager::TYPE_TUTORIAL: //チュートリアル

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\tutorial.jpg");
		break;

	case CUIManager::TYPE_RESULT:   //リザルト

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\res.jpg");
		break;

	case CUIManager::TYPE_GUNGAGE:

		m_nIdxTexture = -1;
		break;

	case CUIManager::TYPE_LIFEFOOT:

		m_nIdxTexture = -1;
		break;

	case CUIManager::TYPE_LIFECHIBI:

		m_nIdxTexture = -1;
		break;

	case CUIManager::TYPE_ICONFOOT:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\icon001.png");
		break;

	case CUIManager::TYPE_ICONCHIBI:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\icon000.png");
		break;

	case CUIManager::TYPE_MAGIC:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\magic.png");
		break;

	case CUIManager::TYPE_TITLESELECT:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\titlesele.png");
		break;

	case CUIManager::TYPE_RANK:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\rank.png");
		break;

	case CUIManager::TYPE_SCORE:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\score.png");
		break;

	case CUIManager::TYPE_PAUSEFRAME:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\fream.png");
		break;

	case CUIManager::TYPE_COUTINUE:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\pause000.png");
		break;

	case CUIManager::TYPE_RETRY:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\pause001.png");
		break;

	case CUIManager::TYPE_QUIT:

		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\pause002.png");
		break;

	case CUIManager::TYPE_MAX:
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CUIManager::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	//自身の破棄
	Release();
}

//===========================================================
//更新処理
//===========================================================
void CUIManager::Update(void)
{
	//チビの情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	//デブの情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//更新処理
	CObject2D::Update();

	//大きさとか設定
	switch (m_type)
	{
	case CUIManager::TYPE_NONE:     //なんもない
		break;

	case CUIManager::TYPE_TITLE:    //タイトル

		CObject2D::SetVtxUI(Getpos(), 500.0f, 150.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_TUTORIAL: //チュートリアル

		CObject2D::SetVtxUI(Getpos(),SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_RESULT:   //リザルト

		CObject2D::SetVtxUI(Getpos(), 400.0f, 200.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_GUNGAGE:  //残弾数

		if (pChibi != nullptr)
		{
			CObject2D::SetVtxUI(Getpos(), (float)pChibi->GetRestBullet() * 7.0f, 10.0f, { 0.0f,0.5f,0.5f,1.0f });
		}
		
		break;

	case CUIManager::TYPE_LIFEFOOT:

		if (pFoot != nullptr)
		{
			CObject2D::SetVtxUI(Getpos(), (float)pFoot->GetLife() * 10.0f, 20.0f, { 0.5f,0.9f,0.5f,1.0f });
		}

		break;

	case CUIManager::TYPE_LIFECHIBI:

		if (pChibi != nullptr)
		{
			CObject2D::SetVtxUI(Getpos(), (float)pChibi->GetLife() * 10.0f, 20.0f, { 0.5f,0.0f,0.5f,1.0f });
		}

		break;

	case CUIManager::TYPE_ICONFOOT:

		CObject2D::SetVtxUI(Getpos(), 100.0f, 50.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_ICONCHIBI:

		CObject2D::SetVtxUI(Getpos(), 100.0f, 50.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_MAGIC:

		CObject2D::SetVtxUI(Getpos(), 50.0f, 25.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_TITLESELECT:

		CObject2D::SetVtxUI(Getpos(), 500.0f, 50.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_RANK:

		CObject2D::SetVtxUI(Getpos(), 100.0f, 250.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_SCORE:

		CObject2D::SetVtxUI(Getpos(), 400.0f, 40.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_PAUSEFRAME:

		CObject2D::SetVtxUI(Getpos(), 300.0f, 200.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_COUTINUE:

		CObject2D::SetVtxUI(Getpos(), 400.0f, 40.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_RETRY:

		CObject2D::SetVtxUI(Getpos(), 400.0f, 40.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_QUIT:

		CObject2D::SetVtxUI(Getpos(), 400.0f, 40.0f, { 1.0f,1.0f,1.0f,1.0f });
		break;

	case CUIManager::TYPE_MAX:
		break;

	default:
		break;
	}
}

//===========================================================
//描画処理
//===========================================================
void CUIManager::Draw(void)
{
	//テクスチャの情報を取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//レンダラーの情報を取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	//デバイスの情報を取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャ設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CObject2D::Draw();
}