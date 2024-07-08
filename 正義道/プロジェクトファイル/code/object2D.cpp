//===========================================================
//
//ポリゴンを出すやつ[object2D.cpp]
//Author 大原怜将
//
//===========================================================
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "multiplexbg.h"
#include "effect.h"
#include "texture.h"

//================================================================
//コンストラクタ
//================================================================
CObject2D::CObject2D()
{
	//値をクリア
	//m_pTexture = NULL;  //テクスチャへのポインタ
	m_nIdxTexture = -1;
	m_pVtxBuff = NULL;  //頂点情報を格納
	//m_nLife = 30;
	m_nCounterAnimPlayer = 0;
	m_nPatternAnimPlayer = 0;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CObject2D::CObject2D(D3DXVECTOR3 pos)
{
	//値をクリア
	SetPos(&pos);
	//m_pTexture = NULL;  //テクスチャへのポインタ
	m_nIdxTexture = -1;
	m_pVtxBuff = NULL;  //頂点情報を格納
	//m_nLife = 30;
	m_nCounterAnimPlayer = 0;
	m_nPatternAnimPlayer = 0;
}

//================================================================
//デストラクタ
//================================================================
CObject2D::~CObject2D()
{

}

//================================================================
//生成処理
//================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CObject2D *pObject2D = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pObject2D == NULL)
		{
			//オブジェクト2Dの生成
			pObject2D = new CObject2D(pos);

			//初期化処理
			pObject2D->Init();
		}
	}
	
	return pObject2D;
}

//================================================================
//初期化処理
//================================================================
HRESULT CObject2D::Init(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破壊
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//================================================================
//更新処理
//================================================================
void CObject2D::Update(void)
{
	
}

//================================================================
//描画処理
//================================================================
void CObject2D::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	CTexture *pTexture = CManager::GetTexture();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類
		0,                                         //描画する最初の頂点インデックス
		2                                          //描画するプリミティブ数
	);
}

//================================================================
//半径の更新
//================================================================
void CObject2D::SetVtxEffect(D3DXVECTOR3 pos, float m_fRadius, D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius , 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ブロックの設定
//================================================================
void CObject2D::SetVtxBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x,          pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x,          pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);
	
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//弾の設定
//================================================================
void CObject2D::SetVtxBullet(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y - fWidth, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fHeight, pos.y - fWidth, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fHeight, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//プレイヤーの設定
//================================================================
void CObject2D::SetVtxPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth,  pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth,  pos.y , 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//アイテムの設定
//================================================================
void CObject2D::SetVtxItem(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fWidth, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fHeight, pos.y - fWidth, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fHeight, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//アイテムの設定
//================================================================
void CObject2D::SetVtxNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, int m_nNumber)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fWidth, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fHeight, pos.y - fWidth, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fHeight, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//背景の設定
//================================================================
void CObject2D::SetVtxBg(void)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	D3DXVECTOR3 pos = Getpos();

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x + 0.0f,   pos.y + 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 580.0f, pos.y + 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + 0.0f,   pos.y + 320.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 580.0f, pos.y + 320.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//背景の設定
//================================================================
void CObject2D::SetVtxMessage(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//フレームの設定
//================================================================
void CObject2D::SetVtxFrame(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//アイテムスロットの設定
//================================================================
void CObject2D::SetVtxItemSlot(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//タイトルロゴの設定
//================================================================
void CObject2D::SetVtxTitleLogo(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//集中線の設定
//================================================================
void CObject2D::SetVtxEffectLine(void)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ライフゲージの設定
//================================================================
void CObject2D::SetVtxLifeGage(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

													 //頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ライフゲージの設定
//================================================================
void CObject2D::SetVtxIcon(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ライフの設定
//================================================================
void CObject2D::SetVtxLife(D3DXVECTOR3 pos, float fWidth, float fHeight, float fTex)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x,        pos.y          , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fTex, pos.y          , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x ,       pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fTex, pos.y + fHeight, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.9f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.9f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.9f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.9f, 0.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//フェードの設定
//================================================================
void CObject2D::SetVtxFade(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//フェードの設定
//================================================================
void CObject2D::SetVtxTarget(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ポーズの設定
//================================================================
void CObject2D::SetVtxPause(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//UIの設定
//================================================================
void CObject2D::SetVtxUI(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ランキングの設定
//================================================================
void CObject2D::SetVtxRanking(int Tex)
{
	D3DXVECTOR3 pos = Getpos();

	VERTEX_2D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x + -25.0f, pos.y + -50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y + -50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + -25.0f, pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y + 50.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.1f * Tex + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * Tex + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * Tex + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * Tex + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

////================================================================
////位置設定
////================================================================
//void CObject2D::SetPosition(D3DXVECTOR3 pos)
//{
//	m_pos = pos;  //位置を代入
//}
//
////================================================================
////位置取得
////================================================================
//D3DXVECTOR3 CObject2D::GetPosition(void)
//{
//	return m_pos;
//}

//================================================================
//テクスチャ取得
//================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
{
	//m_pTexture = m_Texture;
}