//=============================================================================
//
// オブジェクトX処理 [object3D.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "main.h"
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//マクロ定義
//#define MAX_TEXTURE     (8)
#define MOVELIMIT       (580.0f)
#define PLAYERMOVE      (0.5f)     //プレイヤーのスピード
#define PLAYERDESH      (10.0f)    //ダッシュのスピード
#define PlAYERLOWMOVE   (0.1f)     //減速

//================================================================
//静的メンバ変数宣言
//================================================================
//LPDIRECT3DTEXTURE9 *CObjectX::m_pTexture = NULL;

//================================================================
//コンストラクタ
//================================================================
CObjectX::CObjectX()
{
	//値をクリア
	m_vtxMax = D3DXVECTOR3(-900000.0f, -900000.0f, -900000.0f);
	m_vtxMini = D3DXVECTOR3(900000.0f, 900000.0f, 900000.0f);
	m_vtxMax = D3DXVECTOR3(-900000.0f, -900000.0f, -900000.0f);
	m_vtxMini = D3DXVECTOR3(900000.0f, 900000.0f, 900000.0f);

	//m_nIdxTexture[5] = -1;
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CObjectX::CObjectX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aModelFliename)
{
	//値をクリア
	m_vtxMax = D3DXVECTOR3(-900000.0f, -900000.0f, -900000.0f);
	m_vtxMini = D3DXVECTOR3(900000.0f, 900000.0f, 900000.0f);
	m_vtxMax = D3DXVECTOR3(-900000.0f, -900000.0f, -900000.0f);
	m_vtxMini = D3DXVECTOR3(900000.0f, 900000.0f, 900000.0f);

	//値をクリア
	//m_pTexture = NULL;  //テクスチャへのポインタ

	SetPos(&pos);
	SetRot(&rot);
	//m_pos = pos;
	//m_rot = rot;
	//SetPos(&pos);
	m_Fliename = aModelFliename;
	//m_nIdxTexture[5] = -1;
}

//================================================================
//デストラクタ
//================================================================
CObjectX::~CObjectX()
{

}

//================================================================
//生成処理
//================================================================
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aModelFliename)
{
	//オブジェクトXのポインタ
	CObjectX *pObjectX = NULL;

	//モデル情報を取得
	CModel *pModel = CManager::Getinstance()->GetModel();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pObjectX == NULL)
		{
			//オブジェクト2Dの生成
			pObjectX = new CObjectX(pos, rot, aModelFliename);

			//初期化処理
			pObjectX->Init();
		}
	}

	return pObjectX;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CObjectX::Init(void)
{
	int nNumVtx;      //頂点数
	DWORD dwSizeFVF;  //頂点フォーマットのサイズ
	BYTE *pVtxBuff;   //頂点バッファへのポインタ

	//デバイスの取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int n = 0; n < MAX_TEX; n++)
	{
		m_nIdxTexture[n] = -1;
	}

	//Xファイル読み込み
	D3DXLoadMeshFromX(m_Fliename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
 	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//マテリアルへのポインタ
	D3DXMATERIAL *pMat;

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャが存在する

			m_nIdxTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_nIdxTexture[nCntMat] = -1;
		}
	}

	//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
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

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;     //頂点座標の代入

		//最小値-------------------------------------------------
		if (m_vtxMini.x > vtx.x)
		{
			m_vtxMini.x = vtx.x;
		}

		if (m_vtxMini.y > vtx.y)
		{
			m_vtxMini.y = vtx.y;
		}

		if (m_vtxMini.z > vtx.z)
		{
			m_vtxMini.z = vtx.z;
		}

		//最大値-------------------------------------------------
		if (m_vtxMax.x < vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}

		if (m_vtxMax.y < vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}

		if (m_vtxMax.z < vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;    //頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CObjectX::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
	
	//テクスチャの処理
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//頂点バッファの破壊
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CObjectX::Update(void)
{
	
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CObjectX::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	
	D3DXVECTOR3 pos = Getpos();
	D3DXVECTOR3 rot = GetRot();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture[nCntMat]));

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//================================================================
//モデルのバインド処理
//================================================================
void CObjectX::BindModel(OBJX pObjX)
{
	m_aObjectX = pObjX;
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CObjectX::UpdateItemPos(void)
{
	
}