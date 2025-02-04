//===========================================================
//
//ポリゴンを出すやつ[bg.h]
//Author 大原怜将
//
//===========================================================
#ifndef _BG_H_             //このマクロ定義がされてなかったら
#define _BG_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//背景クラス
class CBg : public CObject2D
{
public:
	CBg();  //コンストラクタ
	~CBg();  //デストラクタ

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void UnLoad(void);   //テクスチャの破棄

	static CBg *Create(void);  //生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    //頂点情報を格納
};

#endif