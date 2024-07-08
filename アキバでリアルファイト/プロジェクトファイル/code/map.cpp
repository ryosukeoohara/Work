//===========================================================
//
// �}�b�v�̃��f��[map.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "map.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const char* MAPTEXT = "data\\TEXT\\set_map_model.txt";  // �}�b�v�̃e�L�X�g�t�@�C��
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CMap::CMap()
{
	m_nNumModel = 0;
	m_nNumItem = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CMap::~CMap()
{

}

//===========================================================
// ��������
//===========================================================
CMap *CMap::Create(void)
{
	// �}�b�v�̃|�C���^
	CMap *pMap = nullptr;

	if (pMap == nullptr)
	{
		// ��������
		pMap = new CMap();

		// ����������
		pMap->Init();
	}

	return pMap;
}

//===========================================================
// �e�L�X�g�t�@�C���Ǎ�����
//===========================================================
void CMap::TextLoad(void)
{
	char aString[128] = {};    // �����ǂݎ��p
	char aComment[128] = {};   // �e�L�X�g�t�@�C�����̃R�����g�ǂݎ��p
	char aFileName[128] = {};  // �t�@�C���̖��O�ǂݎ��p
	int nCntItem = 0;
	int nCntFileName = 0;
	int nType = -1;
	D3DXVECTOR3 pos, rot;      // �ǂݎ��p

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(MAPTEXT, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_ITEM", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumItem);  //���f���̑���

				}  // NUM_ITEM�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       //=
					fscanf(pFile, "%s", &aFileName[0]);  //���f���̖��O

					strcpy(m_aTex[nCntFileName].aName, aFileName);
					nCntFileName++;

					m_appObjectX = new CObjectX*[MAX_MODEL];

				}  // MODEL_LILENAME�̂�����

				if (strcmp("MODELSET", aString) == 0)
				{
					while (strcmp("END_MODELSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%d", &nType);  //���f���̑���
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &pos.x);  //���f���̑���
							fscanf(pFile, "%f", &pos.y);  //���f���̑���
							fscanf(pFile, "%f", &pos.z);  //���f���̑���
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &rot.x);  //���f���̑���
							fscanf(pFile, "%f", &rot.y);  //���f���̑���
							fscanf(pFile, "%f", &rot.z);  //���f���̑���
						}
					}

					m_appObjectX[nCntItem] = CObjectX::Create(m_aTex[nType].aName);
					m_appObjectX[nCntItem]->SetPosition(pos);
					m_appObjectX[nCntItem]->SetRotition(rot);

					if (nType >= 43 && nType <= 51 || nType == 56)
					{
						m_appObjectX[nCntItem]->SetbEnable(false);
					}
					else
					{
						m_appObjectX[nCntItem]->SetbEnable(true);
					}

					nCntItem++;

					m_nNumModel++;
				}
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//===========================================================
// ����������
//===========================================================
HRESULT CMap::Init(void)
{
	// �}�b�v�̃e�L�X�g�t�@�C���Ǎ�
	TextLoad();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CMap::Uninit(void)
{
	if (m_appObjectX != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_appObjectX[nCount]->Uninit();
			m_appObjectX[nCount] = nullptr;
		}

		delete m_appObjectX;
		m_appObjectX = nullptr;
	}
}

//===========================================================
// �X�V����
//===========================================================
void CMap::Update(void)
{

}