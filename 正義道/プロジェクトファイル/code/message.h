//===========================================================
//
//�|���S�����o�����[message.cpp]
//Author �匴�叫
//
//===========================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include "main.h"
#include "object2D.h"

#define MAX_MESSA   (3)       //�\�����郁�b�Z�[�W�̍ő吔

typedef enum
{
	TYPEMESS_NONE = 0,  //�Ȃ�
	TYPEMESS_START,     //�ŏ�
	TYPEMESS_DAMEGE,    //�_���[�W
	TYPEMESS_MAX
} TYPEMESS;

//���b�Z�[�W�N���X
class CMessage : public CObject2D
{
public:
	CMessage();
	CMessage(D3DXVECTOR3 pos, TYPEMESS type);
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Control(void);  //���䏈��
	static CMessage *Create(D3DXVECTOR3 pos, TYPEMESS type);  //����

private:
	TYPEMESS m_nType;  //���
	int MessaCounter;  //���b�Z�[�W��\�����Ă�������
	static int m_nIdx;        //�C���f�b�N�X�ԍ�
	static CMessage *Obj2D[MAX_MESSA];
};

#endif // !_MESSAGE_H_