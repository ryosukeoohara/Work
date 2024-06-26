//===========================================================
//
// タイム[time.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "time.h"
#include "texture.h"
#include "game.h"
#include "fade.h"
#include "number.h"

//===========================================================
// コンストラクタ
//===========================================================
CTime::CTime()
{
	
}

//================================================================
// コンストラクタ
//================================================================
CTime::CTime(D3DXVECTOR3 pos)
{
	
}

//===========================================================
//デストラクタ
//===========================================================
CTime::~CTime()
{

}

//===========================================================
// 生成処理
//===========================================================
CTime *CTime::Create(void)
{
	// タイムのポインタ
	CTime *pTime = nullptr;

	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	if (pTime == nullptr)
	{
		//生成
		pTime = new CTime();

		// 初期化処理
		pTime->Init();
	}
	
	return pTime;
}

//===========================================================
// 初期化処理
//===========================================================
HRESULT CTime::Init(void)
{
	return S_OK;
}

//===========================================================
// 終了処理
//===========================================================
void CTime::Uninit(void)
{
	
}

//===========================================================
// 更新処理
//===========================================================
void CTime::Update(void)
{
	
}

//===========================================================
// 描画処理
//===========================================================
void CTime::Draw(void)
{
	
}

//================================================================
// タイム
//================================================================
void CTime::TimeCounter(void)
{
	
}