//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "InputMouse.h"
#include "InputJoyPad.h"
#include "title.h"
#include "game.h"
#include "player.h"
#include "enemymanager.h"
#include "UImanager.h"
#include "appearanceUI.h"
#include "tutorial.h"
#include "enemy.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const D3DXVECTOR3 HEAT_CAMERAROT = { 0.0f, -D3DX_PI * 0.75f, D3DX_PI * -0.38f };   // �ڕW�̊p�x
	const D3DXVECTOR3 ONSTAGE_POSV = { 0.0f, 150.0f, -100.0f };   // �ڕW�̊p�x
	const D3DXVECTOR3 ONSTAGE_POSR = { 0.0f, 50.0f, 0.0f };       // �ڕW�̊p�x
	const float CAMERA_DISTNCE = 300.0f;  // ����
	const float CAMERA_MOVE = 2.0f;       // �ړ���
	const float CAMERA_ROT_Y = 0.03f;     // Y���̉�]��
}

//================================================================
// �R���X�g���N�^
//================================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mode = MODE_NONE;
	m_nCounter = 0;
	m_fLen = 0.0f;
}

//================================================================
// �f�X�g���N�^
//================================================================
CCamera::~CCamera()
{

}

//================================================================
// ����������
//================================================================
void CCamera::Init(void)
{
	CScene *pScene = CManager::Getinstance()->GetScene();

	if (pScene->GetMode() == CScene::MODE_TITLE)
	{
		m_posV = D3DXVECTOR3(0.0f, 200.0f, -500.0f);
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ����
	m_fLen = CAMERA_DISTNCE;
}

//================================================================
// �I������
//================================================================
void CCamera::Uninit(void)
{
	
}

//================================================================
// �X�V����
//================================================================
void CCamera::Update(void)
{
	Mode();
} 

//================================================================
// �ݒ菈��
//================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		100000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//================================================================
// �������Z�b�g
//================================================================
void CCamera::Reset(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================================
// ���[�h�ݒ�
//================================================================
void CCamera::SetMode(MODE type)
{
	m_mode = type;
}

//================================================================
// �����_�ݒ�
//================================================================
void CCamera::SetPositionR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}

//================================================================
// ���_�ݒ�
//================================================================
void CCamera::SetPositionV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//================================================================
// �����ݒ�
//================================================================
void CCamera::SetRotation(D3DXVECTOR3 Rot)
{
	m_rot = Rot;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================================
// �����ݒ�
//================================================================
void CCamera::SetDistnce(float fLen)
{
	m_fLen = fLen;
}

//================================================================
// ���[�h�擾
//================================================================
CCamera::MODE CCamera::GetMode(void)
{
	return m_mode;
}

//================================================================
// ���[�h
//================================================================
void CCamera::Mode(void)
{
	//�V�[���̏�������
	CScene *pScene = CManager::Getinstance()->GetScene();

	switch (m_mode)
	{
	case MODE_NONE:
		break;

	case MODE_TITLE:

		Title();
		break;

	case MODE_TUTORIAL:

		m_OldposR = m_posR;
		m_OldposV = m_posV;
		m_Oldrot = m_rot;
		m_fOldLen = m_fLen;
		Tutorial();
		break;

	case MODE_GAME:

		m_OldposR = m_posR;
		m_OldposV = m_posV;
		m_Oldrot = m_rot;
		m_fOldLen = m_fLen;

		CameraV();
		break;

	case MODE_RESULT:

		break;

	case MODE_HEAT:

		Heat();
		break;

	case MODE_RETURN:
		
		Return();
		break;

	case MODE_DEBUG:

		Debug();
		break;

	case MODE_ONSTAGE:

		OnStage();
		break;

	case MODE_MAX:
		break;

	default:
		break;
	}

	//������ݒ�
	SetRotation(m_rot);

	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n---�J�����̏��---");
	pDebugProc->Print("\n�J�����̈ʒu���_�FX��<%f>,Y��<%f>,Z��<%f>", m_posV.x, m_posV.y, m_posV.z);
	pDebugProc->Print("\n�J�����̈ʒu�����_�FX��<%f>,Y��<%f>,Z��<%f>", m_posR.x, m_posR.y, m_posR.z);
	pDebugProc->Print("\n�J�����̌��� �FX��<%f>,Y��<%f>,Z��<%f>", m_rot.x, m_rot.y, m_rot.z);
}

//================================================================
// ���A�c�A�N�V����
//================================================================
void CCamera::Heat(void)
{
	m_posV.x = m_posR.x - sinf(m_rot.y) * -m_fLen;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -m_fLen;

	D3DXVECTOR3 pos = CPlayer::GetPlayer()->GetPosition();

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, 50.0f, pos.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//�ڕW�̒����_��ݒ�
	m_posRDest.x = pos.x;
	m_posRDest.z = pos.z;

	//�J�����̈ړ���
	m_move.x = m_posRDest.x - m_posR.x;
	m_move.z = m_posRDest.z - m_posR.z;

	//�ʒu�Ɉړ��ʂ�ۑ�
	m_posR.x += m_move.x;
	m_posR.z += m_move.z;
}

//================================================================
// ���̈ʒu�ɖ߂��Ă���
//================================================================
void CCamera::Return(void)
{
	if (m_nCounter <= 90)
	{
		// �J������ڕW�̌����܂ŉ�]������
		D3DXVECTOR3 rotDest = m_Oldrot - m_rot;
		SetRotation(m_rot + rotDest * 0.05f);

		D3DXVECTOR3 posDestR = m_OldposR - m_posR;
		SetPositionR(m_posR + posDestR * 0.05f);

		D3DXVECTOR3 posDestV = m_OldposV - m_posV;
		SetPositionV(m_posV + posDestV * 0.05f);

		float fLenDest = m_fOldLen - m_fLen;
		SetDistnce(m_fLen + fLenDest * 0.05f);

		m_nCounter++;
	}
	else
	{
		// �J�E���^�[�����Z�b�g
		m_nCounter = 0;

		if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
		{
			// �J�������[�h���Q�[��
			m_mode = MODE_GAME;

			CGame::GetPlayer()->SetMobile();

			CGame::GetEnemyManager()->SetMobility();
		}
		else if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// �J�������[�h���Q�[��
			m_mode = MODE_TUTORIAL;

			CTutorial::GetPlayer()->SetMobile();
		}
	}
}

//================================================================
// ����[����
//================================================================
void CCamera::Debug(void)
{
	
}

//================================================================
// �o��
//================================================================
void CCamera::OnStage(void)
{
	if (m_nCounter <= 80)
	{
		D3DXVECTOR3 posDestR = ONSTAGE_POSR - m_posR;
		SetPositionR(m_posR + posDestR * 0.05f);

		D3DXVECTOR3 posDestV = ONSTAGE_POSV - m_posV;
		SetPositionV(m_posV + posDestV * 0.05f);

		m_posV.x = m_posR.x - sinf(m_rot.y) * -m_fLen;
		m_posV.z = m_posR.z - cosf(m_rot.y) * -m_fLen;

		m_nCounter++;
	}
	/*else if (m_nCounter <= 80 && m_nCounter <= 140)
	{
		if (CGame::GetWave() == CGame::WAVE_00)
		{
			CAppearanceUI::Create(CAppearanceUI::TYPE_WEAKNAME);
		}
		else if (CGame::GetWave() == CGame::WAVE_01)
		{
			CAppearanceUI::Create(CAppearanceUI::TYPE_BOSSNAME);
		}

		m_nCounter++;
	}*/
	else
	{
		// �J�������[�h���Q�[��
		m_mode = MODE_RETURN;

		// �J�E���^�[�����Z�b�g
		m_nCounter = 0;

		if (CGame::GetWave() == CGame::WAVE_00)
		{
			CAppearanceUI::Create(CAppearanceUI::TYPE_WEAKNAME);
		}
		else if (CGame::GetWave() == CGame::WAVE_01)
		{
			CAppearanceUI::Create(CAppearanceUI::TYPE_BOSSNAME);
		}
	}
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::CameraV(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X�̏����擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	CPlayer *pPlayer = CGame::GetPlayer();

	if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) > 0)
	{
		m_rot.y += 0.05f;
	}
	else if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) < 0)
	{
		m_rot.y -= 0.05f;
	}

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * -m_fLen;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -m_fLen;

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f, 0.0f + m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, 50.0f, pos.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//�ڕW�̒����_��ݒ�
	m_posRDest.x = pos.x;
	m_posRDest.z = pos.z;

	//�J�����̈ړ���
	m_move.x = m_posRDest.x - m_posR.x;
	m_move.z = m_posRDest.z - m_posR.z;

	//�ʒu�Ɉړ��ʂ�ۑ�
	m_posR.x += m_move.x;
	m_posR.z += m_move.z;
}

//================================================================
// �`���[�g���A��
//================================================================
void CCamera::Tutorial(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X�̏����擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	CPlayer *pPlayer = CTutorial::GetPlayer();

	if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) > 0)
	{
		m_rot.y += 0.05f;
	}
	else if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) < 0)
	{
		m_rot.y -= 0.05f;
	}

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * -m_fLen;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -m_fLen;

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, 50.0f, pos.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//�ڕW�̒����_��ݒ�
	m_posRDest.x = pos.x;
	m_posRDest.z = pos.z;

	//�J�����̈ړ���
	m_move.x = m_posRDest.x - m_posR.x;
	m_move.z = m_posRDest.z - m_posR.z;

	//�ʒu�Ɉړ��ʂ�ۑ�
	m_posR.x += m_move.x;
	m_posR.z += m_move.z;
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::CameraR(void)
{
	
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::Title(void)
{
	/*m_rot.y -= 0.002f;

	m_posV.x = m_posR.x - sinf(m_rot.y) * -300.0f;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -300.0f;

	m_posV = D3DXVECTOR3(m_posV.x, 50.0f, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(0.0f, 50.0f, 500.0f);*/

	m_posV.x = m_posR.x - sinf(m_rot.y) * -m_fLen;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -m_fLen;

	CPlayer *pPlayer = CPlayer::GetPlayer();

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPosition();

		m_posV = D3DXVECTOR3(100.0f, 50.0f, 100.0f);
		m_posR = D3DXVECTOR3(50.0f, 50.0f, 10.0f);
		m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}
}