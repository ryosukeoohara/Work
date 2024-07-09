//===========================================================
//
// 目標UI処理[target.h]
// Author 大原怜将
//
//===========================================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "manager.h"
#include "object2D.h"
#include "number.h"

//マクロ定義
#define MAX_TITLEOBJ   (64)   //タイトル内での2Dオブジェクトの最大数
#define MAX_NUMBER     (2)

//===========================================================
// クラス定義
//===========================================================
class CTarget : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_FIRST,     //一つ目の目標
		TYPE_SECOND,    //二つ目の目標
		TYPE_FINAL,     //最後の目標
		TYPE_MAX
	};

	CTarget();
	CTarget(TYPE type, D3DXVECTOR3 pos);
	~CTarget();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTarget *Create(TYPE type, D3DXVECTOR3 pos);

	static void SetType(TYPE type) { m_type = type; }

private:
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	static TYPE m_type;                                //種類
	static CNumber *m_apNumber[MAX_NUMBER];		  //ナンバーへのポインタ
	static CNumber *m_apNumCount[MAX_NUMBER];     //ナンバーへのポインタ

};
#endif // !_TITLE_H_