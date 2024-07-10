//===========================================================
//
//エフェクト処理[effect.h]
//Author 大原怜将
//
//===========================================================
#ifndef _EFFECT_H__             //このマクロ定義がされてなかったら
#define _EFFECT_H__             //2重インクルード防止のマクロ定義をする

#include "billboard.h"

//マクロ定義
#define EFFECTMOVE   (5.0f)    //エフェクトの最大数

//エフェクトクラス
class CEffect : public CBillBoard
{
public:

	enum TYPEEFF
	{
		TYPEEFF_NONE = 0,   //なんもない
		TYPEEFF_GROUND,     //土煙
		TYPEEFF_BLOOD,      //血液
		TYPEEFF_SMOOK,      //煙
		TYPEEFF_CIRCLE,     //円形
		TYPEEFF_MAX
	};

	CEffect();  //コンストラクタ
	CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPEEFF type);  //コンストラクタ
	~CEffect();  //デストラクタ

	//エフェクトの構造体
	typedef struct
	{
		D3DXVECTOR3 m_pos;        //位置
		D3DXVECTOR3 m_move;       //移動量
		D3DXCOLOR m_col;          //色
		float m_fRadius;          //半径(大きさ)
		int m_nLife;              //寿命(表示時間)
	} Effect;

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void UnLoad(void);   //テクスチャの破棄

	void Ground(void);
	void Blood(void);
	void Smook(void);
	void Circle(void);

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPEEFF type);  //生成
	D3DXCOLOR m_col;          //色
	float m_fRadius;          //半径(大きさ)
	int m_nLife;              //寿命(表示時間)
	D3DXVECTOR3 m_move;
	static Effect m_effect;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャへのポインタ
	TYPEEFF m_type;                        //種類
	int m_nIdxTexture;                     //テクスチャのインデックス番号

};

#endif