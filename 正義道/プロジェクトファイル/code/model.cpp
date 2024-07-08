//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include<string.h>

//================================================================
//�ÓI�����o�ϐ�
//================================================================
int CModel::m_nNumAll = 0;

//================================================================
//�R���X�g���N�^
//================================================================
CModel::CModel()
{
	m_pTexture = NULL;
}

//================================================================
//�f�X�g���N�^
//================================================================
CModel::~CModel()
{

}

//================================================================
//����������
//================================================================
HRESULT CModel::Load(void)
{
	return S_OK;
}

//================================================================
//�I������
//================================================================
void CModel::UnLoad(void)
{
	
}

//================================================================
//�w��̃e�N�X�`���ǂݍ���
//================================================================
int CModel::Regist(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename)
{
	int nIdx = m_nNumAll;

	for (int nCount = 0; nCount < m_nNumAll; nCount++)
	{
		if (strcmp(pFilename, m_aModel[nCount].aName) == 0)
		{
			return nCount;
		}
	}

	if (m_aModel[nIdx].m_aModel == NULL)
	{
		strcpy(m_aModel[nIdx].aName, pFilename);

		m_aModel[nIdx].m_aModel = CObjectX::Create(pos, rot, pFilename);

		m_nNumAll++;  //�e�N�X�`���̑������J�E���g�A�b�v
	}

	
	

	//int nNumVtx;      //���_��
	//DWORD dwSizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y
	//BYTE *pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^

	////�f�o�C�X�̎擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////X�t�@�C���ǂݍ���
	//D3DXLoadMeshFromX(pFilename,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&m_aModel[nIdx].m_pBuffMat,
	//	NULL,
	//	&m_aModel[nIdx].m_dwNumMat,
	//	&m_aModel[nIdx].m_pMesh);

	////���_�����擾
	//nNumVtx = m_aModel[nIdx].m_pMesh->GetNumVertices();

	////���_�t�H�[�}�b�g�̃T�C�Y���擾
	//dwSizeFVF = D3DXGetFVFVertexSize(m_aModel[nIdx].m_pMesh->GetFVF());

	//if (m_pTexture == NULL)
	//{
	//	m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_aModel[nIdx].m_dwNumMat];
	//}

	////�}�e���A���ւ̃|�C���^
	//D3DXMATERIAL *pMat;

	////�}�e���A�����ɑ΂���|�C���^���擾
	//pMat = (D3DXMATERIAL*)m_aModel[nIdx].m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_aModel[nIdx].m_dwNumMat; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{//�e�N�X�`�������݂���

	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{
	//		m_pTexture[nCntMat] = NULL;
	//	}
	//}

	////���_�o�b�t�@�����b�N
	//m_aModel[nIdx].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;     //���_���W�̑��

	//	//�ŏ��l-------------------------------------------------
	//	if (m_aModel[nIdx].m_vtxMini.x > vtx.x)
	//	{
	//		m_aModel[nIdx].m_vtxMini.x = vtx.x;
	//	}

	//	if (m_aModel[nIdx].m_vtxMini.y > vtx.y)
	//	{
	//		m_aModel[nIdx].m_vtxMini.y = vtx.y;
	//	}

	//	if (m_aModel[nIdx].m_vtxMini.z > vtx.z)
	//	{
	//		m_aModel[nIdx].m_vtxMini.z = vtx.z;
	//	}

	//	//�ő�l-------------------------------------------------
	//	if (m_aModel[nIdx].m_vtxMax.x < vtx.x)
	//	{
	//		m_aModel[nIdx].m_vtxMax.x = vtx.x;
	//	}

	//	if (m_aModel[nIdx].m_vtxMax.y < vtx.y)
	//	{
	//		m_aModel[nIdx].m_vtxMax.y = vtx.y;
	//	}

	//	if (m_aModel[nIdx].m_vtxMax.z < vtx.z)
	//	{
	//		m_aModel[nIdx].m_vtxMax.z = vtx.z;
	//	}

	//	pVtxBuff += dwSizeFVF;    //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	//}

	////���_�o�b�t�@���A�����b�N
	//m_aModel[nIdx].m_pMesh->UnlockVertexBuffer();

	m_nNumAll++;

	return nIdx;
}

//================================================================
//�e�N�X�`���̃A�h���X�擾
//================================================================
CObjectX CModel::GetAddress(int nIdx)
{
	return *m_aModel[nIdx].m_aModel;
}
