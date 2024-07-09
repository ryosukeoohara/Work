//===========================================================
//
// エネミーマネージャ処理[enemymanager.h]
// Author 大原怜将
//
//===========================================================
#ifndef _ENEMYMANAGER_H_       //このマクロ定義がされてなかったら
#define _ENEMYMANAGER_H_       //2重インクルード防止のマクロ定義をする

#include "main.h"

//===============================================================
// クラス定義
//===============================================================
class CEnemyManager
{
public:
	CEnemyManager();  //コンストラクタ
	~CEnemyManager();  //デストラクタ

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static int GetCounter(void) { return m_DieCounter; }
	static void SetCounter(int nCounter) { m_DieCounter = nCounter; }

	static int GetNumEneWeak(void) { return m_nNumEneWeakCounter; }
	static void SetNumEneWeak(int nCounter) { m_nNumEneWeakCounter = nCounter; }

	static int GetNumEneMedBoss(void) { return m_nNumEneMedBossCounter; }
	static void SetNumEneMedBoss(int nCounter) { m_nNumEneMedBossCounter = nCounter; }

	static int GetNumEneBoss(void) { return m_nNumEneBossCounter; }
	static void SetNumEneBoss(int nCounter) 
	{ 
		m_nNumEneBossCounter = nCounter;
	}

	static int GetNumAll(void) { return m_nNumAll; }
	static void SetNumAll(int NumAll) { m_nNumAll = NumAll; }

	static int GetIdx(void) { return m_nIdx; }
	static void SetIdx(int nidx) { m_nIdx = nidx; }

private:
	static int m_DieCounter;
	static int m_nNumEneWeakCounter;
	static int m_nNumEneMedBossCounter;
	static int m_nNumEneBossCounter;
	static int m_nNumAll;
	static int m_nIdx;  //敵の番号
	bool m_bAppearExecutive;
	bool m_bAppearBoss;

};

#endif