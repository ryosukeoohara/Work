//===========================================================
//
//�|���S�����o�����[itemslot.h]
//Author �匴�叫
//
//===========================================================
#ifndef _TUTORIALLOGO_H_             //���̃}�N����`������ĂȂ�������
#define _TUTORIALLOGO_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//�A�C�e���N���X
class CTutoriallogo : public CObject2D
{
public:

	CTutoriallogo();                                //�R���X�g���N�^
	CTutoriallogo(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CTutoriallogo();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CTutoriallogo *Create(D3DXVECTOR3 pos);             //����

private:

	int m_nIdxTexture;
};

#endif