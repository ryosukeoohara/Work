//===========================================================
//
// �X�R�A����[score.h]
// Author �匴�叫
//
//===========================================================
#ifndef _SCORE_H_             //���̃}�N����`������ĂȂ�������
#define _SCORE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "number.h"

//===========================================================
// �X�R�A�N���X��`
//===========================================================
class CScore : public CNumber
{
public:
	CScore();                 // �R���X�g���N�^
	CScore(D3DXVECTOR3 pos);  // �R���X�g���N�^(�I�[�o�[���[�h)
	~CScore();                // �f�X�g���N�^

	HRESULT Init(void);      // ����������    
	void Uninit(void);       // �I������
	void Update(void);       // �X�V����
	void Draw(void);         // �`�揈��

	static CScore *Create(void);  // ��������

	// �ݒ�n
	static void SetScore(int nScore) { m_nScore += nScore; }  // �X�R�A

	// �擾�n
	CScore *GetScore(void) { return m_Score; };               // �X�R�A�̃|�C���^
	static int Getscore(void) { return m_nScore; }            // �X�R�A

	static void AddScore(int nScore);  // �X�R�A���Z

protected:
	static int m_nScore;

private:
	D3DXVECTOR3 m_pos;              // �ʒu
	static CScore *m_Score;         // �X�R�A�̃|�C���^
	static CNumber *m_apNumber[8];  // �i���o�[�̃|�C���^
};

#endif