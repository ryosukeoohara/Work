//===========================================================
//
// ���f���̃G�t�F�N�g[effect3D.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFECT3D_H__             //���̃}�N����`������ĂȂ�������
#define _EFFECT3D_H__             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "objectX.h"

//===========================================================
// �G�t�F�N�g3D�N���X��`
//===========================================================
class CEffect3D : public CObjectX
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   // �Ȃ���Ȃ�
		TYPE_BIKE,       // ���]��
		TYPE_GLASS,      // �K���X�̔j��
		TYPE_MAX
	};

	CEffect3D();  // �R���X�g���N�^
	CEffect3D(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife, TYPE type, const char *modelfilename);  // �R���X�g���N�^
	~CEffect3D();  // �f�X�g���N�^

				 // �G�t�F�N�g�̍\����
	struct Info
	{
		D3DXVECTOR3 pos;        // �ʒu
		D3DXVECTOR3 rot;        // ����
		D3DXVECTOR3 move;       // �ړ���
		D3DXCOLOR col;          // �F
		float fRadius;          // ���a(�傫��)
		int nLife;              // ����(�\������)
	} ;

	HRESULT Init(void);           // ����������    
	void Uninit(void);            // �I������
	void Update(void);            // �X�V����
	void Draw(void);              // �`�揈��
	 
	void Bike(void);              // ���]��
	void Glass(void);             // �K���X�̔j��

	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife, TYPE type, const char *modelfilename);  // ����
	D3DXCOLOR m_col;          // �F
	float m_fRadius;          // ���a(�傫��)
	int m_nLife;              // ����(�\������)
	D3DXVECTOR3 m_move;
	Info m_Info;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���ւ̃|�C���^
	TYPE m_type;                           // ���
	int m_nIdxTexture;                     // �e�N�X�`���̃C���f�b�N�X�ԍ�

};

#endif