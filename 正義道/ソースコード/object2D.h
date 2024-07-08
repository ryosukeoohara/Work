//===========================================================
//
//ポリゴンを出すやつ[object2D.h]
//Author 大原怜将
//
//===========================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"


//オブジェクト2Dクラス
class CObject2D : public CObject
{
public:		//誰でもアクセスできる
	CObject2D();  //コンストラクタ
	CObject2D(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CObject2D(); //デストラクタ

	//typedef enum
	//{
	//	TYPE_PLAYER = 0,  //プレイヤー
	//	TYPE_BULLET,      //弾
	//} TYPE;

	HRESULT Init(void);   //初期化処理
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CObject2D *Create(D3DXVECTOR3 pos);  //生成

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //テクスチャをバインド
	void SetVtxEffect(D3DXVECTOR3 pos, float m_fRadius ,D3DXCOLOR col);
	void SetVtxBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxBullet(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxItem(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxNumber(D3DXVECTOR3 pos, float fWidth, float fHeight, int m_nNumber);
	void SetVtxBg(void);
	void SetVtxMessage(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxFrame(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxItemSlot(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxTitleLogo(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxEffectLine(void);
	void SetVtxLifeGage(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxIcon(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxLife(D3DXVECTOR3 pos, float fWidth, float fHeight, float fTex);
	void SetVtxFade(D3DXCOLOR col);
	void SetVtxTarget(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetVtxPause(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);
	void SetVtxUI(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);
	void SetVtxRanking(int Tex);
	int GetIdxTex(void) { return m_nIdxTexture;	}
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }

	//CItemSlot:: GetAttackType()

protected:

	//int m_nIdxTexture;

private:	//自分だけがアクセスできる
	//LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点情報を格納
	int m_nIdxTexture;
	int m_nCounterAnimPlayer = 0;     //カウンターを初期化する
	int m_nPatternAnimPlayer = 0;     //パターンNo.を初期化する

};

#endif // !1