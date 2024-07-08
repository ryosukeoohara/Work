//===========================================================
//
// 2D�G�t�F�N�g[effect2D.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect2D.h"
#include "debugproc.h"
#include "texture.h"

//===========================================================
// �ÓI�����o�ϐ��錾
//===========================================================
const char *CEffect2D::m_apTexName[TYPE_MAX] =
{
	"data\\TEXTURE\\smook.png",
	"data\\TEXTURE\\smook.png",
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CEffect2D::CEffect2D()
{
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
	m_nIdxTexture = -1;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CEffect2D::CEffect2D(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type)
{
	m_Info.pos = pos;
	m_Info.move = move;
	m_Info.col = col;
	m_Info.nLife = nLife;
	m_Info.fRadius = fRadius;
	m_type = type;
	m_nIdxTexture = -1;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CEffect2D::~CEffect2D()
{

}

//===========================================================
// ��������
//===========================================================
CEffect2D *CEffect2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CEffect2D *pEffect = nullptr;

	if (pEffect == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pEffect = new CEffect2D(pos, move, col, fRadius, nLife, type);

		//����������
		pEffect->Init();
		pEffect->SetPosition(pos);
		pEffect->SetSize(fRadius, fRadius);
		pEffect->SetColor(col);
		pEffect->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[type]));
		pEffect->SetDraw(true);
	}
	
	return pEffect;
}

//===========================================================
// ����������
//===========================================================
HRESULT CEffect2D::Init(void)
{
	//����������
	CObject2D::Init();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CEffect2D::Uninit(void)
{
	//�I������
	CObject2D::Uninit();
}

//===========================================================
// �X�V����
//===========================================================
void CEffect2D::Update(void)
{
	m_Info.nLife--;

	//�X�V����
	CObject2D::Update();

	switch (m_type)
	{
	case TYPE_GROUND:
		Ground();
		break;

	case TYPE_SMOOK:
		Smook();
		break;

	case TYPE_MAX:
		break;

	default:
		break;
	}

	//�ړ��ʂ��X�V(����������)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.y += (0.0f - m_Info.move.y) * 0.1f;

	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.y += m_Info.move.y;

	SetPosition(m_Info.pos);

	if (m_Info.nLife <= 0)
	{
		CEffect2D::Uninit();
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CEffect2D::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���u�����f�B���O�����Z���v�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`�揈��
	CObject2D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================================================
// �y���̃G�t�F�N�g
//===========================================================
void CEffect2D::Ground(void)
{
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.y += (0.0f - m_Info.move.y) * 0.1f;
}

//===========================================================
// ���t�̃G�t�F�N�g
//===========================================================
void CEffect2D::Blood(void)
{

}

//===========================================================
// ���̃G�t�F�N�g
//===========================================================
void CEffect2D::Smook(void)
{
	if (m_Info.col.a >= 0.0f)
	{
		m_Info.col.a -= 0.005f;
	}

	m_Info.fRadius += 1.0f;

	SetColor(m_Info.col);
	SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===========================================================
// �~�`�̃G�t�F�N�g
//===========================================================
void CEffect2D::Circle(void)
{
	
}