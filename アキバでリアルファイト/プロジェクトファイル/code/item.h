//===========================================================
//
// �A�C�e������[item.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ITEM_H_             //���̃}�N����`������ĂȂ�������
#define _ITEM_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "objectX.h"

//===========================================================
// �O���錾
//===========================================================
class CObjectX;
class CBillBoard;

//===========================================================
// �A�C�e���N���X��`
//===========================================================
class CItem : public CObjectX
{
public:

	// ���
	enum TYPE
	{
		TYPE_REF = 0,       // �①��
		TYPE_BIKE,          // ���]��
		TYPE_MICROWAVE,     // �d�q�����W
		TYPE_TABLE,         // �e�[�u��
		TYPE_POSTER,        // �Ŕ�
		TYPE_MAX
	};

	CItem();   // �R���X�g���N�^
	CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, int nIdx, const char *aModelFliename);  // �R���X�g���N�^(�I�[�o�[���[�h)
	~CItem();  // �f�X�g���N�^

	HRESULT Init(void);   // ����������    
	void Uninit(void);    // �I������
	void Update(void);    // �X�V����

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, int nIdx, const char *aModelFliename);
	void Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, float fRadius);

	// �ݒ�n
	void SetType(TYPE type) { m_Type = type; }
	void SetID(int id) { m_nID = id; }
	
	// �擾�n
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	TYPE GetType(void) { return m_Type; }
	int GetID(void) { return m_nID; }
	static CItem *GetTop(void) { return m_pTop; }
	CItem *GetNext(void) { return m_pNext; }

private:
	CObjectX **m_appObjectX;
	CBillBoard *m_pBill;
	static CItem *m_pTop;  // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CItem *m_pCur;  // �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CItem *m_pNext;
	CItem *m_pPrev;        // �O�̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_Type;
	int m_nID;
	static const char *m_apTexName[2];
};

#endif