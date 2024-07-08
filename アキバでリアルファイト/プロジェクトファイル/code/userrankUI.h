//===========================================================
//
// �G�o�ꎞ��UI[userrankUI.h]
// Author �匴�叫
//
//===========================================================
#ifndef _USERRANKUI_H_
#define _USERRANKUI_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object.h"

//===========================================================
// �O���錾
//===========================================================
class CObject2D;
class CNumber;

//*==========================================================
// �N���X��`
//*==========================================================
class CUserRankUI : CObject
{
public:

	//���
	enum TYPE
	{
		TYPE_NOEN = 0, // �Ȃ���Ȃ�
		TYPE_TOP,      // �ō�
		TYPE_MIDDLE,   // ����
		TYPE_UNDER,    // �����[
		TYPE_WEAKEST,  // �Ŏ�
		TYPE_MAX
	};

public:

	CUserRankUI();                  // �R���X�g���N�^
	CUserRankUI(TYPE type, int nPriority = 7);         // �R���X�g���N�^
	~CUserRankUI();                 // �f�X�g���N�^

	HRESULT Init(void);             // ����������
	void Uninit(void);              // �I������
	void Update(void);              // �X�V����
	void Draw(void);                // �`�揈��

	static CUserRankUI *Create(TYPE type); // ��������

private:
	TYPE m_type;
	CObject2D *m_pObject;

};

#endif