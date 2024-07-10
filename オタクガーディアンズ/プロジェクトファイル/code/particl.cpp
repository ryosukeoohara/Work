//===========================================================
//
//パーティクル処理[particl.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect.h"
#include "particl.h"

#include <time.h>

//マクロ定義
#define TYPE_BLOOD    (20)   //血のパーティクル
#define TYPE_GROUND   (10)   //土埃のパーティクル
#define TYPE_CIRCLE   (314)   //円形のパーティクル
#define SPEED    (2.0f)  //移動量

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CParticl::m_pTexture = NULL;

//================================================================
//コンストラクタ
//================================================================
CParticl::CParticl()
{
	m_fRadius = 0;
	m_nLife = 0;
	m_type = TYPEPAR_NONE;
}

//================================================================
//コンストラクタ
//================================================================
CParticl::CParticl(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, TYPEPAR type)
{
	SetPos(&pos);
	SetRot(&rot);
	m_col = col;
	m_fRadius = fRadius;
	m_nLife = 0;
	m_type = type;
}

//================================================================
//デストラクタ
//================================================================
CParticl::~CParticl()
{

}

//================================================================
//生成処理
//================================================================
CParticl *CParticl::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, TYPEPAR type)
{
	//オブジェクト2Dのポインタ
	CParticl *pParticl = NULL;

	if (GetNumAll() < MAX_OBJECT)
	{
		if (pParticl == NULL)
		{
			//オブジェクト2Dの生成
			pParticl = new CParticl(pos, rot, col, fRadius, type);

			//テクスチャをバインド
			pParticl->BindTexture(m_pTexture);

			//初期化処理
			pParticl->Init();
		}
	}

	return pParticl;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CParticl::Init(void)
{
	//種類の設定
	SetType(TYPE_PARTICL);

	//初期化処理
	CBillBoard::Init();
	//m_fRadius = 15.0f;
	//m_nLife = 20;
	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CParticl::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//終了処理
	CBillBoard::Uninit();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CParticl::Update(void)
{
	//更新処理
	CBillBoard::Update();

	switch (m_type)
	{
	case TYPEPAR_NONE:
		break;

	case TYPEPAR_BULLET:
		ParticlMove();
		break;

	case TYPEPAR_BLOOD:
		Blood();
		break;

	case TYPEPAR_GROUND:
		Ground();
		break;

	case TYPEPAR_SMOOK:
		Smook();
		break;

	case TYPEPAR_CIRCLE:
		Circle();
		break;
	}

	m_nLife--;

	if (m_nLife <= 0)
	{
		//終了処理
		CParticl::Uninit();
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CParticl::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//αブレンディングを加算合計に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画処理
	CBillBoard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CParticl::ParticlMove(void)
{
	D3DXVECTOR3 pos;

	pos = Getpos();

	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;
		
		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 0.8f, 1.0f, 1.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_NONE);
	}

	SetPos(&pos);
}

//================================================================
//血液のパーティクル
//================================================================
void CParticl::Blood(void)
{
	D3DXVECTOR3 pos;

	pos = Getpos();

	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_BLOOD);
	}

	SetPos(&pos);
}

//================================================================
//土埃みたいなパーティクル
//================================================================
void CParticl::Ground(void)
{
	D3DXVECTOR3 pos;

	pos = Getpos();

	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fPosX, fPosZ, fMove, fRot, fRange;

		fPosX = (float)(rand() % 100);
		fPosZ = (float)(rand() % 100);
		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;
		fRange = (float)(rand() % 10) - D3DX_PI * 2;

		m_move.x = sinf(fRot * fRange) * fMove;
		m_move.y = cosf(fRot * fRange) * fMove;
		m_move.z = cosf(fRot * fRange) * fMove;

		if (m_move.y < 0.0f)
		{
			m_move.y *= -1;
		}

		CEffect::Create({pos.x, 0.0f, pos.z}, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_GROUND);
	}

	SetPos(&pos);
}

//================================================================
//煙みたいなパーティクル
//================================================================
void CParticl::Smook(void)
{
	D3DXVECTOR3 pos;

	pos = Getpos();

	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fPosX, fPosZ, fMove, fRot, fRange;

		fPosX = (float)(rand() % 100);
		fPosZ = (float)(rand() % 100);
		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;
		fRange = (float)(rand() % 10) - D3DX_PI * 2;

		//m_move.x = sinf(fRot * fRange) * fMove;
		m_move.y = cosf(fRot * fRange) * fMove * 2.0f;
		//m_move.z = cosf(fRot * fRange) * fMove;

		if (m_move.y < 0.0f)
		{
			m_move.y *= -1;
		}

		CEffect::Create({ pos.x, 0.0f, pos.z }, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, 10.0f, 30, CEffect::TYPEEFF_SMOOK);
	}

	SetPos(&pos);
}

//================================================================
//円形のパーティクル
//================================================================
void CParticl::Circle(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 pos;
	float fRot;

	//位置取得
	pos = Getpos();

	for (int nCnt = 0; nCnt < TYPE_CIRCLE; nCnt++)
	{
		//向き設定
		fRot = ((float)nCnt / (D3DX_PI * 1.0f));

		//移動量設定
		m_move.x = sinf(fRot) * SPEED;
		m_move.y = cosf(fRot) * SPEED;

		//エフェクトの生成
		CEffect::Create({ pos.x, pos.y + 50.0f, pos.z }, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, 3.0f, 30, CEffect::TYPEEFF_CIRCLE);
	}

	//位置設定
	SetPos(&pos);
}