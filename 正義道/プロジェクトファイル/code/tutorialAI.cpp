//===============================================================
//
// �`���[�g���A��AI����[tutorialAI.cpp]
// Author �匴�叫
//
//===============================================================
#include "tutorialAI.h"
#include "motion.h"
#include "shadow.h"
#include "manager.h"
#include "renderer.h"

//================================================================
//�}�N����`
//================================================================
#define PLAYER_TEXT ("data\\TEXT\\yankinear.txt")      //�v���C���[�̃e�L�X�g�t�@�C��

//===============================================================
//�R���X�g���N�^
//===============================================================
CTutorialAI::CTutorialAI()
{

}

//===============================================================
//�R���X�g���N�^
//===============================================================
CTutorialAI::CTutorialAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);
	SetRot(&rot);
}

//===============================================================
//�f�X�g���N�^
//===============================================================
CTutorialAI::~CTutorialAI()
{
	
}

//===============================================================
//�N���G�C�g
//===============================================================
CTutorialAI * CTutorialAI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CTutorialAI *pTutorialAI = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pTutorialAI == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pTutorialAI = new CTutorialAI(pos, rot);

			//����������
			pTutorialAI->Init();
		}
	}

	return pTutorialAI;
}

//===============================================================
//����������
//===============================================================
HRESULT CTutorialAI::Init(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//����������
		m_motion->Init();
	}

	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow(pos);

		//����������
		m_pShadow->Init();
	}

	ReadText();

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return E_NOTIMPL;
}

//===============================================================
//�I������
//===============================================================
void CTutorialAI::Uninit(void)
{
	if (m_motion != NULL)
	{
		//�I������
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
	}

	if (m_pShadow != NULL)
	{
		//�I������
		m_pShadow->Uninit();

		m_pShadow = NULL;
	}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//�g�p���Ă�����

			m_apModel[nCount]->Uninit();  //�I������
			delete m_apModel[nCount];  //���������J��
			m_apModel[nCount] = NULL;  //�g�p���Ă��Ȃ���Ԃɂ���
		}
	}

	CObject::Release();
}

//===============================================================
//�X�V����
//===============================================================
void CTutorialAI::Update(void)
{
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Update();
	}

	if (m_motion != NULL)
	{
		//����������
		m_motion->Update();
	}
}

//===============================================================
//�`�揈��
//===============================================================
void CTutorialAI::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = Getpos();
	D3DXVECTOR3 rot = GetRot();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//�`�揈��
		m_apModel[nCount]->Draw();
	}
	
}

//===============================================================
//�e�L�X�g�t�@�C���ǂݍ��ݏ���
//===============================================================
void CTutorialAI::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(PLAYER_TEXT, "r");

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
					fscanf(pFile, "%s", &m_filename[0]);  //���f���̖��O

					m_apModel[nCntModel] = CCharacter::Create(m_filename);
					//m_apModel[nCntModel]->BindTexture(pTexture->GetAddress(m_nIdxTexture));
					nCntModel++;

					nCntParts++;

				}  //MODEL_LILENAME�̂�����


				if (strcmp("CHARACTERSET", aString) == 0)
				{
					while (strcmp("END_CHARACTERSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("PARTSSET", aString) == 0)
						{
							while (strcmp("END_PARTSSET", aString) != 0)
							{
								fscanf(pFile, "%s", &aString);

								if (strcmp("INDEX", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nIdx);  //���f���̔ԍ�
								}

								if (strcmp("PARENT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nParent);  //�e���f���̔ԍ�

									if (m_nParent > -1 && m_nNumModel > m_nParent)
									{
										m_apModel[nCntParts2]->SetParent(m_apModel[m_nParent]);
									}
									else
									{
										m_apModel[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.z);  //���f���̑���

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.z);  //���f���̑���

									m_apModel[nCntParts2]->SetRotOrigin(m_Readrot);

									m_apModel[nCntParts2]->SetRot(m_Readrot);
								}

							}//END_PARTSSET�̂�����

							nCntParts2++;

						}//PARTSSET�̂�����

					}//END_CHARACTERSET�̂����� 

				}//CHARACTERSET�̂����� 
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}

	if (m_motion != NULL)
	{
		//����������
		m_motion->ReadText(PLAYER_TEXT);
	}
}
