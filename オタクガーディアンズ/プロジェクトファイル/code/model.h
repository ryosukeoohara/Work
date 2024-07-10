//=============================================================================
//
// モデル処理 [model.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define MAX_MODEL  (1024)  //最大数
#define MAX_CHAR   (128)   //文字列の最大数

class CModel
{
public:

	CModel();
	~CModel();

	struct MODEL
	{
		int *m_pIdxTexture;            //テクスチャのインデックス番号
		char aName[MAX_CHAR] = "a";    //モデルのファイルネーム
		LPD3DXMESH m_pMesh;            //テクスチャへのポインタ
		LPD3DXBUFFER m_pBuffMat;       //頂点バッファへのポインタ
		DWORD m_dwNumMat;              //マテリアルの数
	};

	HRESULT Load(void);
	void UnLoad(void);

	int Regist(const char *pFilename);

	int GetNumAll(void) { return m_nNumAll; };

private:
	int m_nNumAll;                 //モデルの総数
	int m_nIdxModel;               //モデルのインデックス番号       
	MODEL *m_aModel[MAX_MODEL];    //モデルの構造体

};
#endif // !_MODEL_H_
