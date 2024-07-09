//===========================================================
//
// �G�̏���[enemy.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "object.h"
#include "enemy.h"
#include "texture.h"
#include "manager.h"
#include "character.h"
#include "enemymanager.h"
#include "game.h"
#include "score.h"
#include "debugproc.h"
#include "particl.h"
#include "enemyweak.h"
#include "fade.h"
#include "life.h"
#include "item.h"
#include "player.h"

//�ÓI�����o�ϐ�
int CEnemy::m_nNumAll = 0;
CEnemy *CEnemy::m_Enemy[MAX_ENEMY] = {};
//CEnemy::TYPE CEnemy::m_type = TYPE_NONE;

//�}�N����`
#define ENEMYNEAR_TEXT     ("data\\TEXT\\yanki001.txt")  //�G�̃e�L�X�g�t�@�C��
#define ENEMYFAR_TEXT      ("data\\TEXT\\enemyfar.txt")  //�G�̃e�L�X�g�t�@�C��

//================================================================
//�R���X�g���N�^
//================================================================
CEnemy::CEnemy()
{
	m_nNumber = 0;
	m_pShadow = NULL;
	m_Life = NULL;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemy::~CEnemy()
{

}

//================================================================
//�G�̏���������
//================================================================
HRESULT CEnemy::Init(void)
{
	D3DXVECTOR3 pos = Getpos();

	if (m_pShadow == NULL)
	{
		m_pShadow = new CShadow(pos);

		//����������
		m_pShadow->Init();
	}

	/*if (m_Life == NULL)
	{
		m_Life = new CLife(pos);

		m_Life->Init();
	}*/

	//CLife::Set({pos.x, pos.y + 50.0f, pos.z});

	return S_OK;
}

//================================================================
//�G�̏I������
//================================================================
void CEnemy::Uninit(void)
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

		//delete m_pShadow;

		m_pShadow = NULL;
	}

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//�g�p���Ă�����

			m_apModel[nCount]->Uninit();  //�I������
			delete m_apModel[nCount];     //���������J��
			m_apModel[nCount] = NULL;     //�g�p���Ă��Ȃ���Ԃɂ���
		}
	}

	if (m_Enemy[m_nNumber] != NULL)
	{
		m_Enemy[m_nNumber] = NULL;
	}

	CObject::Release();
}

//================================================================
//�G�̍X�V����
//================================================================
void CEnemy::Update(void)
{
	//�e�̏����擾
	CShadow *pShadow = CGame::GetShadow();

	CLife *pLife = CGame::GetLife();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();

	//�G�}�l�[�W���̏��擾
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	//�v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();

	//�G�̑����擾
	int nNumEnemy = CEnemyManager::GetNumAll();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//�X�V����
		m_apModel[nCount]->Update();
	}

	if (m_motion != NULL)
	{//�g�p����Ă�����

		//����������
		m_motion->Update();
	}

	//�f�o�b�O�\���p�̗͎擾
	int nLife = GetLife();

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		if (m_Enemy[nCount] != NULL)
		{
			int life = m_Enemy[nCount]->GetLife();

			if (life <= 0 && m_Enemy[nCount]->GetState() != STATE_DEATH && m_Enemy[nCount]->GetState() != STATE_END)
			{//�̗͂��Ȃ��Ȃ�����

				if (m_Enemy[nCount]->m_type == TYPE_NEAR)
				{
					
				}

				/*if (m_Enemy[nCount]->m_type == TYPE_FAR)
				{
					CItem::Create(m_Enemy[nCount]->Getpos(), CItem::TYPE_BOM, "data\\MODEL\\bom.x");
				}*/

				m_Enemy[nCount]->SetState(STATE_DEATH);
			}

			if (m_Enemy[nCount]->GetState() == STATE_END)
			{
				//CItem::Create(m_Enemy[nCount]->Getpos(), CItem::TYPE_NAILBAT, "data\\MODEL\\kugibat.x");



				//�I������
				m_Enemy[nCount]->Uninit();

				//�g�p���Ă��Ȃ���Ԃɂ���
				m_Enemy[nCount] = NULL;

				CScore::AddScore(500);

				int DeathCounter = pEnemyManager->GetCounter();

				DeathCounter++;

				pEnemyManager->SetCounter(DeathCounter);

				pPlayer->SetBullet(6);

				

				return;
			}
		}
	}

	m_pShadow->SetPosition(m_nIdxShaadow, { EnemyPos.x, 2.0f, EnemyPos.z });

	CDebugProc *pDebugProc = CManager::GetDebugProc();
	pDebugProc->Print("\n�G�̗̑́F<<%d>>", nLife);
	pDebugProc->Print("\n�G�̈ʒu�F<<X��:%f,Y��:%f,Z��:%f>>", EnemyPos.x, EnemyPos.y, EnemyPos.z);
	pDebugProc->Print("\n�G�̌����F<<X��:%f,Y��:%f,Z��:%f>>", m_rot.x, m_rot.y, m_rot.z);
}

//================================================================
//�G�̕`�揈��
//================================================================
void CEnemy::Draw(void)
{
	
}

//================================================================
//�q�b�g����
//================================================================
void CEnemy::Hit(void)
{
	if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE &&  m_state != STATE_JUMP && m_state != STATE_END && m_state != STATE_DEATH)
	{
		int Life = GetLife();

		Life -= 1;

		SetLife(Life);

		SetState(CEnemy::STATE_DAMEGE);

		D3DXVECTOR3 pos = Getpos();

		D3DXVECTOR3 rot = GetRot();
	}
}

//================================================================
//�O���t�@�C���ǂݍ���
//================================================================
void CEnemy::ReadText(char *Filename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;
	int nCntPatrol = 0;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(Filename, "r");

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
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumModel);  //���f���̑���

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);        //=
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
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%f", &m_Readpos.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.z);  //���f���̑���

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);  //=
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

				 //if (strcmp("SET_PATROL", aString) == 0)   //����n�_�ݒ�
				 //{
				 //	while (strcmp("END_PATROL", aString) != 0)
				 //	{
				 //		fscanf(pFile, "%s", &aString);

				 //		if (strcmp("NUM_PATROL", aString) == 0)
				 //		{
				 //			fscanf(pFile, "%s", &aString);  //=
				 //			fscanf(pFile, "%d", &m_nNumPatrol);  //���񂷂�n�_�̐�
				 //		}
				 //		
				 //		if (strcmp("PATROLPOS", aString) == 0)
				 //		{
				 //			fscanf(pFile, "%s", &aString);  //=
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.x);  //����n�_
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.y);  //����n�_
				 //			fscanf(pFile, "%f", &m_Vigi[nCntPatrol].m_PatrolPos.z);  //����n�_

				 //			nCntPatrol++;
				 //		}

				 //	}
				 //}
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
		switch (m_type)
		{
		case TYPE_NONE:
			break;

		case TYPE_NEAR:		//�ߋ���

			//�e�L�X�g�t�@�C���ǂݍ���
			m_motion->ReadText(ENEMYNEAR_TEXT);

			break;

		case TYPE_FAR:		//������

			//�e�L�X�g�t�@�C���ǂݍ���
			m_motion->ReadText(ENEMYFAR_TEXT);

			break;
		}
	}
}