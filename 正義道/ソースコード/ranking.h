//===========================================================
//
//ポリゴンを出すやつ[ranking.h]
//Author 大原怜将
//
//===========================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "object2D.h"

//マクロ定義
#define MAX_RANK        (5)     //ランクの数
#define MAX_SCORE       (8)     //スコアの桁数

class CRanking : public CObject2D
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(void);             //初期化処理
	void Uninit(void);              //終了処理
	void Update(void);              //更新処理
	void Draw(void);                //描画処理
	static CRanking *Create(void);  //生成

	void ResetRanking(void);        //リセット処理
	static void SetRanking(int nScore);    //ランキング設定

	void SaveData(void);            //ランキング保存
	void LoadData(void);            //ランキング読み込み

private:
	CObject2D *m_apObject2D[MAX_RANK][MAX_SCORE];  //オブジェクト2Dのポインタ
												   //CObject2D *m_apScoreObj[MAX_SCORE];
	int m_nIdxTexture;                             //テクスチャのインデックス番号
	static int m_nScore[MAX_RANK];
};

#endif // !_RANKING_H_