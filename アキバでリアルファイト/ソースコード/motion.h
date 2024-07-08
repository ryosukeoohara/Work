//===========================================================
//
// ���[�V��������[motion.h]
// Author �匴�叫
//
//===========================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "objectX.h"

//�}�N����`
#define MAX_INFO   (64)

//===========================================================
// �O���錾
//===========================================================
class CCharacter;

//===========================================================
// ���[�V�����N���X��`
//===========================================================
class CMotion
{
private:

	//���f��---------------------------------------------------------------
	typedef struct
	{
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_rot;

	} KEY;

	//���f��---------------------------------------------------------------
	typedef struct
	{
		KEY m_aKey[MAX_INFO];  //���݂̃L�[
		int m_nFrame;   //���[�V�����̃t���[����

	} KEYINFO;

	//���[�V����---------------------------------------------------------------
	typedef struct
	{
		int m_nNumKey;    // �L�[�̑���
		int m_nLoop;      // ���[�v���邩�ǂ���
		int m_nNumFrame;  // �t���[���̑���
		int m_nAttackOccurs;  // �U�����蔭���t���[��
		int m_nAttackEnd;  // �U������I���t���[��
		int m_nAttackDamege;  // �U����
		int m_nInvincibleStart;  // ���S���G��ԊJ�n
		int m_nInvincibleEnd;    // ���S���G�I��
		int nCancellFrame;   // �L�����Z���\�t���[��
		int nCancellFrameEnd;  // �L�����Z���\�t���[��
		float m_nKnockBack;      // �������
		bool m_bLoop;     // ���[�v���邩�ǂ���
		bool m_bFinish;   // �I���������ǂ���

		KEYINFO m_KeySet[MAX_INFO];

	} INFO;

public:
	CMotion();
	~CMotion();

	void Init(void);
	void Uninit(void);
	void Update(void);

	bool IsFinish(void);
	
	// �ǂݍ��݌n
	void ReadText(const char *TextFilename);            // �O���t�@�C���ǂݍ���
	
	// �ݒ�n
	void Set(int nType);                                // ���[�V����
	void SetInfo(void);                                 // ���
	void SetModel(CCharacter **ppModel, int nNumModel); // �L�����N�^�[�̃��f��

	// �擾�n
	int GetType(void);                                  // ���
	int GetNumFrame(void) { return m_nNowFrame; }   // ���[�V�����̑��t���[��
	int GetNowFrame(void);
	int GetAttackOccurs(void);
	int GetAttackEnd(void);
	int GetAttackDamege(void);
	int GetInvincibleStrat(void);
	int GetInvincibleEnd(void);
	int GetCancellFrame(void);
	int GetCancellFrameEnd(void);
	float GetKnockBack(void);
	INFO GetInfo(void);

private:

	void RotCorrect(float rot);

	INFO m_aInfo[MAX_INFO];
	KEY m_aOldInfo[MAX_INFO];
	int  m_nNumAll;              //���[�V�����̑���
	int  m_nType;                //���[�V�����̎��
	int m_nTypeold;              //�O��̃��[�V�����̎��
	bool m_bLoop;                //���[�v���邩�ǂ���
	int  m_nNumKey;              //�L�[�̑���
	int  m_nKey;                 //���݂̃L�[
	int  m_nCounter;             //�t���[�����ɒB������
	int  m_nCntkeySet;
	int m_nNumFrame;             //���[�V�����̃t���[����
	int m_nNowFrame;
	bool m_bFinish;              //�I���������ǂ���
	
	CCharacter **m_ppModel;  //���f���ւ̃_�u���|�C���^
	int m_nNumModel;         //���f���̑���
	static int m_nObj;       //�N�̃��[�V������
};

#endif