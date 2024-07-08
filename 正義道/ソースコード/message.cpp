//===========================================================
//
//ポリゴンを出すやつ[message.cpp]
//Author 大原怜将
//
//===========================================================
#include "message.h"
#include "object2D.h"

//マクロ定義
#define WIDTH       (150.0f)   //横
#define HIGHT       (25.0f)    //縦
#define MESSAEND    (120)      //メッセージを表示しておく時間

//===========================================================
//静的メンバ変数
//===========================================================
CMessage *CMessage::Obj2D[MAX_MESSA] = {};
int CMessage::m_nIdx = 0;

//===========================================================
//コンストラクタ
//===========================================================
CMessage::CMessage()
{
	m_nType = TYPEMESS_NONE;
	MessaCounter = 0;
}

//===========================================================
//コンストラクタ
//===========================================================
CMessage::CMessage(D3DXVECTOR3 pos, TYPEMESS type)
{
	m_nType = type;
	SetPos(&pos);
	MessaCounter = 0;
}

//===========================================================
//デストラクタ
//===========================================================
CMessage::~CMessage()
{

}

//===========================================================
//インスタンス生成
//===========================================================
CMessage *CMessage::Create(D3DXVECTOR3 pos, TYPEMESS type)
{
	//オブジェクト2Dのポインタ
	//CMessage *pMessage = NULL;

	int Idx = m_nIdx;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (Obj2D[Idx] == NULL && m_nIdx < MAX_MESSA)
		{
			//オブジェクト2Dの生成
			Obj2D[Idx] = new CMessage(pos, type);

			//初期化処理
			Obj2D[Idx]->Init();

			m_nIdx++;
		}
	}

	return Obj2D[Idx];
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CMessage::Init(void)
{
	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CMessage::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	Obj2D[m_nIdx] = NULL;
}

//===========================================================
//更新処理
//===========================================================
void CMessage::Update(void)
{
	//更新処理
	CObject2D::Update();

	//位置取得
	D3DXVECTOR3 pos = Getpos();

	//頂点情報設定
	SetVtxMessage(pos, WIDTH, HIGHT);

	//制御処理
	Control();

	//カウントアップ
	MessaCounter++;

	if (MessaCounter >= MESSAEND)
	{//表示して億時間を超えたら

		//終了処理
		Uninit();
	}
}

//===========================================================
//描画処理
//===========================================================
void CMessage::Draw(void)
{
	//描画処理
	CObject2D::Draw();
}

//===========================================================
//制御処理
//===========================================================
void CMessage::Control(void)
{
	for (int nCount = 0; nCount < m_nIdx; nCount++)
	{
		D3DXVECTOR3 pos = Obj2D[nCount]->Getpos();

		pos.y -= 1.0f;

		Obj2D[nCount]->SetPos(&pos);
	}
	
	for (int nCount = 0; nCount < MAX_MESSA - 1; nCount++)
	{
		if (Obj2D[nCount] == NULL && Obj2D[nCount + 1] != NULL)
		{
			Obj2D[nCount] = Obj2D[nCount + 1];
			Obj2D[nCount + 1] = NULL;
		}
	}

	if (m_nIdx >= MAX_MESSA)
	{
		m_nIdx = 0;
	}
}