//===========================================================
//
// ランキングのロゴ処理[rankinglogo.h]
// Author 大原怜将
//
//===========================================================
#ifndef _RANKINGLOGO_H_             //このマクロ定義がされてなかったら
#define _RANKINGLOGO_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//===========================================================
// クラス定義
//===========================================================
class CRankinglogo : public CObject2D
{
public:

	CRankinglogo();                                //コンストラクタ
	CRankinglogo(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CRankinglogo();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CRankinglogo *Create(D3DXVECTOR3 pos);             //生成

private:

	int m_nIdxTexture;
};

#endif