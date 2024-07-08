//===========================================================
//
// �p�[�e�B�N������[particle.h]
// Author �匴�叫
//
//===========================================================
#ifndef _PARTICLE_H__             //���̃}�N����`������ĂȂ�������
#define _PARTICLE_H__             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "billboard.h"

//===========================================================
// �p�[�e�B�N���N���X��`
//===========================================================
class CParticle
{
public:

	// ���
	enum TYPE
	{
		TYPE_GROUND = 0,  // �y��
		TYPE_BLOOD,       // ���t
		TYPE_SMOOK,       // ��
		TYPE_CIRCLE,      // �~�`
		TYPE_GLASS,       // �K���X�̔j��
		TYPE_MAX
	};

	CParticle();                            // �R���X�g���N�^
	CParticle(D3DXVECTOR3 pos, TYPE type);  // �R���X�g���N�^
	~CParticle();                           // �f�X�g���N�^

	HRESULT Init(void);                     // ����������    
	void Uninit(void);                      // �I������
	void Update(void);                      // �X�V����
	void Draw(void);                        // �`�揈��

	static HRESULT Load(void);              // �e�N�X�`���̐���(�ǂݍ���)
	static void UnLoad(void);               // �e�N�X�`���̔j��

	void Move(void);
	void Blood(void);
	void Ground(void);
	void Smook(void);
	void Circle(void);
	void Glass(void);

	static CParticle *Create(D3DXVECTOR3 pos, TYPE type);  // ����
	D3DXCOLOR m_col;                                       // �F
	float m_fRadius;                                       // ���a(�傫��)
	int m_nLife;                                           // ����(�\������)
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                  // �e�N�X�`���ւ̃|�C���^
	TYPE m_type;

};

#endif