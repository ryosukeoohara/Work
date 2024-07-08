//===========================================================
//
//�|���S�����o�����[enemy.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ENEMY_H_             //���̃}�N����`������ĂȂ�������
#define _ENEMY_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "motion.h"
#include "character.h"
#include "shadow.h"
#include "life.h"

//�}�N����`
#define MAX_ENEMY   (128)   //�G�̍ő吔
#define MAX_RARTS   (128)   //�p�[�c�̍ő吔

//�G�N���X
class CEnemy : public CObject
{
public:
	CEnemy();  //�R���X�g���N�^
	~CEnemy();  //�f�X�g���N�^

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_NEAR,                 //�ߋ����̃U�R
		TYPE_FAR,                  //�������̃U�R
		TYPE_MEDBOSS,              //���{�X
		TYPE_BOSS,                 //�{�X
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,
		STATE_MOVE,                 //�ړ�
		STATE_JUMP,                 //�W�����v
		STATE_GETUP,                //�N���オ��
		STATE_ACTION,               //�U��
		STATE_RUSH,                 //�ːi�U��
		STATE_ACTIONNEUTRAL,        //�U���j���[�g����
		STATE_DAMEGE,               //�_���[�W��
		STATE_STAGGER,              //��낯
		STATE_DEATH,                //���S
		STATE_END,                  //�I��
		STATE_MAX
	};

	HRESULT Init(void);   //����������    
	void Uninit(void);    //�I������
	void Update(void);    //�X�V����
	void Draw(void);      //�`�揈��

	void ReadText(char *Filename);  //�O���t�@�C���ǂݍ���
	static CEnemy **GetEnemy(void) { return &m_Enemy[0]; }

	void SetPosOld(D3DXVECTOR3 posold) { m_posOld = posold; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	void SetState(STATE state) { m_state = state; }  //��Ԑݒ�
	STATE GetState(void) { 
		return m_state; 
	}         //��Ԏ擾

	void SetNumber(int nNum) { m_nNumber = nNum; }

	void Hit(void);                                  //�q�b�g����

	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }

protected:
	static CEnemy *m_Enemy[MAX_ENEMY];
	static int m_nNumAll;                        //�����G�̑���
	static LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	CCharacter *m_apModel[MAX_RARTS];            //���f��(�p�[�c)�ւ̃|�C���^
	CMotion *m_motion;                           //���[�V�����ւ̃|�C���^
	D3DXVECTOR3 m_pos;                           //�ʒu
	D3DXVECTOR3 m_posOld;                        //�O��̈ʒu
	D3DXVECTOR3 m_move;                          //�ړ�
	D3DXVECTOR3 m_rot;                           //����

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;

	int m_nIdxTexture;
	int m_nIdxShaadow;

	D3DXMATRIX m_mtxWorld;    //���[���h�}�g���b�N�X
	char m_filename[128] = {};

	int m_nNumModel;  //���f���̑���

	STATE m_state;  //���

	CShadow *m_pShadow;   //�e�ւ̃|�C���^
	CLife *m_Life;        //���C�t�ւ̃|�C���^

private:
	TYPE m_type;

	int m_nIdx;
	int m_nParent;

	int m_nNumber;

	

};

#endif