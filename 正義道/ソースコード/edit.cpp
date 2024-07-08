//===========================================================
//
//ポリゴンを出すやつ[edit.cpp]
//Author 大原怜将
//
//===========================================================
#include "edit.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"

#include <stdio.h>
#include<string.h>

//マクロ定義
#define MODEL_SET_TEXT  ("data\\TEXT\\model_set.txt")

//===========================================================
//コンストラクタ
//===========================================================
CEdit::CEdit()
{
	m_nNumModel = 0;
	m_nIdx = 0;
	m_dwNumMat = 0;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_pTexture = NULL;
}

//===========================================================
//デストラクタ
//===========================================================
CEdit::~CEdit()
{

}

//===========================================================
//初期化処理
//===========================================================
HRESULT CEdit::Init(void)
{
	//テキストファイル読み込み
	ReadText();

	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//初期化処理
	//		m_apModel[nCount]->Init();
	//	}
	//}
	

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CEdit::Uninit(void)
{
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//初期化処理
	//		m_apModel[nCount]->Uninit();
	//	}
	//}

	if (m_pTexture != NULL)
	{
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
}

//===========================================================
//更新処理
//===========================================================
void CEdit::Update(void)
{
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	////更新処理
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//初期化処理
	//		m_apModel[nCount]->Update();
	//	}
	//}

	//右に移動----------------------------------------------
	if (InputKeyboard->GetPress(DIK_N) == true)
	{//Dキーだけ押した

		//移動量
		m_move.x += sinf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
		m_move.z += cosf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
	}

	//左に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_M) == true)
	{//Aキーだけ押した

		//移動量
		m_move.x -= sinf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
		m_move.z -= cosf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
	}
}

//===========================================================
//描画処理
//===========================================================
void CEdit::Draw(void)
{
	////描画処理
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//初期化処理
	//		m_apModel[nCount]->Draw();
	//	}
	//}

	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, *&m_pTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===========================================================
//セーブ処理
//===========================================================
void CEdit::Save(void)
{

}

//===========================================================
//ロード処理
//===========================================================
void CEdit::Load(void)
{

}

//===========================================================
//テキストファイル読み込み
//===========================================================
void CEdit::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	//int nCntModel = 0;

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(MODEL_SET_TEXT, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_MODEL", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumModel);  //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_Model[m_nIdx].m_filename[0]);  //モデルの名前

					CPlayer *pPlayer = CManager::GetPlayer();

					D3DXVECTOR3 pos = pPlayer->Getpos();

					//m_apModel[m_nIdx] = CObjectX::Create(pos, m_filename);
					int nNumVtx;      //頂点数
					DWORD dwSizeFVF;  //頂点フォーマットのサイズ
					BYTE *pVtxBuff;   //頂点バッファへのポインタ

					//デバイスの取得
					CRenderer *pRenderer = CManager::GetRenderer();
					LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

					//Xファイル読み込み
					D3DXLoadMeshFromX(m_Model[m_nIdx].m_filename,
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

					//マテリアルへのポインタ
					D3DXMATERIAL *pMat;

					//マテリアル情報に対するポインタを取得
					pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
					{
						if (pMat[nCntMat].pTextureFilename != NULL)
						{//テクスチャが存在する

							if (m_pTexture == NULL)
							{
								m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
							}

							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&m_pTexture[nCntMat]);
						}
						else if (pMat[nCntMat].pTextureFilename == NULL)
						{
							m_pTexture[nCntMat] = NULL;
						}
					}

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

					m_nIdx++;

				}  //MODEL_LILENAMEのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	
}