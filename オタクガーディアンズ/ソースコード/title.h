//===========================================================
//
// タイトル処理[title.h]
// Author 大原怜将
//
//===========================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "manager.h"
#include "object2D.h"

//前方宣言
class CChibi;
class CFoot;

//タイトルクラス
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitle *Create(void);

	static CChibi *GetPlayerChibi(void) { return m_PlayerChibi; }
	static CFoot *GetPlayerFoot(void) { return m_PlayerFoot; }

private:
	static CChibi *m_PlayerChibi;
	static CFoot *m_PlayerFoot;

};
#endif