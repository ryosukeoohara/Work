//===========================================================
//
// 2D�I�u�W�F�N�g����[object2D.cpp]
// Author �匴�叫
//
//===========================================================
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "game.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�l���N���A
	m_nIdxTexture = -1;
	m_pVtxBuff = NULL;  //���_�����i�[
	m_nCounterAnimPlayer = 0;
	m_nPatternAnimPlayer = 0;
	m_Number = 0;
	m_bDraw = false;
}

//===========================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CObject2D::CObject2D(D3DXVECTOR3 pos, int nPriority)
{
	// �l���N���A
	m_pos = pos;
	m_nIdxTexture = -1;
	m_pVtxBuff = NULL;
	m_nCounterAnimPlayer = 0;
	m_nPatternAnimPlayer = 0;
	m_Number = 0;
	m_bDraw = false;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CObject2D::~CObject2D()
{

}

//===========================================================
// ��������
//===========================================================
CObject2D * CObject2D::Create(int nPriority)
{
	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		// �I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D();

		// ����������
		pObject2D->Init();
	}
	
	return pObject2D;
}

//===========================================================
// ��������
//===========================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, int nPriority)
{
	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D *pObject2D = nullptr;

	if (pObject2D == NULL)
	{
		// �I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D(pos, nPriority);

		// ����������
		pObject2D->Init();
	}
	return pObject2D;
}

//===========================================================
// ����������
//===========================================================
HRESULT CObject2D::Init(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::Getinstance()->GetRenderer();
	
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CObject2D::Update(void)
{
	
}

//===========================================================
// �`�揈��
//===========================================================
void CObject2D::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::Getinstance()->GetRenderer();
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_bDraw == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��
			0,                                         //�`�悷��ŏ��̒��_�C���f�b�N�X
			2                                          //�`�悷��v���~�e�B�u��
		);
	}
}

//===========================================================
// �F�ݒ菈��
//===========================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �T�C�Y�ݒ菈��
//===========================================================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - m_fWidth;
	pVtx[0].pos.y = m_pos.y - m_fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + m_fWidth;
	pVtx[1].pos.y = m_pos.y - m_fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x - m_fWidth;
	pVtx[2].pos.y = m_pos.y + m_fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + m_fWidth;
	pVtx[3].pos.y = m_pos.y + m_fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �T�C�Y�ݒ菈��:���S�����[
//===========================================================
void CObject2D::SetEdgeCenter(float fWidth, float fHeight)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x;
	pVtx[0].pos.y = m_pos.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + m_fWidth;
	pVtx[1].pos.y = m_pos.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x;
	pVtx[2].pos.y = m_pos.y + m_fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + m_fWidth;
	pVtx[3].pos.y = m_pos.y + m_fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �T�C�Y�ݒ菈��:���S�����[
//===========================================================
void CObject2D::SetEdgeCenterTex(float ftex)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x;
	pVtx[0].pos.y = m_pos.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + ftex;
	pVtx[1].pos.y = m_pos.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x;
	pVtx[2].pos.y = m_pos.y + m_fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + ftex;
	pVtx[3].pos.y = m_pos.y + m_fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �`�揈��
//===========================================================
void CObject2D::SetTex(float fTex)
{
	m_Number = (int)fTex;

	if (m_Number >= 10)
	{
		m_Number = 0;
	}

	if (m_Number < 0)
	{
		m_Number = 9;
	}

	VERTEX_2D * pVtx;     //���_���ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);        //���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾

	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * m_Number, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * m_Number, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * m_Number, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * m_Number, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �����x�ݒ�
//===========================================================
void CObject2D::SetColorA(float fCola)
{
	m_col.a += fCola;

	if (m_col.a >= 1.0f || m_col.a < 0.3f)
	{
		m_col.a *= -1;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}