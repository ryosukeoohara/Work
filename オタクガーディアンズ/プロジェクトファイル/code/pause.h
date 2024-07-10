//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _PAUSE_H_             //このマクロ定義がされてなかったら
#define _PAUSE_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"

//マクロ定義
#define MAX_PAUSEOBJ   (5)

class CPause
{
public:
	CPause();                                  //コンストラクタ
	~CPause();                                 //デストラクタ
								               
	//ポーズメニュー				            
	typedef enum				               
	{
		MENU_BACK = 0, 
		MENU_FRAME,
		MENU_COUTINUE,                         //ゲームに戻る
		MENU_RETRY,                            //ゲームをやり直す
		MENU_QUIT,                             //タイトル画面に戻る
		MENU_MAX			               
	} PAUSE_MENU;	

	struct COL
	{
		D3DXCOLOR col;
	};

	//構造体
	struct PAUSE
	{
		CObject2D *pBackGround;   //一番後ろに出す黒い背景
		CObject2D *pFrame;        //ポーズのフレーム
		CObject2D *pContinue;     //続ける
		CObject2D *pReStart;      //やり直す
		CObject2D *pTitleBack;    //タイトルに戻る
		
	};

	HRESULT Init(void);                        //ポーズ初期化処理    
	void Uninit(void);                         //ポーズ終了処理
	void Update(void);                         //ポーズ更新処理
	void Draw(void);                           //ポーズ描画処理
							                   
private:					                   
	//int m_nIdxTexture[MAX_PAUSEOBJ];           //テクスチャのインデックス番号

	CObject2D *m_Object2D[MAX_PAUSEOBJ];       //オブジェクト2Dへのポインタ
	PAUSE m_Pause;                             //ポーズの構造体
	PAUSE_MENU m_pauseMenu;                    //ポーズメニュー
	COL m_Color[5];
	bool m_bPause;                             //ポーズ中かどうか

};

#endif