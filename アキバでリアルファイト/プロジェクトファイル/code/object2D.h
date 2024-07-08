//===========================================================
//
// 2D�I�u�W�F�N�g����[object2D.h]
// Author �匴�叫
//
//===========================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object.h"

//===========================================================
// 2D�I�u�W�F�N�g�N���X��`
//===========================================================
class CObject2D : public CObject
{
public:		//�N�ł��A�N�Z�X�ł���
	CObject2D(int nPriority = 3);                   // �R���X�g���N�^
	CObject2D(D3DXVECTOR3 pos, int nPriority = 3);  // �R���X�g���N�^
	~CObject2D();                                   // �f�X�g���N�^

	HRESULT Init(void);                             // ����������
	void Uninit(void);                              // �I������
	void Update(void);                              // �X�V����
	void Draw(void);                                // �`�揈��

	static CObject2D *Create(int nPriority = 3);                   // ����
	static CObject2D *Create(D3DXVECTOR3 pos, int nPriority = 3);  // ����

	// �ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }              // �ʒu
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }              // ����
	void SetColor(D3DXCOLOR col);                                   // �F
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }                // �e�N�X�`���̃C���f�b�N�X�ԍ�
	void SetSize(float fWidth, float fHeight);                      // �T�C�Y:���S���^��
	void SetEdgeCenter(float fWidth, float fHeight);                // �T�C�Y:���S�����[
	void SetEdgeCenterTex(float ftex);                              // �e�N�X�`�����W�ύX:���S���^��
	void SetTex(float fTex);                                        // �e�N�X�`�����W�ύX:���S�����[
	void SetDraw(bool bverdict = true) { m_bDraw = bverdict; }      // �`�悷�邩�ǂ���
	void SetColorA(float fCola);
	
	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_pos; }     // �ʒu
	D3DXVECTOR3 GetRotition(void) { return m_rot; }     // ����
	D3DXCOLOR GetColor(void) { return m_col; }          // �F
	int GetIdxTex(void) { return m_nIdxTexture;	}       // �e�N�X�`���̃C���f�b�N�X�ԍ�
	float GetHeight(void) { return m_fHeight; }         // ����
	float GetWidth(void) { return m_fWidth; }           // ��
	bool GetDraw(void) { return m_bDraw; }              // �`�悷�邩�ǂ���

private:	//�����������A�N�Z�X�ł���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   // ���_�����i�[
	D3DXVECTOR3 m_pos;                    // �ʒu
	D3DXVECTOR3 m_rot;                    // ����
	D3DXCOLOR m_col;                      // �F
	int m_nIdxTexture;                    // �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCounterAnimPlayer = 0;         // �J�E���^�[������������
	int m_nPatternAnimPlayer = 0;         // �p�^�[��No.������������
	int m_Number;
	float m_fHeight;                      // ����
	float m_fWidth;                       // ��
	bool m_bDraw;                         // �`�悷�邩�ǂ���
};

#endif