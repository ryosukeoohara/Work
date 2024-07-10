//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _CAMERA_H_             //このマクロ定義がされてなかったら
#define _CAMERA_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"

//カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_TITLE,      //タイトルのカメラ
		TYPE_GAME,       //ゲームのカメラ
		TYPE_RESULT,     //リザルトのカメラ
		TYPE_EDIT,       //エディットのカメラ
		TYPE_MAX 
	};

	void Init(void);          //カメラの初期化処理    
	void Uninit(void);        //カメラの終了処理
	void Update(void);        //カメラの更新処理
	void CameraV(void);
	void Edit(void);          //エディットのカメラ
	void CameraR(void);
	void Title(void);
	void Scope(void);
	void SetCamera(void);

	void Boss(void);

	void SetRot(D3DXVECTOR3 Rot) { m_rot = Rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

private:
	D3DXMATRIX m_mtxView;        //ビューマトリックス
	D3DXMATRIX m_mtxProjection;  //プロジェクションマトリックス

	D3DXVECTOR3 m_posV;    //視点
	D3DXVECTOR3 m_posR;    //注視点
	D3DXVECTOR3 m_posU;    //上方向ベクトル

	D3DXVECTOR3 m_posVDest;  //目的の視点
	D3DXVECTOR3 m_posRDest;  //目的の注視点

	D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_move; //移動

	TYPE m_type;

	int m_nCounter;     //カメラが切り替わっている時間
};



#endif
