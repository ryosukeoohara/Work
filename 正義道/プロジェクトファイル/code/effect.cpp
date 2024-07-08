//===========================================================
//
//ポリゴンを出すやつ[effect.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "bg.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect.h"
#include "debugproc.h"
#include "texture.h"

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
//struct CEffect::Effect CEffect::m_effect;
//float CEffect::m_fRadius = 0.0f;
//D3DXCOLOR CEffect::m_col = { 0.0f,0.0f,0.0f,0.0f };

//================================================================
//コンストラクタ
//================================================================
CEffect::CEffect()
{
	m_fRadius = 0;
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_type = TYPEEFF_NONE;
}

//================================================================
//コンストラクタ
//================================================================
CEffect::CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPEEFF type)
{
	SetPos(&pos);
	m_col = col;
	m_fRadius = fRadius;
	m_nLife = nLife;
	m_move = move;
	m_type = type;
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CEffect::~CEffect()
{

}

//================================================================
//生成処理
//================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPEEFF type)
{
	//オブジェクト2Dのポインタ
	CEffect *pEffect = NULL;

	if (GetNumAll() < MAX_OBJECT)
	{
		if (pEffect == NULL)
		{
			//オブジェクト2Dの生成
			pEffect = new CEffect(pos, move, col, fRadius, nLife, type);

			//テクスチャをバインド
			//pEffect->BindTexture(m_pTexture);

			//初期化処理
			pEffect->Init();
		}
	}
	
	return pEffect;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CEffect::Init(void)
{
	//種類の設定
	SetType(TYPE_EFFECT);

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	//初期化処理
	CBillBoard::Init();
	//m_fRadius = 15.0f;
	//m_nLife = 15;
	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CEffect::Uninit(void)
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
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = Getpos();  //位置取得

	m_nLife--;
	
	//m_fRadius -= 0.1f;
	
	//更新処理
	CBillBoard::Update();

	pos.x += m_move.x;
	pos.y += m_move.y;
	pos.z += m_move.z;

	switch (m_type)
	{
	case CEffect::TYPEEFF_NONE:
		
		break;

	case CEffect::TYPEEFF_GROUND:

		Ground();
		break;

	case CEffect::TYPEEFF_BLOOD:

		Blood();
		break;

	case CEffect::TYPEEFF_SMOOK:

		Smook();
		break;

	case CEffect::TYPEEFF_MAX:
		break;

	default:
		break;
	}

	SetVtxEffect(pos, m_fRadius, m_col);

	if (m_nLife <= 0)
	{//寿命が尽きたら

		//終了処理
		CEffect::Uninit();
	}
	else
	{
		//位置を設定
		SetPos(&pos);
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CEffect::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//αブレンディングを加算合計に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CBillBoard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================
//テクスチャの生成(読み込み)
//================================================================
void CEffect::Ground(void)
{
	D3DXVECTOR3 pos = Getpos();  //位置取得

	if (pos.y >= 30.0f)
	{
		m_move.y *= -1;
	}
}

//================================================================
//テクスチャの生成(読み込み)
//================================================================
void CEffect::Blood(void)
{
	D3DXVECTOR3 pos = Getpos();  //位置取得

	if (pos.y >= 60.0f)
	{
		m_move.y *= -1;
	}
}

//================================================================
//テクスチャの生成(読み込み)
//================================================================
void CEffect::Smook(void)
{
	m_fRadius += 1.0f;
}

//================================================================
//テクスチャの生成(読み込み)
//================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//================================================================
//テクスチャの破棄
//================================================================
void CEffect::UnLoad(void)
{
	//テクスチャの処理
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}