//=============================================================================
//
// �|���S������ [billboard.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "object2D.h"
#include "texture.h"
#include "debugproc.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const D3DXVECTOR2 XYPATTERN[CBillBoard::TYPE_MAX] = 
	{
		D3DXVECTOR2(1.0f, 1.0f), // �Ȃ���Ȃ�
		D3DXVECTOR2(4.0f, 3.0f), // �U���q�b�g
	}; // ������

	const int NUMPATTERN[CBillBoard::TYPE_MAX] =
	{
		0,  // �Ȃ���Ȃ�
		10, // �U���q�b�g
	}; // �p�^�[���̑���
}

//================================================================
//�R���X�g���N�^
//================================================================
CBillBoard::CBillBoard(int nPriority) : CObject(nPriority)
{
	//�l���N���A
	m_pTexture = NULL;  //�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;  //���_�����i�[
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nIdxTexture = -1;
	m_nNumPattern = 0;
	m_nNowPattern = 0;
	m_nCounterAnim = 0;
	m_nHeight = 0;
	m_nWidth = 0;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_bDraw = true;
	m_Type = TYPE_NONE;
}

//================================================================
//�f�X�g���N�^
//================================================================
CBillBoard::~CBillBoard()
{

}

//================================================================
//��������
//================================================================
//CBillBoard *CBillBoard::Create(void)
//{
//	//�I�u�W�F�N�g2D�̃|�C���^
//	CBillBoard *pBillBoard = NULL;
//
//	if (pBillBoard == NULL)
//	{
//		//�I�u�W�F�N�g2D�̐���
//		pBillBoard = new CBillBoard();
//
//		//����������
//		pBillBoard->Init();
//	}
//
//	return pBillBoard;
//}

//================================================================
//��������
//================================================================
CBillBoard * CBillBoard::Create(int nPriority)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CBillBoard *pBillBoard = nullptr;

	if (pBillBoard == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pBillBoard = new CBillBoard(nPriority);

		//����������
		pBillBoard->Init();
	}

	return pBillBoard;
}

//================================================================
//��������
//================================================================
void CBillBoard::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, -fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
// �T�C�Y�ݒ菈��:���S�����[
//================================================================
void CBillBoard::SetEdgeCenter(float fWidth, float fHeight)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_fWidth;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -m_fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_fWidth;
	pVtx[3].pos.y = -m_fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
// ��������
//================================================================
void CBillBoard::SetTex(float fTex)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(50.0f,             + fTex, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f + m_fHeight, + fTex, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f,             0.0f,  0.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f + m_fHeight, 0.0f,  0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
// �A�j���[�V���������
//================================================================
void CBillBoard::SetAnim(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nNowPattern++;

	if (m_nNowPattern % 1 == 0)
	{
		m_nCounterAnim = (m_nCounterAnim + 1) % m_nNumPattern;

		float fx = m_nCounterAnim % m_nWidth * (1.0f / XYPATTERN[m_Type].x);
		float fy = m_nCounterAnim / m_nHeight * (1.0f / XYPATTERN[m_Type].y);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + fx,                         0.0f + fy);
		pVtx[1].tex = D3DXVECTOR2((1.0f / XYPATTERN[m_Type].x) + fx, 0.0f + fy);
		pVtx[2].tex = D3DXVECTOR2(0.0f + fx,                         (1.0f / XYPATTERN[m_Type].y) + fy);
		pVtx[3].tex = D3DXVECTOR2((1.0f / XYPATTERN[m_Type].x) + fx, (1.0f / XYPATTERN[m_Type].y) + fy);

		m_nNowPattern = 0;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (m_nCounterAnim + 1 >= m_nNumPattern)
	{
		Uninit();
	}
}

//================================================================
// �F�ݒ菈��
//================================================================
void CBillBoard::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

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

//================================================================
//�ǂ̏���������
//===============================================================
HRESULT CBillBoard::Init(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;     //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / XYPATTERN[m_Type].x), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, (1.0f / XYPATTERN[m_Type].y));
	pVtx[3].tex = D3DXVECTOR2((1.0f / XYPATTERN[m_Type].x), (1.0f / XYPATTERN[m_Type].y));

	m_nHeight = (int)XYPATTERN[m_Type].x;
	m_nWidth = (int)XYPATTERN[m_Type].y;

	m_nNumPattern = NUMPATTERN[m_Type];

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================
//�ǂ̏I������
//================================================================
void CBillBoard::Uninit(void)
{
	//�e�N�X�`���̏���
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//================================================================
//�ǂ̕ǂ̍X�V����
//================================================================
void CBillBoard::Update(void)
{
	
}

//================================================================
//�ǂ̕`�揈��
//================================================================
void CBillBoard::Draw(void)
{
	if (m_bDraw == true)
	{
		//�f�o�C�X�̎擾
		CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//z�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

		D3DXMATRIX m_mtxTrans;           // �v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&m_mtxWorld, NULL, &m_mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;

		if (m_pCurrent == nullptr)
		{
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);
		}
		else
		{
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

			// �}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
			D3DXMatrixMultiply(&m_mtxWorld,
				&m_mtxWorld, m_pCurrent);
		}

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//z�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::Getinstance()->GetTexture()->GetAddress(m_nIdxTexture));

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��
			0,                      //�`�悷��ŏ��̒��_�C���f�b�N�X
			2                       //�`�悷��v���~�e�B�u��
		);

		//z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 160);
	}
}