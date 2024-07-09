//===========================================================
//
// �Ռ��g[impact.h]
// Author �匴�叫
//
//===========================================================
#ifndef _IMPACT_H_             //���̃}�N����`������ĂȂ�������
#define _IMPACT_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object3D.h"

//===========================================================
// �N���X��`
//===========================================================
class CImpact : public CObject3D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,   //�ߐ�
		TYPE_MAX
	};

	CImpact();                                //�R���X�g���N�^
	CImpact(D3DXVECTOR3 pos, TYPE type);      //�R���X�g���N�^(�I�[�o�[���[�h)
	~CImpact();                               //�f�X�g���N�^

	HRESULT Init(void);                         //�|���S���̏���������    
	void Uninit(void);                          //�|���S���̏I������
	void Update(void);                          //�|���S���̍X�V����
	void Draw(void);                            //�|���S���̕`�揈��

	static CImpact *Create(D3DXVECTOR3 pos, TYPE type);             //����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	TYPE m_type;                                //���

	float m_SizeX;		                        //X�̂�������
	float m_SizeZ;		                        //Z�̂�������
};

#endif