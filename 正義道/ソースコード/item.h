//===========================================================
//
//ポリゴンを出すやつ[item.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ITEM_H_             //このマクロ定義がされてなかったら
#define _ITEM_H_             //2重インクルード防止のマクロ定義をする

#include "objectX.h"



//アイテムクラス
class CItem : public CObject
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NEAR,      //近距離
		TYPE_FAR,       //遠距離
		TYPE_NAILBAT,   //釘バット
		TYPE_BOM,       //爆弾
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		STATE_NONE = 0,
		STATE_FALL,
		STATE_LAND,
		STATE_MAX
	} STATE;

	CItem();  //コンストラクタ
	CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //コンストラクタ(オーバーロード)
	~CItem();  //デストラクタ

	HRESULT Init(void);      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	static CItem *Create(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //生成
	//static HRESULT Load(void);  //テクスチャの生成(読み込み)
	//static void UnLoad(void);   //テクスチャの破棄
	static CItem *GetItem(void) { return m_Item; };  //弾を取得
	void SetState(STATE state) { m_state = state; }

private:
	//static LPDIRECT3DTEXTURE9 m_pTexture[ITEMTYPE_MAX];        //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_move; //移動
	int m_nLife;  //寿命
	const char *m_aFilename;  //Xファイルの名前
	CObjectX *m_apModel[128];  //モデル(パーツ)へのポインタ
	TYPE m_ItemType;
	static CItem *m_Item;
	int m_Indx;
	STATE m_state;

	bool CollisionItem(D3DXVECTOR3 pos);  //敵との当たり判定
};

#endif