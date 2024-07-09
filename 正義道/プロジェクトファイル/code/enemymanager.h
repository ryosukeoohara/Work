//===========================================================
//
// �G�l�~�[�}�l�[�W������[enemymanager.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ENEMYMANAGER_H_       //���̃}�N����`������ĂȂ�������
#define _ENEMYMANAGER_H_       //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"

//===============================================================
// �N���X��`
//===============================================================
class CEnemyManager
{
public:
	CEnemyManager();  //�R���X�g���N�^
	~CEnemyManager();  //�f�X�g���N�^

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

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
	static int m_nIdx;  //�G�̔ԍ�
	bool m_bAppearExecutive;
	bool m_bAppearBoss;

};

#endif