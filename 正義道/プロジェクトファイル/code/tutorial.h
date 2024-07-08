//===============================================================
//
//チュートリアル処理[tutorial.h]
// Author 大原怜将
//
//===============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "manager.h"

class CTutorial : public CScene
{
public:

	CTutorial();
	~CTutorial();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_LESSON01,
		TYPE_LESSON02,
		TYPE_LESSON03,
		TYPE_LESSON04,
		TYPE_LESSON05,
		TYPE_LESSON06,
		TYPE_MAX
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial *Create(void);
	static CPlayer *GetPlayer(void);
	static TYPE GetLesson(void) { return m_type; }
	static bool GetEndlesson(void) { return m_bEndlesson; }
	static void SetEndlesson(bool m_bEnd) { m_bEndlesson = m_bEnd; }

private:

	static CPlayer *m_Player;
	static TYPE m_type;
	static bool m_bEndlesson;
	bool m_bCrateUI;
};

#endif 