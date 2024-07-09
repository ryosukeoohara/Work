//===========================================================
//
// �A�C�e���A�C�R������[itemicon.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ITEMICON_H_             //���̃}�N����`������ĂȂ�������
#define _ITEMICON_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//===========================================================
// �N���X��`
//===========================================================
class CItemIcon : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_PROXIMITY = 0,   //�ߐ�
		TYPE_PROJECTILE,	  //��ѓ���
		TYPE_KUGIBAT,         //�B�o�b�g
		TYPE_BOM,             //���e
		TYPE_MAX
	};

	CItemIcon();                                //�R���X�g���N�^
	CItemIcon(D3DXVECTOR3 pos, TYPE type);      //�R���X�g���N�^(�I�[�o�[���[�h)
	~CItemIcon();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CItemIcon *Create(D3DXVECTOR3 pos, TYPE type);             //����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�

	TYPE m_type;
};

#endif
