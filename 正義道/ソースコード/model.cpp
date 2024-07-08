//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include<string.h>

//================================================================
//静的メンバ変数
//================================================================
int CModel::m_nNumAll = 0;

//================================================================
//コンストラクタ
//================================================================
CModel::CModel()
{
	m_pTexture = NULL;
}

//================================================================
//デストラクタ
//================================================================
CModel::~CModel()
{

}

//================================================================
//初期化処理
//================================================================
HRESULT CModel::Load(void)
{
	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CModel::UnLoad(void)
{
	
}

//================================================================
//指定のテクスチャ読み込み
//================================================================
int CModel::Regist(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename)
{
	int nIdx = m_nNumAll;

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		if (strcmp(pFilename, m_aModel[nCount].aName) == 0)
		{
			return nCount;
		}
	}

	if (m_aModel[nIdx].m_aModel == NULL)
	{
		strcpy(m_aModel[nIdx].aName, pFilename);

		m_aModel[nIdx].m_aModel = CObjectX::Create(pos, rot, pFilename);

		m_nNumAll++;  //テクスチャの総数をカウントアップ
	}

	
	

	//int nNumVtx;      //頂点数
	//DWORD dwSizeFVF;  //頂点フォーマットのサイズ
	//BYTE *pVtxBuff;   //頂点バッファへのポインタ

	////デバイスの取得
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////Xファイル読み込み
	//D3DXLoadMeshFromX(pFilename,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&m_aModel[nIdx].m_pBuffMat,
	//	NULL,
	//	&m_aModel[nIdx].m_dwNumMat,
	//	&m_aModel[nIdx].m_pMesh);

	////頂点数を取得
	//nNumVtx = m_aModel[nIdx].m_pMesh->GetNumVertices();

	////頂点フォーマットのサイズを取得
	//dwSizeFVF = D3DXGetFVFVertexSize(m_aModel[nIdx].m_pMesh->GetFVF());

	//if (m_pTexture == NULL)
	//{
	//	m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_aModel[nIdx].m_dwNumMat];
	//}

	////マテリアルへのポインタ
	//D3DXMATERIAL *pMat;

	////マテリアル情報に対するポインタを取得
	//pMat = (D3DXMATERIAL*)m_aModel[nIdx].m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_aModel[nIdx].m_dwNumMat; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{//テクスチャが存在する

	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{
	//		m_pTexture[nCntMat] = NULL;
	//	}
	//}

	////頂点バッファをロック
	//m_aModel[nIdx].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;     //頂点座標の代入

	//	//最小値-------------------------------------------------
	//	if (m_aModel[nIdx].m_vtxMini.x > vtx.x)
	//	{
	//		m_aModel[nIdx].m_vtxMini.x = vtx.x;
	//	}

	//	if (m_aModel[nIdx].m_vtxMini.y > vtx.y)
	//	{
	//		m_aModel[nIdx].m_vtxMini.y = vtx.y;
	//	}

	//	if (m_aModel[nIdx].m_vtxMini.z > vtx.z)
	//	{
	//		m_aModel[nIdx].m_vtxMini.z = vtx.z;
	//	}

	//	//最大値-------------------------------------------------
	//	if (m_aModel[nIdx].m_vtxMax.x < vtx.x)
	//	{
	//		m_aModel[nIdx].m_vtxMax.x = vtx.x;
	//	}

	//	if (m_aModel[nIdx].m_vtxMax.y < vtx.y)
	//	{
	//		m_aModel[nIdx].m_vtxMax.y = vtx.y;
	//	}

	//	if (m_aModel[nIdx].m_vtxMax.z < vtx.z)
	//	{
	//		m_aModel[nIdx].m_vtxMax.z = vtx.z;
	//	}

	//	pVtxBuff += dwSizeFVF;    //頂点フォーマットのサイズ分ポインタを進める
	//}

	////頂点バッファをアンロック
	//m_aModel[nIdx].m_pMesh->UnlockVertexBuffer();

	m_nNumAll++;

	return nIdx;
}

//================================================================
//テクスチャのアドレス取得
//================================================================
CObjectX CModel::GetAddress(int nIdx)
{
	return *m_aModel[nIdx].m_aModel;
}
