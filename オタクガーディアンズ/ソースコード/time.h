//===========================================================
//
//タイマー処理[time.h]
//Author 大原怜将
//
//===========================================================
#ifndef _TIME_H_             //このマクロ定義がされてなかったら
#define _TIME_H_             //2重インクルード防止のマクロ定義をする

#include "number.h"

//マクロ定義
#define SETTIME   (2)  //時間の桁
#define TIME      (99) //ゲームの制限時間
#define INITTIME  (9)  //それぞれの桁の初期値

//タイムクラス
class CTime : public CNumber
{
public:
	CTime();  //コンストラクタ
	CTime(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CTime();  //デストラクタ

	HRESULT Init(void);      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	static CTime *Create(void);  //生成
	static HRESULT Load(void);  //
	static void UnLoad(void);
	static CTime *GetTime(void) { return m_Time; };
	static void SetTime(int nTime) { m_nTime = nTime; };
	static int Gettime(void) { return m_nTime; };
	static void TimeCounter(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_move; //移動
	static CTime *m_Time;
	static CNumber *m_apNumber[SETTIME];
	static int m_nTimerCount;
	static int m_nTime;  //時間
	int m_nIdxTexture;
};

#endif