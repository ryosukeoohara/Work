//===========================================================
//
// �����L���O�̃��S����[rankinglogo.h]
// Author �匴�叫
//
//===========================================================
#ifndef _RANKINGLOGO_H_             //���̃}�N����`������ĂȂ�������
#define _RANKINGLOGO_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//===========================================================
// �N���X��`
//===========================================================
class CRankinglogo : public CObject2D
{
public:

	CRankinglogo();                                //�R���X�g���N�^
	CRankinglogo(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CRankinglogo();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CRankinglogo *Create(D3DXVECTOR3 pos);             //����

private:

	int m_nIdxTexture;
};

#endif