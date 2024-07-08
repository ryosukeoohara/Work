//===========================================================
//
//ポリゴンを出すやつ[item.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "item.h"
#include "score.h"
#include "particl.h"
#include "debugproc.h"
#include "texture.h"
#include "collision.h"
#include "game.h"

//================================================================
//静的メンバ変数宣言
//================================================================
CItem *CItem::m_Item = NULL;

//================================================================
//コンストラクタ
//================================================================
CItem::CItem()
{
	m_nLife = 0;
	m_Indx = 0;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_ItemType = TYPE_NONE;
	m_state = STATE_NONE;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
{
	SetPos(&pos);
	//SetType(type);
	m_pos = pos;
	m_ItemType = m_Type;
	m_aFilename = aModelFliename;
	m_nLife = 0;
	m_Indx = 0;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
	m_state = STATE_NONE;
}

//================================================================
//デストラクタ
//================================================================
CItem::~CItem()
{

}

//================================================================
//生成処理
//================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, TYPE m_Typeconst, const char *aModelFliename)
{
	//オブジェクト2Dのポインタ
	CItem *pItem = NULL;

	//CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//オブジェクト2Dの生成
			pItem = new CItem(pos, m_Typeconst, aModelFliename);

			//初期化処理
			pItem->Init();

			m_Item = pItem;
		}
	}

	return pItem;
}

//================================================================
//アイテムの初期化処理
//================================================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);

	m_apModel[m_Indx] = CObjectX::Create(m_pos, {0.0f, 0.0f, 0.0f}, m_aFilename);

	//CObjectX::Init();

	m_Indx++;

	m_move.y = 0.04f;

	return S_OK;
}

//================================================================
//アイテムの終了処理
//================================================================
void CItem::Uninit(void)
{
	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//終了処理
			m_apModel[nCount]->Uninit();

			//m_apModel[nCount]->Release();

			m_apModel[nCount] = NULL;

			
		}
	}

	Release();
}

//================================================================
//アイテムの更新処理
//================================================================
void CItem::Update(void)
{
	//当たり判定の情報取得
	CCollision *pCollision = CManager::GetCollsion();

	CPlayer *pPlayer = CGame::GetPlayer();

	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//更新処理
			m_apModel[nCount]->Update();
		}
	}

	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			D3DXVECTOR3 pos = m_apModel[nCount]->Getpos();

			if (pos.y >= 5.0f)
			{
				m_move *= -1.0f;
			}
			else if (pos.y <= 0.0f)
			{
				m_move *= -1.0f;
			}

			pos.y += m_move.y;

			if (pCollision->CollisionItem(&pos, 30.0f, 30.0f, m_ItemType, pPlayer) == true)
			{
				Uninit();

				return;
			}

			SetPos(&pos);
		}
	}

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\nモデルの位置：X軸<%f>,Y軸<%f>,Z軸<%f>\n", m_pos.x, m_pos.y, m_pos.z);
}

//================================================================
//アイテムの描画処理
//================================================================
void CItem::Draw(void)
{
	//for (int nCount = 0; nCount < m_Indx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//描画処理
	//		m_apModel[nCount]->Draw();
	//	}
	//}
}

//================================================================
//プレイヤーとの当たり判定
//================================================================
bool CItem::CollisionItem(D3DXVECTOR3 pos)
{
	//for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	//{
	//	CObject *pObj;

	//	//オブジェクトを取得
	//	pObj = Getobject(nCount);

	//	if (pObj != NULL)  //わすれてた
	//	{
	//		//種類を取得
	//		TYPE type = pObj->GetType();

	//		if (type == TYPE_PLAYER)
	//		{//種類がプレイヤーの場合

	//			CPlayer *pPlayer = CManager::GetPlayer();

	//			D3DXVECTOR3 posPlayer = pPlayer->Getpos();

	//			if (pos.x >= posPlayer.x - 50.0f
	//			 && pos.x <= posPlayer.x + 50.0f
	//			 && pos.z >= posPlayer.y - 50.0f
	//			 && pos.z <= posPlayer.y + 50.0f)
	//			{
	//				return true;
	//			}

	//		}
	//	}
	//}

	return false;
}