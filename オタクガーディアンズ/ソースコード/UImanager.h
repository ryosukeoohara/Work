//===========================================================
//
//UIマネージャ[UImanager.h]
//Author 大原怜将
//
//===========================================================
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*==========================================================
//インクルードファイル
//*==========================================================
#include "object2D.h"

//*==========================================================
//クラス定義
//*==========================================================
class CUIManager : CObject2D
{
public:

	//種類
	enum TYPE
	{
		TYPE_NONE = 0,                              //なんもない
		TYPE_TITLE,                                 //タイトル
		TYPE_TUTORIAL,                              //チュートリアル
		TYPE_RESULT,                                //リザルト
		TYPE_GUNGAGE,                               //銃の残弾表示
		TYPE_LIFEFOOT,                              //体力
		TYPE_LIFECHIBI,                             //体力
		TYPE_ICONFOOT,                              //デブの顔アイコン
		TYPE_ICONCHIBI,                             //チビの顔アイコン
		TYPE_MAGIC,                                 //魔法
		TYPE_TITLESELECT,                           //ゲームスタート
		TYPE_RANK,                                  //順位
		TYPE_SCORE,                                 //ランキングの上の見出し
		TYPE_PAUSEFRAME,                            //ポーズのフレーム
		TYPE_COUTINUE,                              //ゲームに戻る
		TYPE_RETRY,                                 //ゲームをやり直す
		TYPE_QUIT,                                  //タイトル画面に戻る
		TYPE_MAX							        
	};

	CUIManager();                                   //コンストラクタ
	CUIManager(D3DXVECTOR3 pos, TYPE type);         //コンストラクタ
	~CUIManager();                                  //デストラクタ

	HRESULT Init(void);                             //初期化処理
	void Uninit(void);                              //終了処理
	void Update(void);                              //更新処理
	void Draw(void);                                //描画処理

	static CUIManager *Create(D3DXVECTOR3 pos, TYPE type); //生成処理

private:
	TYPE m_type;                                    //種類
	int m_nIdxTexture;                              //テクスチャのインデックス番号
};

#endif // !_UIMANAGER_H_