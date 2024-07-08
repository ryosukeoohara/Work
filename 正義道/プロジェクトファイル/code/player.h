//===========================================================
//
//�|���S�����o�����[player.h]
//Author �匴�叫
//
//===========================================================
#ifndef _PLAYER_H_             //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object3D.h"
#include "objectX.h"
#include "character.h"
#include "shadow.h"

//�O���錾
class CMotion;
class CEnemy;

//�}�N����`
#define PLAYERMOVE   (1.0f)



//�v���C���[�N���X
class CPlayer : public CObject
{
public:
	CPlayer();  //�R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CPlayer();  //�f�X�g���N�^

	//���
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,                //�ҋ@
		STATE_DAMEGE,                 //�_���[�W
		STATE_MOVE,                   //�ړ�
		STATE_STAGGER,                //���炢
		STATE_AVOI,                   //���
		STATE_ACTION,                 //�U��(�ߋ���)
		STATE_ACTIONNEUTAL,           //�U���ҋ@(�ߋ���)
		STATE_SNPSTAN,                //�U�����(������) 
		STATE_SNP,                    //�U��(������)
		STATE_KNIFESTAN,              //�U���ҋ@(�i�C�t)
		STATE_KNIFEAC,                //�U��(�i�C�t)
		STATE_CONSECAC,               //�A��
		STATE_CONSECACSEC,            //�A����
		STATE_CONSECACTHI,            //�A���O��
		STATE_DEATH,                  //����
		STATE_END,                    //�I��
		STATE_TUTOMOVE,               //�`���[�g���A���̈ړ�
		STATE_MAX
	} STATE;

	//���[�V����
	typedef enum
	{
		MOTIONTYPE_NONE = 0,                 //�Ȃ�
		MOTIONTYPE_MOVE,                     //�ړ�
		MOTIONTYPE_ACTION,                   //�U��
		MOTIONTYPE_ACTIONNEUTAL,             //�j���[�g����
		MOTIONTYPE_SNPSTAN,                  //�ˌ��҂�
		MOTIONTYPE_SNP,                      //�ˌ�
		MOTIONTYPE_KNIFESTAN,                //�i�C�t�\��
		MOTIONTYPE_KNIFEAC,                  //�i�C�t�ōU��
		MOTIONTYPE_ACFRIST,                  //�U���̈�i��
		MOTIONTYPE_ACSECOND,                 //�U���̓�i��
		MOTIONTYPE_ACTHIRD,                  //�U���̎O�i��
		MOTIONTYPE_DAMEGE,                   //���炢���[�V����
		MOTIONTYPE_AVOI,                     //���
		MOTIONTYPE_BATNEUTAL,                //�o�b�g�������Ă���Ƃ��̃j���[�g����
		MOTIONTYPE_BATMOVE,                  //�o�b�g�������Ă���Ƃ��̈ړ�
		MOTIONTYPE_BATACTION,                //�o�b�g�������Ă���Ƃ��̍U��
		MOTIONTYPE_DEATH,                    //���S
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	//�U�����@
	enum ACTIONTYPE
	{ 
		ACTIONTYPE_NEAR = 0,     //�i�C�t
		ACTIONTYPE_FAR,          //�e    
		ACTIONTYPE_BAT,          //�o�b�g
		ACTIONTYPE_MAX
	};

	//�`���[�g���A���̏��
	enum TUTOSTATE
	{
		TUTOSTATE_NONE = 0,
		TUTOSTATE_MOVE,
		TUTOSTATE_STOP,
		TUTOSTATE_MAX
	};


	HRESULT Init(void);      //�v���C���[�̏���������    
	void Uninit(void);       //�v���C���[�̏I������
	void Update(void);       //�v���C���[�̍X�V����
	void Draw(void);         //�v���C���[�̕`�揈��

	static CPlayer *Create(D3DXVECTOR3 pos);  //����
	//static CPlayer *GetPlayer(void) { return m_Player; };
	void SetState(STATE state) { m_State = state; };
	STATE GetState(void) { return m_State; };
	void ReadText(void);  //�O���t�@�C���ǂݍ���
	void Hit(void);       //�U��������������̏���
	void CollsionENEMY(CEnemy *pEnemy);  //�G�Ƃ̓����蔻��

	D3DXVECTOR3 GetMove(void) { return m_move; }      //�ړ��ʎ擾
	void SetMove(D3DXVECTOR3 move) {m_move = move; }  //�ړ��ʐݒ�

	void SetBullet(int RestBullet) { m_RestBullet = RestBullet; }

	TUTOSTATE GetTutostate(void) { return m_Tutostate; }
	void SetTutostate(TUTOSTATE state) { m_Tutostate = state; }

	bool GetbAttack(void) { return m_bAttack; }

	int GetRestBullet(void) { return m_RestBullet; }
	
private:

	void ControlPlayer(void);    //�v���C���[�̐���
	//D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_posOld;  //�O��̈ʒu
	//D3DXVECTOR3 m_rot;  //����
	D3DXVECTOR3 m_move;   //�ړ�
	STATE m_State;
	TUTOSTATE m_Tutostate;
	ACTIONTYPE m_AcType;
	D3DXMATRIX m_mtxWorld;              //���[���h�}�g���b�N�X
	CCharacter *m_apModel[MAX_PRATS];   //���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;                    //���f��(�p�[�c)�̑���
	int m_nIdxTexture;
	int m_nIdxShaadow;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	int m_nCntInvincible;                //���G����
	int m_nIdx;				             
	int m_nParent;			             
	int m_nLoop;			             
	int m_nFrame;                        //���[�V�����̃t���[����
	int m_nCntColi;                      //�U�����肪�o�Ă��鎞��
	int m_nCntEff;                       //�G�t�F�N�g�������J�E���g
	int m_nCntDuration;                  //�A���ł��鎞��
	int m_nCntDie;                       //�|���܂ł̎���
	int m_nCntSound;                     //�T�E���h�����čēx��܂ł̎���
	int m_nNumMotion;		             
	int m_nCntMotion;		             
	int m_nCnterMotion;		             
	int m_nNumkey;			             
	int m_nLifeGage;		             
	int m_RestBullet;                    //�c�e��
	float m_fDiff;			             
	float m_fDest;			             
	bool m_bDash;                        //�����Ă��邩�ǂ���
	bool m_bAction;		                 
	bool m_bEncounter;                   //�퓬���Ă��邩�ǂ���
	bool m_bIconDisp;                    //�A�C�R�����������
	bool m_bAcFir;                       //�A����
	bool m_bAcSec;                       //�A����
	bool m_bAcThr;                       //�A����
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_motion;                   //���[�V�����ւ̃|�C���^
	CShadow *m_pShadow;                  //�e�ւ̃|�C���^

	//�`���[�g���A���Ŏg���֐�,�ϐ�
	void ControlTutorial(void);          //�`���[�g���A���̃v���C���[�̐���
	bool m_bPushW;                       //W�L�[��������
	bool m_bPushA;                       //A�L�[��������
	bool m_bPushS;                       //S�L�[��������
	bool m_bPushD;                       //D�L�[��������
	bool m_bAttack;                      //�U��������
	bool m_bAvoi;                        //�������
	bool m_bWhee;                       //�z�C�[������]����
};

#endif