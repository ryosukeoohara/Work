//===========================================================
//
//�|���S�����o�����[enemy.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ENEMYWEAK_H_             //���̃}�N����`������ĂȂ�������
#define _ENEMYWEAK_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"
#include "objectX.h"
#include "character.h"
#include "enemy.h"

//�O���錾
class CMotion;
class CEnemy;

//�}�N����`
#define ENEMYMOVE    (2.0f)
#define MAX_PATROL   (16)  //����ł���n�_�̍ő吔

//�G�N���X
class CEnemyWeak : public CEnemy
{
public:
	CEnemyWeak();  //�R���X�g���N�^
	CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyWeak();  //�f�X�g���N�^

	//���[�V����
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //�j���[�g����
		MOTIONTYPE_MOVE,             //�ړ�
		MOTIONTYPE_ACTION,           //�U��
		MOTIONTYPE_ACTIONNEUTRAL,    //�U���ҋ@
		MOTIONTYPE_DAMEGE,           //�_���[�W
		MOTIONTYPE_DEATH,            //���S
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

	static CEnemyWeak *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //����
												 
	void ReadText(char *Filename);  //�O���t�@�C���ǂݍ���
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);
	//static void SetType(TYPE type) { m_type = type; }

	void Control(void);  //�G�̓���
	void Death(int nCntEnemy);    //���񂾂Ƃ�

	void SetState(STATE state) { m_state = state; }  //��Ԑݒ�
	STATE GetState(void) { return m_state; }  //��Ԏ擾

protected:
	static CEnemyWeak *m_EnemyWeak[128];
	

private:

	static TYPE m_type;

	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //���񂷂�n�_�̐�
	int m_nCurrentpos;     //���݂ǂ��̏���n�_�ɂ��邩
	int m_nCntAction;      //�U�����Ă���ĂэU������܂ł̎���
	int m_nCntDeath;       //���S���Ă�����ł���܂ł̎���
	int m_DeathEnemyIdx;   //���S�����G�̔ԍ�
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //�v���C���[��ǔ����邩�ǂ���
	bool m_bAction;        //�U���������ǂ���
};

//�G�N���X(�ߋ���)
class CEnemyNear : public CEnemyWeak
{
public:
	CEnemyNear();                 //�R���X�g���N�^
	CEnemyNear(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyNear();                //�f�X�g���N�^

	////���
	//enum STATE
	//{
	//	TATE_NONE = 0,             //�j���[�g����
	//	TATE_MOVE,                 //�ړ�
	//	TATE_ACTION,               //�U��
	//	TATE_ACTIONNEUTRAL,        //�U���j���[�g����
	//	TATE_DAMEGE,               //�_���[�W��
	//	TATE_STAGGER,              //��낯
	//	TATE_DEATH,                //���S
	//	TATE_MAX
	//};

	//���[�V����
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //�j���[�g����
		MOTIONTYPE_MOVE,             //�ړ�
		MOTIONTYPE_ACTION,           //�U��
		MOTIONTYPE_RUSH,             //�ˌ��U��
		MOTIONTYPE_ACTIONNEUTRAL,    //�U���ҋ@
		MOTIONTYPE_DAMEGE,           //�_���[�W
		MOTIONTYPE_DEATH,            //���S
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

	static CEnemyNear *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //����

	void ReadText(char *Filename);  //�O���t�@�C���ǂݍ���
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);

	void Control(void);           //�G�̓���
	void Death(int nCntEnemy);    //���񂾂Ƃ�

	void SetState(STATE state) { m_state = state; }  //��Ԑݒ�
	STATE GetState(void) { return m_state; }  //��Ԏ擾



private:

	//static LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	//CCharacter *m_apModel[128];                  //���f��(�p�[�c)�ւ̃|�C���^
	//CMotion *m_motion;                           //���[�V�����ւ̃|�C���^
	//D3DXVECTOR3 m_pos;                           //�ʒu
	//D3DXVECTOR3 m_move;                          //�ړ�
	//D3DXVECTOR3 m_rot;                           //����

	//D3DXVECTOR3 m_Readpos;
	//D3DXVECTOR3 m_Readrot;
	//static CEnemyWeak *m_EnemyWeak[128];
	//static int m_nNumAll;  //�����G�̑���

	//STATE m_state;  //���

	//int m_nNumModel;  //���f���̑���
	//int m_nIdxTexture;
	//D3DXMATRIX m_mtxWorld;    //���[���h�}�g���b�N�X
	//char m_filename[128] = {};

	TYPE m_type;
	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //���񂷂�n�_�̐�
	int m_nCurrentpos;     //���݂ǂ��̏���n�_�ɂ��邩
	int m_nCntAction;      //�U�����Ă���ĂэU������܂ł̎���
	int m_nCntDeath;       //���S���Ă�����ł���܂ł̎���
	int m_DeathEnemyIdx;   //���S�����G�̔ԍ�
	int m_nCntRush;          //�ːi�U�������Ă���܂ł̃J�E���g
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //�v���C���[��ǔ����邩�ǂ���
	bool m_bAction;        //�U���������ǂ���
};

//�G�N���X(�ߋ���)
class CEnemyFar : public CEnemyWeak
{
public:
	CEnemyFar();                 //�R���X�g���N�^
	CEnemyFar(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyFar();                //�f�X�g���N�^

	////���------------------------------------------------------------------
	//enum STATE
	//{
	//	TATE_NONE = 0,             //�j���[�g����
	//	TATE_MOVE,                 //�ړ�
	//	TATE_ACTION,               //�U��
	//	TATE_ACTIONNEUTRAL,        //�U���j���[�g����
	//	TATE_DAMEGE,               //�_���[�W��
	//	TATE_STAGGER,              //��낯
	//	TATE_DEATH,                //���S
	//	TATE_MAX
	//};

	//���[�V����-------------------------------------------------------------
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //�j���[�g����
		MOTIONTYPE_MOVE,             //�ړ�
		MOTIONTYPE_ACTION,           //�U��
		MOTIONTYPE_ACTIONNEUTRAL,    //�U���ҋ@
		MOTIONTYPE_REROAD,           //���e���|�b�P������o��
		MOTIONTYPE_DAMEGE,           //�_���[�W
		MOTIONTYPE_DEATH,            //���S
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

	static CEnemyFar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //����

	void ReadText(char *Filename);  //�O���t�@�C���ǂݍ���
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);

	void Control(void);  //�G�̓���
	void Death(int nCntEnemy);    //���񂾂Ƃ�

	void SetState(STATE state) { m_state = state; }  //��Ԑݒ�
	STATE GetState(void) { return m_state; }  //��Ԏ擾

private:

	TYPE m_type;
	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //���񂷂�n�_�̐�
	int m_nCurrentpos;     //���݂ǂ��̏���n�_�ɂ��邩
	int m_nCntAction;      //�U�����Ă���ĂэU������܂ł̎���
	int m_nCntDeath;       //���S���Ă�����ł���܂ł̎���
	int m_DeathEnemyIdx;   //���S�����G�̔ԍ�
	int m_nCntReload;      //�����[�h����܂ł̃J�E���g
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //�v���C���[��ǔ����邩�ǂ���
	bool m_bAction;        //�U���������ǂ���
	bool m_bBom;           //���e���|�b�P������o��
};

#endif