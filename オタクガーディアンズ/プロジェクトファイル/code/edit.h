//===========================================================
//
//エディット処理[edit.h]
//Author 大原怜将
//
//===========================================================
#ifndef _EDIT_H_
#define _EDIT_H_
#include "main.h"
#include "objectX.h"

//マクロ定義
#define MAX_MODELSET    (1024)

class CEdit : public CObject
{
public:
	CEdit();
	~CEdit();

	typedef enum
	{
		MODE_CREATE = 0,
		MODE_DELETE,
		MODE_MAX
	} MODE;

	

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void XLoad(void);
	void TEXTLoad(void);
	void ReadText(void);

	void Control(void);
	void SetModelDelete(void);

private:

	struct MODEL
	{
		char m_filename[256] = {};
		int m_nType;
		D3DXVECTOR3 m_pos;		  //位置
		D3DXVECTOR3 m_rot;		  //向き
		D3DXVECTOR3 m_move;		  //移動量
		D3DXVECTOR3 m_vtxMini;    //モデルの最小値
		D3DXVECTOR3 m_vtxMax;     //モデルの最大値
		LPD3DXMESH   m_pMesh;       //テクスチャへのポインタ
		LPD3DXBUFFER m_pBuffMat;  //頂点バッファへのポインタ
		DWORD m_dwNumMat;         //マテリアルの数
		D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
		LPDIRECT3DTEXTURE9* m_pTexture;    //テクスチャへのポインタ

	};

	CObjectX *m_apModel[MAX_MODELSET];  //モデル(パーツ)へのポインタ
	MODEL m_Model[MAX_MODELSET];
	MODE m_mode;
	D3DXVECTOR3 m_pos;   //位置
	D3DXVECTOR3 m_rot;   //向き
	int m_nIdx;          //モデルのインデックス番号
	int m_nNumAll;       //読み込んだモデルの総数
	int m_SetModel;      //設置したモデルの総数
	int m_nSelectModel;  //現在選択しているモデル
};

#endif // !_EDIT_H_