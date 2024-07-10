//===========================================================
//
//スコア処理[score.h]
//Author 大原怜将
//
//===========================================================
#ifndef _SCORE_H_             //このマクロ定義がされてなかったら
#define _SCORE_H_             //2重インクルード防止のマクロ定義をする

#include "number.h"

//マクロ定義
#define SETSCORE   (8)   //スコアの桁

//スコアクラス
class CScore : public CNumber
{
public:
	CScore();  //コンストラクタ
	CScore(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CScore();  //デストラクタ

	HRESULT Init(void);      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	static CScore *Create(void);  //生成
	static HRESULT Load(void);  //
	static void UnLoad(void);
	CScore *GetScore(void) { return m_Score; };
	static void AddScore(int nScore);  //スコア加算

	static void SetScore(int nScore) 
	{ 
		m_nScore += nScore;
	};

	static int Getscore(void) 
	{ 
		return m_nScore; 
	};

	static void GameEndScore(void);     //ゲーム終了時に加算するスコア

protected:
	static int m_nScore;

private:
	void ControlPlayer(void);  //プレイヤーの制御
	static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
												 //LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //頂点情報を格納
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_move; //移動
	static CScore *m_Score;
	static CNumber *m_apNumber[8];
	int m_nIdxTexture;
	//int m_nScore;  //スコア
};

#endif