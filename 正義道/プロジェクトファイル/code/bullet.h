//===========================================================
//
// バレット処理[bullet.h]
// Author 大原怜将
//
//===========================================================
#ifndef _BULLET_H_             //このマクロ定義がされてなかったら
#define _BULLET_H_             //2重インクルード防止のマクロ定義をする

#include "billboard.h"

//===========================================================
// クラス定義
//===========================================================
class CBullet : public CBillBoard
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,  // 何もない
		TYPE_PLAYER,    // プレイヤー
		TYPE_ENEMY,     // 敵
		TYPE_BOM,       // 爆弾
		TYPE_MAX
	};

	CBullet();                                             // コンストラクタ
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);  // コンストラクタ(オーバーロード)
	~CBullet();                                            // デストラクタ

	HRESULT Init(void);                                    // 初期化処理    
	void Uninit(void);                                     // 終了処理
	void Update(void);                                     // 更新処理
	void Draw(void);                                       // 描画処理

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);  // 生成
	static CBullet *GetBullet(void) { return m_Bullet; };                 // 弾を取得
	void SetLife(int nLife) { m_nLife = nLife; }                          // 寿命取得
	int GetLife(void) { return m_nLife; }                                 // 寿命設定

private:
	D3DXVECTOR3 m_move;                                                   // 移動
	D3DXVECTOR3 m_posOld;                                                 // 前回の位置
	int m_nLife;                                                          // 寿命
	int m_nIdxTexture;                                                    // テクスチャの番号
	TYPE m_type;                                                          // 種類
	static CBullet *m_Bullet;
};

#endif