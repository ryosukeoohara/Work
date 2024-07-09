//===========================================================
//
// ビルボード処理 [billboard.h]
// Author : 大原　怜将
//
//===========================================================
#ifndef _BILLBOARD_H_             // このマクロ定義がされてなかったら
#define _BILLBOARD_H_             // 2重インクルード防止のマクロ定義をする

#include "object3D.h"

//===========================================================
// クラス定義
//===========================================================
class CBillBoard : public CObject3D
{
public:
	CBillBoard();
	~CBillBoard();

	HRESULT Init(void);  // 初期化処理    
	void Uninit(void);   // 終了処理
	void Update(void);   // 更新処理
	void Draw(void);     // 描画処理

	static CBillBoard *Create(void);  // 生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;       // テクスチャへのポインタ
	D3DXMATRIX m_mtxView;
};


#endif