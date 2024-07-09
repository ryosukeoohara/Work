//===========================================================
//
// オブジェクトX処理[oBjectX.h]
// Author 大原怜将
//
//===========================================================
#ifndef _OBJECTX_H__             //このマクロ定義がされてなかったら
#define _OBJECTX_H__             //2重インクルード防止のマクロ定義をする

#include "object.h"

#define MAX_FILENAME   (128)

class CModel;

//===========================================================
// クラス定義
//===========================================================
class CObjectX : public CObject
{
public:
	CObjectX();
	CObjectX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aModelFliename);
	~CObjectX();

	HRESULT Init(void);     //モデルの初期化処理    
	void Uninit(void);   //モデルの終了処理
	void Update(void);   //モデルの更新処理
	void Draw(void);     //モデルの描画処理

	typedef struct
	{
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_posOrigin;
		D3DXVECTOR3 m_rot;
		D3DXVECTOR3 m_rotOrigin;
		D3DXVECTOR3 m_vtxMini;    //モデルの最小値
		D3DXVECTOR3 m_vtxMax;     //モデルの最大値
		LPD3DXMESH m_pMesh;       //テクスチャへのポインタ
		LPD3DXBUFFER m_pBuffMat;  //頂点バッファへのポインタ
		DWORD m_dwNumMat;         //マテリアルの数
		D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	} OBJX;

	static CObjectX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aModelFliename);  //生成

	void BindModel(OBJX pObjX);

	void SetPositionOri(D3DXVECTOR3 posOrigin) { m_aObjectX.m_posOrigin = posOrigin;}  //原点の位置設定
	D3DXVECTOR3 GetPositionOri(void) { return m_aObjectX.m_posOrigin; }     //原点の位置取得  

	void SetRotOrigin(D3DXVECTOR3 rotOrigin) { m_aObjectX.m_rotOrigin = rotOrigin; }       //向き設定
	D3DXVECTOR3 GetRotOrigin(void) { return m_aObjectX.m_rotOrigin; }          //向き取得

	//void SetIdx(int nIdx) {}

	D3DXMATRIX GetMtxWorld(void) { return m_aObjectX.m_mtxWorld; }     //マトリックス取得

	D3DXVECTOR3 GetVtxMin(void) { return m_aObjectX.m_vtxMini; }  //モデルの最小値取得
	D3DXVECTOR3 GetVtxMax(void) { return m_aObjectX.m_vtxMax; }   //モデルの最大値取得

	int GetIdxModel(void) { return m_nIdxModel; }
	void SetIdxModel(int nIdx) { m_nIdxModel = nIdx; }


	void UpdateItemPos(void);

	

private:
	

	LPDIRECT3DTEXTURE9 *m_pTexture;     //テクスチャへのポインタ
	OBJX m_aObjectX;
	int m_nNumModel;          //モデル(パーツ)の総数
	int m_nIdxModel;	      //モデルのインデックス番号
	int m_nIdxTexture[5];
	const char *m_Fliename;       //モデルのXファイルの名前
};

#endif