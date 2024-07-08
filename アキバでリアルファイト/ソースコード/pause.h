//===========================================================
//
// �|�[�Y���� [pause.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _PAUSE_H_             //���̃}�N����`������ĂȂ�������
#define _PAUSE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object2D.h"

//===========================================================
// �|�[�Y�N���X��`
//===========================================================
class CPause
{
private:

	// �e�N�X�`��			            
	enum TYPE
	{
		TYPE_COUTINUE = 0,                     // �Q�[���ɖ߂�
		TYPE_RETRY,                            // �Q�[������蒼��
		TYPE_QUIT,                             // �^�C�g����ʂɖ߂�
		TYPE_BACK,                             // ���̍����w�i
		TYPE_FRAME,                            // �g
		TYPE_MAX
	};

	// ����	
	enum MENU
	{
		MENU_COUTINUE = 0,                     // �Q�[���ɖ߂�
		MENU_RETRY,                            // �Q�[������蒼��
		MENU_QUIT,                             // �^�C�g����ʂɖ߂�
		MENU_MAX
	};

	//�\����
	struct PAUSE
	{
		CObject2D *Object2D;                   // 2D�I�u�W�F�N�g�̃|�C���^
		D3DXCOLOR col;                         // �F
	};

public:
	CPause();                                  // �R���X�g���N�^
	~CPause();                                 // �f�X�g���N�^
								               
	HRESULT Init(void);                        // �|�[�Y����������    
	void Uninit(void);                         // �|�[�Y�I������
	void Update(void);                         // �|�[�Y�X�V����
	void Draw(void);                           // �|�[�Y�`�揈��

	static CPause *Create(void);               // ��������

	void SetDraw(bool bPause);                 // �`�悷�邩�ǂ���
	void SetCol(void);
							                   
private:
	CObject2D *m_pBg;                           // �����w�i�p�̃|�C���^
	CObject2D *m_pFrame;                        // �g�p�̃|�C���^
	PAUSE m_aMenu[MENU_MAX];                    // ���j���[
	int m_nSelect;                              // �I�����Ă���ԍ�
	static const char *m_apTexName[TYPE_MAX];   // �e�N�X�`���̂����O
};

#endif