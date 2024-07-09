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

//マクロ定義
#define MAX_TITLEOBJ   (64)   //タイトル内での2Dオブジェクトの最大数

//===========================================================
// クラス定義
//===========================================================
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

private:
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	CObject2D *m_apObject2D[MAX_TITLEOBJ];      //2Dオブジェクトへのポインタ
	CObject3D *m_apObject3D[MAX_TITLEOBJ];      //3Dオブジェクトへのポインタ

};
#endif // !_TITLE_H_