//===========================================================
//
//�|���S�����o�����[enemy.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ENEMYMEDBOSS_H_             //���̃}�N����`������ĂȂ�������
#define _ENEMYMEDBOSS_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"
#include "objectX.h"
#include "character.h"
#include "enemy.h"

//�O���錾
class CMotion;
class CEnemy;

//�}�N����`
#define ENEMYMOVE   (2.0f)
#define MAX_PATROL   (16)  //����ł���n�_�̍ő吔

//�G�N���X
class CEnemyMedBoss : public CEnemy
{
public:

	enum TYPEENE
	{
		TYPE_NONE = 0,
		TYPE_001,
		TYPE_002,
		TYPE_003,
		TYPE_MAX
	};

	CEnemyMedBoss();  //�R���X�g���N�^
	CEnemyMedBoss(D3DXVECTOR3 pos, TYPEENE type);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyMedBoss();  //�f�X�g���N�^

	enum ATTACKTYPE
	{
		ATTACKTYPE_NONE = 0,    //�ʏ�U��
		ATTACKTYPE_JUMP,        //�W�����v�U��
		ATTACKTYPE_AROUND,      //�͈͍U��
		ATTACKTYPE_BOM,         //�����U��
		ATTACKTYPE_MAX
	};

	//���[�V����
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //�j���[�g����
		MOTIONTYPE_MOVE,             //�ړ�
		MOTIONTYPE_GETUP,            //�N���オ��
		MOTIONTYPE_ACTION,           //�U��
		MOTIONTYPE_JUMP,             //�W�����v�U��
		MOTIONTYPE_BOM,              //���e�U��
		MOTIONTYPE_ACTIONNEUTRAL,    //�U���ҋ@
		MOTIONTYPE_DAMEGE,           //���炢���[�V����
		MOTIONTYPE_DEATH,            //���S
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

	static CEnemyMedBoss *Create(D3DXVECTOR3 pos, TYPEENE type);  //����
												
	void ReadText(TYPEENE type);  //�O���t�@�C���ǂݍ���
	static CEnemyMedBoss *GetEnemy(void) { return m_EnemyMedBoss; };

	void Control(void);  //�G�̓���

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	static CEnemyMedBoss *m_EnemyMedBoss;

	//STATE m_state;  //���
	TYPE m_type;
	TYPEENE m_typeEne;
	ATTACKTYPE m_ACKTYpe;

	int m_nNumModel;  //���f���̑���
	int m_nIdxTexture;
	D3DXMATRIX m_mtxWorld;    //���[���h�}�g���b�N�X
	char m_filename[128] = {};
	int m_nIdx;
	int m_nParent;
	int m_nLoop;
	int m_nFrame;   //���[�V�����̃t���[����
	int m_nCntColli;   //�����蔻�肪�������Ă��鎞��
	int m_nNumMotion;
	int m_nCntMotion;
	int m_nCnterMotion;
	int m_nNumkey;
	int m_nNumPatrol;   //���񂷂�n�_�̐�
	int m_nCurrentpos;  //���݂ǂ��̏���n�_�ɂ��邩
	int m_nCntAction;   //�U�����Ă���ĂэU������܂ł̎���
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;  //�v���C���[��ǔ����邩�ǂ���
	bool m_bAction;
	D3DXVECTOR3 m_posOrigin;
	D3DXVECTOR3 m_JumpPoint;
};

#endif