//===========================================================
//
// �v���C���[�̏���[player.h]
// Author �匴�叫
//
//===========================================================
#ifndef _PLAYER_H_             //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object.h"

//===========================================================
// �O���錾
//===========================================================
class CMotion;
class CCharacter;
class CObjectX;
class CGage2D;
class CGage3D;
class CBillBoard;
class CEnemy;
class CObject2D;
class CItem;
class CHeatAction;

//===========================================================
// �v���C���[�N���X��`
//===========================================================
class CPlayer : public CObject
{
public:
	// ���
	enum STATE
	{
		STATE_NONE = 0,     // �Ȃ���Ȃ�
		STATE_NEUTRAL,      // �j���[�g����
		STATE_GRAPNEUTRAL,  // �͂ݏ�Ԃ̃j���[�g����
		STATE_MOVE,         // �ړ�
		STATE_ATTACK,       // �U��
		STATE_AVOID,        // ���
		STATE_LIFT,         // �A�C�e���͂�ł�
		STATE_GRAP,         // �͂�
		STATE_THROW,        // ������
		STATE_HEAT,         // �q�[�g�A�N�V����
		STATE_GRAPDASH,     // �͂�ő���
		STATE_ENEMYGRAP,    // �G�𓊂���
		STATE_GRAPWALK,     // �G��͂�ŕ���
		STATE_POWERFUL,     // �n�ʂɂ���������
		STATE_DAMEGE,       // �_���[�W
		STATE_INVINCIBE,    // ���G
		STATE_DEATH,        // ���S
		STATE_OTA,
		STATE_MAX
	};

	enum HEAT
	{
		HEAT_NONE = 0,  // �Ȃ���Ȃ�
		HEAT_SMASH,     // ��������
		HEAT_FIRE,      // �d�q�����W
		HEAT_MAX
	};

	// �A��
	enum ATTACKTYPE
	{
		TYPE_ATTACK1 = 0,       // ��i��
		TYPE_ATTACK2,           // ��i��
		TYPE_ATTACK3,           // �O�i��
		TYPE_HEATACTBIKE,       // �q�[�g�A�N�V�����E�o�C�N
		TYPE_HEATACTREF,        // �q�[�g�A�N�V�����E�①��
		TYPE_HEATACTMICROWAVE,  // �q�[�g�A�N�V�����E�d�q�����W
		TYPE_HEATACTPOWERFUL,   // �q�[�g�A�N�V�����E�n�ʂɂ���������
		TYPEMAX_ATTACK
	};

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,       // �j���[�g����
		TYPE_MOVE,              // �ړ�
		TYPE_ATTACK01,          // �A��1�i��
		TYPE_ATTACK02,          // �A��2�i��
		TYPE_ATTACK03,          // �A��3�i�� 
		TYPE_AVOID,             // ���
		TYPE_LIFT,              // �����グ��
		TYPE_THROW,             // ������
		TYPE_GRAPDASH,          // �����đ���
		TYPE_GRAP,              // �͂�
		TYPE_GRAPNEUTRAL,       // �͂݃j���[�g����
		TYPE_ENEMYGRAP,         // �G��͂�œ�����
		TYPE_GRAPWALK,          // �͂�ŕ���
		TYPE_POWERFUL,          // �n�ʂ�������
		TYPE_DAMAGE,            // �_���[�W
		TYPE_OTA,               // �^�C�g���ł���I�^�|
		TYPE_MAX
	};

private:

	enum DAMEGESTATE
	{
		DAMEGE_NONE = 0,
		DAMEGE_SMALL,
		DAMEGE_BIG,
		DAMEGE_MAX
	};

	// ���
	struct INFO
	{
		D3DXVECTOR3 pos;                  // �ʒu
		D3DXVECTOR3 posOld;               // �O��̈ʒu
		D3DXVECTOR3 rot;                  // ����
		D3DXVECTOR3 move;                 // �ړ�
		D3DXCOLOR col;                    // �F
		D3DXMATRIX mtxWorld;              // ���[���h�}�g���b�N�X
		STATE state;                      // ���
		ATTACKTYPE Atc;                   // �U�������
		int nLife;                        // �̗�
		float fRadius;                    // ����
	};

	struct GRAP
	{
		CItem *pItem;                     // �A�C�e��
		CEnemy *pEnemy;                   // �G
	};

	enum MOBILITY
	{
		Mobile = 0,  // ������
		Immobile,    // �����Ȃ�
		MAX
	};

	INFO m_Info;                          // ���
	GRAP m_Grap;                          // �͂ނł������
	HEAT m_HeatAct;
	MOBILITY m_Mobility;
	
public:
	CPlayer();  //�R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos, int nPriority = 2);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CPlayer();  //�f�X�g���N�^

	HRESULT Init(void);        // ����������    
	void Uninit(void);		   // �I������
	void Update(void);         // �X�V����
	void Draw(void);           // �`�揈��

	static CPlayer *Create(D3DXVECTOR3 pos, int nPriority = 2);  // ����
	static CPlayer *Create(void);
	void Damage(int nDamage, float fKnockBack);			              // �U��������������̏���
	void TitleWalk(void);                     // �^�C�g��

	//�@�ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_Info.pos = pos; }         // �ʒu�ݒ�
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // �����ݒ�
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }           // �ړ��ʐݒ�
	void SetState(STATE state) { m_Info.state = state; }             // ���
	void SetGrapItem(CItem *obj) { m_Grap.pItem = obj; }             // �A�C�e��
	void SetGrapEnemy(CEnemy *enemy) { m_Grap.pEnemy = enemy; }      // �G
	void SetLife(int nlife) { m_Info.nLife = nlife; }                // �̗�
	void SetMobile(void) { m_Mobility = Mobile; }                    // ������悤�ɂ���
	void SetImmobile(void) { m_Mobility = Immobile; }                // �����Ȃ��悤�ɂ���
	void SetDefeat(int nValue) { m_nDefeat = nValue; }
	void SetUseMicroCount(int nValue) { m_nUseCounter = nValue; }
	void SetbHeatActFlag(bool bValue) { m_bHeatActFlag = bValue; }

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // �ʒu�擾
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // �����擾
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // �ړ��ʎ擾
	STATE GetState(void) { return m_Info.state; }              // ���
	int GetLife(void) { return m_Info.nLife; }                 // �̗�
	float GetRadius(void) { return m_Info.fRadius; }           // ����
	D3DXMATRIX *GetMatrix(void) { return &m_Info.mtxWorld; }   // �}�g���b�N�X
	CCharacter **GetChar(void) { return m_ppCharacter; }
	bool GetbAttack(void) { return m_bAttack; }                // �U�������ǂ���
	CMotion *GetMotion(void) { return m_pMotion; }
	ATTACKTYPE GetActType(void) { return m_Info.Atc; }
	CItem *GetItem(void) { return m_pItemMicro; }
	CEnemy *GetGrapEnemy(void) { return m_Grap.pEnemy; }
	CItem *GetGrapItem(void) { return m_Grap.pItem; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	int GetDefeat(void) { return m_nDefeat; }
	HEAT GetHeatAct(void) { return m_HeatAct; }
	bool GetHeatActFlag(void) { return m_bHeatActFlag; }

private:

	// �����o�֐�
	void Control(void);                   // ����
	void Move(void);                      // �ړ�
	void Attack(void);                    // �U��
	void GrapRotition(void);              // �W���C�A���g�X�C���O
	void Grap(void);                      // �͂�
	void Avoid(void);                     // ���
	void State(void);                     // ���
	void Damege(void);                    // �_���[�W
	void Heat(void);                      // �q�[�g�A�N�V����
	void ReadText(const char *fliename);  // �e�L�X�g�t�@�C���ǂݍ���
	float EnemyDistance(void);              // �G�Ƃ̋���
	float ItemDistance(void);

	// �����o�ϐ�
	int m_nNumModel;                    //���f��(�p�[�c)�̑���
	int m_nIdxTexture;
	int m_nIdxShaadow;
	int m_nIdx;
	int m_nParent;
	int m_nCntColi;
	int m_nDamegeCounter;
	int m_nUseCounter;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_pMotion;                   // ���[�V�����ւ̃|�C���^
	CCharacter **m_ppCharacter;           // �L�����N�^�[�ւ̃|�C���^
	CItem *m_pItemMicro;                  // �d�q�����W�ۑ��p
	CGage2D *m_pLife;                     // �Q�[�W�̃|�C���^
	CGage3D *m_pStamina;                  // �Q�[�W�̃|�C���^
	CEnemy *m_pEnemy;                     // �ꎞ�ۑ��p
	CItem *m_pItem;                       // �ꎞ�ۑ��p
	CObject2D *m_pBotton;
	CObject2D *m_pGekiatu;
	CHeatAction *m_pHeatAct;
	static CPlayer *m_pPlayer;
	int m_nDefeat;  // �G��|������
	int m_nIdxEne;
	int m_nIdxItem;
	int m_nDamageCounter;
	int m_nCntSound;
	float m_fDest;
	float m_fDestOld;
	float m_fDiff;
	float m_fGrapRot;
	float m_fStamina;                     // �X�^�~�i
	bool m_bDesh;                         // �_�b�V��
	bool m_bAttack;                       // �U��
	bool m_bAvoid;                        // ���
	bool m_bLift;                         // �����グ��
	bool m_bGrap;                         // ����
	bool m_bInvi;                         // ���G���ǂ���
	bool m_bHeatActFlag;                  // �q�[�g�A�N�V�������Ă��邩�ǂ���

	//�`���[�g���A���Ŏg���֐�,�ϐ�
	void ControlTutorial(void);          // �`���[�g���A���̃v���C���[�̐���
	bool m_bPushW;                       // W�L�[��������
	bool m_bPushA;                       // A�L�[��������
	bool m_bPushS;                       // S�L�[��������
	bool m_bPushD;                       // D�L�[��������
	bool m_bAvoi;                        // �������
	bool m_bWhee;                        // �z�C�[������]����
};

#endif