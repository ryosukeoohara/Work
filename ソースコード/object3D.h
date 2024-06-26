//===========================================================
//
// 3D�I�u�W�F�N�g����[object3D.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _OBJECT3D_H_             //���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"
#include "object.h"

//===========================================================
// 3D�I�u�W�F�N�g�N���X��`
//===========================================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);  // �R���X�g���N�^
	CObject3D(D3DXVECTOR3 pos);    // �R���X�g���N�^
	~CObject3D();                  // �f�X�g���N�^

	HRESULT Init(void);            // ����������    
	void Uninit(void);             // �I������
	void Update(void);             // �X�V����
	void Draw(void);               // �`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  // �e�N�X�`�����o�C���h

	// �ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }                    // �ʒu
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }                    // ����
	void SetColor(D3DXCOLOR col) { m_col = col; }                         // �F
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }                      // �e�N�X�`���̃C���f�b�N�X�ԍ�
	void SetSize(float fHeight, float fWidth);                            // �T�C�Y
	void SetEdgeCenter(float fWidth, float fHeight);                      // �T�C�Y
	void SetDraw(bool bverdict) { m_bDraw = bverdict; }                   // �`�悷�邩�ǂ���
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }        // �e�̃}�g���b�N�X

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_pos; }     // �ʒu
	D3DXVECTOR3 GetRotition(void) { return m_rot; }     // ����
	D3DXCOLOR GetColor(void) { return m_col; }          // �F
	int GetIdxTex(void) { return m_nIdxTexture; }       // �e�N�X�`���̃C���f�b�N�X�ԍ�
	
	static CObject3D *Create(int nPriority = 3);  //����
	static CObject3D *Create(D3DXVECTOR3 pos);    //����

private:
	LPDIRECT3DTEXTURE9 m_pTexture;             // �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;                     // ���[���h�}�g���b�N�X
	D3DXMATRIX *m_pCurrent;                    // �e�̃}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;        // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;                         // �ʒu
	D3DXVECTOR3 m_rot;                         // ����
	D3DXCOLOR m_col;                           // �F
	int m_nIdxTexture;                         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	float m_fHeight;                           // ����
	float m_fWidth;                            // ��
	bool m_bDraw;                              // �`�悷�邩�ǂ���
};



#endif