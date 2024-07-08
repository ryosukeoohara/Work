//===========================================================
//
//�|���S�����o�����[bg.h]
//Author �匴�叫
//
//===========================================================
#ifndef _FRAME_H_             //���̃}�N����`������ĂȂ�������
#define _FRAME_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"
#include "itemslot.h"

//�w�i�N���X
class CFrame : public CObject2D
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,    //�Ȃ�
		TYPE_NEAR,        //�ߋ���
		TYPE_FAR,         //������
		TYPE_BAT,         //�o�b�g
		TYPE_BOM,         //���e
		TYPE_MAX
	};

	CFrame();  //�R���X�g���N�^
	CFrame(D3DXVECTOR3 pos);  //�R���X�g���N�^
	~CFrame();  //�f�X�g���N�^

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static CFrame *Create(void);  //����

	static CFrame *GetFrame(void) { return m_Frame; }
	void SetACType(CFrame::TYPE type) { m_type = type; }
	CFrame::TYPE GetACType(void) { return m_type; }

private:
	static CFrame *m_Frame;
	int m_nIdxTexture;

	CFrame::TYPE m_type;
};

#endif