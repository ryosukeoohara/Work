//===========================================================
//
// �G�̊Ǘ� [enemymanager.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//===========================================================
// �O���錾
//===========================================================
class CEnemy;

//===========================================================
// �G�̃}�l�[�W���[�N���X��`
//===========================================================
class CEnemyManager
{
public:
	CEnemyManager();              //�R���X�g���N�^
	~CEnemyManager();             //�f�X�g���N�^
							       
	HRESULT Init(void);            //����������
	void Uninit(void);             //�I������
	void Update(void);             //�X�V����

	static CEnemyManager *Create(void);   // ��������
	void ReadText(const char *text);           //�e�L�X�g�t�@�C���ǂݍ���

	// �ݒ�n
	static void SetNum(int num) { m_nNum = num; }
	void SetTarget(int idx);
	void SetTrue(int idx);
	void SetMobility(void);
	
	// �擾�n
	CEnemy **GetEnemy(void) { return m_appEnemy; }
	static int GetNum(void) { return m_nNum; }
							       
private:
	
	int m_nEnemyAll;               // �G�̑���
	static int m_nNum;
	int m_nCntWave;
	CEnemy **m_appEnemy;   //�G�l�~�[�ւ̃|�C���^

	D3DXVECTOR3 m_Readpos;           //�e�L�X�g�t�@�C���̈ʒu�ǂݎ��p
	D3DXVECTOR3 m_Readrot;           //�e�L�X�g�t�@�C���̌����ǂݎ��p

	static CEnemy *m_pTop;  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pCur;  //�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pSNext;
	CEnemy *m_pPrev;       //�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pNext;       //���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;         //���S�t���O
};

#endif // !_ENEMYMANAGER_H_