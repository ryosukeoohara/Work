//=============================================================================
//
// シャドウ処理 [shadow.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _LIFE_H_             //このマクロ定義がされてなかったら
#define _LIFE_H_             //2重インクルード防止のマクロ定義をする

#include "billboard.h"

//マクロ定義
#define MAX_SHADOW   (128)   //影の最大数

class CLife : public CBillBoard
{
public:

	CLife();
	CLife(D3DXVECTOR3 pos);
	~CLife();

	typedef enum
	{
		SHADOWTYPE_PLAYER = 0,
		SHADOWTYPE_BULLET,
		SHADOWTYPE_MAX
	}SHADOWTYPE;

	//プロトタイプ宣言
	HRESULT Init(void);          //影の初期化処理    
	void Uninit(void);        //影の終了処理
	void Update(void);        //影の更新処理
	void Draw(void);          //影の描画処理
	static CLife *Create(D3DXVECTOR3 pos);

	CLife *Get(void);

	static int Set(D3DXVECTOR3 pos);
	void SetPosition(int nIdxShadow, D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;
	static CBillBoard *m_Life[MAX_SHADOW];

	CLife *m_shadow;

};

#endif