//=============================================================================
//
// オブジェクト3D処理[object3D.cpp]
// Author : 大原　怜将
//
//=============================================================================

#include "main.h"
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//================================================================
//コンストラクタ
//================================================================
CObject3D::CObject3D()
{
	//値をクリア
	m_pTexture = NULL;  //テクスチャへのポインタ
	m_pVtxBuff = NULL;  //頂点情報を格納
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CObject3D::CObject3D(D3DXVECTOR3 pos)
{
	//値をクリア
	m_pTexture = NULL;  //テクスチャへのポインタ
	m_pVtxBuff = NULL;  //頂点情報を格納
	SetPos(&pos);
}

//================================================================
//デストラクタ
//================================================================
CObject3D::~CObject3D()
{

}

//================================================================
//生成処理
//================================================================
CObject3D *CObject3D::Create(void)
{
	//オブジェクト2Dのポインタ
	CObject3D *pObject3D = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pObject3D == NULL)
		{
			//オブジェクト2Dの生成
			pObject3D = new CObject3D();

			//初期化処理
			pObject3D->Init();
		}
	}

	return pObject3D;
}

//================================================================
//3Dオブジェクトの初期化処理
//================================================================
HRESULT CObject3D::Init(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;     //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
//3Dオブジェクトの終了処理
//================================================================
void CObject3D::Uninit(void)
{
	//テクスチャの処理
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点バッファの破壊
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//================================================================
//3Dオブジェクトの更新処理
//================================================================
void CObject3D::Update(void)
{
	
}

//================================================================
//3Dオブジェクトの描画処理
//================================================================
void CObject3D::Draw(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = Getpos();
	D3DXVECTOR3 rot = GetRot();

	//zテストを無効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画  D3DPT_LINESTRIP
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類
		0,                                         //描画する最初の頂点インデックス
		2                                          //描画するプリミティブ数
	);					

	//zテストを有効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);
}

//================================================================
//テクスチャ取得
//================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
{
	m_pTexture = m_Texture;
}

//================================================================
//ビルボードの設定
//================================================================
void CObject3D::SetVtxBillBoard(void)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
   	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(5.0f,  5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(5.0f,  -5.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//フィールドの設定
//================================================================
void CObject3D::SetVtxField(void)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-5000.0f, 0.0f, 5000.0f);
	pVtx[1].pos = D3DXVECTOR3(5000.0f, 0.0f, 5000.0f);
	pVtx[2].pos = D3DXVECTOR3(-5000.0f, 0.0f, -5000.0f);
	pVtx[3].pos = D3DXVECTOR3(5000.0f, 0.0f, -5000.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//弾の設定
//================================================================
void CObject3D::SetVtxBullet(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y + fWidth,  0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fHeight, pos.y + fWidth,  0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth,  pos.y - fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fHeight, pos.y - fHeight, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//エフェクトの設定
//================================================================
void CObject3D::SetVtxEffect(D3DXVECTOR3 pos, float m_fRadius, D3DXCOLOR col)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fRadius, +m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fRadius, +m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fRadius, -m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fRadius, -m_fRadius, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//エフェクトの設定
//================================================================
void CObject3D::SetVtxEffectSword(float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_3D * pVtx;                                //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-fWidth,  0.0f,  fWidth);
	pVtx[1].pos = D3DXVECTOR3(fHeight,  0.0f,  fWidth);
	pVtx[2].pos = D3DXVECTOR3(-fWidth,  0.0f, -fHeight);
	pVtx[3].pos = D3DXVECTOR3(fHeight,  0.0f, -fHeight);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//当たり判定の円の設定
//================================================================
void CObject3D::SetVtxCircle(float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_3D * pVtx;                                //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-fWidth, 0.0f, fWidth);
	pVtx[1].pos = D3DXVECTOR3(fHeight, 0.0f, fWidth);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, 0.0f, -fHeight);
	pVtx[3].pos = D3DXVECTOR3(fHeight, 0.0f, -fHeight);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//影の設定
//================================================================
void CObject3D::SetShadowPosition(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth,  0.0f, pos.z + fWidth);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fHeight, 0.0f, pos.z + fWidth);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth,  0.0f, pos.z - fHeight);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fHeight, 0.0f, pos.z - fHeight);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//ライフの設定
//================================================================
void CObject3D::SetVtxLife(D3DXVECTOR3 pos, float fWidth, float fHeight, float fTex)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //頂点バッファをロックし、頂点情報へポインタを取得

													 //頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x,        pos.y,           0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fTex, pos.y,           0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x,        pos.y + fHeight, 0.0f);
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
//テクスチャ取得
//================================================================
//float CObject3D::GetHeight(D3DXVECTOR3 pos)
//{
//	//float fHeight = 0.0f;
//
//	//VERTEX_3D * pVtx;     //頂点情報へのポインタ
//
//	////頂点バッファをロックし、頂点情報へポインタを取得
//	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//if (pos.x >= -500.0f && pos.x <= 500.0f && pos.z >= -500.0f && pos.z <= 500.0f)
//	//{
//	//	m_vec0 = pVtx[0].pos - pVtx[2].pos;
//	//	m_vec1 = pVtx[3].pos - pVtx[2].pos;
//
//	//	m_vec2 = pVtx[0].pos - pVtx[1].pos;
//	//	m_vec3 = pVtx[3].pos - pVtx[1].pos;
//
//	//	m_nor0 = pVtx[2].nor;
//
//	//	D3DXVec3Cross(&m_nor0, &m_vec0, &m_vec1);
//
//	//	//ベクトルを正規化する
//	//	D3DXVec3Normalize(&m_nor0, &m_nor0);
//
//	//	m_nor1 = pVtx[1].nor;
//
//	//	D3DXVec3Cross(&m_nor1, &m_vec2, &m_vec3);
//
//	//	//ベクトルを正規化する
//	//	D3DXVec3Normalize(&m_nor1, &m_nor1);
//
//	//	D3DXVECTOR3 vecA, vecB, vecC;
//
//	//	vecA.x = pVtx[0].pos.y * pVtx[2].pos.z - pVtx[0].pos.z * pVtx[2].pos.y;
//	//	vecA.y = pVtx[0].pos.z * pVtx[2].pos.x - pVtx[0].pos.x * pVtx[2].pos.z;
//	//	vecA.z = pVtx[0].pos.x * pVtx[2].pos.y - pVtx[0].pos.y * pVtx[2].pos.x;
//
//	//	vecB.x = pVtx[0].pos.y * pVtx[2].pos.z - pVtx[0].pos.z * pVtx[2].pos.y;
//	//	vecB.y = pVtx[0].pos.z * pVtx[2].pos.x - pVtx[0].pos.x * pVtx[2].pos.z;
//	//	vecB.z = pVtx[0].pos.x * pVtx[2].pos.y - pVtx[0].pos.y * pVtx[2].pos.x;
//
//
//
//
//	//	if (m_nor0.y != 0.0f)
//	//	{
//	//		fHeight = ((pos.x + pVtx[2].pos.x) * m_nor0.x - pVtx[2].pos.y - (pos.z + pVtx[2].pos.z) * m_nor0.z) / m_nor0.y;
//	//	}
//	//	
//
//	//	
//
//	//	/*if (m_nor1.y != 0.0f)
//	//	{
//	//		fHeight = ((pos.x + pVtx[2].pos.x) * m_nor1.x - pVtx[2].pos.y - (pos.z + pVtx[2].pos.z) * m_nor1.z) / m_nor1.y;
//	//	}*/
//
//	//	//法線ベクトルの設定
//	//	pVtx[1].nor = D3DXVECTOR3(m_nor1.x, m_nor1.y, m_nor1.z);
//	//	pVtx[2].nor = D3DXVECTOR3(m_nor0.x, m_nor0.y, m_nor0.z);
//	//	
//	//	//頂点バッファをアンロックする
//	//	m_pVtxBuff->Unlock();
//	//}
//
//	//return fHeight;
//}