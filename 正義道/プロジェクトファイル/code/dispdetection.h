//===========================================================
//
// ポリゴンを出すやつ[dispdetection.h]
// Author 大原怜将
//
//===========================================================
#ifndef _DISPDETECTION_H_             //このマクロ定義がされてなかったら
#define _DISPDETECTION_H_             //2重インクルード防止のマクロ定義をする

#include "object3D.h"

//===========================================================
// クラス定義
//===========================================================
class CDISPDETECTION : public CObject3D
{
public:

	enum TYPE
	{
		TYPE_NEAR = 0,
		TYPE_FAR,
		TYPE_MAX
	};

	CDISPDETECTION();  //コンストラクタ
	CDISPDETECTION(D3DXVECTOR3 pos);  //コンストラクタ
	~CDISPDETECTION();  //デストラクタ

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static CDISPDETECTION *Create(D3DXVECTOR3 pos);  //生成

	static CDISPDETECTION *GetFrame(void) { return m_DispDetection; }
	CDISPDETECTION::TYPE GetACType(void) { return m_type; }

private:
	static CDISPDETECTION *m_DispDetection;
	int m_nIdxTexture;

	CDISPDETECTION::TYPE m_type;
	D3DXCOLOR m_col;    //色

};

#endif