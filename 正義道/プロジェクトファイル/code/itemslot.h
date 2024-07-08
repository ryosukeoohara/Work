//===========================================================
//
//�|���S�����o�����[itemslot.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ITEMSLOT_H_             //���̃}�N����`������ĂȂ�������
#define _ITEMSLOT_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//�A�C�e���N���X
class CItemSlot : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_PROXIMITY = 0,   //�ߐ�
		TYPE_PROJECTILE,	  //��ѓ���
		TYPE_MAX
	};

	CItemSlot();                                //�R���X�g���N�^
	CItemSlot(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CItemSlot();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CItemSlot *Create(D3DXVECTOR3 pos);             //����

	CItemSlot::TYPE GetAttackType(void) { return m_type; }
	void SetAttackType(TYPE type) { m_type = type; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�

	//CObject2D *m_apObject2D[MAX_SLOT];

	TYPE m_type;
};

#endif