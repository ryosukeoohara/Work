//===========================================================
//
//�|���S�����o�����[item.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "item.h"
#include "score.h"
#include "particl.h"
#include "debugproc.h"
#include "texture.h"
#include "collision.h"
#include "game.h"

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
CItem *CItem::m_Item = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CItem::CItem()
{
	m_nLife = 0;
	m_Indx = 0;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_ItemType = TYPE_NONE;
	m_state = STATE_NONE;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
{
	SetPos(&pos);
	//SetType(type);
	m_pos = pos;
	m_ItemType = m_Type;
	m_aFilename = aModelFliename;
	m_nLife = 0;
	m_Indx = 0;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_state = STATE_NONE;
}

//================================================================
//�f�X�g���N�^
//================================================================
CItem::~CItem()
{

}

//================================================================
//��������
//================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, TYPE m_Typeconst, const char *aModelFliename)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CItem *pItem = NULL;

	//CTexture *pTexture = CManager::GetTexture();

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pItem = new CItem(pos, m_Typeconst, aModelFliename);

			//����������
			pItem->Init();

			m_Item = pItem;
		}
	}

	return pItem;
}

//================================================================
//�A�C�e���̏���������
//================================================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);

	m_apModel[m_Indx] = CObjectX::Create(m_pos, {0.0f, 0.0f, 0.0f}, m_aFilename);

	//CObjectX::Init();

	m_Indx++;

	m_move.y = 0.04f;

	return S_OK;
}

//================================================================
//�A�C�e���̏I������
//================================================================
void CItem::Uninit(void)
{
	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//�I������
			m_apModel[nCount]->Uninit();

			//m_apModel[nCount]->Release();

			m_apModel[nCount] = NULL;

			
		}
	}

	Release();
}

//================================================================
//�A�C�e���̍X�V����
//================================================================
void CItem::Update(void)
{
	//�����蔻��̏��擾
	CCollision *pCollision = CManager::GetCollsion();

	CPlayer *pPlayer = CGame::GetPlayer();

	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//�X�V����
			m_apModel[nCount]->Update();
		}
	}

	for (int nCount = 0; nCount < m_Indx; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			D3DXVECTOR3 pos = m_apModel[nCount]->Getpos();

			if (pos.y >= 5.0f)
			{
				m_move *= -1.0f;
			}
			else if (pos.y <= 0.0f)
			{
				m_move *= -1.0f;
			}

			pos.y += m_move.y;

			if (pCollision->CollisionItem(&pos, 30.0f, 30.0f, m_ItemType, pPlayer) == true)
			{
				Uninit();

				return;
			}

			SetPos(&pos);
		}
	}

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\n���f���̈ʒu�FX��<%f>,Y��<%f>,Z��<%f>\n", m_pos.x, m_pos.y, m_pos.z);
}

//================================================================
//�A�C�e���̕`�揈��
//================================================================
void CItem::Draw(void)
{
	//for (int nCount = 0; nCount < m_Indx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//�`�揈��
	//		m_apModel[nCount]->Draw();
	//	}
	//}
}

//================================================================
//�v���C���[�Ƃ̓����蔻��
//================================================================
bool CItem::CollisionItem(D3DXVECTOR3 pos)
{
	//for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	//{
	//	CObject *pObj;

	//	//�I�u�W�F�N�g���擾
	//	pObj = Getobject(nCount);

	//	if (pObj != NULL)  //�킷��Ă�
	//	{
	//		//��ނ��擾
	//		TYPE type = pObj->GetType();

	//		if (type == TYPE_PLAYER)
	//		{//��ނ��v���C���[�̏ꍇ

	//			CPlayer *pPlayer = CManager::GetPlayer();

	//			D3DXVECTOR3 posPlayer = pPlayer->Getpos();

	//			if (pos.x >= posPlayer.x - 50.0f
	//			 && pos.x <= posPlayer.x + 50.0f
	//			 && pos.z >= posPlayer.y - 50.0f
	//			 && pos.z <= posPlayer.y + 50.0f)
	//			{
	//				return true;
	//			}

	//		}
	//	}
	//}

	return false;
}