//===========================================================
//
// ���U���g���[result.h]
// Author �匴�叫
//
//===========================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "manager.h"

//===========================================================
// �O���錾
//===========================================================
class CField;
class CMap;
class CAppearanceUI;
class CUserRankUI;

//===========================================================
// ���U���g�N���X��`
//===========================================================
class CResult : public CScene
{
public:
	CResult();                     // �R���X�g���N�^
	~CResult();                    // �f�X�g���N�^
						           
	HRESULT Init(void);            // ����������
	void Uninit(void);             // �I������
	void Update(void);             // �X�V����
	void Draw(void);               // �`�揈��

	static CResult *Create(void);  // ��������

private:
	CMap *m_pMap;
	CField *m_pField;
	CAppearanceUI *m_pNumber;
	CUserRankUI *m_pUserRank;

	int m_nCounter;
};

#endif