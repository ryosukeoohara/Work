//=============================================================================
//
// ライト処理 [light.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _LIGHT_H_             //このマクロ定義がされてなかったら
#define _LIGHT_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"

//マクロ定義
#define MAX_LIGHT     (3)

//ライトクラス
class CLight
{
public:
	CLight();
	~CLight();

	//プロトタイプ宣言
	void Init(void);          //ライトの初期化処理    
	void Uninit(void);        //ライトの終了処理
	void Update(void);        //ライトの更新処理

private:
	//D3DLIGHT9 m_light;    //カメラの情報
						  
	D3DLIGHT9 m_light[MAX_LIGHT];     //カメラの情報
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];  //設定用方向ベクトル

};


#endif