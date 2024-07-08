//===========================================================
//
// �G�̏��� [enemy.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "enemy.h"
#include "player.h"

//===========================================================
// �O���錾
//===========================================================
class CMotion;
class CCharacter;
class CGage2D;

//===========================================================
// �{�X�G�N���X��`
//===========================================================
class CEnemyBoss : public CEnemy
{
public:

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_PUNCH = CEnemy::MOTIONTYPE::TYPE_MAX,                    // �p���`
		TYPE_GURUGURU,                 // ���邮��p���`
		TYPE_MAX
	};

	enum ATTACKTYPE
	{
		ATTACKTYPE_GURUGURU = 0,
		ATTACKTYPE_PUNCH,
		ATTACKTYPE_FLY,
		ATTACKTYPE_MAX
	};

public:

	CEnemyBoss();                                  //�R���X�g���N�^
	CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //�R���X�g���N�^
	~CEnemyBoss();                                 //�f�X�g���N�^

	HRESULT Init(void) override;                        //������
	void Uninit(void) override;                         //�I��
	void Update(void) override;                         //�X�V
	void Draw(void) override;                           //�`��

	static CEnemyBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //����

	// �ݒ�n
	void SetChase(CHASE cha) { m_Chase = cha; }

private:

	// �G�̓�������
	//void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act) override;
	void RollingPunch(void);
	void NormalPunch(void);
	void Fly(void);
	//void MicroWave(void) override;

	CGage2D *m_pLife2D;                          // �Q�[�W�̃|�C���^

	int m_nDamegeCounter;         // �_���[�W��Ԃł���J�E���g
	int m_nBiriBiriCount;         // �d�q�����W�т�т�J�E���g
	int m_nAtcCounter;            // �U���̃C���^�[�o��
	int m_nReceivedAttack;        // �U�����󂯂���
	int m_nAttackType;
	int m_nIdx;
	

};

#endif // !_ENEMY_H_