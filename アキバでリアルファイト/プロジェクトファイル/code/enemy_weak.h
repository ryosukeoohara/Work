//===========================================================
//
// �G�̏��� [enemy_weak.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _ENEMY_WEAK_H_
#define _ENEMY_WEAK_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "enemy.h"

//===========================================================
// �O���錾
//===========================================================
class CMotion;
class CCharacter;
class CGage3D;

//===========================================================
// �U�R�G�N���X��`
//===========================================================
class CEnemyWeak : public CEnemy
{
public:

	CEnemyWeak();                                  //�R���X�g���N�^
	CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //�R���X�g���N�^
	~CEnemyWeak();                                 //�f�X�g���N�^

	HRESULT Init(void) override;                        //������
	void Uninit(void) override;                         //�I��
	void Update(void) override;                         //�X�V
	void Draw(void) override;                           //�`��

	static CEnemyWeak *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //����

	 // �ݒ�n
	void SetChase(CHASE cha) { m_Chase = cha; }
	
private:

	// �G�̓�������
	//void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act) override;
	//void MicroWave(void) override;

	CGage3D *m_pLife3D;                          // �Q�[�W�̃|�C���^

	int m_nDamegeCounter;                      // �_���[�W��Ԃł���J�E���g
	int m_nBiriBiriCount;
	int m_nAtcCounter;                         // �U���̃C���^�[�o��
	int m_nIdx;
};

#endif