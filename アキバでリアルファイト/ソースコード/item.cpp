//===========================================================
//
// �A�C�e������[item.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "item.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"
#include "itemmanager.h"
#include "game.h"
#include "collision.h"
#include "player.h"
#include "billboard.h"
#include "texture.h"

//===========================================================
// �ÓI�����o�ϐ�
//===========================================================
CItem *CItem::m_pTop = nullptr;
CItem *CItem::m_pCur = nullptr;

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const D3DXVECTOR2 TEX_SIZE = { 15.0f, 15.0f };           // �T�C�Y
	const char *ITEM_TEXT = "data\\TEXT\\item.txt";          // �A�C�e���̔z�u
	const char* GRAP_BOTTON = "data\\TEXTURE\\Ybutton.png";  // �A�C�e����͂߂�Ƃ��ɏo��UI�̃e�N�X�`���p�X
}

//================================================================
// �R���X�g���N�^
//================================================================
CItem::CItem()
{
	m_pBill = nullptr;

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

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, int nIdx, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
	m_pBill = nullptr;

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

//================================================================
// �f�X�g���N�^
//================================================================
CItem::~CItem()
{

}

//================================================================
// ��������
//================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, int nIdx, const char *aModelFliename)
{
	// �A�C�e���̃|�C���^
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{
		// ��������
		pItem = new CItem(pos, rot, type, nIdx, aModelFliename);

		// ����������
		pItem->Init();
		pItem->SetType(type);
		pItem->SetID(nIdx);
	}
	
	return pItem;
}

//================================================================
// �f�[�u���Ƃ̓����蔻��
//================================================================
void CItem::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, float fRadius)
{
	if (m_Type == TYPE_TABLE)
	{
		D3DXVECTOR3 vtxMax = GetVtxMax();
		D3DXVECTOR3 vtxMin = GetVtxMin();

		D3DXVECTOR3 Itempos = GetPosition();

		if (pos->z + fRadius > Itempos.z + vtxMin.z
			&& pos->z + -fRadius < Itempos.z + vtxMax.z)
		{
			//�u���b�N�̉E����==================================
			if (pos->x + -fRadius <= Itempos.x + vtxMax.x
				&& posOld->x + -fRadius >= Itempos.x + vtxMax.x)
			{
				pos->x = (Itempos.x + vtxMax.x) - -fRadius;
			}
			//�u���b�N�̍�����==================================
			if (pos->x + fRadius >= Itempos.x + vtxMin.x
				&& posOld->x + fRadius <= Itempos.x + vtxMin.x)
			{
				pos->x = (Itempos.x + vtxMin.x) - fRadius;
			}
		}

		if (pos->x + fRadius > Itempos.x + vtxMin.x
			&& pos->x + -fRadius < Itempos.x + vtxMax.x)
		{
			//�u���b�N�̏�======================================
			if (pos->z - fRadius - fRadius <= Itempos.z + vtxMax.z
				&& posOld->z - fRadius >= Itempos.z + vtxMax.z)
			{
				pos->z = (Itempos.z + vtxMax.z) + fRadius + fRadius;
			}

			//�u���b�N�̉�======================================
			if (pos->z + fRadius >= Itempos.z + vtxMin.z
				&& posOld->z + fRadius <= Itempos.z + vtxMin.z)
			{
				pos->z = (Itempos.z + vtxMin.z) - fRadius;
			}
		}
	}
}

//================================================================
// ����������
//================================================================
HRESULT CItem::Init(void)
{
	CObjectX::Init();

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CItem::Uninit(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪

		if (m_pNext != nullptr)
		{// �������݂��Ă���

			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�

			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��

		if (m_pPrev != nullptr)
		{// �������݂��Ă���

			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�

			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	CObjectX::Uninit();
}

//================================================================
// �X�V����
//================================================================
void CItem::Update(void)
{
	CObjectX::Update();

	if (CPlayer::GetPlayer() == nullptr)
		return;

	if (CGame::GetCollision()->Circle(&GetPosition(), &CPlayer::GetPlayer()->GetPosition(), 40.0f, 40.0f) == true)
	{// �͈͓�

		if (m_Type != TYPE_MICROWAVE && m_Type != TYPE_TABLE && m_Type != TYPE_POSTER && CPlayer::GetPlayer()->GetGrapItem() == nullptr && m_pBill == nullptr)
		{// ��ނ��d�q�����W���e�[�u���ȊO

			// �������Ĉʒu�A�T�C�Y�A�`�悷�邩�ǂ����A�g�p����e�N�X�`���ݒ�
			m_pBill = CBillBoard::Create();
			m_pBill->SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y + 40.0f, GetPosition().z));
			m_pBill->SetSize(TEX_SIZE.x, TEX_SIZE.y);
			m_pBill->SetDraw();
			m_pBill->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(GRAP_BOTTON));
		}
	}
	
	if((CGame::GetCollision()->Circle(&GetPosition(), &CPlayer::GetPlayer()->GetPosition(), 40.0f, 40.0f) != true || CPlayer::GetPlayer()->GetGrapItem() != nullptr)
	 && m_pBill != nullptr)
	{// �͈͊O

		// �I��
		m_pBill->Uninit();
		m_pBill = nullptr;
	}
}