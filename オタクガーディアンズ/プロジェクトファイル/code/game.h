//===========================================================
//
//ゲーム処理[game.h]
//Author 大原怜将
//
//===========================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"

//前方宣言
class CChibi;
class CFoot;
class CEnemyManager;

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

	static CChibi *GetPlayerChibi(void);
	static CFoot *GetPlayerFoot(void);
	static CPlayer *GetPlayer(void);
	static CEnemy *GetEnemy(void);
	static CCollision *GetCollsion(void);
	static CMap *GetMap(void);
	static CPause *GetPause(void);
	static CEdit *GetEdit(void);
	static CEnemyManager * GetEnemyManager(void);

	static void SetCounter(int nCounter) { m_nCounter = nCounter; }
	static int GetCounter(void) { return m_nCounter; }

private:
	static CChibi *m_PlayerChibi;
	static CFoot *m_PlayerFoot;
	static CPlayer *m_Player;
	static CEnemy *m_Enemy;
	static CCollision *m_Collision;
	static CMap *m_Map;
	static CPause *m_Pause;
	static CEdit *m_Edit;
	static CEnemyManager *m_EnemyManager;

	static bool m_bPause;
	bool m_bUse;  //エディットモード中かどうか
	static int m_nCounter;
};

#endif // !_GAME_H_