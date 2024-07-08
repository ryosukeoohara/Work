//===============================================================
//
//�`���[�g���A��UI����[tutorialUI.h]
// Author �匴�叫
//
//===============================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "object2D.h"

#define MAX_TUTOOBJ     (8)

class CGameUI : public CObject2D
{
public:
	CGameUI();
	~CGameUI();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_AIM00,
		TYPE_AIM01,
		TYPE_AIM02,
		TYPE_AIM03,
		TYPE_LESSON01,
		TYPE_LESSON02,
		TYPE_LESSON03,
		TYPE_LESSON04,
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,     //�����Ȃ�
		STATE_MOVE,         //�ړ�
		STATE_STOP,         //�`���b�g�~�܂�
		STATE_MAX
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGameUI *Create(D3DXVECTOR3 pos, TYPE type);

	static CGameUI *GetUI(void) { return m_pGameUI; }
	TYPE GetTypeUI(void) { return m_type; }
	STATE GetState(void) { return m_state; }

private:
	static CGameUI *m_pGameUI;
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCntMove;                             //�Ăшړ����n�߂�܂ł̃J�E���g
	TYPE m_type;                                //���
	STATE m_state;                              //���
};

#endif