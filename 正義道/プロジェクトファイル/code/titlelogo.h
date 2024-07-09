//===========================================================
//
// �^�C�g�����S����[titlelogo.h]
// Author �匴�叫
//
//===========================================================
#ifndef _TITLELOGO_H_             //���̃}�N����`������ĂȂ�������
#define _TITLELOGO_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "itemslot.h"

//�}�N����`
#define MAX_SLOT   (7)  //�X���b�g�̍ő吔

//===========================================================
// �N���X��`
//===========================================================
class CTitlelogo : public CObject2D
{
public:

	CTitlelogo();                                //�R���X�g���N�^
	CTitlelogo(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CTitlelogo();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CTitlelogo *Create(D3DXVECTOR3 pos);             //����

private:
	
	int m_nIdxTexture;
};

#endif