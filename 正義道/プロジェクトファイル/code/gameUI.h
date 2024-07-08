//===============================================================
//
//チュートリアルUI処理[tutorialUI.h]
// Author 大原怜将
//
//===============================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "object2D.h"

#define MAX_TUTOOBJ     (8)

class CGameUI : public CObject2D
{
public:
	CGameUI();
	~CGameUI();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_AIM00,
		TYPE_AIM01,
		TYPE_AIM02,
		TYPE_AIM03,
		TYPE_LESSON01,
		TYPE_LESSON02,
		TYPE_LESSON03,
		TYPE_LESSON04,
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,     //何もない
		STATE_MOVE,         //移動
		STATE_STOP,         //チョット止まる
		STATE_MAX
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGameUI *Create(D3DXVECTOR3 pos, TYPE type);

	static CGameUI *GetUI(void) { return m_pGameUI; }
	TYPE GetTypeUI(void) { return m_type; }
	STATE GetState(void) { return m_state; }

private:
	static CGameUI *m_pGameUI;
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	int m_nCntMove;                             //再び移動し始めるまでのカウント
	TYPE m_type;                                //種類
	STATE m_state;                              //状態
};

#endif