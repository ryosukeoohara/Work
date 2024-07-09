//===========================================================
//
// オブジェクト処理[object.cpp]
// Author 大原怜将
//
//===========================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"

CObject *CObject::m_apObjct[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//================================================================
//コンストラクタ
//================================================================
CObject::CObject()
{
	if (m_nNumAll < MAX_OBJECT)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObjct[nCntObject] == NULL)
			{//使用されていなかったら

				m_apObjct[nCntObject] = this;  //自分自身を代入
				m_nID = nCntObject;  //自分自身のID
				m_nNumAll++;         //総数をカウントアップ
				break;
			}
		}
	}
}

//================================================================
//デストラクタ
//================================================================
CObject::~CObject()
{
	
}

//================================================================
//すべてのオブジェクトの破棄
//================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObjct[nCntObject] != NULL)
		{
			//終了処理
			m_apObjct[nCntObject]->Uninit();
		}
	}
}

//================================================================
//すべてのオブジェクトの更新
//================================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObjct[nCntObject] != NULL)
		{
			//更新処理
			m_apObjct[nCntObject]->Update();
		}
	}

	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\n\nオブジェクトの総数：%d", m_nNumAll);
}

//================================================================
//すべてのオブジェクトの描画
//================================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != NULL)
	{
		//カメラの設定
		pCamera->SetCamera();
	}
	
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObjct[nCntObject] != NULL)
		{
			//描画処理
			m_apObjct[nCntObject]->Draw();
		}
	}
}

//================================================================
//オブジェクトの破棄
//================================================================
void CObject::Release(void)
{
	int nIdx = m_nID;

	//オブジェクトの破棄
	if (m_apObjct[nIdx] != NULL)
	{
		//メモリを開放
		delete m_apObjct[nIdx];

		//使用していない状態にする
		m_apObjct[nIdx] = NULL;

		m_nNumAll--;    //総数をカウントダウン
	}
}

//================================================================
//オブジェクトの取得
//================================================================
CObject *CObject::Getobject(int nIdx)
{
	return m_apObjct[nIdx];
}

//================================================================
//テクスチャ取得
//================================================================
//void CObject::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
//{
//	m_pTexture = m_Texture;
//}

CObject *CObject::m_pTop = NULL;
CObject *CObject::m_pCur = NULL;

////================================================================
////コンストラクタ
////================================================================
//CObject::CObject()
//{
//	m_bDeath = false;
//
//	CObject *pObject = m_pTop;
//
//	if (m_pTop == NULL)
//	{
//		m_pTop = this;
//
//		m_pCur = this;
//	}
//	else if (m_pTop != NULL)
//	{
//		m_pPrev = m_pCur;
//		m_pPrev->m_pNext = this;
//		m_pCur = this;
//	}
//}
//
////================================================================
////デストラクタ
////================================================================
//CObject::~CObject()
//{
//
//}
//
////================================================================
////すべてのオブジェクトの破棄
////================================================================
//void CObject::ReleaseAll(void)
//{
//	CObject *pobject = m_pTop;
//
//	while (pobject != NULL)
//	{
//		CObject *pObjectNext = pobject->m_pNext;
//
//		if (pobject->m_bDeath == true)
//		{
//			pobject->m_pPrev->m_pNext = pobject->m_pNext;
//
//			if (pobject->m_pNext != NULL)
//			{
//				pobject->m_pNext->m_pPrev = pobject->m_pPrev;
//			}
//			else
//			{
//				m_pCur = pobject->m_pPrev;
//			}
//
//			delete pobject;
//			pobject = NULL;
//		}
//
//		pobject = pObjectNext;
//	}
//}
//
////================================================================
////すべてのオブジェクトの更新
////================================================================
//void CObject::UpdateAll(void)
//{
//	CObject *pObject = m_pTop;
//
//	while (pObject != NULL)
//	{
//		CObject *pObjectNext = pObject->m_pNext;
//
//		pObject->Update();
//		pObject = pObjectNext;
//	}
//
//	CObject *pobject = m_pTop;
//
//	while (pobject != NULL)
//	{
//		CObject *pObjectNext = pobject->m_pNext;
//
//		if (pobject->m_bDeath == true)
//		{
//			pobject->m_pPrev->m_pNext = pobject->m_pNext;
//
//			if (pobject->m_pNext != NULL)
//			{
//				pobject->m_pNext->m_pPrev = pobject->m_pPrev;
//			}
//			else
//			{
//				m_pCur = pobject->m_pPrev;
//			}
//
//			delete pobject;
//			pobject = NULL;
//		}
//
//		pobject = pObjectNext;
//	}
//
//	CDebugProc *pDebugProc = CManager::GetDebugProc();
//
//	pDebugProc->Print("\n\nオブジェクトの総数：%d", m_nNumAll);
//}
//
////================================================================
////すべてのオブジェクトの描画
////================================================================
//void CObject::DrawAll(void)
//{
//	CCamera *pCamera = CManager::GetCamera();
//
//	//カメラの設定
//	pCamera->SetCamera();
//
//	CObject *pObject = m_pTop;
//
//	while (pObject != NULL)
//	{
//		CObject *pObjectNext = pObject->m_pNext;
//
//		pObject->Draw();
//		pObject = pObjectNext;
//	}
//}
//
////================================================================
////オブジェクトの破棄
////================================================================
//void CObject::Release(void)
//{
//	CObject *pObject = this;
//
//	if (pObject->m_bDeath == false)
//	{
//		pObject->m_bDeath = true;
//	}
//}
//
////================================================================
////オブジェクトの取得
////================================================================
//CObject *CObject::Getobject(int nIdx)
//{
//	return m_apObjct[nIdx];
//}