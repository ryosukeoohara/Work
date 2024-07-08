//===========================================================
//
// ���b�V���I�u�W�F�N�g����[objectMesh.cpp]
// Author : �匴�@�叫
//
//===========================================================
#include "main.h"
#include "objectMesh.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int HEIGHT = 2;  // �c��
	const int WIDHT = 2;   // ����
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CObjectMesh::CObjectMesh()
{
	//�l���N���A
	m_pTexture = nullptr;  //�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = nullptr;  //���_�����i�[
	m_pIdxBuff = nullptr;
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
// �R���X�g���N�^
//===========================================================
CObjectMesh::CObjectMesh(D3DXVECTOR3 pos)
{
	//�l���N���A
	m_pTexture = nullptr;  //�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = nullptr;  //���_�����i�[
	m_pCurrent = nullptr;
	m_pIdxBuff = nullptr;
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
CObjectMesh::~CObjectMesh()
{

}

//===========================================================
// ��������
//===========================================================
CObjectMesh *CObjectMesh::Create(void)
{
	// �I�u�W�F�N�g3D�̃|�C���^
	CObjectMesh *pObject3D = NULL;

	if (pObject3D == NULL)
	{
		// �I�u�W�F�N�g3D�̐���
		pObject3D = new CObjectMesh();

		// ����������
		pObject3D->Init();
	}
	
	return pObject3D;
}

//===========================================================
// ����������
//===========================================================
HRESULT CObjectMesh::Init(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 13,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;     //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nHeight = 0; nHeight < 2; nHeight++)
	{
		for (int nWidth = 0; nWidth < 2; nWidth++)
		{
			pVtx[0].pos = D3DXVECTOR3((100.0f * nWidth) - 100.0f, 0.0f, (100.0f * nHeight) - 100.0f);

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
	}

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	//pVtx[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	//pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//���_�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * 9,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//�C���f�b�N�X���ւ̃|�C���^
	WORD * pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	
	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 1;
	pIdx[1] = 3;
	pIdx[2] = 0;
	pIdx[3] = 2;

	// ���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CObjectMesh::Uninit(void)
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
void CObjectMesh::Update(void)
{

}

//===========================================================
// �`�揈��
//===========================================================
void CObjectMesh::Draw(void)
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

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexture);

	////�|���S���̕`��  D3DPT_LINESTRIP
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��
	//	0,                                         //�`�悷��ŏ��̒��_�C���f�b�N�X
	//	8                                          //�`�悷��v���~�e�B�u��
	//);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 13, 0, 9);

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
void CObjectMesh::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
{
	m_pTexture = m_Texture;
}

//===========================================================
// �T�C�Y�ݒ菈��
//===========================================================
void CObjectMesh::SetSize(float fHeight, float fWidth)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	/*pVtx[0].pos.x = m_pos.x - m_fHeight;
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
	pVtx[3].pos.z = m_pos.z - m_fWidth;*/

	/*for (int nHeight = 0; nHeight < HEI + 1; nHeight++)
	{
		for (int nWidth = 0; nWidth < WID + 1; nWidth++)
		{
			pVtx[0].pos.x = m_pos.x + (m_fWidth * nWidth) - ((m_fWidth * WID) * 0.5f);
			pVtx[0].pos.y = 0.0f;
			pVtx[0].pos.z = m_pos.z + -((m_fHeight * nHeight) - ((m_fHeight * HEI) * 0.5f));

			pVtx += 1;
		}
	}*/

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	int n = 0;

	//�C���f�b�N�X���ւ̃|�C���^
	WORD * pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//for (int nHeight = 0; nHeight < HEI + 1; nHeight++)
	//{
	//	for (int nWidth = 0; nWidth < WID + 1; nWidth++)
	//	{
	//		/*pIdx[0] = (WID + ((nWidth + nHeight) * 2) + 2 / HEI + nWidth) +
	//			     -(HEI + (nHeight * 2) + 1 / WID + nHeight + nWidth);*/
	//		int i = (nHeight + 1) + nWidth  * WID - (nHeight * HEI);

	//		pIdx += 1;

	//		n++;
	//	}
	//}

	// ���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//===========================================================
// �T�C�Y�ݒ菈��:���S�����[
//===========================================================
void CObjectMesh::SetEdgeCenter(float fWidth, float fHeight)
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