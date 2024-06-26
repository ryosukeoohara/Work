//===========================================================
//
// �t�B�[���h[field.h]
// Author �匴�叫
//
//===========================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "objectMesh.h"
#include "object3D.h"

//===========================================================
// �t�B�[���h�N���X��`
//===========================================================
class CField : public CObject3D
{
public:
	CField();
	~CField();

	HRESULT Init(void);   //�@����������    
	void Uninit(void);    //�@�I������
	void Update(void);    //�@�X�V����
	void Draw(void);      //�@�`�揈��

	static CField *Create(void);  //�@����

private:
	int m_nIdxTexture;  //�@�e�N�X�`���̃C���f�b�N�X�ԍ�

};

#endif // !_FIELD_H_