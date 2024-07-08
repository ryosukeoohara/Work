//===============================================================
//
//�`���[�g���A��UI����[tutorialUI.h]
// Author �匴�叫
//
//===============================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

#include "object2D.h"

#define MAX_TUTOOBJ     (8)

class CTutorialUI : public CObject2D
{
public:
	CTutorialUI();
	~CTutorialUI();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_AIM00,
		TYPE_AIM01,
		TYPE_AIM02,
		TYPE_AIM03,
		TYPE_AIM04,
		TYPE_AIM05,
		TYPE_LESSON01,
		TYPE_LESSON02,
		TYPE_LESSON03,
		TYPE_LESSON04,
		TYPE_LESSON05,
		TYPE_MAX
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialUI *Create(D3DXVECTOR3 pos, TYPE type);

	static CTutorialUI *GetUI(void) { return m_TutorialUI; }
	TYPE GetTypeUI(void) { return m_type; }

private:
	static CTutorialUI *m_TutorialUI;
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject2D *m_Object2D[MAX_TUTOOBJ];         //2D�I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;                                //���
};

#endif