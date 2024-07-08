//===========================================================
//
//ポリゴンを出すやつ[map.h]
//Author 大原怜将
//
//===========================================================
#ifndef _MAP_H_             //このマクロ定義がされてなかったら
#define _MAP_H_             //2重インクルード防止のマクロ定義をする

#include "objectX.h"

//マクロ定義
#define MAX_MODEL    (1024)

//プレイヤークラス
class CMap : public CObject
{
public:
	CMap();  //コンストラクタ
	~CMap();  //デストラクタ

	HRESULT Init(void);   //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理
	void Draw(void);      //ポリゴンの描画処理

	void ReadText(void);  //外部ファイル読み込み

	typedef struct
	{
		char m_filename[256] = {};
		int m_nIdx;                         //モデルのインデックス番号
		D3DXVECTOR3 m_pos;		            //位置
		D3DXVECTOR3 m_rot;		            //向き
		D3DXVECTOR3 m_move;		            //移動量
		D3DXVECTOR3 m_vtxMini;              //モデルの最小値
		D3DXVECTOR3 m_vtxMax;               //モデルの最大値
		LPD3DXMESH   m_pMesh;               //テクスチャへのポインタ
		LPD3DXBUFFER m_pBuffMat;            //頂点バッファへのポインタ
		DWORD m_dwNumMat;                   //マテリアルの数
		D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
		LPDIRECT3DTEXTURE9  *m_pTexture;    //テクスチャへのポインタ

		D3DXVECTOR3 GetVtxMin(void) { return m_vtxMini; }  //モデルの最小値取得
		D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }   //モデルの最大値取得

		void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
		D3DXVECTOR3 Getpos(void) { return m_pos; }

		void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
		D3DXVECTOR3 GetRot(void) { return m_rot; }

	} MODEL;

	static CObjectX **GetX(void) { return &m_apModel[0]; }   //マップモデルを取得
	int GetnNumAll(void) { return m_nNumAll; }        //総数を取得

private:
	static CObjectX *m_apModel[MAX_MODEL];  //モデル(パーツ)へのポインタ
	MODEL m_aModel[MAX_MODEL];
	D3DXVECTOR3 m_pos;                  //位置
	D3DXVECTOR3 m_rot;                  //向き
	int m_nIdx;                         //モデルのインデックス番号
	int m_nIdxModel;
	int m_nNumAll;                      //読み込んだモデルの総数
	int m_SetModel;                     //設置したモデルの総数
	int m_nSelectModel;                 //現在選択しているモデル
	char m_filename[MAX_MODEL][256] = {};
	//char m_filename[256] = {};
};

#endif