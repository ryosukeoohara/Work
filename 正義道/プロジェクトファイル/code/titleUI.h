//===============================================================
//
// タイトルUI処理[titleUI.h]
// Author 大原怜将
//
//===============================================================
#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "object2D.h"

#define MAX_TUTOOBJ     (8)

//===========================================================
// クラス定義
//===========================================================
class CTitleUI : public CObject2D
{
public:
	CTitleUI();
	~CTitleUI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleUI *Create(D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;                          //テクスチャのインデックス番号
	int m_nCntMove;                             //再び移動し始めるまでのカウント
	float m_colA;                               //透明度
	TYPE m_type;                                //種類
	D3DXCOLOR m_col;                            //色
};

#endif