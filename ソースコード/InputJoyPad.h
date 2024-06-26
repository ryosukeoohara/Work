//===========================================================
//
// �Q�[���p�b�g�̏���[InputJoyPad.h]
// Author �匴�叫
//
//===========================================================
#ifndef _INPUTJOYPAD_H_
#define _INPUTJOYPAD_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "input.h"

//===========================================================
// �Q�[���p�b�g�̃N���X��`
//===========================================================
class CInputJoyPad : public CInput
{
public:
	
	// �{�^���̎��
	enum PADBUTTON
	{
		BUTTON_UP = 0,  // �\���L�[��
		BUTTON_DOWN,    // �\���L�[��
		BOTTON_LEFT,    // �\���L�[��
		BUTTON_RIGHT,   // �\���L�[�E
		BUTTON_START,   // �X�^�[�g
		BUTTON_BACK,    // �߂�
		BUTTON_LTHUMB,  // 
		BUTTON_RTHUMB,  // 
		BUTTON_LB,      // ��
		BUTTON_RB,      // �E
		BUTTON_LT,      // ���g���K�[
		BUTTON_RT,      // �E�g���K�[
		BUTTON_A,       // A
		BUTTON_B,       // B
		BUTTON_X,       // X
		BUTTON_Y,       // Y
		STICK_LX,       // ���X�e�B�b�NX��
		STICK_LY,       // ���X�e�B�b�NY��
		STICK_RX,       // �E�X�e�B�b�NX��
		STICK_RY,       // �E�X�e�B�b�NY��
		BUTTON_MAX
	};

	CInputJoyPad();   //�R���X�g���N�^
	~CInputJoyPad();  //�f�X�g���N�^

	HRESULT Init(void);  //����������
	void Uninit(void);  //�I������
	void Update(void);  //�X�V����

	bool GetPress(PADBUTTON nKey, int nCntPlayer);
	bool GetTrigger(PADBUTTON nKey, int nCntPlayer);
	bool GetRelease(PADBUTTON nKey, int nCntPlayer);

	bool GetLeftTirgger(PADBUTTON nKey, int nCntPlayer);
	bool GetRightTirgger(PADBUTTON nKey, int nCntPlayer);

	float GetLXStick(PADBUTTON nKey, int nCntPlayer);
	float GetLYStick(PADBUTTON nKey, int nCntPlayer);

	float GetRXStick(PADBUTTON nKey, int nCntPlayer);
	float GetRYStick(PADBUTTON nKey, int nCntPlayer);

	float GetLYTriggerStick(PADBUTTON nKey, int nCntPlayer);

private:
	XINPUT_STATE m_State;
	XINPUT_STATE m_StateTrigger;
	XINPUT_STATE m_StateRelease;
	XINPUT_STATE m_StateRepeat;
};

#endif