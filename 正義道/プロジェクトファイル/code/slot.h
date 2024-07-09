//===========================================================
//
// スロット処理[slot.h]
// Author 大原怜将
//
//===========================================================
#ifndef _SLOT_H_             //このマクロ定義がされてなかったら
#define _SLOT_H_             //2重インクルード防止のマクロ定義をする

#include "itemslot.h"
#include "item.h"
#include "frame.h"

//マクロ定義
#define MAX_SLOT   (2)  //スロットの最大数

//===========================================================
// クラス定義
//===========================================================
class CSlot : public CItemSlot
{
public:

	CSlot();                                //コンストラクタ
	CSlot(D3DXVECTOR3 pos);                 //コンストラクタ(オーバーロード)
	~CSlot();                               //デストラクタ

	HRESULT Init(void);                     //ポリゴンの初期化処理    
	void Uninit(void);                      //ポリゴンの終了処理
	void Update(void);                      //ポリゴンの更新処理
	void Draw(void);                        //ポリゴンの描画処理

	static CSlot *Create(void);             //生成

	void Collision(void);
	static void Set(CItem::TYPE type);

	//CItemSlot::TYPE GetAttackType(void) { return m_type; }

private:
	struct SLOT
	{
		bool m_bUse;
		CFrame::TYPE m_type;
	};

	static LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	//static bool m_bUse[MAX_SLOT];

	static SLOT m_aSlot[MAX_SLOT];

	static CItemSlot *m_apItemSlot[MAX_SLOT];
};

#endif