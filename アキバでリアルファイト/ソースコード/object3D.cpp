//===========================================================
//
// 3D�I�u�W�F�N�g����[object3D.cpp]
// Author : �匴�@�叫
//
//===========================================================
#include "main.h"
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//�l���N���A
	m_pTexture = NULL;  //�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;  //���_�����i�[
	m_pCurrent = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);                   
	m_nIdxTexture = -1;                        
	m_fHeight = 0.0f;                           
	m_fWidth = 0.0f;                            
	m_bDraw = true;                              
}

//===========================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CObject3D::CObject3D(D3DXVECTOR3 pos)
{
	//�l���N���A
	m_pTexture = NULL;  //�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;  //���_�����i�[
	m_pCurrent = nullptr;
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nIdxTexture = -1;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_bDraw = true;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CObject3D::~CObject3D()
{

}

//===========================================================
// ��������
//===========================================================
CObject3D *CObject3D::Create(int nPriority)
{
	// �I�u�W�F�N�g3D�̃|�C���^
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		// ����
		pObject3D = new CObject3D(nPriority);

		// ����������
		pObject3D->Init();
	}
	
	return pObject3D;
}

//===========================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===========================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�g3D�̃|�C���^
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		// �I�u�W�F�N�g3D�̐���
		pObject3D = new CObject3D(pos);

		// ����������
		pObject3D->Init();
	}
	
	return pObject3D;
}

//===========================================================
// ����������
//===========================================================
HRESULT CObject3D::Init(void)
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
	pVtx[1].tex = D3DXVECTOR2(50.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 50.0f);
	pVtx[3].tex = D3DXVECTOR2(50.0f, 50.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CObject3D::Uninit(void)
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

//===========================================================
// �X�V����
//===========================================================
void CObject3D::Update(void)
{
	
}

//===========================================================
// �`�揈��
//===========================================================
void CObject3D::Draw(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//z�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

	D3DXMATRIX m_mtxRot, m_mtxTrans;           // �v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_pCurrent == nullptr)
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);
	}
	else
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

		// �}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld, m_pCurrent);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::Getinstance()->GetTexture()->GetAddress(m_nIdxTexture));

	//�|���S���̕`��  D3DPT_LINESTRIP
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��
		0,                                         //�`�悷��ŏ��̒��_�C���f�b�N�X
		2                                          //�`�悷��v���~�e�B�u��
	);					

	//z�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);
}

//===========================================================
// �e�N�X�`���擾
//===========================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
{
	m_pTexture = m_Texture;
}

//===========================================================
// �T�C�Y�ݒ菈��
//===========================================================
void CObject3D::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - m_fHeight;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = m_pos.z + m_fWidth;
	pVtx[1].pos.x = m_pos.x + m_fHeight;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = m_pos.z + m_fWidth;
	pVtx[2].pos.x = m_pos.x - m_fHeight;
	pVtx[2].pos.y = 0.0f;
	pVtx[2].pos.z = m_pos.z - m_fWidth;
	pVtx[3].pos.x = m_pos.x + m_fHeight;
	pVtx[3].pos.y = 0.0f;
	pVtx[3].pos.z = m_pos.z - m_fWidth;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================
// �T�C�Y�ݒ菈��:���S�����[
//===========================================================
void CObject3D::SetEdgeCenter(float fWidth, float fHeight)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_3D *pVtx;

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