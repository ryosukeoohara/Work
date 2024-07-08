//===========================================================
//
//ポリゴンを出すやつ[bg.h]
//Author 大原怜将
//
//===========================================================
#ifndef _FRAME_H_             //このマクロ定義がされてなかったら
#define _FRAME_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"
#include "itemslot.h"

//背景クラス
class CFrame : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,    //なし
		TYPE_NEAR,        //近距離
		TYPE_FAR,         //遠距離
		TYPE_BAT,         //バット
		TYPE_BOM,         //爆弾
		TYPE_MAX
	};

	CFrame();  //コンストラクタ
	CFrame(D3DXVECTOR3 pos);  //コンストラクタ
	~CFrame();  //デストラクタ

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static CFrame *Create(void);  //生成

	static CFrame *GetFrame(void) { return m_Frame; }
	void SetACType(CFrame::TYPE type) { m_type = type; }
	CFrame::TYPE GetACType(void) { return m_type; }

private:
	static CFrame *m_Frame;
	int m_nIdxTexture;

	CFrame::TYPE m_type;
};

#endif