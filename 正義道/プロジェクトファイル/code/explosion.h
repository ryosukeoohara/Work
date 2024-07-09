//===========================================================
//
// ポリゴンを出すやつ[explosion.h]
// Author 大原怜将
//
//===========================================================
#ifndef _EXPLOSION_H_             //このマクロ定義がされてなかったら
#define _EXPLOSION_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//マクロ定義
#define EXPLOSIONPOS   (80.0f)   //爆発の位置
#define EXPLOSIONLIFE  (50)      //爆発の寿命

//===========================================================
// クラス定義
//===========================================================
class CExplosion : public CObject2D
{
public:
	CExplosion();  //コンストラクタ
	CExplosion(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CExplosion();  //デストラクタ

	HRESULT Init();      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	static CExplosion *Create(D3DXVECTOR3 pos);  //生成
	static HRESULT Load(void);  //テクスチャを生成(読み込み)
	static void UnLoad(void);   //テクスチャを破棄
	static CExplosion *GetExplosion(void) { return m_Explosion; };  //爆発の取得

private:
	//void ControlPlayer(void);  //プレイヤーの制御
	static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	D3DXVECTOR3 m_move; //移動
	int m_nLife;  //寿命
	static CExplosion *m_Explosion;
};

#endif