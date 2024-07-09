//===========================================================
//
// アイコン処理[icon.h]
// Author 大原怜将
//
//===========================================================
#ifndef _ICON_H_             //このマクロ定義がされてなかったら
#define _ICON_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//===========================================================
// クラス定義
//===========================================================
class CIcon : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //近接
		TYPE_PLAYER,	 //プレイヤー
		TYPE_MAX
	};

	CIcon();                                                      //コンストラクタ
	CIcon(D3DXVECTOR3 pos, TYPE type);                            //コンストラクタ(オーバーロード)
	~CIcon();                                                     //デストラクタ

	HRESULT Init(void);                                           //アイコンの初期化処理    
	void Uninit(void);                                            //アイコンの終了処理
	void Update(void);                                            //アイコンの更新処理
	void Draw(void);                                              //アイコンの描画処理

	static CIcon *Create(D3DXVECTOR3 pos, TYPE type);             //生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                         //テクスチャへのポインタ
	int m_nIdxTexture;                                            //テクスチャのインデックス番号

	TYPE m_type;                                                  //種類
};

#endif