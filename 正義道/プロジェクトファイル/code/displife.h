//===========================================================
//
// ポリゴンを出すやつ[displife.h]
// Author 大原怜将
//
//===========================================================
#ifndef _DISPLIFE_H_             //このマクロ定義がされてなかったら
#define _DISPLIFE_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//マクロ定義
#define MAX_DISPLIFE   (64)

//===============================================================
// クラス定義
//===============================================================
class CDispLife : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //近接
		TYPE_PLAYER,	 //プレイヤー
		TYPE_MAX
	};

	CDispLife();                                                  //コンストラクタ
	CDispLife(D3DXVECTOR3 pos);                                   //コンストラクタ(オーバーロード)
	~CDispLife();                                                 //デストラクタ

	HRESULT Init(void);                                           //アイコンの初期化処理    
	void Uninit(void);                                            //アイコンの終了処理
	void Update(void);                                            //アイコンの更新処理
	void Draw(void);                                              //アイコンの描画処理

	static CDispLife *Create(D3DXVECTOR3 pos);                    //生成
	int SetDispLife(void);
	//CDispLife *GetDispLife(void) { return m_pDispLife; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                         //テクスチャへのポインタ
	int m_nIdxTexture;                                            //テクスチャのインデックス番号
	int m_nMaxLife;

	TYPE m_type;                                                  //種類

	//static CDispLife *m_pDispLife;                                
	static CObject2D *m_apObject2D[MAX_DISPLIFE];                   //2Dオブジェクトへのポインタ                  
};

#endif