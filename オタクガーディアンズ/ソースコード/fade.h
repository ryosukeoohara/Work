//=============================================================================
//
// フェード処理 [fade.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _FADE_H_             //このマクロ定義がされてなかったら
#define _FADE_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"
#include "manager.h"

class CFade
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX

	}FADE;

	CFade();                                   //コンストラクタ
	CFade(CScene::MODE modenext);              //コンストラクタ
	~CFade();                                  //デストラクタ

	HRESULT Init(void);                        //初期化処理
	void Uninit(void);                         //終了処理
	void Update(void);                         //更新処理
	void Draw(void);                           //描画処理
	void Set(CScene::MODE modenext);           //設定処理
	FADE Get(void) { return m_fade; }          //取得処理

	static CFade *Create(CScene::MODE modenext);                //生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;              //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         //頂点情報を格納
	FADE m_fade;                                //フェードの状態
	CScene::MODE m_modeNext;                    //次の画面
	D3DXCOLOR m_Color;                          //ポリゴンの色
							                    
	int m_nIdxTexture;                          //テクスチャのインデックス番号
};

#endif