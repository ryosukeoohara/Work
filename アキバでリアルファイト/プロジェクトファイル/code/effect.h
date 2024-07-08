//===========================================================
//
// �G�t�F�N�g����[effect.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFECT_H__             //���̃}�N����`������ĂȂ�������
#define _EFFECT_H__             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "billboard.h"

//===========================================================
// �G�t�F�N�g�N���X��`
//===========================================================
class CEffect : public CBillBoard
{
public:

	enum TYPE
	{
		TYPE_GROUND = 0,   // �y��
		TYPE_SMOOK,        // ��
		TYPE_MAX
	};

	CEffect();  //�R���X�g���N�^
	CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type);  //�R���X�g���N�^
	~CEffect();  //�f�X�g���N�^

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

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type);  //����
	
	INFO m_Info;

private:
	
	TYPE m_type;               // ���
	int m_nIdxTexture;         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	static const char *m_apTexName[TYPE_MAX];

};

#endif