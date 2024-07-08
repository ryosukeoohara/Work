//===========================================================
//
//�|���S�����o�����[enemy.h]
//Author �匴�叫
//
//===========================================================
#ifndef _POLICE_H_             //���̃}�N����`������ĂȂ�������
#define _POLICE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "motion.h"
#include "character.h"
#include "shadow.h"
#include "life.h"

//�}�N����`
#define MAX_ENEMY   (128)   //�G�̍ő吔
#define MAX_RARTS   (128)   //�p�[�c�̍ő吔
#define MAX_PATROL   (16)   //����ł���n�_�̍ő吔

//�G�N���X
class CPolice : public CObject
{
public:
	CPolice();                                                                          //�R���X�g���N�^
	CPolice(D3DXVECTOR3 pos);                                                           //�R���X�g���N�^
	~CPolice();                                                                         //�f�X�g���N�^
								                                                        
	enum TYPE					                                                        
	{							                                                        
		TYPE_NONE = 0,			                                                        
		TYPE_NEAR,                                                                      //�ߋ����̃U�R
		TYPE_FAR,                                                                       //�������̃U�R
		TYPE_MEDBOSS,                                                                   //���{�X
		TYPE_BOSS,                                                                      //�{�X
		TYPE_MAX				                                                        
	}; 							                                                        
								                                                        
	enum STATE					                                                        
	{							                                                        
		TATE_NONE = 0,			                                                        
		TATE_MOVE,                                                                       //�ړ�
		TATE_JUMP,                                                                       //�W�����v
		TATE_GETUP,                                                                      //�N���オ��
		TATE_ACTION,                                                                     //�U��
		TATE_RUSH,                                                                       //�ːi�U��
		TATE_ACTIONNEUTRAL,                                                              //�U���j���[�g����
		TATE_DAMEGE,                                                                     //�_���[�W��
		TATE_STAGGER,                                                                    //��낯
		TATE_DEATH,                                                                      //���S
		TATE_MAX				                                                        
	};							                                                        
								                                                        
	HRESULT Init(void);                                                                  //����������    
	void Uninit(void);                                                                   //�I������
	void Update(void);                                                                   //�X�V����
	void Draw(void);                                                                     //�`�揈��

	void ReadText(char *Filename);                                                       //�O���t�@�C���ǂݍ���
	static CPolice **GetPolice(void) { return &m_Police[0]; }                             //�x�@�擾����

	void Controll(void);                                                                 //�������䏈��

	void SetPosOld(D3DXVECTOR3 posold) { m_posOld = posold; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	void SetState(STATE state) { m_state = state; }                                       //��Ԑݒ�
	STATE GetState(void) { return m_state; }                                              //��Ԏ擾
													                                      
	void SetNumber(int nNum) { m_nNumber = nNum; }	                                      
													                                      
	void Hit(void);                                                                       //�q�b�g����

	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }

	typedef struct
	{
		D3DXVECTOR3 m_PatrolPos;                                                          //����n�_

	}PATROL;

private:

	static CPolice *m_Police[MAX_ENEMY];
	static int m_nNumAll;                                                                 //�x�@�̑���
	static LPDIRECT3DTEXTURE9 m_pTexture;                                                 //�e�N�X�`���ւ̃|�C���^
	CCharacter *m_apModel[MAX_RARTS];                                                     //���f��(�p�[�c)�ւ̃|�C���^
	CMotion *m_motion;                                                                    //���[�V�����ւ̃|�C���^
	PATROL m_Vigi[MAX_PATROL];					                                          
	D3DXVECTOR3 m_posOld;                                                                 //�O��̈ʒu
	D3DXVECTOR3 m_Readpos;                                                                //�ǂݍ��ނƂ��̈ʒu
	D3DXVECTOR3 m_Readrot;                                                                //�ǂݍ��ނƂ��̌���
	//D3DXVECTOR3 m_posOld;                                                                 //�O��̈ʒu
	D3DXVECTOR3 m_move;                                                                   //�ړ�
	D3DXMATRIX m_mtxWorld;                                                                //���[���h�}�g���b�N�X
	char m_filename[128] = {};					                                          
												                                          
	CShadow *m_pShadow;                                                                   //�e�ւ̃|�C���^
	CLife *m_Life;                                                                        //���C�t�ւ̃|�C���^
	TYPE m_type;                                                                          //���
	STATE m_state;                                                                        //���
	int m_nIdxTexture;                                                                    //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nIdxShaadow;                                                                    //�e�̃C���f�b�N�X�ԍ�
	int m_nNumModel;                                                                      //���f���̑���
	int m_nNumPatrol;                                                                     //�p�g���[������n�_�̐�
	int m_nCurrentpos;                                                                    //���݂ǂ��̏���n�_�ɂ��邩
	int m_nIdx;             
	int m_nParent;
	int m_nNumber;
};

#endif