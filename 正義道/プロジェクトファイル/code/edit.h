//===========================================================
//
//ポリゴンを出すやつ[edit.h]
//Author 大原怜将
//
//===========================================================
#ifndef _EDIT_H_
#define _EDIT_H_
#include "main.h"
#include "objectX.h"

//マクロ定義
#define MAX_MODELSET    (1028)

class CEdit
{
public:
	CEdit();
	~CEdit();

	typedef enum
	{
		MODELTYPE_BOSS = 0,
		MODELTYPE_KEN,
		MODELTYPE_MAX
	} MODELTYPE;

	typedef struct
	{
		char m_filename[128] = {};
	} MODEL;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Load(void);
	void ReadText(void);

private:
	LPDIRECT3DTEXTURE9  *m_pTexture;    //テクスチャへのポインタ
	CObjectX *m_apModel[MAX_MODELSET];  //モデル(パーツ)へのポインタ
	int m_nNumModel;  //読み込んだモデルの総数
	int m_nIdx;
	MODEL m_Model[1024];

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;

	D3DXVECTOR3 m_vtxMini;    //モデルの最小値
	D3DXVECTOR3 m_vtxMax;     //モデルの最大値
	LPD3DXMESH   m_pMesh   ;       //テクスチャへのポインタ
	LPD3DXBUFFER m_pBuffMat;  //頂点バッファへのポインタ
	DWORD m_dwNumMat;         //マテリアルの数
	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス

	char m_filename[128] = {};
};
#endif // !_EDIT_H_