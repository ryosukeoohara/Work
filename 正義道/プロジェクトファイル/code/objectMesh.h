//=============================================================================
//
// メッシュポリゴン処理 [objectMesh.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _OBJECTMESH_H_             //このマクロ定義がされてなかったら
#define _OBJECTMESH_H_             //2重インクルード防止のマクロ定義をする

#include "object.h"

//オブジェクト3Dクラス
class CObjectMesh : public CObject
{
public:
	CObjectMesh();
	CObjectMesh(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CObjectMesh();

	HRESULT Init(void);   //3Dオブジェクトの初期化処理    
	void Uninit(void);    //3Dオブジェクトの終了処理
	void Update(void);    //3Dオブジェクトの更新処理
	void Draw(void);      //3Dオブジェクトの描画処理

	static CObjectMesh *Create(void);  //生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;    //計算用マトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;        //頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;     //インデックスバッファへのポイント
};



#endif