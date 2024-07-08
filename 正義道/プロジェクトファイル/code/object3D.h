//=============================================================================
//
// ポリゴン処理 [object3D.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _OBJECT3D_H_             //このマクロ定義がされてなかったら
#define _OBJECT3D_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"
#include "object.h"

//オブジェクト3Dクラス
class CObject3D : public CObject
{
public:
	CObject3D();
	CObject3D(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CObject3D();

	HRESULT Init(void);   //3Dオブジェクトの初期化処理    
	void Uninit(void);    //3Dオブジェクトの終了処理
	void Update(void);    //3Dオブジェクトの更新処理
	void Draw(void);      //3Dオブジェクトの描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //テクスチャをバインド
	void SetVtxBillBoard(void);
	void SetVtxField(void);
	void SetVtxEffect(D3DXVECTOR3 pos, float m_fRadius, D3DXCOLOR col);
	void SetVtxBullet(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxEffectSword(float fWidth, float fHeight, D3DXCOLOR col);
	void SetVtxCircle(float fWidth, float fHeight, D3DXCOLOR col);
	void SetShadowPosition(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxLife(D3DXVECTOR3 pos, float fWidth, float fHeight, float fTex);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; } //位置設定
	

	D3DXVECTOR3 GetPosition(void) { return m_pos; }     //位置取得   

	static CObject3D *Create(void);  //生成
	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;    //計算用マトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;        //頂点バッファへのポインタ
//	float GetHeight(D3DXVECTOR3 pos);

private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;       //テクスチャへのポインタ
	D3DXVECTOR3 m_vec0;
	D3DXVECTOR3 m_vec1;
	D3DXVECTOR3 m_vec2;
	D3DXVECTOR3 m_vec3;
	D3DXVECTOR3 m_vecLine0;
	D3DXVECTOR3 m_vecLine1;
	D3DXVECTOR3 m_vecLine2;
	D3DXVECTOR3 m_vecLine3;
	D3DXVECTOR3 m_nor0;
	D3DXVECTOR3 m_nor1;

	D3DXVECTOR3 m_pos;
};



#endif