//===========================================================
//
//ポリゴンを出すやつ[itemslot.h]
//Author 大原怜将
//
//===========================================================
#ifndef _TUTORIALLOGO_H_             //このマクロ定義がされてなかったら
#define _TUTORIALLOGO_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//アイテムクラス
class CTutoriallogo : public CObject2D
{
public:

	CTutoriallogo();                                //コンストラクタ
	CTutoriallogo(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CTutoriallogo();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CTutoriallogo *Create(D3DXVECTOR3 pos);             //生成

private:

	int m_nIdxTexture;
};

#endif