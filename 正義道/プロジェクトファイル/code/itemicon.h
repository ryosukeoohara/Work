//===========================================================
//
// アイテムアイコン処理[itemicon.h]
// Author 大原怜将
//
//===========================================================
#ifndef _ITEMICON_H_             //このマクロ定義がされてなかったら
#define _ITEMICON_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//===========================================================
// クラス定義
//===========================================================
class CItemIcon : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_PROXIMITY = 0,   //近接
		TYPE_PROJECTILE,	  //飛び道具
		TYPE_KUGIBAT,         //釘バット
		TYPE_BOM,             //爆弾
		TYPE_MAX
	};

	CItemIcon();                                //コンストラクタ
	CItemIcon(D3DXVECTOR3 pos, TYPE type);      //コンストラクタ(オーバーロード)
	~CItemIcon();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CItemIcon *Create(D3DXVECTOR3 pos, TYPE type);             //生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	int m_nIdxTexture;                          //テクスチャのインデックス番号

	TYPE m_type;
};

#endif
