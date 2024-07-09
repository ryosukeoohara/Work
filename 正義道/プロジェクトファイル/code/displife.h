//===========================================================
//
// �|���S�����o�����[displife.h]
// Author �匴�叫
//
//===========================================================
#ifndef _DISPLIFE_H_             //���̃}�N����`������ĂȂ�������
#define _DISPLIFE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//�}�N����`
#define MAX_DISPLIFE   (64)

//===============================================================
// �N���X��`
//===============================================================
class CDispLife : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //�ߐ�
		TYPE_PLAYER,	 //�v���C���[
		TYPE_MAX
	};

	CDispLife();                                                  //�R���X�g���N�^
	CDispLife(D3DXVECTOR3 pos);                                   //�R���X�g���N�^(�I�[�o�[���[�h)
	~CDispLife();                                                 //�f�X�g���N�^

	HRESULT Init(void);                                           //�A�C�R���̏���������    
	void Uninit(void);                                            //�A�C�R���̏I������
	void Update(void);                                            //�A�C�R���̍X�V����
	void Draw(void);                                              //�A�C�R���̕`�揈��

	static CDispLife *Create(D3DXVECTOR3 pos);                    //����
	int SetDispLife(void);
	//CDispLife *GetDispLife(void) { return m_pDispLife; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                         //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                                            //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nMaxLife;

	TYPE m_type;                                                  //���

	//static CDispLife *m_pDispLife;                                
	static CObject2D *m_apObject2D[MAX_DISPLIFE];                   //2D�I�u�W�F�N�g�ւ̃|�C���^                  
};

#endif