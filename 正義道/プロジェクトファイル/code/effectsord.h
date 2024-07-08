//===========================================================
//
//ポリゴンを出すやつ[effextsord.h]
//Author 大原怜将
//
//===========================================================
#ifndef _EFFECTSORD_H_
#define _EFFECTSORD_H_

#include "object3D.h"

class CEffectSword : public CObject3D
{
public:
	CEffectSword();
	CEffectSword(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CEffectSword();

	HRESULT Init(void);   //斬撃エフェクトの初期化処理    
	void Uninit(void);    //斬撃エフェクトの終了処理
	void Update(void);    //斬撃エフェクトの更新処理
	void Draw(void);      //斬撃エフェクトの描画処理

	static CEffectSword *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //生成

private:
	int m_nIdxTexture;  //テクスチャのインデックス番号
	int m_DispCounter;  //描画している時間
	D3DXCOLOR m_col;    //色

};

#endif // !_FIELD_H_