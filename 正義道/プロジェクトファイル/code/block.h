//===========================================================
//
//ポリゴンを出すやつ[block.h]
//Author 大原怜将
//
//===========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "object2D.h"

//マクロ定義
#define MAX_BLOCK       (128)       //ブロックの最大数
#define BLOCK_WIDTH     (50.0f)     //ブロックの幅
#define BLOCK_HEIGHT    (50.0f)     //ブロックの高さ
#define BLOCK_MOVEY     (0.5f)      //ブロックの移動量

//ブロックの種類
typedef enum
{
	BLOCKTYPE_NORMAL = 0,  //動かないブロック
	BLOCKTYPE_MOVE,        //動くブロック
} BLOCKSTATE;

//ブロッククラス
class CBlock : public CObject2D
{
public:
	CBlock();
	CBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);
	~CBlock();

	HRESULT Init(void);       //ブロックの初期化処理    
	void Uninit(void);        //ブロックの終了処理
	void Update(void);        //ブロックの更新処理
	void Draw(void);          //ブロックの描画処理

	static CBlock *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);  //生成
	static HRESULT Load(void);  //テクスチャをロード
	static void UnLoad(void);   //テクスチャを破棄

	void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
	bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);
	bool CollisionBulletBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

	static CBlock *GetBlock(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	static CObject2D *m_apObject2D[MAX_BLOCK];
	static CBlock *m_aBlock[MAX_BLOCK];         //ブロックの情報
};


#endif