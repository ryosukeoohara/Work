//=============================================================================
//
// シャドウ処理 [shadow.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _SHADOW_H_             //このマクロ定義がされてなかったら
#define _SHADOW_H_             //2重インクルード防止のマクロ定義をする

#include "object3D.h"

//マクロ定義
#define MAX_SHADOW   (128)   //影の最大数

class CShadow : public CObject3D
{
public:

	CShadow();
	CShadow(D3DXVECTOR3 pos);
	~CShadow();

	typedef enum
	{
		SHADOWTYPE_PLAYER = 0,
		SHADOWTYPE_BULLET,
		SHADOWTYPE_MAX
	}SHADOWTYPE;

	//プロトタイプ宣言
	HRESULT Init(void);       //影の初期化処理    
	void Uninit(void);        //影の終了処理
	void Update(void);        //影の更新処理
	void Draw(void);          //影の描画処理
	static CShadow *Create(D3DXVECTOR3 pos);

	CShadow *GetShadow(void);

	int Set(D3DXVECTOR3 pos);
	void SetPosition(int nIdxShadow, D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;
	static CObject3D *m_Shadow[MAX_SHADOW];

	CShadow *m_shadow;

};

#endif