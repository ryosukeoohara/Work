//===========================================================
//
//ポリゴンを出すやつ[field.h]
//Author 大原怜将
//
//===========================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "object3D.h"

//マクロ定義
#define MAX_WALL   (4)

class CWall : public CObject3D
{
public:
	CWall();
	~CWall();

	HRESULT Init(void);   //フィールドの初期化処理    
	void Uninit(void);    //フィールドの終了処理
	void Update(void);    //フィールドの更新処理
	void Draw(void);      //フィールドの描画処理

	static CWall *Create(void);  //生成

private:
	int m_nIdxTexture;  //テクスチャのインデックス番号
	CObject3D *m_Object3D[MAX_WALL];    //3Dオブジェクトへのポインタ

};
#endif // !_FIELD_H_