//===========================================================
//
//ポリゴンを出すやつ[itemslot.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ITEMSLOT_H_             //このマクロ定義がされてなかったら
#define _ITEMSLOT_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//アイテムクラス
class CItemSlot : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_PROXIMITY = 0,   //近接
		TYPE_PROJECTILE,	  //飛び道具
		TYPE_MAX
	};

	CItemSlot();                                //コンストラクタ
	CItemSlot(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CItemSlot();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CItemSlot *Create(D3DXVECTOR3 pos);             //生成

	CItemSlot::TYPE GetAttackType(void) { return m_type; }
	void SetAttackType(TYPE type) { m_type = type; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	int m_nIdxTexture;                          //テクスチャのインデックス番号

	//CObject2D *m_apObject2D[MAX_SLOT];

	TYPE m_type;
};

#endif