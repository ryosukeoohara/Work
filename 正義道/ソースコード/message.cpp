//===========================================================
//
//�|���S�����o�����[message.cpp]
//Author �匴�叫
//
//===========================================================
#include "message.h"
#include "object2D.h"

//�}�N����`
#define WIDTH       (150.0f)   //��
#define HIGHT       (25.0f)    //�c
#define MESSAEND    (120)      //���b�Z�[�W��\�����Ă�������

//===========================================================
//�ÓI�����o�ϐ�
//===========================================================
CMessage *CMessage::Obj2D[MAX_MESSA] = {};
int CMessage::m_nIdx = 0;

//===========================================================
//�R���X�g���N�^
//===========================================================
CMessage::CMessage()
{
	m_nType = TYPEMESS_NONE;
	MessaCounter = 0;
}

//===========================================================
//�R���X�g���N�^
//===========================================================
CMessage::CMessage(D3DXVECTOR3 pos, TYPEMESS type)
{
	m_nType = type;
	SetPos(&pos);
	MessaCounter = 0;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CMessage::~CMessage()
{

}

//===========================================================
//�C���X�^���X����
//===========================================================
CMessage *CMessage::Create(D3DXVECTOR3 pos, TYPEMESS type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	//CMessage *pMessage = NULL;

	int Idx = m_nIdx;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (Obj2D[Idx] == NULL && m_nIdx < MAX_MESSA)
		{
			//�I�u�W�F�N�g2D�̐���
			Obj2D[Idx] = new CMessage(pos, type);

			//����������
			Obj2D[Idx]->Init();

			m_nIdx++;
		}
	}

	return Obj2D[Idx];
}

//===========================================================
//����������
//===========================================================
HRESULT CMessage::Init(void)
{
	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CMessage::Uninit(void)
{
	//�I������
	CObject2D::Uninit();

	Obj2D[m_nIdx] = NULL;
}

//===========================================================
//�X�V����
//===========================================================
void CMessage::Update(void)
{
	//�X�V����
	CObject2D::Update();

	//�ʒu�擾
	D3DXVECTOR3 pos = Getpos();

	//���_���ݒ�
	SetVtxMessage(pos, WIDTH, HIGHT);

	//���䏈��
	Control();

	//�J�E���g�A�b�v
	MessaCounter++;

	if (MessaCounter >= MESSAEND)
	{//�\�����ĉ����Ԃ𒴂�����

		//�I������
		Uninit();
	}
}

//===========================================================
//�`�揈��
//===========================================================
void CMessage::Draw(void)
{
	//�`�揈��
	CObject2D::Draw();
}

//===========================================================
//���䏈��
//===========================================================
void CMessage::Control(void)
{
	for (int nCount = 0; nCount < m_nIdx; nCount++)
	{
		D3DXVECTOR3 pos = Obj2D[nCount]->Getpos();

		pos.y -= 1.0f;

		Obj2D[nCount]->SetPos(&pos);
	}
	
	for (int nCount = 0; nCount < MAX_MESSA - 1; nCount++)
	{
		if (Obj2D[nCount] == NULL && Obj2D[nCount + 1] != NULL)
		{
			Obj2D[nCount] = Obj2D[nCount + 1];
			Obj2D[nCount + 1] = NULL;
		}
	}

	if (m_nIdx >= MAX_MESSA)
	{
		m_nIdx = 0;
	}
}