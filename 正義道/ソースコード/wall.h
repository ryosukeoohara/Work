//===========================================================
//
//�|���S�����o�����[field.h]
//Author �匴�叫
//
//===========================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "object3D.h"

//�}�N����`
#define MAX_WALL   (4)

class CWall : public CObject3D
{
public:
	CWall();
	~CWall();

	HRESULT Init(void);   //�t�B�[���h�̏���������    
	void Uninit(void);    //�t�B�[���h�̏I������
	void Update(void);    //�t�B�[���h�̍X�V����
	void Draw(void);      //�t�B�[���h�̕`�揈��

	static CWall *Create(void);  //����

private:
	int m_nIdxTexture;  //�e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject3D *m_Object3D[MAX_WALL];    //3D�I�u�W�F�N�g�ւ̃|�C���^

};
#endif // !_FIELD_H_