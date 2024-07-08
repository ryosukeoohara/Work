//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _CONLLISION_H_
#define _CONLLISION_H_

#include "item.h"

//=============
//前方宣言
//=============
class CEnemyWeak;
class CEnemyBoss;
class CPlayer;
class CEnemy;
class CBullet;
class CObjectX;


//コリジョンクラス
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);

	bool CollsionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy *pEnemy);  //敵との当たり判定(プレイヤー基準)
	bool CollisionBulletEnemy(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CEnemy **pEnemy);     //弾との当たり判定
	bool CollisionBulletPlayer(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CPlayer *pPlayer);  //弾との当たり判定
	bool CollisionPunch(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ);  //敵とこぶしの当たり判定
	bool CollisionCircle(D3DXVECTOR3 *pos, float fRadius, CPlayer *pPlayer);  //円の当たり判定
	bool CollisionItem(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CItem::TYPE type, CPlayer *pPlayer);    //アイテムとプレイヤーの当たり判定
	//bool Enemy(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CEnemy *pEnemy);    //アイテムとプレイヤーの当たり判定
	bool Knife(D3DXVECTOR3 *pos, D3DXVECTOR3 rot, float fRadius, CEnemy **pEnemy);
	bool kugibat(D3DXVECTOR3 *pos, CPlayer *pPlayer);    //アイテムとプレイヤーの当たり判定
	bool Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer);  //ぷれいやーとの当たり判定
	bool Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX);  //マップにある建物との当たり判定
	
private:

};
#endif // !_CONLLISION_H_