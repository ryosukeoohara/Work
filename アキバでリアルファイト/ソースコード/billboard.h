//===========================================================
//
// �r���{�[�h���� [billboard.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _BILLBOARD_H_             //���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"
#include "object.h"

//===========================================================
// �r���{�[�h�N���X��`
//===========================================================
class CBillBoard : public CObject
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_HIT,
		TYPE_MAX
	};

	CBillBoard(int nPriority = 3);
	~CBillBoard();

	HRESULT Init(void);  // ����������    
	void Uninit(void);   // �I������
	void Update(void);   // �X�V����
	void Draw(void);     // �`�揈��
	
	static CBillBoard *Create(int nPriority = 3);  //����

	// �ݒ�n
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }        // �e�̃}�g���b�N�X
	void SetSize(float fHeight, float fWidth);                            // �T�C�Y(���S���^��)
	void SetEdgeCenter(float fWidth, float fHeight);                      // �T�C�Y(�p���^��)
	void SetTex(float fTex);
	void SetAnim(void);
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }                      // �e�N�X�`���̃C���f�b�N�X�ԍ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }                    // �ʒu
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }                    // ����
	void SetColor(D3DXCOLOR col);                                         // �F
	void SetType(TYPE type) { m_Type = type; }                            // ���
	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }                  // �`�悷�邩�ǂ���

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotition(void) { return m_rot; }

private:
	LPDIRECT3DTEXTURE9 m_pTexture;             // �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxWorld;                     // ���[���h�}�g���b�N�X
	D3DXMATRIX *m_pCurrent;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;        // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;                         // �ʒu
	D3DXVECTOR3 m_rot;                         // ����
	D3DXCOLOR m_col;                           // �F
	int m_nIdxTexture;                         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nNowPattern;                         // �A�j���[�V�����p�^�[��
	int m_nNumPattern;                         // �A�j���[�V�����p�^�[��
	int m_nCounterAnim;
	int m_nHeight;
	int m_nWidth;
	float m_fHeight;                           // ����
	float m_fWidth;                            // ��
	bool m_bDraw;                              // �`�悷�邩�ǂ���

	TYPE m_Type;
};

#endif