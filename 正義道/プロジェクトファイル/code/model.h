//=============================================================================
//
// モデル処理 [model.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "objectX.h"

//マクロ定義
#define MAX_MODEL   (1024)   //テクスチャの最大数

//===========================================================
// クラス定義
//===========================================================
class CModel
{
public:
	CModel();
	~CModel();

	//テクスチャの種類
	typedef enum
	{
		TYPE_PLAYER = 0,  //プレイヤー
		TYPE_ENEMY,       //敵
		TYPE_BULLET,      //弾
		TYPE_MAX
	} TYPE;

	const char *c_apFilename[TYPE_MAX] =
	{
		"data\\TEXTURE\\niwatori.png",
		"data\\TEXTURE\\003.png",
		"data\\TEXTURE\\000.png"
	};

	struct MODEL
	{
		char aName[64] = "a";
		CObjectX *m_aModel;  //モデル(パーツ)へのポインタ
	};

	//typedef struct
	//{
	//	D3DXVECTOR3 m_pos;
	//	D3DXVECTOR3 m_posOrigin;
	//	D3DXVECTOR3 m_rot;
	//	D3DXVECTOR3 m_rotOrigin;
	//	D3DXVECTOR3 m_vtxMini;    //モデルの最小値
	//	D3DXVECTOR3 m_vtxMax;     //モデルの最大値
	//	LPD3DXMESH m_pMesh;       //テクスチャへのポインタ
	//	LPD3DXBUFFER m_pBuffMat;  //頂点バッファへのポインタ
	//	DWORD m_dwNumMat;         //マテリアルの数
	//	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス

	//} MODEL;

	HRESULT Load(void);
	void UnLoad(void);

	int Regist(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);
	CObjectX GetAddress(int nIdx);

	int GetNumTexture(void) { return m_nNumAll; };

private:
	LPDIRECT3DTEXTURE9  *m_pTexture;     //テクスチャへのポインタ
	static int m_nNumAll;
	
	MODEL m_aModel[MAX_MODEL];
};

#endif // !_TEXTURE_H_