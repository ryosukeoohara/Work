//===========================================================
//
//ポリゴンを出すやつ[number.h]
//Author 大原怜将
//
//===========================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"

//ナンバークラス
class CNumber : public CObject2D 
{
public:		//誰でもアクセスできる
	CNumber();  //コンストラクタ
	CNumber(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CNumber(); //デストラクタ

	typedef enum
	{
		TYPENUMBER_NONE = 0,
		TYPENUMBER_TIME,              //時間
		TYPENUMBER_SCORE,             //スコア
		TYPENUMBER_DESTROYCOUNTER,    //敵を倒した数
		TYPENUMBER_MAX
	} TYPENUMBER;

	HRESULT Init(void);   //初期化処理
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	void SetPosition(D3DXVECTOR3 pos); //位置設定
	D3DXVECTOR3 GetPosition(void);     //位置取得   

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //テクスチャをバインド
	void UpdateTime(int m_nTime);  //時間の更新
	void UpdateScore(void);  //スコア加算

	void SetVtxCounter(D3DXVECTOR3 pos, float fWidth, float fHeight);

	void SetNumberType(TYPENUMBER type) { m_ntype = type;};

	TYPENUMBER GetNumberType(void) { return m_ntype; };

	void SetNumber(int nNumber);
	int GetNumber(void) { return m_Number; };

	static CNumber *Create(D3DXVECTOR3 pos);  //生成
	int m_Number;

private:	//自分だけがアクセスできる
	LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点情報を格納
	D3DXVECTOR3 m_pos;  //位置
	TYPENUMBER m_ntype; //種類
	static CObject2D *m_apObject2D;
	int m_nTimerCount;                          //時間のカウンター
	int m_nIdxTexture;                          //テクスチャのインデックス番号

};

#endif // !1