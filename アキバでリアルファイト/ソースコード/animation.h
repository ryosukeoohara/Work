//===========================================================
//
// �e�N�X�`���A�j���[�V����[animation.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ANIMATION_H__             // ���̃}�N����`������ĂȂ�������
#define _ANIMATION_H__             // 2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "billboard.h"

//===========================================================
// �A�j���[�V�����N���X��`
//===========================================================
class CAnimation : public CBillBoard
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,    // �Ȃ���Ȃ�
		TYPE_HIT,         // �U���q�b�g
		TYPE_MAX
	};

	CAnimation();  //�R���X�g���N�^
	CAnimation(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, TYPE type);  //�R���X�g���N�^
	~CAnimation();  //�f�X�g���N�^

	// ���
	struct INFO
	{
		D3DXVECTOR3 pos;        // �ʒu
		D3DXVECTOR3 move;       // �ړ���
		D3DXCOLOR col;          // �F
		TYPE type;              // ���
		float fRadius;          // ���a(�傫��)
		int nLife;              // ����(�\������)
	};

	HRESULT Init(void); // ����������    
	void Uninit(void);  // �I������
	void Update(void);  // �X�V����
	void Draw(void);    // �`�揈��

	static CAnimation *Create(D3DXVECTOR3 pos, float fRadius, CBillBoard::TYPE type);  //����

	INFO m_Info;

private:

	
	int m_nIdxTexture;         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	static const char *m_apTexName[TYPE_MAX];

};

#endif