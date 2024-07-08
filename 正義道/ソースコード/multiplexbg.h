//===========================================================
//
//ポリゴンを出すやつ[multiplexbg.h]
//Author 大原怜将
//
//===========================================================
#ifndef _MULTIPLEXBG_H_             //このマクロ定義がされてなかったら
#define _MULTIPLEXBG_H_             //2重インクルード防止のマクロ定義をする

#include "object.h"

//多重背景クラス
class CMultiplexBg : public CObject
{
public:
	CMultiplexBg();  //コンストラクタ
	~CMultiplexBg();  //デストラクタ

	typedef enum
	{
		TYPETEX_00 = 0,
		TYPETEX_01,
		TYPETEX_02,
		TYPETEX_MAX
	}TYPETEX;

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void UnLoad(void);   //テクスチャの破棄

	static CMultiplexBg *Create(void);  //生成

	static float m_fTexV;
	static float m_fTexU;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPETEX_MAX];  //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    //頂点情報を格納
	static CObject2D *m_apObject2D[TYPETEX_MAX];

};


#endif