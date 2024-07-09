//===========================================================
//
// �ڕWUI����[target.h]
// Author �匴�叫
//
//===========================================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "manager.h"
#include "object2D.h"
#include "number.h"

//�}�N����`
#define MAX_TITLEOBJ   (64)   //�^�C�g�����ł�2D�I�u�W�F�N�g�̍ő吔
#define MAX_NUMBER     (2)

//===========================================================
// �N���X��`
//===========================================================
class CTarget : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_FIRST,     //��ڂ̖ڕW
		TYPE_SECOND,    //��ڂ̖ڕW
		TYPE_FINAL,     //�Ō�̖ڕW
		TYPE_MAX
	};

	CTarget();
	CTarget(TYPE type, D3DXVECTOR3 pos);
	~CTarget();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTarget *Create(TYPE type, D3DXVECTOR3 pos);

	static void SetType(TYPE type) { m_type = type; }

private:
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	static TYPE m_type;                                //���
	static CNumber *m_apNumber[MAX_NUMBER];		  //�i���o�[�ւ̃|�C���^
	static CNumber *m_apNumCount[MAX_NUMBER];     //�i���o�[�ւ̃|�C���^

};
#endif // !_TITLE_H_