//===========================================================
//
// 斬撃エフェクト処理[effectsord.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "effectsord.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "texture.h"
#include "enemyBoss.h"
#include "debugproc.h"
#include "enemymanager.h"

//================================================================
//コンストラクタ
//================================================================
CEffectSword::CEffectSword()
{
	m_DispCounter = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nIdxTexture = -1;
}

//================================================================
//コンストラクタ
//================================================================
CEffectSword::CEffectSword(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);
	SetRot(&rot);
	m_DispCounter = 0;
	m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CEffectSword::~CEffectSword()
{

}

//================================================================
//生成処理
//================================================================
CEffectSword *CEffectSword::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//オブジェクト2Dのポインタ
	CEffectSword *pEffectSword = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEffectSword == NULL)
		{
			//オブジェクト2Dの生成
			pEffectSword = new CEffectSword(pos, rot);

			//初期化処理
			pEffectSword->Init();
		}
	}

	return pEffectSword;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CEffectSword::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\zangeki.png");

	CObject3D::Init();

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CEffectSword::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CEffectSword::Update(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_col.a < 1.0f)
	{
		m_col.a += 0.1f;
	}
	else
	{
		int n = 0;
	}
	
	SetVtxEffectSword(150.0f, 150.0f, m_col);

	CObject3D::Update();

	m_DispCounter++;

	if (m_DispCounter >= 20)
	{
		Uninit();
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CEffectSword::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////αブレンディングを加算合計に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CObject3D::Draw();

	////αブレンディングを元に戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}