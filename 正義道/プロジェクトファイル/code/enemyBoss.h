//===========================================================
//
// �{�X�̏���[enemyBoss.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ENEMYBOSS_H_             //���̃}�N����`������ĂȂ�������
#define _ENEMYBOSS_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

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

//===============================================================
// �N���X��`
//===============================================================
class CEnemyBoss : public CEnemy
{
public:
	CEnemyBoss();  //�R���X�g���N�^
	CEnemyBoss(D3DXVECTOR3 pos);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyBoss();  //�f�X�g���N�^

	enum ATTACKTYPE
	{
		ATTACKTYPE_NONE = 0,    //�ʏ�U��
		ATTACKTYPE_JUMP,        //�W�����v�U��
		ATTACKTYPE_AROUND,      //�͈͍U��
		ATTACKTYPE_BOM,         //�����U��
		ATTACKTYPE_MAX
	};

	//enum STATE
	//{
	//	TATE_NONE = 0,
	//	TATE_MOVE,                 //�ړ�
	//	TATE_JUMP,                 //�W�����v
	//	TATE_GETUP,                //�N���オ��
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

	static CEnemyBoss *Create(D3DXVECTOR3 pos);  //����
	//static HRESULT Load(void);
	//static void UnLoad(void);
	//static CEnemyBoss *GetEnemy(void) { return m_Enemy; };
	void ReadText(void);  //�O���t�@�C���ǂݍ���
	static CEnemyBoss *GetEnemy(void) { return m_EnemyBoss; };

	void Control(void);  //�G�̓���

	//void SetState(STATE state) { m_state = state; }  //��Ԑݒ�
	//STATE GetState(void) { return m_state; }  //��Ԏ擾

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	static CEnemyBoss *m_EnemyBoss;

	//STATE m_state;  //���
	TYPE m_type;
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