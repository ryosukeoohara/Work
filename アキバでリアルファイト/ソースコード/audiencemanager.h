//===========================================================
//
// ����Ō��Ă���l�̊Ǘ�[audiencemanager.h]
// Author �匴�叫
//
//===========================================================
#ifndef _AUDIENCEMANAGER_H_      //���̃}�N����`������ĂȂ�������
#define _AUDIENCEMANAGER_H_      //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"
#include "objectX.h"

//===========================================================
// �N���X��`
//===========================================================
class CAudienceManager
{
public:

	// ���
	enum TYPE
	{
		TYPE_01 = 0,
		TYPE_02,
		TYPE_03,
		TYPE_04,
		TYPE_MAX
	};

	CAudienceManager();   // �R���X�g���N�^
	~CAudienceManager();  // �f�X�g���N�^

	HRESULT Init(void);   // ����������    
	void Uninit(void);    // �I������
	void Update(void);    // �X�V����
	void Draw(void);      // �`�揈��

	static CAudienceManager* Create(void);  // ��������

private:

};

#endif