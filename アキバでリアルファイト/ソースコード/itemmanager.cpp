//===========================================================
//
// �A�C�e���̊Ǘ� [itemmanager.cpp]
// Author : �匴�@�叫
//
//===========================================================

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "itemmanager.h"
#include "item.h"

//===========================================================
// �ÓI�����o�ϐ�
//===========================================================
const char *CItemManager::m_apTexName[CItem::TYPE_MAX] =
{
	"data\\MODEL\\refrigerator.x",  // �①��
	"data\\MODEL\\bike.x",          // ���]��
	"data\\MODEL\\microwave.x",     // �d�q�����W
	"data\\MODEL\\table.x",         // �f�[�u��
	"data\\MODEL\\poster.x",        // �Ŕ�
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CItemManager::CItemManager()
{
	// �l���N���A
	m_nNum = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CItemManager::~CItemManager()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CItemManager::Init(void)
{
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CItemManager::Uninit(void)
{
	
}

//===========================================================
// �X�V����
//===========================================================
void CItemManager::Update(void)
{
	
}

//===========================================================
// ��������
//===========================================================
CItemManager * CItemManager::Create(const char* filename)
{
	CItemManager *pItemManager = nullptr;

	if (pItemManager == nullptr)
	{
		pItemManager = new CItemManager();

		pItemManager->Init();

		pItemManager->ReadText(filename);
	}

	return pItemManager;
}

//===========================================================
// ����
//===========================================================
void CItemManager::Release(int idx)
{
	CItem *pItem = CItem::GetTop();

	while (pItem != nullptr)
	{
		CItem *pItemNext = pItem->GetNext();

		if (pItem->GetID() == idx)
		{
			pItem->Uninit();
		}

		pItem = pItemNext;
	}
}

//===========================================================
// �e�L�X�g�t�@�C���ǂݍ���
//===========================================================
void CItemManager::ReadText(const char *text)
{
	char aString[128] = {};              // �����ǂݎ��p
	char aFileName[128] = {};            // �t�@�C���̖��O�ǂݎ��p
	int nIdx = 0;                        // �ԍ��ǂݎ��p
	int nType = -1;                      // ��ޓǂݎ��p
	D3DXVECTOR3 pos = {}, rot = {};      // �ǂݎ��p

	FILE *pFile;   // �t�@�C���|�C���^��錾

	pFile = fopen(text, "r");

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
					fscanf(pFile, "%s", &aString);  // =�Ǎ�
					fscanf(pFile, "%d", &m_nNum);   // ���f���̑���
					
				}  // NUM_ITEM�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       // =�Ǎ�
					fscanf(pFile, "%s", &aFileName[0]);  // ���f���̖��O

				}  // MODEL_LILENAME�̂�����

				if (strcmp("ITEMSET", aString) == 0)
				{
					while (strcmp("END_ITEMSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      // =�Ǎ�
							fscanf(pFile, "%d", &nType);        // ��ނ̑���
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      // =�Ǎ�
							fscanf(pFile, "%f", &pos.x);        // �ʒuX
							fscanf(pFile, "%f", &pos.y);        // �ʒuY
							fscanf(pFile, "%f", &pos.z);        // �ʒuZ
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      // =�Ǎ�
							fscanf(pFile, "%f", &rot.x);        // ����X
							fscanf(pFile, "%f", &rot.y);        // ����Y
							fscanf(pFile, "%f", &rot.z);        // ����Z
						}
					}

					// �A�C�e������
					CItem::Create(pos, rot, (CItem::TYPE)nType, nIdx, m_apTexName[nType]);

					// �ԍ����Z
					nIdx++;
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