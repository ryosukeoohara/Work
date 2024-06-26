//===========================================================
//
// �G�t�F�N�g2D[effect2D.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFECT2D_H__             //���̃}�N����`������ĂȂ�������
#define _EFFECT2D_H__             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object2D.h"

//===========================================================
// �G�t�F�N�g2D�N���X��`
//===========================================================
class CEffect2D : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_GROUND = 0,   // �y��
		TYPE_SMOOK,        // ��
		TYPE_MAX
	};

	CEffect2D();  //�R���X�g���N�^
	CEffect2D(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type);  //�R���X�g���N�^
	~CEffect2D();  //�f�X�g���N�^

				 // ���
	struct INFO
	{
		D3DXVECTOR3 pos;        // �ʒu
		D3DXVECTOR3 move;       // �ړ���
		D3DXCOLOR col;          // �F
		float fRadius;          // ���a(�傫��)
		int nLife;              // ����(�\������)
	};

	HRESULT Init(void); // ����������    
	void Uninit(void);  // �I������
	void Update(void);  // �X�V����
	void Draw(void);    // �`�揈��

	void Ground(void);
	void Blood(void);
	void Smook(void);
	void Circle(void);

	static CEffect2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type);  //����

	INFO m_Info;

private:

	TYPE m_type;               // ���
	int m_nIdxTexture;         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	static const char *m_apTexName[TYPE_MAX];

};

#endif