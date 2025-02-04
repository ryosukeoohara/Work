//===========================================================
//
//体力処理[life.h]
//Author 大原怜将
//
//===========================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "object2D.h"
#include "UImanager.h"

class CLife : CObject2D
{
public:
	CLife();
	~CLife();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(void);

private:
	CUIManager *m_pUI;

};

#endif // !_LIFE_H_

