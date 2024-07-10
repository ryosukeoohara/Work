//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _CONLLISION_H_
#define _CONLLISION_H_

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

	bool Enemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy **pEnemy);  //敵との当たり判定(プレイヤー基準)
	bool BulletEnemy(D3DXVECTOR3 *pos, float fWidthX, float fWidthY, CEnemy **pEnemy);     //弾との当たり判定
	bool BulletPlayer(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CPlayer *pPlayer);  //弾との当たり判定
	bool BulletMap(D3DXVECTOR3 *pos, CObjectX **pObjectX);       //弾と建物の当たり判定
	bool Circle(D3DXVECTOR3 *pos, float fRadius, CPlayer *pPlayer);  //円の当たり判定
	bool Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer);  //ぷれいやーとの当たり判定
	void Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX);  //マップにある建物との当たり判定
	bool Block(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ);  //ブロックとの判定
	bool Sword(D3DXMATRIX pos, D3DXMATRIX matrix, float flength, CEnemy **pEnemy);
	void MapEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX, CEnemy *enemy);  //マップにある建物との当たり判定
	
private:

};
#endif // !_CONLLISION_H_