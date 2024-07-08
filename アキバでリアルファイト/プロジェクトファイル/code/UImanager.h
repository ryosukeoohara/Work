//===========================================================
//
// UI�}�l�[�W��[UImanager.h]
// Author �匴�叫
//
//===========================================================
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object2D.h"

//===========================================================
// UI�}�l�[�W���N���X��`
//===========================================================
class CUIManager : CObject2D
{
public:
	//���
	enum TYPE
	{
		TYPE_NONE = 0,                              // �Ȃ���Ȃ�
		TYPE_TITLE,                                 // �^�C�g��
		TYPE_TUTORIAL,                              // �`���[�g���A��
		TYPE_RESULT,                                // ���U���g
		TYPE_WEAKNAME,                              // �U�R
		TYPE_BOSSNAME,                              // �{�X
		TYPE_LINE,                                  // ���O�̉��̐�
		TYPE_MAX
	};

private:

	// ���
	struct INFO
	{
		D3DXVECTOR3 pos;  // �ʒu
		D3DXVECTOR3 rot;  // ����	
		D3DXVECTOR3 move; // �ړ�
		D3DCOLOR col;     // �F
		TYPE type;        // ���
	};

	INFO m_Info;          // ���

public:

	CUIManager();                                   // �R���X�g���N�^
	CUIManager(D3DXVECTOR3 pos, TYPE type);         // �R���X�g���N�^
	~CUIManager();                                  // �f�X�g���N�^
													   
	HRESULT Init(void);                             // ����������
	void Uninit(void);                              // �I������
	void Update(void);                              // �X�V����
	void Draw(void);                                // �`�揈��

	static CUIManager *Create(D3DXVECTOR3 pos, TYPE type); // ��������

private:

	// �����o�֐�
	void LineMove(void);    // ���̈ړ�
	void ShrinkSize(void);  // �������Ⴍ�Ȃ�
	
	// �����o�ϐ�
	int m_nIdxTexture;                              // �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif // !_UIMANAGER_H_