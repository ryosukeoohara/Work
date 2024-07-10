//===========================================================
//
//エディット処理[edit.cpp]
//Author 大原怜将
//
//===========================================================
#include "edit.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "player.h"
#include "game.h"

#include <stdio.h>
#include<string.h>

//マクロ定義
#define MODEL_SET_TEXT  ("data\\TEXT\\model_set.txt")
#define MODEL  ("data\\TEXT\\model.txt")
#define MOVE   (2.0f)  //移動量

//===========================================================
//コンストラクタ
//===========================================================
CEdit::CEdit()
{
	//m_pos = { 0.0f, 0.0f, 0.0f };
	m_nIdx = 0;
	m_nNumAll = 0;
	m_SetModel = 0;
	m_nSelectModel = 0;
	m_mode = MODE_CREATE;
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
	//全部にNULL入れる
	for (int nCount = 0; nCount < MAX_MODELSET; nCount++)
	{
		m_apModel[nCount] = NULL;
	}

	//テキストファイル読み込み
	ReadText();

	//Xファイル読み込み
	XLoad();

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CEdit::Uninit(void)
{
	for (int nCount = 0; nCount < m_SetModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//初期化処理
			m_apModel[nCount]->Uninit();

			m_apModel[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		if (m_Model[nCount].m_pTexture != NULL)
		{
			m_Model[nCount].m_pTexture = NULL;
		}
	}

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		//テクスチャの処理
		if (m_Model[nCount].m_pMesh != NULL)
		{
			m_Model[nCount].m_pMesh->Release();
			m_Model[nCount].m_pMesh = NULL;
		}
	}

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		//頂点バッファの破壊
		if (m_Model[nCount].m_pBuffMat != NULL)
		{
			m_Model[nCount].m_pBuffMat->Release();
			m_Model[nCount].m_pBuffMat = NULL;
		}
	}

	CObject::Release();
}

//===========================================================
//更新処理
//===========================================================
void CEdit::Update(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	pDebugProc->Print("\n---エディットの情報---");
	pDebugProc->Print("\n<<モードの切り替え : F2>>");

	if (m_mode == MODE_CREATE)
	{//現在のモードがクリエイトモードだったら

		pDebugProc->Print("\n<<現在のモード : クリエイト>>");
	}

	if (m_mode == MODE_DELETE)
	{//現在のモードがデリートモードだったら

		pDebugProc->Print("\n<<現在のモード : デリート>>");
	}

	for (int nCount = 0; nCount < MAX_MODELSET; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用されていたら

			//更新処理
			m_apModel[nCount]->Update();
		}
	}

	if (InputKeyboard->GetTrigger(DIK_F2) == true)
	{//F2キーが押された

		if (m_mode == MODE_CREATE)
		{//現在のモードがクリエイトモードだったら

			m_mode = MODE_DELETE;  //モードをデリートにする
		}

		else if (m_mode == MODE_DELETE)
		{//現在のモードがデリートモードだったら

			m_mode = MODE_CREATE;  //モードをクリエイトにする
		}
	}

	switch (m_mode)
	{
	case MODE_CREATE:  //配置

		//制御処理
		Control();

		break;

	case MODE_DELETE:  //置いたもの消す

		//セットしたモデルを消す処理
		SetModelDelete();

		break;
	}
}

//===========================================================
//描画処理
//===========================================================
void CEdit::Draw(void)
{
	for (int nCount = 0; nCount < MAX_MODELSET; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//使用されていたら

			//描画処理
			m_apModel[nCount]->Draw();
		}
	}

	//デバイスの取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//αブレンディングを加算合計に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	if (m_mode == MODE_CREATE)
	{//現在のモードがクリエイトモードだったら

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Model[m_nIdx].m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_Model[m_nIdx].m_rot.y, m_Model[m_nIdx].m_rot.x, m_Model[m_nIdx].m_rot.z);

		D3DXMatrixMultiply(&m_Model[m_nIdx].m_mtxWorld, &m_Model[m_nIdx].m_mtxWorld, &m_mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&m_mtxTrans, m_Model[m_nIdx].m_pos.x, m_Model[m_nIdx].m_pos.y, m_Model[m_nIdx].m_pos.z);

		D3DXMatrixMultiply(&m_Model[m_nIdx].m_mtxWorld, &m_Model[m_nIdx].m_mtxWorld, &m_mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[m_nIdx].m_mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
 		pMat = (D3DXMATERIAL*)m_Model[m_nIdx].m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_Model[m_nIdx].m_dwNumMat; nCntMat++)
		{
			pMat[nCntMat].MatD3D.Diffuse.a = 0.7f;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, *&m_Model[m_nIdx].m_pTexture[nCntMat]);

			//モデル(パーツ)の描画
			m_Model[m_nIdx].m_pMesh->DrawSubset(nCntMat);
		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================================================
//セーブ処理
//===========================================================
void CEdit::Save(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	FILE * pFile;

	pFile = fopen(MODEL, "w");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fprintf(pFile, "SCRIPT\n");

		fprintf(pFile, "\n");

		fprintf(pFile, "NUM_MODEL = %d\n", m_SetModel);

		for (int nCount = 0; nCount < m_SetModel; nCount++)
		{
			D3DXVECTOR3 pos = m_apModel[nCount]->Getpos();  //位置取得
			D3DXVECTOR3 rot = m_apModel[nCount]->GetRot();  //向き取得

			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "    TYPE = %d\n", m_apModel[nCount]->GetIdxModel());        //種類
			fprintf(pFile, "    POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);      //位置
			fprintf(pFile, "    ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);      //向き
			fprintf(pFile, "END_MODELSET\n");
			fprintf(pFile, "\n");
		}

		fprintf(pFile, "END_SCRIPT\n");

		//ファイルを閉じる
		fclose(pFile);
	}

	pDebugProc->Print("\n保存したよ～");
}

//===========================================================
//Xファイルロード処理
//===========================================================
void CEdit::XLoad(void)
{
	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		int nNumVtx;      //頂点数
		DWORD dwSizeFVF;  //頂点フォーマットのサイズ
		BYTE *pVtxBuff;   //頂点バッファへのポインタ

						  //デバイスの取得
		CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//Xファイル読み込み
		D3DXLoadMeshFromX(m_Model[nCount].m_filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[nCount].m_pBuffMat,
			NULL,
			&m_Model[nCount].m_dwNumMat,
			&m_Model[nCount].m_pMesh);

		//頂点数を取得
		nNumVtx = m_Model[nCount].m_pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		dwSizeFVF = D3DXGetFVFVertexSize(m_Model[nCount].m_pMesh->GetFVF());

		if (m_Model[nCount].m_pTexture == NULL)
		{
			m_Model[nCount].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[nCount].m_dwNumMat];
		}

		//マテリアルへのポインタ
		D3DXMATERIAL *pMat;

		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)m_Model[nCount].m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_Model[nCount].m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャが存在する

				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_Model[nCount].m_pTexture[nCntMat]);
			}
			else
			{
				m_Model[nCount].m_pTexture[nCntMat] = NULL;
			}
		}

		//頂点バッファをロック
		m_Model[nCount].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;     //頂点座標の代入

														   //最小値-------------------------------------------------
			if (m_Model[nCount].m_vtxMini.x > vtx.x)
			{
				m_Model[nCount].m_vtxMini.x = vtx.x;
			}

			if (m_Model[nCount].m_vtxMini.y > vtx.y)
			{
				m_Model[nCount].m_vtxMini.y = vtx.y;
			}

			if (m_Model[nCount].m_vtxMini.z > vtx.z)
			{
				m_Model[nCount].m_vtxMini.z = vtx.z;
			}

			//最大値-------------------------------------------------
			if (m_Model[nCount].m_vtxMax.x < vtx.x)
			{
				m_Model[nCount].m_vtxMax.x = vtx.x;
			}

			if (m_Model[nCount].m_vtxMax.y < vtx.y)
			{
				m_Model[nCount].m_vtxMax.y = vtx.y;
			}

			if (m_Model[nCount].m_vtxMax.z < vtx.z)
			{
				m_Model[nCount].m_vtxMax.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;    //頂点フォーマットのサイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		m_Model[nCount].m_pMesh->UnlockVertexBuffer();
	}
}

//===========================================================
//マップファイルロード処理
//===========================================================
void CEdit::TEXTLoad(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntModel = 0;
	int ntype = 0;

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(MODEL, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("MODELSET", aString) == 0)
				{
					while (strcmp("END_MODELSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);   //=
							fscanf(pFile, "%d", &ntype);     //種類
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &m_Model[ntype].m_pos.x);  //位置
							fscanf(pFile, "%f", &m_Model[ntype].m_pos.y);  //位置
							fscanf(pFile, "%f", &m_Model[ntype].m_pos.z);  //位置
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);          //=
							fscanf(pFile, "%f", &m_Model[ntype].m_rot.x);  //位置
							fscanf(pFile, "%f", &m_Model[ntype].m_rot.y);  //位置
							fscanf(pFile, "%f", &m_Model[ntype].m_rot.z);  //位置

																		   //オブジェクトXを生成
							m_apModel[m_SetModel] = CObjectX::Create(m_Model[ntype].m_pos, m_Model[ntype].m_rot, m_Model[ntype].m_filename);

							//種類設定
							m_apModel[m_SetModel]->SetIdxModel(ntype);

							m_SetModel++;  //カウントアップ
						}
					}
				}  //NUM_MODELのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===========================================================
//テキストファイル読み込み
//===========================================================
void CEdit::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntModel = 0;
	CFoot *pPlayer = CGame::GetPlayerFoot();

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
					fscanf(pFile, "%d", &m_nNumAll);  //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_Model[nCntModel].m_filename[0]);  //モデルの名前
					m_Model[nCntModel].m_nType = nCntModel;
					m_pos = pPlayer->Getpos();
					nCntModel++;

				}  //MODEL_LILENAMEのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===========================================================
//制御処理
//===========================================================
void CEdit::Control(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{//1キーが押された

		if (m_nIdx > -1)
		{//インデックス番号が-1より大きいとき

			m_nIdx -= 1;  //インデックス番号を一つ戻す
		}

		if (m_nIdx < 0)
		{//インデックス番号が0より小さいとき

			m_nIdx = m_nNumAll - 1;  //インデックス番号を総数-1にする
		}
	}

	if (InputKeyboard->GetTrigger(DIK_2) == true)
	{//2キーが押された

		if (m_nIdx < m_nNumAll)
		{//インデックス番号が総数より小さいとき

			m_nIdx += 1;  //インデックス番号を一つ進める
		}

		if (m_nIdx >= m_nNumAll)
		{//インデックス番号が総数以上になったとき

			m_nIdx = 0;  //インデックス番号を0にする
		}
	}

	if (InputKeyboard->GetTrigger(DIK_L) == true)
	{//ENTERキーが押された

		for (int nCount = 0; nCount < MAX_MODELSET; nCount++)
		{
			if (m_apModel[nCount] == NULL)
			{//使用されていないとき

				//オブジェクトXを生成
				m_apModel[nCount] = CObjectX::Create(m_Model[m_nIdx].m_pos, m_Model[m_nIdx].m_rot, m_Model[m_nIdx].m_filename);

				//種類設定
				m_apModel[nCount]->SetIdxModel(m_nIdx);

				//総数をカウントアップ
				m_SetModel++;

				break;
			}
		}
	}

	if (InputKeyboard->GetTrigger(DIK_F7) == true)
	{//F8キーが押された

		for (int nCount = 0; nCount < m_SetModel; nCount++)
		{
			if (m_apModel[nCount] != NULL)
			{//使用されているとき

			 //終了処理
				m_apModel[nCount]->Uninit();

				//メモリを開放
				delete m_apModel[nCount];

				//使用していない状態にする
				m_apModel[nCount] = NULL;
			}
		}

		m_SetModel = 0;
	}

	if (InputKeyboard->GetTrigger(DIK_F8) == true)
	{//F8キーが押されたm_Model[m_nIdx].m_move

	 //外部ファイル書き出し
		Save();
	}

	if (InputKeyboard->GetTrigger(DIK_F9) == true)
	{//F8キーが押されたm_Model[m_nIdx].m_move

	 //マップファイル読み込み
		TEXTLoad();
	}

	//上に移動----------------------------------------------
	if (InputKeyboard->GetPress(DIK_UP) == true)
	{//Wキーが押された

		m_Model[m_nIdx].m_move.y += cosf(CameraRot.y) * MOVE;
	}
	//下に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_DOWN) == true)
	{//Sキーが押された

		m_Model[m_nIdx].m_move.y -= cosf(CameraRot.y) * MOVE;
	}

	//右に移動----------------------------------------------
	if (InputKeyboard->GetPress(DIK_RIGHT) == true)
	{//Dキーだけ押した

		//移動量
		m_Model[m_nIdx].m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.5f)) * MOVE;
	}
	//左に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_LEFT) == true)
	{//Aキーだけ押した

		//移動量
		m_Model[m_nIdx].m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * MOVE;
	}

	if (InputKeyboard->GetPress(DIK_RSHIFT) == true)
	{
		//移動量
		m_Model[m_nIdx].m_move.z += MOVE;
	}
	else if (InputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		//移動量
		m_Model[m_nIdx].m_move.z -= MOVE;
	}

	if (InputKeyboard->GetPress(DIK_U) == true)
	{//Uキーを押した

		m_Model[m_nIdx].m_rot.y += 0.01f;
	}

	if (InputKeyboard->GetPress(DIK_I) == true)
	{//Iキーを押した

		m_Model[m_nIdx].m_rot.y -= 0.01f;
	}

	if (InputKeyboard->GetTrigger(DIK_O) == true)
	{//Oキーを押した

		m_Model[m_nIdx].m_rot.y = 0.0f;
	}

	if (m_Model[m_nIdx].m_rot.y > D3DX_PI)
	{
		m_Model[m_nIdx].m_rot.y = -D3DX_PI;
	}

	else if (m_Model[m_nIdx].m_rot.y < -D3DX_PI)
	{
		m_Model[m_nIdx].m_rot.y = D3DX_PI;
	}

	//移動量を更新(減衰させる)--------------------------------------------
	m_Model[m_nIdx].m_move.x += (0.0f - m_Model[m_nIdx].m_move.x) * 0.5f;
	m_Model[m_nIdx].m_move.y += (0.0f - m_Model[m_nIdx].m_move.y) * 0.5f;
	m_Model[m_nIdx].m_move.z += (0.0f - m_Model[m_nIdx].m_move.z) * 0.5f;

	//移動量加算
	m_pos.x += m_Model[m_nIdx].m_move.x;
	m_pos.y += m_Model[m_nIdx].m_move.y;
	m_pos.z += m_Model[m_nIdx].m_move.z;

	//位置を代入
	m_Model[m_nIdx].m_pos = m_pos;

	pDebugProc->Print("\n<< オブジェクトの位置：X軸<%f>,Y軸<%f>,Z軸<%f> >>", m_Model[m_nIdx].m_pos.x, m_Model[m_nIdx].m_pos.y, m_Model[m_nIdx].m_pos.z);
	pDebugProc->Print("\n<< オブジェクトの向き：X軸<%f>,Y軸<%f>,Z軸<%f> >>", m_Model[m_nIdx].m_rot.x, m_Model[m_nIdx].m_rot.y, m_Model[m_nIdx].m_rot.z);
	pDebugProc->Print("\n<< 現在のオブジェクトの番号：%d/%d >>", m_nIdx, m_nNumAll);
	pDebugProc->Print("\n<< 設置したオブジェクトの数：%d >>", m_SetModel);
	pDebugProc->Print("\n<< 配置リセット：F7 >>");
	pDebugProc->Print("\n<< 外部ファイル書き出し：F8 >>");
	pDebugProc->Print("\n<< 外部ファイル読み込み：F9 >>");
	pDebugProc->Print("\n<< モデルの旋回 : U/I >>");
	pDebugProc->Print("\n<< モデルの向きリセット : O >>");
}

//===========================================================
//セットしたモデルを消す処理
//===========================================================
void CEdit::SetModelDelete(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{//1キーが押された

		if (m_nSelectModel > -1)
		{//インデックス番号が-1より大きいとき

			m_nSelectModel -= 1;  //インデックス番号を一つ戻す
		}
	}

	if (m_nSelectModel < 0)
	{//インデックス番号が0より小さいとき

		m_nSelectModel = m_SetModel - 1;  //インデックス番号を総数-1にする
	}

	if (InputKeyboard->GetTrigger(DIK_2) == true)
	{//2キーが押された

		if (m_nSelectModel < m_SetModel)
		{//インデックス番号が総数より小さいとき

			m_nSelectModel += 1;  //インデックス番号を一つ進める
		}
	}

	if (m_nSelectModel >= m_SetModel)
	{//インデックス番号が総数以上になったとき

		m_nSelectModel = 0;  //インデックス番号を0にする
	}

	if (InputKeyboard->GetTrigger(DIK_DELETE) == true)
	{//deleteキーを押した

		if (m_apModel[m_nSelectModel] != NULL)
		{//使用されていたら

		 //初期化処理
			m_apModel[m_nSelectModel]->Uninit();

			//使用していない状態にする
			m_apModel[m_nSelectModel] = NULL;

			//カウントダウン
			m_SetModel--;
		}

		for (int nCount = 0; nCount < m_SetModel; nCount++)
		{
			if (m_apModel[nCount] == NULL && m_apModel[nCount + 1] != NULL)
			{//現在のカウントが使用されていないかつ、次のカウントが使用されているとき

			 //代入
				m_apModel[nCount] = m_apModel[nCount + 1];

				//次のカウントを使用していない状態にする
				m_apModel[nCount + 1] = NULL;
			}
		}
	}

	if (m_SetModel > 0)
	{
		pDebugProc->Print("\n<< 削除するオブジェクトの番号：%d/%d >>", m_nSelectModel, m_SetModel);
	}

	if (m_SetModel <= 0)
	{
		pDebugProc->Print("\n<< 削除できるオブジェクトはありません >>");
	}
}