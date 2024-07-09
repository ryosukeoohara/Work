//===========================================================
//
// オブジェクト処理[object.h]
// Author 大原怜将
//
//===========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//マクロ定義
#define MAX_OBJECT    (2048)  //オブジェクトの最大数

//===========================================================
// クラス定義
//===========================================================
class CObject
{
public:		//誰でもアクセスできる

	CObject();             //コンストラクタ
	virtual ~CObject();    //デストラクタ

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,  //プレイヤー
		TYPE_ENEMY,   //敵
		TYPE_BULLET,  //弾
		TYPE_EXPLOSION, //爆発
		TYPE_EFFECT,    //エフェクト
		TYPE_PARTICL,   //パーティクル
		TYPE_ITEM,      //アイテム
		TYPE_TIME,      //時間
		TYPE_SCORE,     //スコア
		TYPE_MAX
	} TYPE;

	virtual HRESULT Init(void) = 0;   //初期化処理
	virtual void Uninit(void) = 0;    //終了処理
	virtual void Update(void) = 0;    //更新処理
	virtual void Draw(void) = 0;      //描画処理

	static void ReleaseAll(void);  //すべてを終了
	static void UpdateAll(void);   //すべてを更新
	static void DrawAll(void);     //すべてを描画
	void Release(void);

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //テクスチャをバインド
	static CObject *Getobject(int nIdx);
	int GetID(void) { return m_nID; }

	void SetType(TYPE type) { m_ntype = type;  }   //種類設定
	TYPE GetType(void) { return m_ntype; }         //種類取得

	void SetPos(D3DXVECTOR3 *pos) { m_pos = *pos; }
	D3DXVECTOR3 Getpos(void) { return m_pos; }

	void SetRot(D3DXVECTOR3 *rot) { m_rot = *rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetLife(int nLife) { m_nLife = nLife; }  //体力の設定
	int GetLife(void) { return m_nLife; }		  //体力を取得
	
	static int GetNumAll(void) { return m_nNumAll; }
	
private:	//自分だけがアクセスできる
	//LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	static CObject *m_apObjct[MAX_OBJECT];
	static int m_nNumAll;   //オブジェクトの総数
	int m_nID;  //自分自身のID
	static CObject *m_pTop;  //先頭のオブジェクトへのポインタ
	static CObject *m_pCur; //最後尾のオブジェクトへのポインタ
	static CObject *m_pSNext;
	CObject *m_pPrev;       //前のオブジェクトへのポインタ
	CObject *m_pNext;       //次のオブジェクトへのポインタ
	bool m_bDeath;          //死亡フラグ

	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_rot;  //向き
	TYPE m_ntype;        //種類
	int m_nLife; //体力

};

#endif // !1