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

//===========================================================
// 静的メンバ変数
//===========================================================
CObject* CObject::m_pTop = {};
CObject* CObject::m_pCur = {};
int CObject::m_nNumAll = 0;

//===========================================================
// コンストラクタ
//===========================================================
CObject::CObject()
{
	m_bDeath = false;

	CObject* pObject = m_pTop;

	if (m_pTop != nullptr)
	{// 先頭が存在している場合

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// 存在しない場合

		m_pTop = this;
		m_pCur = this;
	}
}

//===========================================================
// デストラクタ
//===========================================================
CObject::~CObject()
{

}

//===========================================================
// すべて破棄
//===========================================================
void CObject::ReleaseAll(void)
{
	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Uninit();

		pObject = pObjectNext;
	}
}

//===========================================================
// すべて更新
//===========================================================
void CObject::UpdateAll(void)
{
	DeadChuck();

	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Update();
		pObject = pObjectNext;
	}
	
	CDebugProc* pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n\nオブジェクトの総数：%d", m_nNumAll);
}

//===========================================================
// すべて描画
//===========================================================
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::Getinstance()->GetCamera();

	DeadChuck();

	//カメラの設定
	pCamera->SetCamera();

	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Draw();
		pObject = pObjectNext;
	}
}

//===========================================================
// 破棄
//===========================================================
void CObject::Release(void)
{
	// 死んだ
	m_bDeath = true;
}

//===========================================================
// 死亡しているかチェック
//===========================================================
void CObject::DeadChuck(void)
{
	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			// リストから自分自身を削除する
			if (m_pTop == pObject)
			{// 自身が先頭

				if (pObject->m_pNext != nullptr)
				{// 次が存在している

					m_pTop = pObject->m_pNext;	// 次を先頭にする
					pObject->m_pNext->m_pPrev = nullptr;	// 次の前のポインタを覚えていないようにする
				}
				else
				{// 存在していない

					m_pTop = nullptr;	// 先頭がない状態にする
					m_pCur = nullptr;	// 最後尾がない状態にする
				}
			}
			else if (m_pCur == pObject)
			{// 自身が最後尾

				if (pObject->m_pPrev != nullptr)
				{// 次が存在している

					m_pCur = pObject->m_pPrev;			// 前を最後尾にする
					pObject->m_pPrev->m_pNext = nullptr;	// 前の次のポインタを覚えていないようにする
				}
				else
				{// 存在していない

					m_pTop = nullptr;	// 先頭がない状態にする
					m_pCur = nullptr;	// 最後尾がない状態にする
				}
			}
			else
			{
				if (pObject->m_pNext != nullptr)
				{
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;	// 自身の次に前のポインタを覚えさせる
				}
				if (pObject->m_pPrev != nullptr)
				{
					pObject->m_pPrev->m_pNext = pObject->m_pNext;	// 自身の前に次のポインタを覚えさせる
				}
			}
		}

		pObject = pObjectNext;
	}
}