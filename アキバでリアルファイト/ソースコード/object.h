//===========================================================
//
// �I�u�W�F�N�g����[object.h]
// Author �匴�叫
//
//===========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�}�N����`
#define NUM_PRIORITY  (8)     // �D�揇��

//===========================================================
// �I�u�W�F�N�g�N���X��`
//===========================================================
class CObject
{
public:		//�N�ł��A�N�Z�X�ł���

	CObject(int nPriority = 3);             //�R���X�g���N�^
	virtual ~CObject();    //�f�X�g���N�^

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,    // �v���C���[
		TYPE_ENEMY,     // �G
		TYPE_BULLET,    // �e
		TYPE_EXPLOSION, // ����
		TYPE_EFFECT,    // �G�t�F�N�g
		TYPE_PARTICL,   // �p�[�e�B�N��
		TYPE_ITEM,      // �A�C�e��
		TYPE_TIME,      // ����
		TYPE_SCORE,     // �X�R�A
		TYPE_MAX
	} TYPE;

	virtual HRESULT Init(void) = 0;   // ����������
	virtual void Uninit(void) = 0;    // �I������
	virtual void Update(void) = 0;    // �X�V����
	virtual void Draw(void) = 0;      // �`�揈��
										 
	static void ReleaseAll(void);     // ���ׂďI��
	static void UpdateAll(void);      // ���ׂčX�V
	static void DrawAll(void);        // ���ׂĕ`��
	void Release(void);

	

	// �ݒ�n
	void SetType(TYPE type) { m_ntype = type; }                   // ���
	void SetPriority(int nPriority) { m_nPriority = nPriority; }  //�@�D�揇��

	// �擾�n
	TYPE GetType(void) { return m_ntype; }             // ���
	static CObject *Getobject(int nIdx);               // 
	static int GetNumAll(void) { return m_nNumAll; }   // ����
	int GetID(void) { return m_nID; }                  // ID
	
	
private:	//�����������A�N�Z�X�ł���

	static void DeadChuck(void);           // ���S���Ă��邩�`�F�b�N

	static int m_nNumAll;                  // �I�u�W�F�N�g�̑���
	int m_nID;                             // �������g��ID
	int m_nPriority;                       // �D�揇��
	static CObject *m_pTop[NUM_PRIORITY];  // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCur[NUM_PRIORITY];  // �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;                      // ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;                      // �O�̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;                         // ���S�t���O
	TYPE m_ntype;                          // ���

};

#endif // !1