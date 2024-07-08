//===========================================================
//
//�|���S�����o�����[enemy.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyweak.h"
#include "number.h"
#include "texture.h"
#include "motion.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "message.h"
#include "game.h"
#include "enemymanager.h"
#include "score.h"
#include "effect.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//�}�N����`
#define ENEMY_WIDTH     (40.0f)    //��
#define ENEMY_HEIGHT    (100.0f)   //����
#define ENEMY_LIFE      (3)        //�̗�
#define ENEMYNEAR_TEXT     ("data\\TEXT\\yankinear.txt")  //�G�̃e�L�X�g�t�@�C��
#define ENEMYFAR_TEXT      ("data\\TEXT\\enemyfar.txt")  //�G�̃e�L�X�g�t�@�C��

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
//LPDIRECT3DTEXTURE9 CEnemyWeak::m_pTexture = NULL;
CEnemyWeak *CEnemyWeak::m_EnemyWeak[128] = {};

CEnemyWeak::TYPE CEnemyWeak::m_type = TYPE_NONE;

//================================================================
//�R���X�g���N�^
//================================================================
CEnemyWeak::CEnemyWeak()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CEnemyWeak::CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //�ʒu�ݒ�
				   //SetType(type);     //��ގ擾
	//m_pos = pos;
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemyWeak::~CEnemyWeak()
{

}

//================================================================
//��������
//================================================================
CEnemyWeak *CEnemyWeak::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CEnemyWeak *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pEnemy = new CEnemyWeak(pos, rot);

			//����������
			pEnemy->Init();

			for (int nCount = 0; nCount < 128; nCount++)
			{
				if (m_EnemyWeak[nCount] == NULL)
				{
					m_EnemyWeak[nCount] = pEnemy;

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					//m_nNumAll++;

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//�G�̏���������
//================================================================
HRESULT CEnemyWeak::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	//��ނ̐ݒ�
	//SetType(TYPE_ENEMY);

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//����������
		m_motion->Init();
	}

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\yanki.jpg");

	//�̗�
	SetLife(ENEMY_LIFE);

	m_move.x = sinf(m_rot.y + (D3DX_PI * 0.5f)) * ENEMYMOVE;
	//m_move.z = cosf(m_rot.y + (D3DX_PI * 0.5f)) * ENEMYMOVE;

	//�e�L�X�g�t�@�C���ǂݍ���
	//ReadText();

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	//m_pos = GetPosition();

	return S_OK;
}

//================================================================
//�G�̏I������
//================================================================
void CEnemyWeak::Uninit(void)
{
	if (m_motion != NULL)
	{
		//�I������
		m_motion->Uninit();

		delete m_motion;

		m_motion = NULL;
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

	CObject::Release();
}

//================================================================
//�G�̍X�V����
//================================================================
void CEnemyWeak::Update(void)
{
	
}

//================================================================
//�G�̕`�揈��
//================================================================
void CEnemyWeak::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//�g�p���Ă�����

			//�`�揈��
			m_apModel[nCount]->Draw();
		}
	}
}

//================================================================
//�G�̓���
//================================================================
void CEnemyWeak::Control(void)
{
	

	
}

//================================================================
//���S����
//================================================================
void CEnemyWeak::Death(int nCntEnemy)
{
	//�I������
	m_Enemy[nCntEnemy]->Uninit();

	//�g�p���Ă��Ȃ���Ԃɂ���
	m_Enemy[nCntEnemy] = NULL;
}

//================================================================
//�O���t�@�C���ǂݍ���
//================================================================
void CEnemyWeak::ReadText(char *Filename)
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

//================================================================
//�U�R�G�S���̏I������
//================================================================
void CEnemyWeak::UninitWeak(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (m_Enemy[nCount] != NULL)
		{
			m_Enemy[nCount]->Uninit();

			m_Enemy[nCount] = NULL;
		}
	}

	////�G�̑������Z�b�g
	//CEnemyManager::SetNumEneWeak(0);
	//CEnemyManager::SetNumEneMedBoss(0);
	//CEnemyManager::SetNumEneBoss(0);
	//CEnemyManager::SetNumAll(0);
}

//***************************************************************************************************
//�ߋ��������G
//***************************************************************************************************

//================================================================
//�R���X�g���N�^
//================================================================
CEnemyNear::CEnemyNear()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_nCntRush = 0;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CEnemyNear::CEnemyNear(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //�ʒu�ݒ�
	SetRot(&rot);  //�����ݒ�
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_nCntRush = 0;
	m_Tracking = false;
	m_bAction = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemyNear::~CEnemyNear()
{

}

//================================================================
//��������
//================================================================
CEnemyNear *CEnemyNear::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CEnemyNear *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pEnemy = new CEnemyNear(pos, rot);

			//����������
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_NEAR);

					m_Enemy[nCount]->SetNumber(nCount);

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					int nNumAll = CEnemyManager::GetNumAll();

					nNumAll++;

					CEnemyManager::SetNumAll(nNumAll);

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//����������
//================================================================
HRESULT CEnemyNear::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	D3DXVECTOR3 pos = Getpos();

	//�e�̏����擾
	CShadow *pShadow = CGame::GetShadow();

	//m_nIdxShaadow = pShadow->Set(pos);

	m_type = TYPE_NEAR;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//����������
		m_motion->Init();
	}

	//�̗�
	SetLife(ENEMY_LIFE);

	CEnemy::Init();

	//�e�L�X�g�t�@�C���ǂݍ���
	CEnemy::ReadText(ENEMYNEAR_TEXT);

	//�e�L�X�g�t�@�C���ǂݍ���
	m_motion->ReadText(ENEMYNEAR_TEXT);

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//�I������
//================================================================
void CEnemyNear::Uninit(void)
{
	//�I������
	CEnemy::Uninit();
}

//================================================================
//�X�V����
//================================================================
void CEnemyNear::Update(void)
{
	Control();

	CEnemy::Update();
}

//================================================================
//�`�揈��
//================================================================
void CEnemyNear::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();

	//�����擾
	D3DXVECTOR3 EnemyRot = GetRot();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, EnemyRot.y, EnemyRot.x, EnemyRot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{//�g�p���Ă�����

		    //�`�揈��
			m_apModel[nCount]->Draw();
		}
	}
}

//================================================================
//����
//================================================================
void CEnemyNear::Control(void)
{
	//�f�o�b�O�v���b�N�̏��擾
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�����蔻��̏��擾
	CCollision *pCollision = CManager::GetCollsion();

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();

	//�����擾
	D3DXVECTOR3 EnemyRot = GetRot();

	if (GetState() != STATE_DEATH && GetState() != STATE_END)
	{
		if ((pCollision->CollisionCircle(&EnemyPos, 300.0f, pPlayer) == true))
		{//�~�̒��Ƀv���C���[���������܂��́A��Ԃ��_���[�W�̂Ƃ�

			D3DXVECTOR3 fDest, pos = pPlayer->Getpos();
			float fDiffmove, fDestmove;

			fDest = EnemyPos - pos;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - EnemyRot.y;

			if (m_state != STATE_RUSH)
			{
				//�p�x�̒l���C������--------------------------------------------------
				if (fDiffmove >= D3DX_PI)
				{
					fDiffmove = -D3DX_PI;
				}
				else if (fDiffmove <= -D3DX_PI)
				{
					fDiffmove = D3DX_PI;
				}

				EnemyRot.y += fDiffmove * 0.05f;

				//�p�x�̒l���C������--------------------------------------------------
				if (EnemyRot.y > D3DX_PI)
				{
					EnemyRot.y = -D3DX_PI;
				}
				else if (EnemyRot.y < -D3DX_PI)
				{
					EnemyRot.y = D3DX_PI;
				}
			}

			//�ړ��ʂ��X�V(����������)
			m_move.x = sinf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 100.0f && fDest.x >= -100.0f && fDest.z <= 100.0f && fDest.z >= -100.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					EnemyPos.x -= m_move.x * 0.5f;
					EnemyPos.z -= m_move.z * 0.5f;

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
				else
				{
					if (m_state != STATE_ACTIONNEUTRAL && m_bAction == false)
					{
						//���[�V�������Z�b�g(�ړ�)
						m_motion->Set(MOTIONTYPE_ACTIONNEUTRAL);

						m_state = STATE_ACTIONNEUTRAL;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{
						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_bAction = false;
					}

					if (m_nCntAction % 60 == 0)
					{
						if (m_state != STATE_ACTION && m_state != STATE_RUSH)
						{
							//���[�V�������Z�b�g(�U��)
							m_motion->Set(MOTIONTYPE_ACTION);

							m_state = STATE_ACTION;

							pSound->Play(CSound::SOUND_LABEL_SE07);

							m_bAction = true;

							m_nCntRush++;
						}
					}

					if (m_bAction == true)
					{
						D3DXMATRIX Matrix = m_apModel[15]->GetMtxWorld();

						D3DXVECTOR3 kugipos = { Matrix._41, Matrix._42, Matrix._43 };

						CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);

						if (pCollision->kugibat(&kugipos, pPlayer))
						{
							int n = 0;
						}
					}

					if (m_nCntRush > 3)
					{
						if (m_state != STATE_RUSH)
						{
							//���[�V�������Z�b�g(�U��)
							m_motion->Set(MOTIONTYPE_RUSH);

							m_state = STATE_RUSH;

							m_bAction = true;

							m_nCntRush = 0;
						}
					}

					if (m_state == STATE_RUSH)
					{
						EnemyPos.x += m_move.x * 1.2f;
						EnemyPos.z += m_move.z * 1.2f;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_state == STATE_STAGGER)
					{
						EnemyPos.x -= m_move.x;
						EnemyPos.z -= m_move.z;
					}
				}
			}
			else
			{
				if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE)
				{
					EnemyPos.x += m_move.x;
					EnemyPos.z += m_move.z;

					if (m_state != STATE_MOVE)
					{
						//���[�V�������Z�b�g(�ړ�)
						m_motion->Set(MOTIONTYPE_MOVE);

						m_state = STATE_MOVE;

						m_bAction = false;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}
				}
				else
				{
					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
			}
		}
		else
		{
			if (m_state != STATE_NONE)
			{
				//���[�V�������Z�b�g(�j���[�g����)
				m_motion->Set(MOTIONTYPE_NONE);

				m_state = STATE_NONE;
			}
		}
	}

	if (m_state == STATE_DEATH && m_state != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//���[�V�������Z�b�g(���S)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->IsFinish() == true && m_state == STATE_DEATH)
	{
		m_state = STATE_END;

		m_bAction = false;
	}

	//�ʒu�ݒ�
	SetPos(&EnemyPos);

	//�����ݒ�
	SetRot(&EnemyRot);
}


//***************************************************************************************************
//�����������G
//***************************************************************************************************

//================================================================
//�R���X�g���N�^
//================================================================
CEnemyFar::CEnemyFar()
{
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_nCntReload = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
	m_bBom = false;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CEnemyFar::CEnemyFar(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(&pos);  //�ʒu�ݒ�
	SetRot(&rot);  //�����ݒ�
	m_state = STATE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nNumAll = 0;
	m_nCntDeath = 0;
	m_nCntReload = 0;
	m_DeathEnemyIdx = 0;
	m_nIdxTexture = -1;
	m_Tracking = false;
	m_bAction = false;
	m_bBom = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemyFar::~CEnemyFar()
{

}

//================================================================
//��������
//================================================================
CEnemyFar *CEnemyFar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CEnemyFar *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pEnemy = new CEnemyFar(pos, rot);

			//����������
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_FAR);

					m_Enemy[nCount]->SetNumber(nCount);

					int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

					nNumEnemyWeak++;

					CEnemyManager::SetNumEneWeak(nNumEnemyWeak);

					int nNumAll = CEnemyManager::GetNumAll();

					nNumAll++;

					CEnemyManager::SetNumAll(nNumAll);

					break;
				}
			}
		}
	}

	return pEnemy;
}

//================================================================
//����������
//================================================================
HRESULT CEnemyFar::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	D3DXVECTOR3 pos = Getpos();

	//�e�̏����擾
	CShadow *pShadow = CGame::GetShadow();

	//m_nIdxShaadow = pShadow->Set(pos);

	m_type = TYPE_FAR;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//����������
		m_motion->Init();
	}

	//�̗�
	SetLife(ENEMY_LIFE);

	CEnemy::Init();

	//�e�L�X�g�t�@�C���ǂݍ���
	CEnemy::ReadText(ENEMYFAR_TEXT);

	//�e�L�X�g�t�@�C���ǂݍ���
	m_motion->ReadText(ENEMYFAR_TEXT);

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//�I������
//================================================================
void CEnemyFar::Uninit(void)
{
	CEnemy::Uninit();

	//CObject::Release();
}

//================================================================
//�X�V����
//================================================================
void CEnemyFar::Update(void)
{
	Control();

	CEnemy::Update();
}

//================================================================
//�`�揈��
//================================================================
void CEnemyFar::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();

	//�����擾
	D3DXVECTOR3 EnemyRot = GetRot();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, EnemyRot.y, EnemyRot.x, EnemyRot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, EnemyPos.x, EnemyPos.y, EnemyPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bBom != true)
	{//�U�����Ă��Ȃ��Ƃ�

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_apModel[nCount] != NULL)
			{//�g�p���Ă�����

				//�`�揈��
				m_apModel[nCount]->Draw();
			}
		}
	}
	else
	{
		for (int nCount = 0; nCount < m_nNumModel - 1; nCount++)
		{
			if (m_apModel[nCount] != NULL)
			{//�g�p���Ă�����

				//�`�揈��
				m_apModel[nCount]->Draw();
			}
		}
	}
}

//================================================================
//����
//================================================================
void CEnemyFar::Control(void)
{
	//�f�o�b�O�v���b�N�̏��擾
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�����蔻��̏��擾
	CCollision *pCollision = CManager::GetCollsion();

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	//�ʒu�擾
	D3DXVECTOR3 EnemyPos = Getpos();
	D3DXVECTOR3 EnemyRot = GetRot();

	m_state = GetState();

	if (GetState() != STATE_DEATH && GetState() != STATE_END)
	{
		if ((pCollision->CollisionCircle(&EnemyPos, 400.0f, pPlayer) == true))
		{//�~�̒��Ƀv���C���[���������܂��́A��Ԃ��_���[�W�̂Ƃ�

			D3DXVECTOR3 fDest, pos = pPlayer->Getpos();

			float fDiffmove, fDestmove;

			fDest = EnemyPos - pos;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - EnemyRot.y;

			//�p�x�̒l���C������--------------------------------------------------
			if (fDiffmove >= D3DX_PI)
			{
				fDiffmove = -D3DX_PI;
			}
			else if (fDiffmove <= -D3DX_PI)
			{
				fDiffmove = D3DX_PI;
			}

			EnemyRot.y += fDiffmove * 0.05f;

			//�p�x�̒l���C������--------------------------------------------------
			if (EnemyRot.y > D3DX_PI)
			{
				EnemyRot.y = -D3DX_PI;
			}
			else if (EnemyRot.y < -D3DX_PI)
			{
				EnemyRot.y = D3DX_PI;
			}
			
			//�ړ��ʂ��X�V(����������)
			m_move.x = sinf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(EnemyRot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 200.0f && fDest.x >= -200.0f && fDest.z <= 200.0f && fDest.z >= -200.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					EnemyPos.x -= m_move.x * 0.5f;
					EnemyPos.z -= m_move.z * 0.5f;

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
				else
				{
					if (m_state != STATE_ACTIONNEUTRAL && m_bAction == false)
					{
						//���[�V�������Z�b�g(�ړ�)
						m_motion->Set(MOTIONTYPE_ACTIONNEUTRAL);

						m_state = STATE_ACTIONNEUTRAL;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{
						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}

					if (m_nCntAction % 120 == 0)
					{
						if (m_state != STATE_ACTION && m_bBom == false)
						{
							//���[�V�������Z�b�g(�U��)
							m_motion->Set(MOTIONTYPE_ACTION);

							m_state = STATE_ACTION;

							CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + 60.0f, EnemyPos.z), D3DXVECTOR3(0.0f, EnemyRot.y, 0.0f), CBullet::TYPE_ENEMY);

							pSound->Play(CSound::SOUND_LABEL_SE07);

							m_bAction = true;
							m_bBom = true;
						}
					}

					if (m_bBom == true)
					{
						m_nCntReload++;
					}

					if (m_nCntReload % 150 == 0)
					{
						if (m_bBom == true)
						{
							//���[�V�������Z�b�g(�U��)
							m_motion->Set(MOTIONTYPE_REROAD);

							m_bBom = false;
							m_nCntReload = 0;
						}
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}

					if (m_state == STATE_STAGGER)
					{
						EnemyPos.x -= m_move.x;
						EnemyPos.z -= m_move.z;
					}
				}

				if (fDest.x <= 50.0f && fDest.x >= -50.0f && fDest.z <= 50.0f && fDest.z >= -50.0f)
				{

				}
			}
			else
			{
				if (m_state != STATE_STAGGER && m_state != STATE_DAMEGE)
				{
					EnemyPos.x += m_move.x;
					EnemyPos.z += m_move.z;

					if (m_state != STATE_MOVE)
					{
						//���[�V�������Z�b�g(�ړ�)
						m_motion->Set(MOTIONTYPE_MOVE);
						
						m_state = STATE_MOVE;

						m_bAction = false;
					}

					if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
					{
						//���[�V�������Z�b�g(�j���[�g����)
						m_motion->Set(MOTIONTYPE_DAMEGE);

						m_state = STATE_STAGGER;
					}
				}
				else
				{
					if (m_motion->IsFinish() == true)
					{
						m_state = STATE_NONE;

						m_bAction = false;
					}
				}
			}
		}
		else
		{
			if (m_state != STATE_NONE)
			{
				//���[�V�������Z�b�g(�j���[�g����)
				m_motion->Set(MOTIONTYPE_NONE);

				m_state = STATE_NONE;
			}
		}

		if (m_state == STATE_NONE)
		{
			EnemyPos.y = -10.0f;
		}
		else
		{
			EnemyPos.y = 0.0f;
		}
	}

	if (m_state != STATE_DEATH || m_state != STATE_END)
	{
		if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
		{
			EnemyPos.x -= m_move.x * 0.5f;
			EnemyPos.z -= m_move.z * 0.5f;

			if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
			{
				//���[�V�������Z�b�g(�j���[�g����)
				m_motion->Set(MOTIONTYPE_DAMEGE);

				m_state = STATE_STAGGER;
			}

			if (m_motion->IsFinish() == true)
			{
				m_state = STATE_NONE;

				m_bAction = false;
			}
		}
	}
	

	if (m_state == STATE_DEATH && m_state != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//���[�V�������Z�b�g(���S)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->IsFinish() == true && m_state != STATE_DEATH)
	{
		m_state = STATE_NONE;

		m_bAction = false;
	}

	if (m_motion->IsFinish() == true && m_state == STATE_DEATH)
	{
		m_state = STATE_END;

		m_bAction = false;
	}

	//�ʒu�ݒ�
	SetPos(&EnemyPos);
	SetRot(&EnemyRot);
}