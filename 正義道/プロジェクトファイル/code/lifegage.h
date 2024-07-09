//===========================================================
//
// ライフゲージ処理[lifegage.h]
// Author 大原怜将
//
//===========================================================
#ifndef _LIFEGAGE_H_             //このマクロ定義がされてなかったら
#define _LIFEGAGE_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//===========================================================
// クラス定義
//===========================================================
class CLifegage : public CObject2D
{
public:

	CLifegage();                                //コンストラクタ
	CLifegage(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CLifegage();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CLifegage *Create(D3DXVECTOR3 pos);             //生成

private:
	int m_nIdxTexture;
};

#endif