//===========================================================
//
// ���C�t�Q�[�W����[lifegage.h]
// Author �匴�叫
//
//===========================================================
#ifndef _LIFEGAGE_H_             //���̃}�N����`������ĂȂ�������
#define _LIFEGAGE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//===========================================================
// �N���X��`
//===========================================================
class CLifegage : public CObject2D
{
public:

	CLifegage();                                //�R���X�g���N�^
	CLifegage(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CLifegage();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CLifegage *Create(D3DXVECTOR3 pos);             //����

private:
	int m_nIdxTexture;
};

#endif