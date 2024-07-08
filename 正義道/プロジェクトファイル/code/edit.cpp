//===========================================================
//
//�|���S�����o�����[edit.cpp]
//Author �匴�叫
//
//===========================================================
#include "edit.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"

#include <stdio.h>
#include<string.h>

//�}�N����`
#define MODEL_SET_TEXT  ("data\\TEXT\\model_set.txt")

//===========================================================
//�R���X�g���N�^
//===========================================================
CEdit::CEdit()
{
	m_nNumModel = 0;
	m_nIdx = 0;
	m_dwNumMat = 0;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_pTexture = NULL;
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CEdit::~CEdit()
{

}

//===========================================================
//����������
//===========================================================
HRESULT CEdit::Init(void)
{
	//�e�L�X�g�t�@�C���ǂݍ���
	ReadText();

	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//����������
	//		m_apModel[nCount]->Init();
	//	}
	//}
	

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CEdit::Uninit(void)
{
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//����������
	//		m_apModel[nCount]->Uninit();
	//	}
	//}

	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	//�e�N�X�`���̏���
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//===========================================================
//�X�V����
//===========================================================
void CEdit::Update(void)
{
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	////�X�V����
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//����������
	//		m_apModel[nCount]->Update();
	//	}
	//}

	//�E�Ɉړ�----------------------------------------------
	if (InputKeyboard->GetPress(DIK_N) == true)
	{//D�L�[����������

		//�ړ���
		m_move.x += sinf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
		m_move.z += cosf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
	}

	//���Ɉړ�----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_M) == true)
	{//A�L�[����������

		//�ړ���
		m_move.x -= sinf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
		m_move.z -= cosf(/*rot.y + */(D3DX_PI * 0.5f)) * 1.0f;
	}
}

//===========================================================
//�`�揈��
//===========================================================
void CEdit::Draw(void)
{
	////�`�揈��
	//for (int nCount = 0; nCount < m_nIdx; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//����������
	//		m_apModel[nCount]->Draw();
	//	}
	//}

	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, *&m_pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================
//�Z�[�u����
//===========================================================
void CEdit::Save(void)
{

}

//===========================================================
//���[�h����
//===========================================================
void CEdit::Load(void)
{

}

//===========================================================
//�e�L�X�g�t�@�C���ǂݍ���
//===========================================================
void CEdit::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	//int nCntModel = 0;

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(MODEL_SET_TEXT, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_MODEL", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumModel);  //���f���̑���

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_Model[m_nIdx].m_filename[0]);  //���f���̖��O

					CPlayer *pPlayer = CManager::GetPlayer();

					D3DXVECTOR3 pos = pPlayer->Getpos();

					//m_apModel[m_nIdx] = CObjectX::Create(pos, m_filename);
					int nNumVtx;      //���_��
					DWORD dwSizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y
					BYTE *pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^

					//�f�o�C�X�̎擾
					CRenderer *pRenderer = CManager::GetRenderer();
					LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

					//X�t�@�C���ǂݍ���
					D3DXLoadMeshFromX(m_Model[m_nIdx].m_filename,
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&m_pBuffMat,
						NULL,
						&m_dwNumMat,
						&m_pMesh);

					//���_�����擾
					nNumVtx = m_pMesh->GetNumVertices();

					//���_�t�H�[�}�b�g�̃T�C�Y���擾
					dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

					//�}�e���A���ւ̃|�C���^
					D3DXMATERIAL *pMat;

					//�}�e���A�����ɑ΂���|�C���^���擾
					pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
					{
						if (pMat[nCntMat].pTextureFilename != NULL)
						{//�e�N�X�`�������݂���

							if (m_pTexture == NULL)
							{
								m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
							}

							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&m_pTexture[nCntMat]);
						}
						else if (pMat[nCntMat].pTextureFilename == NULL)
						{
							m_pTexture[nCntMat] = NULL;
						}
					}

					//���_�o�b�t�@�����b�N
					m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;     //���_���W�̑��

						//�ŏ��l-------------------------------------------------
						if (m_vtxMini.x > vtx.x)
						{
							m_vtxMini.x = vtx.x;
						}

						if (m_vtxMini.y > vtx.y)
						{
							m_vtxMini.y = vtx.y;
						}

						if (m_vtxMini.z > vtx.z)
						{
							m_vtxMini.z = vtx.z;
						}

						//�ő�l-------------------------------------------------
						if (m_vtxMax.x < vtx.x)
						{
							m_vtxMax.x = vtx.x;
						}

						if (m_vtxMax.y < vtx.y)
						{
							m_vtxMax.y = vtx.y;
						}

						if (m_vtxMax.z < vtx.z)
						{
							m_vtxMax.z = vtx.z;
						}

						pVtxBuff += dwSizeFVF;    //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
					}

					//���_�o�b�t�@���A�����b�N
					m_pMesh->UnlockVertexBuffer();

					m_nIdx++;

				}  //MODEL_LILENAME�̂�����
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	
}