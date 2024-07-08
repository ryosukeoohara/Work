//===========================================================
//
//ポリゴンを出すやつ[game.h]
//Author 大原怜将
//
//===========================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"
#include "enemymanager.h"
#include "displife.h"
#include "shadow.h"
#include "life.h"

//ゲームクラス
class CGame : public CScene
{
public:
	CGame();
	CGame(CScene::MODE mode);
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	static void SetbPause(bool bpause) { m_bPause = bpause; }
	static bool GetbPause(void) { return m_bPause; }

	static CPlayer *GetPlayer(void);
	static CEnemy *GetEnemy(void);
	static CEnemyManager *GetEnemyManager(void);
	static CCollision *GetCollsion(void);
	static CMap *GetMap(void);
	static CDispLife *GetDispLife(void);
	static CShadow *GetShadow(void);
	static CLife *GetLife(void);
	static CPause *GetPause(void);

private:
	static CPlayer *m_Player;
	static CEnemy *m_Enemy;
	static CEnemyManager *m_EnemyManager;
	static CCollision *m_Collision;
	static CMap *m_Map;
	static CDispLife *m_DispLife;
	static CShadow *m_Shadow;
	static CLife *m_Life;
	static CPause *m_Pause;

	static bool m_bPause;
};

#endif // !_GAME_H_