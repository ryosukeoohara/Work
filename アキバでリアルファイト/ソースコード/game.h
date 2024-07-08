//===========================================================
//
//�|���S�����o�����[game.h]
//Author �匴�叫
//
//===========================================================
#ifndef _GAME_H_
#define _GAME_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "manager.h"

//===========================================================
// �O���錾
//===========================================================
class CPause;
class CEnemyManager;
class CItemManager;
class CMap;
class CEdit;

//===========================================================
// �Q�[���N���X��`
//===========================================================
class CGame : public CScene
{
public:

	// �E�F�[�u�Ǘ�
	enum WAVE
	{
		WAVE_00 = 0,
		WAVE_01,
		MAVE_CLEAR,
		WAVE_MAX
	};

	static WAVE m_Wave;

public:
	CGame();
	CGame(CScene::MODE mode);
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	// �ݒ�n
	static void SetbPause(bool bpause) { m_bPause = bpause; }

	// �擾�n
	static bool GetbPause(void) { return m_bPause; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CEnemyManager *GetEnemyManager(void) { return m_pEnemyManager; }
	static CCollision *GetCollision(void) { return m_Collision; }
	static CItemManager *GetItemManager(void) { return m_pItemManager; }
	static CMap *GetMap(void) { return m_pMap; }
	static WAVE GetWave(void) { return m_Wave; }

private:

	static void WaveControll(void);

	static CPause *m_pPause;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CEnemyManager *m_pEnemyManager;
	static CCollision *m_Collision;
	static CItemManager *m_pItemManager;
	static CMap *m_pMap;
	CEdit* m_pEdit;
	int m_nOnStageCounter;
	static bool m_bPause;
	bool m_bUse;  //�G�f�B�b�g���[�h�����ǂ���
	static bool m_bOnStage;
	static int m_nCounter;
};

#endif // !_GAME_H_