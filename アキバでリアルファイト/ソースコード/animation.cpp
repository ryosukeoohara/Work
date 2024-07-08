//===========================================================
//
// �e�N�X�`���A�j���[�V����[animation.cpp]
// Author �匴�叫
//
//===========================================================
#include "animation.h"
#include "manager.h"
#include "texture.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const char *TEXTURENAME[CBillBoard::TYPE_MAX] =
	{
		"data\\TEXTURE\\.png",
		"data\\TEXTURE\\hit1.png",
	};  // �e�N�X�`���̖��O
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAnimation::CAnimation()
{
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.type = TYPE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAnimation::CAnimation(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, TYPE type)
{
	m_Info.pos = pos;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = col;
	m_Info.type = type;
	m_Info.nLife = 0;
	m_Info.fRadius = fRadius;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CAnimation::~CAnimation()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CAnimation::Init(void)
{
	CBillBoard::Init();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CAnimation::Uninit(void)
{
	CBillBoard::Uninit();
}

//===========================================================
// �X�V����
//===========================================================
void CAnimation::Update(void)
{
	CBillBoard::Update();

	// �A�j���[�V�����ݒ�
	CBillBoard::SetAnim();
}

//===========================================================
// �`�揈��
//===========================================================
void CAnimation::Draw(void)
{
	CBillBoard::Draw();
}

//===========================================================
// ����
//===========================================================
CAnimation * CAnimation::Create(D3DXVECTOR3 pos, float fRadius, CBillBoard::TYPE type)
{
	CAnimation *pAnim = nullptr;
	pAnim = new CAnimation;

	if (pAnim != nullptr)
	{
		// ��ށA�ʒu�A�T�C�Y�A�e�N�X�`���A�`��ݒ�
		pAnim->SetType(type);
		pAnim->Init();
		pAnim->SetPosition(pos);
		pAnim->SetSize(fRadius, fRadius);
		pAnim->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[type]));
		pAnim->SetDraw();
	}

	return pAnim;
}
