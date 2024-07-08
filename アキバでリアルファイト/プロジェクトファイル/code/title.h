//===========================================================
//
// �^�C�g������[title.h]
// Author �匴�叫
//
//===========================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "manager.h"

//===========================================================
// �O���錾
//===========================================================
class CField;
class CObject2D;
class CMap;
class CPlayer;

//===========================================================
// �^�C�g���N���X��`
//===========================================================
class CTitle : public CScene
{
public:
	CTitle();             // �R���X�g���N�^
	~CTitle();            // �f�X�g���N�^

	HRESULT Init(void);   // ����������
	void Uninit(void);    // �I������
	void Update(void);    // �X�V����
	void Draw(void);      // �`�揈��

	static CTitle *Create(void);  // ��������
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	CField *m_pField;
	CObject2D *m_pBg;
	CObject2D *m_pStart;
	CMap *m_pMap;
	static CPlayer *m_pPlayer;
	int m_nCnt;
	int m_nCntPos;

};
#endif // !_TITLE_H_