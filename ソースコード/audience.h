//===========================================================
//
// ����Ō��Ă���l[audience.h]
// Author �匴�叫
//
//===========================================================
#ifndef _AUDIENCE_H_      //���̃}�N����`������ĂȂ�������
#define _AUDIENCE_H_      //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"
#include "objectX.h"

//===========================================================
// �I�[�f�B�G���X�N���X��`
//===========================================================
class CAudience : public CObjectX
{
public:

	CAudience();  //�R���X�g���N�^
	CAudience(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename);
	~CAudience();  //�f�X�g���N�^

	HRESULT Init(void);   // ����������    
	void Uninit(void);    // �I������
	void Update(void);    // �X�V����
	void Draw(void);      // �`�揈��

	static CAudience *Create(void);
	static CAudience* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename);

	// �ݒ�n

	// �擾�n
	static CAudience* GetTop(void) { return m_pTop; }
	CAudience* GetNext(void) { return m_pNext; }

private:

	static CAudience* m_pTop;  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CAudience* m_pCur;  //�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CAudience* m_pNext;        //���̃I�u�W�F�N�g�ւ̃|�C���^
	CAudience* m_pPrev;        //�O�̃I�u�W�F�N�g�ւ̃|�C���^

	D3DXVECTOR3 m_pos;  // �ʒu
	D3DXVECTOR3 m_move; // �ړ���
	int m_nJumpWaitTime;    // �ĂуW�����v�\�ɂȂ�܂ł̎���
	bool m_bJump;  // �W�����v���Ă��邩�ǂ���
};

#endif