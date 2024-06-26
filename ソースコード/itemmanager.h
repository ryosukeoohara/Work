//===========================================================
//
// �A�C�e���̊Ǘ� [itemmanager.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "item.h"

//===========================================================
// �A�C�e���̊Ǘ��N���X��`
//===========================================================
class CItemManager
{
public:
	CItemManager();              // �R���X�g���N�^
	~CItemManager();             // �f�X�g���N�^

	HRESULT Init(void);          // ����������
	void Uninit(void);           // �I������
	void Update(void);           // �X�V����

	static CItemManager *Create(const char* filename);   // ��������
	void Release(int idx);                               // �w�肵���ԍ��̃A�C�e�����폜����
	void ReadText(const char *text);                     // �e�L�X�g�t�@�C���ǂݍ���

	 // �ݒ�n
	void SetNum(int num) { m_nNum = num; }               // ����

	// �擾�n
	int GetNum(void) { return m_nNum; }                  // ����

private:
	
	int m_nNum;  // ����

	static const char *m_apTexName[CItem::TYPE_MAX];  // ���f���̃t�@�C���l�[��
};

#endif