//===========================================================
//
//ポリゴンを出すやつ[message.cpp]
//Author 大原怜将
//
//===========================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include "main.h"
#include "object2D.h"

#define MAX_MESSA   (3)       //表示するメッセージの最大数

typedef enum
{
	TYPEMESS_NONE = 0,  //なし
	TYPEMESS_START,     //最初
	TYPEMESS_DAMEGE,    //ダメージ
	TYPEMESS_MAX
} TYPEMESS;

//メッセージクラス
class CMessage : public CObject2D
{
public:
	CMessage();
	CMessage(D3DXVECTOR3 pos, TYPEMESS type);
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Control(void);  //制御処理
	static CMessage *Create(D3DXVECTOR3 pos, TYPEMESS type);  //生成

private:
	TYPEMESS m_nType;  //種類
	int MessaCounter;  //メッセージを表示しておく時間
	static int m_nIdx;        //インデックス番号
	static CMessage *Obj2D[MAX_MESSA];
};

#endif // !_MESSAGE_H_