//===========================================================
//
//マップ処理[map.h]
//Author 大原怜将
//
//===========================================================
#ifndef _MAP_H_             //このマクロ定義がされてなかったら
#define _MAP_H_             //2重インクルード防止のマクロ定義をする

#include "objectX.h"

//マクロ定義
#define MAX_MODEL    (1024)
#define MAX_CHAR     (256)

//プレイヤークラス
class CMap
{
public:
	CMap();  //コンストラクタ
	~CMap();  //デストラクタ

	HRESULT Init(void);   //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	void ReadText(void);  //外部ファイル読み込み

	static CMap *Create(void);

	CObjectX **GetX(void) { return &m_apModel[0]; }   //マップモデルを取得
	int GetnNumAll(void) { return m_nNumAll; }        //総数を取得

private:
	CObjectX *m_apModel[MAX_MODEL];          //モデル(パーツ)へのポインタ
	int m_nIdx;                              //モデルのインデックス番号
	int m_nNumAll;                           //読み込んだモデルの総数
	char m_filename[MAX_MODEL][MAX_CHAR] = {};    //文字列読み込み
};

#endif