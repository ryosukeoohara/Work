//=============================================================================
//
// シャドウ処理 [shadow.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "life.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "enemyweak.h"
#include "enemy.h"

//静的メンバ変数
CBillBoard *CLife::m_Life[MAX_SHADOW] = {};

//================================================================
//コンストラクタ
//================================================================
CLife::CLife()
{
	m_nIdxTexture = -1;
}

//================================================================
//コンストラクタ
//================================================================
CLife::CLife(D3DXVECTOR3 pos)
{
	SetPos(&pos);
	m_nIdxTexture = -1;
}

//================================================================
//デストラクタ
//================================================================
CLife::~CLife()
{

}

//================================================================
//デストラクタ
//================================================================
CLife *CLife::Create(D3DXVECTOR3 pos)
{
	CLife *pLife = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pLife == NULL)
		{
			//オブジェクト2Dの生成
			pLife = new CLife(pos);

			//初期化処理
			pLife->Init();
		}
	}

	return pLife;
}

//================================================================
//ライフの初期化処理
//================================================================
HRESULT CLife::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = -1;

	CBillBoard::Init();

	return S_OK;
}

//================================================================
//ライフの終了処理
//================================================================
void CLife::Uninit(void)
{
	CBillBoard::Uninit();
}

//================================================================
//ライフの更新処理
//================================================================
void CLife::Update(void)
{
	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	D3DXVECTOR3 pos = Getpos();

	int nNumEnemy = CEnemyManager::GetNumAll();

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		if (pEnemy[nCount] != NULL)
		{
			float life = (float)pEnemy[nCount]->GetLife();

			CBillBoard::SetVtxLife(pos, 20.0f, 5.0f, life);
		}
	}

	

	CBillBoard::Update();

	
}

//================================================================
//ライフの描画処理
//================================================================
void CLife::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CBillBoard::Draw();
}

//================================================================
//ライフの設定処理
//================================================================
int CLife::Set(D3DXVECTOR3 pos)
{
	int nCntShadow = -1;

	for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
	{
		if (m_Life[nCount] == NULL)
		{
			m_Life[nCount] = Create(pos);

			nCntShadow = nCount;

			break;
		}
	}

	return nCntShadow;
}

//================================================================
//位置更新
//================================================================
void CLife::SetPosition(int nIdxShadow, D3DXVECTOR3 pos)
{
	CLife::SetPos(&pos);
}