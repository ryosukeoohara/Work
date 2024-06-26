//===========================================================
//
// �}�E�X�̏���[InputMouse.cpp]
// Author �匴�叫
//
//===========================================================
#include "InputMouse.h"
#include "debugproc.h"
#include "manager.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CInputMouse::CInputMouse()
{
	
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CInputMouse::~CInputMouse()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != NULL)
	{
		// ���̓f�o�C�X�i�}�E�X�j�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		// �f�[�^�t�H�[�}�b�g
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
		{
			return E_FAIL;
		}

		// �������[�h��ݒ�
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			return E_FAIL;
		}
	}

	// �A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CInputMouse::Uninit(void)
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//===========================================================
// �X�V����
//===========================================================
void CInputMouse::Update(void)
{
	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc* pDebugProc = CManager::Getinstance()->GetDebugProc();

	//�}�E�X���W���擾����
	POINT pos;
	GetCursorPos(&pos);

	//�X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &pos);

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{

	}
	else
	{
		m_pDevice->Acquire();     //�}�E�X�A�N�Z�X�����l��
	}

	if (pDebugProc == nullptr)
		return;
	
	pDebugProc->Print("\n---�}�E�X�̏��---");
	pDebugProc->Print("\n<<�ʒu : X:%d Y:%d>>", pos, pos);
	pDebugProc->Print("\n<<[X] : %f, [Y] : %f>>", (float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
	pDebugProc->Print("\n<<�z�C�[���̉�]�� : %f>>", (float)m_CurrentMouseState.lZ);
}

//===========================================================
// �E�N���b�N�̏��擾
//===========================================================
bool CInputMouse::GetLButton(void)
{
	return (m_CurrentMouseState.rgbButtons[0] & 0x80) ? true : false;
}

//===========================================================
// ���N���b�N�̏��擾
//===========================================================
bool CInputMouse::GetRButton(void)
{
	return (m_CurrentMouseState.rgbButtons[1] & 0x80) ? true : false;
}

//===========================================================
// �z�C�[���擾
//===========================================================
bool CInputMouse::GetWheel(void)
{
	return (m_CurrentMouseState.rgbButtons[2] & 0x80) ? true : false;
}

//===========================================================
// �ړ��ʂ̎擾
//===========================================================
D3DXVECTOR2 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

//===========================================================
// �z�C�[���̉�]�ʎ擾
//===========================================================
float CInputMouse::GetMouseWheel(void)
{
	return (float)m_CurrentMouseState.lZ;
}