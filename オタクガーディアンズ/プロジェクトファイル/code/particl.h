//===========================================================
//
//パーティクル処理[particl.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PARTICL_H__             //このマクロ定義がされてなかったら
#define _PARTICL_H__             //2重インクルード防止のマクロ定義をする

#include "billboard.h"

//マクロ定義
#define EFFECTMOVE   (5.0f)    //エフェクトの最大数



//パーティクルクラス
class CParticl : public CBillBoard
{
public:

	enum TYPEPAR
	{
		TYPEPAR_NONE = 0,  //なんもない
		TYPEPAR_BULLET,    //弾
		TYPEPAR_BLOOD,     //血液
		TYPEPAR_GROUND,    //土煙
		TYPEPAR_SMOOK,     //煙
		TYPEPAR_CIRCLE,    //円形
		TYPEPAR_MAX
	};

	CParticl();  //コンストラクタ
	CParticl(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, TYPEPAR type);  //コンストラクタ
	~CParticl();  //デストラクタ

	

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void UnLoad(void);   //テクスチャの破棄

	void ParticlMove(void);
	void Blood(void);
	void Ground(void);
	void Smook(void);
	void Circle(void);

	static CParticl *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, TYPEPAR type);  //生成
	D3DXCOLOR m_col;          //色
	float m_fRadius;          //半径(大きさ)
	int m_nLife;              //寿命(表示時間)
	D3DXVECTOR3 m_move;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャへのポインタ
	TYPEPAR m_type;

};

#endif