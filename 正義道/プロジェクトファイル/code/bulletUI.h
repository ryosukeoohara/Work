//===============================================================
//
//�`���[�g���A��UI����[tutorialUI.h]
// Author �匴�叫
//
//===============================================================
#ifndef _BULLETUI_H_
#define _BULLETUI_H_

#include "object2D.h"
#include "number.h"

#define MAX_NUMBER     (2)

//===============================================================
// �N���X��`
//===============================================================
class CBulletUI : public CObject2D
{
public:
	CBulletUI();
	CBulletUI(D3DXVECTOR3 pos);
	~CBulletUI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletUI *Create(D3DXVECTOR3 pos);

	static CBulletUI *GetUI(void) { return m_TutorialUI; }
	TYPE GetTypeUI(void) { return m_type; }

private:
	static CBulletUI *m_TutorialUI;
	int m_nIdxTexture;                          // �e�N�X�`���̃C���f�b�N�X�ԍ�
	static CNumber *m_apNumber[MAX_NUMBER];		// �i���o�[�ւ̃|�C���^
	TYPE m_type;                                // ���
};

#endif