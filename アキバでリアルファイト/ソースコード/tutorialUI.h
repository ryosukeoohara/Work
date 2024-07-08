//===========================================================
//
// �`���[�g���A����UI[tutorialUI.h]
// Author �匴�叫
//
//===========================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

//===========================================================
// �O���錾
//===========================================================
class CObject2D;

//===========================================================
// �`���[�g���A��UI�N���X��`
//===========================================================
class CTutorialUI
{
public:

	//���
	enum TYPE
	{
		TYPE_PRACTICE = 0,  // ���o��
		TYPE_MOVE,          // �ړ�
		TYPE_CAMERA,        // �U�R
		TYPE_ATTACK,        // �{�X
		TYPE_AVOID,         // ���
		TYPE_GRAP,          // �͂�
		TYPE_HEAT,          // ���A�c
		TYPE_MAX
	};

public:

	CTutorialUI();                    // �R���X�g���N�^
	~CTutorialUI();                   // �f�X�g���N�^
									  
	HRESULT Init(void);               // ����������
	void Uninit(void);                // �I������
	void Update(void);                // �X�V����
	void Draw(void);                  // �`�揈��

	static CTutorialUI *Create(void); // ��������

private:

	CObject2D *m_apObject2D[TYPE_MAX];
	
};

#endif