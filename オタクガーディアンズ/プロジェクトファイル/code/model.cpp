//=============================================================================
//
// モデル処理 [model->cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
//インクルードファイル
//*============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//================================================================
//コンストラクタ
//================================================================
CModel::CModel()
{
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		m_aModel[nCount]->aName[MAX_CHAR] = {};
		m_aModel[nCount]->m_dwNumMat = NULL;
		m_aModel[nCount]->m_pBuffMat = NULL;
		m_aModel[nCount]->m_pMesh = NULL;
	}
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
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		m_aModel[nCount]->aName[MAX_CHAR] = {};
		m_aModel[nCount]->m_dwNumMat = NULL;
		m_aModel[nCount]->m_pBuffMat = NULL;
		m_aModel[nCount]->m_pMesh = NULL;
	}

	m_nNumAll = 0;
}

//================================================================
//指定のテクスチャ読み込み
//================================================================
int CModel::Regist(const char *pFilename)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		if (strcmp(pFilename, m_aModel[nCount]->aName) == 0)
		{
			return nCount;
		}
	}

	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		//Xファイル読み込み
		D3DXLoadMeshFromX(pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aModel[nCount]->m_pBuffMat,
			NULL,
			&m_aModel[nCount]->m_dwNumMat,
			&m_aModel[nCount]->m_pMesh);

		m_aModel[nCount]->m_pIdxTexture = new int [m_aModel[nCount]->m_dwNumMat];

		//マテリアルへのポインタ
		D3DXMATERIAL *pMat;

		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)m_aModel[nCount]->m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aModel[nCount]->m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャが存在する

				m_aModel[nCount]->m_pIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
			}
			else
			{
				m_aModel[nCount]->m_pIdxTexture[nCntMat] = -1;
			}
		}

		m_nIdxModel = nCount;

		break;
	}

	return m_nIdxModel;
}

////================================================================
////テクスチャのアドレス取得
////================================================================
//LPDIRECT3DTEXTURE9 CModel::GetAddress(int nIdx)
//{
//	if (nIdx >= 0)
//	{
//		return m_aTexture[nIdx]->m_pTexture;
//	}
//	else
//	{
//		return NULL;
//	}
//}
