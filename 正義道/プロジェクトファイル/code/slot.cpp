//===========================================================
//
// スロット処理[slot.cpp]
// Author 大原怜将
//
//===========================================================
#include "slot.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "frame.h"
#include "game.h"
#include "itemicon.h"

//===========================================================
//静的メンバ変数宣言
//===========================================================
LPDIRECT3DTEXTURE9 CSlot::m_pTexture = NULL;
CSlot::SLOT CSlot::m_aSlot[MAX_SLOT] = {};
CItemSlot *CSlot::m_apItemSlot[MAX_SLOT] = {};

//===========================================================
//コンストラクタ
//===========================================================
CSlot::CSlot()
{
	//m_bUse = false;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CSlot::CSlot(D3DXVECTOR3 pos)
{
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CSlot::~CSlot()
{

}

//===========================================================
//クリエイト
//===========================================================
CSlot *CSlot::Create(void)
{
	CSlot *pSlot = NULL;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	if (pSlot == NULL)
	{
		pSlot = new CSlot();

		pSlot->Init();
	}

	return pSlot;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CSlot::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		m_aSlot[nCount].m_bUse = false;
		m_aSlot[nCount].m_type = CFrame::TYPE_NONE;
	}

	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_apItemSlot[nCount] == NULL)
		{
			m_apItemSlot[nCount] = CItemSlot::Create({ 350.0f + 100.0f * nCount, 650.0f, 0.0f });

			switch (nCount)
			{
			case 0:
				m_apItemSlot[nCount]->SetAttackType(TYPE_PROXIMITY);
				m_aSlot[nCount].m_type = CFrame::TYPE_NEAR;
				m_aSlot[nCount].m_bUse = true;

				break;

			case 1:
				m_apItemSlot[nCount]->SetAttackType(TYPE_PROJECTILE);
				m_aSlot[nCount].m_type = CFrame::TYPE_FAR;
				m_aSlot[nCount].m_bUse = true;

				break;
			}
		}
	}

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CSlot::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_apItemSlot[nCount] != NULL)
		{
			m_apItemSlot[nCount]->Uninit();

			m_apItemSlot[nCount] = NULL;
		}
	}

	Release();
}

//===========================================================
//更新処理
//===========================================================
void CSlot::Update(void)
{
	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_apItemSlot[nCount] != NULL)
		{
			m_apItemSlot[nCount]->Update();
		}
	}

	Collision();
}

//===========================================================
//描画処理
//===========================================================
void CSlot::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_apItemSlot[nCount] != NULL)
		{
			m_apItemSlot[nCount]->Draw();
		}
	}
}

//===========================================================
//スロットとフレームの当たり判定
//===========================================================
void CSlot::Collision(void)
{
	CFrame *pFrame = CFrame::GetFrame();

	D3DXVECTOR3 pos = pFrame->Getpos();

	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_apItemSlot[nCount] != NULL)
		{
			if (pos.x <= m_apItemSlot[nCount]->Getpos().x + 50.0f
			 && pos.x >= m_apItemSlot[nCount]->Getpos().x - 50.0f
			 && pos.y <= m_apItemSlot[nCount]->Getpos().y + 50.0f
			 && pos.y >= m_apItemSlot[nCount]->Getpos().y - 50.0f)
			{
				if (m_aSlot[nCount].m_bUse == true)
				{
					pFrame->SetACType(m_aSlot[nCount].m_type);
				}
			}
		}
	}
}

//===========================================================
//スロットの設定
//===========================================================
void CSlot::Set(CItem::TYPE type)
{
	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_aSlot[nCount].m_bUse == true)
		{
			if (m_apItemSlot[nCount] != NULL)
			{
				if (type == m_aSlot[nCount].m_type)
				{
					return;
				}
			}
		}
	}
	for (int nCount = 0; nCount < MAX_SLOT; nCount++)
	{
		if (m_aSlot[nCount].m_bUse == false)
		{
			if (m_apItemSlot[nCount] != NULL)
			{
				D3DXVECTOR3 pos = m_apItemSlot[nCount]->Getpos();

				if (type == CItem::TYPE_NAILBAT)
				{
					CItemIcon::Create(pos, CItemIcon::TYPE_KUGIBAT);
					m_aSlot[nCount].m_type = CFrame::TYPE_BAT;
					m_aSlot[nCount].m_bUse = true;

					break;
				}

				if (type == CItem::TYPE_NAILBAT)
				{
					CItemIcon::Create(pos, CItemIcon::TYPE_KUGIBAT);
					m_aSlot[nCount].m_type = CFrame::TYPE_BOM;
					m_aSlot[nCount].m_bUse = true;

					break;
				}
			}
		}
	}
}