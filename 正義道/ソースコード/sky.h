//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "objectX.h"

class CSky : public CObjectX
{
public:
	CSky();                //コンストラクタ
	CSky(D3DXVECTOR3 pos); //コンストラクタ
	~CSky();               //デストラクタ

	HRESULT Init(void);    //空の初期化処理    
	void Uninit(void);     //空の終了処理
	void Update(void);     //空の更新処理
	void Draw(void);       //空の描画処理

	static CSky *Create(D3DXVECTOR3 pos);  //生成

private:
	int m_nIdxTexture;     //テクスチャのインデックス番号
	CObjectX *m_pObjectX;  //オブジェクトXへのポインタ
};

#endif // !_TEXTURE_H_