//===========================================================
//
// �A�C�R������[icon.h]
// Author �匴�叫
//
//===========================================================
#ifndef _ICON_H_             //���̃}�N����`������ĂȂ�������
#define _ICON_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//===========================================================
// �N���X��`
//===========================================================
class CIcon : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //�ߐ�
		TYPE_PLAYER,	 //�v���C���[
		TYPE_MAX
	};

	CIcon();                                                      //�R���X�g���N�^
	CIcon(D3DXVECTOR3 pos, TYPE type);                            //�R���X�g���N�^(�I�[�o�[���[�h)
	~CIcon();                                                     //�f�X�g���N�^

	HRESULT Init(void);                                           //�A�C�R���̏���������    
	void Uninit(void);                                            //�A�C�R���̏I������
	void Update(void);                                            //�A�C�R���̍X�V����
	void Draw(void);                                              //�A�C�R���̕`�揈��

	static CIcon *Create(D3DXVECTOR3 pos, TYPE type);             //����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                         //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                                            //�e�N�X�`���̃C���f�b�N�X�ԍ�

	TYPE m_type;                                                  //���
};

#endif