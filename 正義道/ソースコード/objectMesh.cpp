//=============================================================================
//
// メッシュポリゴン処理 [objectMesh.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "objectMesh.h"
#include "renderer.h"
#include "manager.h"

#define HIGHT   (100)    //分割数
#define WI      (100)    //分割数
#define HILEN   (100.0f) //縦の長さ
#define WILEN   (100.0f) //横の長さ

//=============================================================================
//コンストラクタ
//=============================================================================
CObjectMesh::CObjectMesh()
{
	//値をクリア
	m_pTexture = NULL;  //テクスチャへのポインタ
	m_pVtxBuff = NULL;  //頂点情報を格納
	m_pIdxBuff = NULL;
}

//=============================================================================
//コンストラクタ
//=============================================================================
CObjectMesh::CObjectMesh(D3DXVECTOR3 pos)
{
	//値をクリア
	m_pTexture = NULL;  //テクスチャへのポインタ
	m_pVtxBuff = NULL;  //頂点情報を格納
	m_pIdxBuff = NULL;
	SetPos(&pos);
}

//=============================================================================
//デストラクタ
//=============================================================================
CObjectMesh::~CObjectMesh()
{

}

//=============================================================================
//生成処理
//=============================================================================
CObjectMesh * CObjectMesh::Create(void)
{
	//オブジェクト2Dのポインタ
	CObjectMesh *pObjectMesh = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pObjectMesh == NULL)
		{
			//オブジェクトメッシュの生成
			pObjectMesh = new CObjectMesh();

			//初期化処理
			pObjectMesh->Init();
		}
	}

	return pObjectMesh;
}


//=============================================================================
//初期化処理
//=============================================================================
HRESULT CObjectMesh::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((HIGHT + 1) * (WI + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;     //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < HIGHT + 1; n++)
	{
		for (int a = 0; a < WI + 1; a++)
		{
			pVtx[0].pos = D3DXVECTOR3((WILEN * a) - ((WILEN * WI) * 0.5f), 0.0f, -((HILEN * n) - ((HILEN * HIGHT) * 0.5f)));

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(((float)a / (1.0f / (float)(WI + 1))) * (1.0f / (float)(WI + 1)), ((float)n / (1.0f / (float)(HIGHT + 1))) * (1.0f / (float)(HIGHT + 1)));

			pVtx += 1;
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//頂点バッファを生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (HIGHT * ((WI + 1) * 2)) + (2 * (HIGHT - 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//インデックス情報へのポインタ
	WORD * pIdx;

	//インデックスバッファをロックし、頂点情報へポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	
	int nCntIdx = 0;

	for (int n = 0; n < HIGHT; n++)
	{
		for (int a = 0; a < WI + 1; a++)
		{
			if ((nCntIdx % 2) == 0)
			{
				pIdx[nCntIdx] = (a + (WI + 1) * (n + 1) + 1);
			}
			else
			{
				pIdx[nCntIdx ] = (a + ((WI + 1) * n));
			}
			
			
			nCntIdx += 1;
		}
	}

	//頂点バッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CObjectMesh::Uninit(void)
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

	//インデックスバッファを破壊
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CObjectMesh::Update(void)
{
	
}

//=============================================================================
//描画処理
//=============================================================================
void CObjectMesh::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

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

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);

	////ポリゴンの描画  D3DPT_LINESTRIP
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類
	//	0,                      //描画する最初の頂点インデックス
	//	HIGHT * WI                      //描画するプリミティブ数
	//);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		((HIGHT + 1) * (WI + 1)),
		0,
		(HIGHT * ((WI + 1) * 2)) + (2 * (HIGHT - 1))
	);

	//zテストを有効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);
}