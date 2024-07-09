//===========================================================
//
// タイトルロゴ処理[titlelogo.h]
// Author 大原怜将
//
//===========================================================
#ifndef _TITLELOGO_H_             //このマクロ定義がされてなかったら
#define _TITLELOGO_H_             //2重インクルード防止のマクロ定義をする

#include "itemslot.h"

//マクロ定義
#define MAX_SLOT   (7)  //スロットの最大数

//===========================================================
// クラス定義
//===========================================================
class CTitlelogo : public CObject2D
{
public:

	CTitlelogo();                                //コンストラクタ
	CTitlelogo(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CTitlelogo();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CTitlelogo *Create(D3DXVECTOR3 pos);             //生成

private:
	
	int m_nIdxTexture;
};

#endif