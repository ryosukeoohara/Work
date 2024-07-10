//===========================================================
//
// �I�u�W�F�N�g����[object.cpp]
// Author �匴�叫
//
//===========================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"

//===========================================================
// �ÓI�����o�ϐ�
//===========================================================
CObject* CObject::m_pTop = {};
CObject* CObject::m_pCur = {};
int CObject::m_nNumAll = 0;

//===========================================================
// �R���X�g���N�^
//===========================================================
CObject::CObject()
{
	m_bDeath = false;

	CObject* pObject = m_pTop;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;
		m_pCur = this;
	}
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CObject::~CObject()
{

}

//===========================================================
// ���ׂĔj��
//===========================================================
void CObject::ReleaseAll(void)
{
	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Uninit();

		pObject = pObjectNext;
	}
}

//===========================================================
// ���ׂčX�V
//===========================================================
void CObject::UpdateAll(void)
{
	DeadChuck();

	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Update();
		pObject = pObjectNext;
	}
	
	CDebugProc* pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n\n�I�u�W�F�N�g�̑����F%d", m_nNumAll);
}

//===========================================================
// ���ׂĕ`��
//===========================================================
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::Getinstance()->GetCamera();

	DeadChuck();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		pObject->Draw();
		pObject = pObjectNext;
	}
}

//===========================================================
// �j��
//===========================================================
void CObject::Release(void)
{
	// ����
	m_bDeath = true;
}

//===========================================================
// ���S���Ă��邩�`�F�b�N
//===========================================================
void CObject::DeadChuck(void)
{
	CObject* pObject = m_pTop;

	while (pObject != nullptr)
	{
		CObject* pObjectNext = pObject->m_pNext;

		if (pObject->m_bDeath == true)
		{
			// ���X�g���玩�����g���폜����
			if (m_pTop == pObject)
			{// ���g���擪

				if (pObject->m_pNext != nullptr)
				{// �������݂��Ă���

					m_pTop = pObject->m_pNext;	// ����擪�ɂ���
					pObject->m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
				}
				else
				{// ���݂��Ă��Ȃ�

					m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
					m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
				}
			}
			else if (m_pCur == pObject)
			{// ���g���Ō��

				if (pObject->m_pPrev != nullptr)
				{// �������݂��Ă���

					m_pCur = pObject->m_pPrev;			// �O���Ō���ɂ���
					pObject->m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
				}
				else
				{// ���݂��Ă��Ȃ�

					m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
					m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
				}
			}
			else
			{
				if (pObject->m_pNext != nullptr)
				{
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
				}
				if (pObject->m_pPrev != nullptr)
				{
					pObject->m_pPrev->m_pNext = pObject->m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
				}
			}
		}

		pObject = pObjectNext;
	}
}