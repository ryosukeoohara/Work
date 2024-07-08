//===========================================================
//
//ポリゴンを出すやつ[bg.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "frame.h"
#include "texture.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "tutorial.h"

//マクロ定義
#define HEIGHT   (50.0f)  //高さ
#define WIDHT    (50.0f)  //横
#define MOVE     (100.0f) //移動

//================================================================
//静的メンバ変数宣言
//================================================================
CFrame *CFrame::m_Frame = NULL;

//================================================================
//コンストラクタ
//================================================================
CFrame::CFrame()
{
	m_nIdxTexture = 0;
}

//================================================================
//コンストラクタ
//================================================================
CFrame::CFrame(D3DXVECTOR3 pos)
{
	m_nIdxTexture = 0;
	SetPos(&pos);
}

//================================================================
//デストラクタ
//================================================================
CFrame::~CFrame()
{

}

//================================================================
//生成処理
//================================================================
CFrame *CFrame::Create(void)
{
	//オブジェクト2Dのポインタ
	CFrame *pFrame = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pFrame == NULL)
		{
			//オブジェクト2Dの生成
			pFrame = new CFrame({ 350.0f, 650.0f, 0.0f });

			//初期化処理
			pFrame->Init();

			m_Frame = pFrame;
		}
	}

	return pFrame;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CFrame::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	SetIdxTex(pTexture->Regist("data\\TEXTURE\\waku.png"));

	CObject2D::Init();

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CFrame::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CFrame::Update(void)
{
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//シーンの情報を取得
	CScene *pScene = CManager::GetScene();

	//プレイヤーの情報を取得
	CPlayer *pPlayer = CTutorial::GetPlayer();

	float MouseWheel = pInputMouse->GetMouseWheel();

	D3DXVECTOR3 pos = Getpos();

	CObject2D::Update();

	CObject2D::SetVtxFrame(pos, WIDHT, HEIGHT);

	if (pScene->GetMode() == CScene::MODE_GAME)
	{
		if (MouseWheel > 0)
		{
			pos.x -= MOVE;
		}

		if (MouseWheel < 0)
		{
			pos.x += MOVE;
		}

		if (pos.x <= 349.0f)
		{
			pos.x = 450.0f;
		}
		else if (pos.x >= 451.0f)
		{
			pos.x = 350.0f;
		}
	}

	if (pScene->GetMode() == CScene::MODE_TUTORIAL && pPlayer->GetbAttack() == true)
	{
		if (MouseWheel > 0)
		{
			pos.x -= MOVE;
		}

		if (MouseWheel < 0)
		{
			pos.x += MOVE;
		}

		if (pos.x <= 349.0f)
		{
			pos.x = 450.0f;
		}
		else if (pos.x >= 451.0f)
		{
			pos.x = 350.0f;
		}
	}

	SetPos(&pos);
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CFrame::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject2D::Draw();
}