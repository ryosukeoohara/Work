//===========================================================
//
//ポリゴンを出すやつ[title.h]
//Author 大原怜将
//
//===========================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "manager.h"
#include "object2D.h"

//リザルトクラス
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult *Create(void);

private:
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	CObject2D *m_apObject2D;

};
#endif // !_TITLE_H_