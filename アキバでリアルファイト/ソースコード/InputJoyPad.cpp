//===========================================================
//
// �Q�[���p�b�g�̏���[InputJoyPad.cpp]
// Author �匴�叫
//
//===========================================================
#include "InputJoyPad.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CInputJoyPad::CInputJoyPad()
{
	ZeroMemory(&m_State, sizeof(m_State));
	ZeroMemory(&m_StateRelease, sizeof(m_StateRelease));
	ZeroMemory(&m_StateTrigger, sizeof(m_StateTrigger));
	ZeroMemory(&m_StateRepeat, sizeof(m_StateRepeat));
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CInputJoyPad::~CInputJoyPad()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CInputJoyPad::Init(void)
{
	XInputEnable(true);

	memset(&m_State, 0, sizeof(XINPUT_STATE));
	memset(&m_StateTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_StateRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_StateRepeat, 0, sizeof(XINPUT_STATE));

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CInputJoyPad::Uninit(void)
{
	XInputEnable(false);
}

//===========================================================
// �X�V����
//===========================================================
void CInputJoyPad::Update(void)
{
	XINPUT_STATE aState;

	if (XInputGetState(0, &aState) == ERROR_SUCCESS)
	{
		// �g���K�[
		m_StateTrigger.Gamepad.wButtons =
			(m_State.Gamepad.wButtons ^ aState.Gamepad.wButtons)
			& aState.Gamepad.wButtons;

		// �����[�X
		m_StateRelease.Gamepad.wButtons =
			(m_State.Gamepad.wButtons | aState.Gamepad.wButtons)
			^ aState.Gamepad.wButtons;

		// �v���X
		m_State = aState;
	}
	else
	{
		return;
	}

}

//===========================================================
// �v���X�擾����
//===========================================================
bool CInputJoyPad::GetPress(PADBUTTON nKey, int nCntPlayer)
{
	return (m_State.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===========================================================
// �g���K�[�擾����
//===========================================================
bool CInputJoyPad::GetTrigger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===========================================================
// �����[�X�擾����
//===========================================================
bool CInputJoyPad::GetRelease(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateRelease.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//===========================================================
// ���g���K�[�{�^���擾����
//===========================================================
bool CInputJoyPad::GetLeftTirgger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger.Gamepad.bLeftTrigger & (0x01 << nKey)) ? true : false;
}

//===========================================================
// �E�g���K�[�{�^���擾����
//===========================================================
bool CInputJoyPad::GetRightTirgger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger.Gamepad.bRightTrigger & (0x01 << nKey)) ? true : false;
}

//===========================================================
// ���X�e�B�b�N��X���擾����
//===========================================================
float CInputJoyPad::GetLXStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State.Gamepad.sThumbLX > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbLX;
	}

	if (m_State.Gamepad.sThumbLX < -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbLX;
	}

	return 0.0f;
}

//===========================================================
// ���X�e�B�b�N��Y���擾����
//===========================================================
float CInputJoyPad::GetLYStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State.Gamepad.sThumbLY > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbLY;
	}

	if (m_State.Gamepad.sThumbLY < -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbLY;
	}

	return 0.0f;
}

//===========================================================
// �E�X�e�B�b�N��X���擾����
//===========================================================
float CInputJoyPad::GetRXStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State.Gamepad.sThumbRX > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbRX;
	}

	if (m_State.Gamepad.sThumbRX < -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbRX;
	}

	return 0.0f;
}

//===========================================================
// �E�X�e�B�b�N��Y���擾����
//===========================================================
float CInputJoyPad::GetRYStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State.Gamepad.sThumbRY > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbRY;
	}

	if (m_State.Gamepad.sThumbRY < -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State.Gamepad.sThumbRY;
	}

	return 0.0f;
}