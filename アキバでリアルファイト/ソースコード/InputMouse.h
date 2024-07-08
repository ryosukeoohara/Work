//===========================================================
//
// �Q�[���p�b�g�̏���[InputMouse.h]
// Author �匴�叫
//
//===========================================================
#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "input.h"

//===========================================================
// �L�[�{�[�h�̃N���X��`
//===========================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();   // �R���X�g���N�^
	~CInputKeyboard();  // �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);  // ����������
	void Uninit(void);                             // �I������
	void Update(void);                             // �X�V����

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];
};

#endif