//===========================================================
//
// 衝撃波[impact.h]
// Author 大原怜将
//
//===========================================================
#ifndef _IMPACT_H_             //このマクロ定義がされてなかったら
#define _IMPACT_H_             //2重インクルード防止のマクロ定義をする

#include "object3D.h"

//===========================================================
// クラス定義
//===========================================================
class CImpact : public CObject3D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //近接
		TYPE_MAX
	};

	CImpact();                                //コンストラクタ
	CImpact(D3DXVECTOR3 pos, TYPE type);      //コンストラクタ(オーバーロード)
	~CImpact();                               //デストラクタ

	HRESULT Init(void);                         //ポリゴンの初期化処理    
	void Uninit(void);                          //ポリゴンの終了処理
	void Update(void);                          //ポリゴンの更新処理
	void Draw(void);                            //ポリゴンの描画処理

	static CImpact *Create(D3DXVECTOR3 pos, TYPE type);             //生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	TYPE m_type;                                //種類

	float m_SizeX;		                        //Xのおおきさ
	float m_SizeZ;		                        //Zのおおきさ
};

#endif