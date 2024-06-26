//===========================================================
//
// �����֘A�̏���[number.h]
// Author �匴�叫
//
//===========================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"
#include "object2D.h"

//===========================================================
// �����֘A�N���X��`
//===========================================================
class CNumber : public CObject2D 
{
public:		//�N�ł��A�N�Z�X�ł���
	CNumber();                         // �R���X�g���N�^
	CNumber(D3DXVECTOR3 pos);          // �R���X�g���N�^
	~CNumber();                        // �f�X�g���N�^
									   
	enum TYPE						   
	{								   
		TYPENUMBER_NONE = 0,		   
		TYPENUMBER_TIME,               // ����
		TYPENUMBER_SCORE,              // �X�R�A
		TYPENUMBER_DESTROYCOUNTER,     // �G��|������
		TYPENUMBER_MAX				   
	} ;								   
									   
	HRESULT Init(void);                // ����������
	void Uninit(void);                 // �I������
	void Update(void);                 // �X�V����
	void Draw(void);                   // �`�揈��

	// �ݒ�
	void SetPosition(D3DXVECTOR3 pos);                                 // �ʒu
	void SetVtxCounter(D3DXVECTOR3 pos, float fWidth, float fHeight);  // 
	void SetNumberType(TYPE type) { m_ntype = type; }                  // ���
	void SetNumber(int nNumber);                                       // ����

	// �擾
	D3DXVECTOR3 GetPosition(void);                                     // �ʒu
	TYPE GetNumberType(void) { return m_ntype; }                       // ���
	int GetNumber(void) { return m_Number; }                           // ����

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);                    // �e�N�X�`�����o�C���h
	static CNumber *Create(D3DXVECTOR3 pos);                           // ��������
	int m_Number;

private:	//�����������A�N�Z�X�ł���
	LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   // ���_�����i�[
	D3DXVECTOR3 m_pos;                    // �ʒu
	TYPE m_ntype;                         // ���
	static CObject2D *m_apObject2D;       // �I�u�W�F�N�g2D�̃|�C���^
	int m_nTimerCount;                    // ���Ԃ̃J�E���^�[
	int m_nIdxTexture;                    // �e�N�X�`���̃C���f�b�N�X�ԍ�

};

#endif // !1