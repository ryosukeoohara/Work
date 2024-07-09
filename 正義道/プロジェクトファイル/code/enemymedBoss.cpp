//===========================================================
//
// ���{�X�̏���[enemymedBoss.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "bullet.h"
#include "motion.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "enemymedBoss.h"
#include "game.h"
#include "texture.h"
#include "score.h"
#include "enemyweak.h"
#include "enemy.h"
#include "effectsord.h"
#include "dispdetection.h"
#include "particl.h"
#include "impact.h"
#include "effect.h"

//================================================================
//�}�N����`
//================================================================
#define ENEMY_WIDTH     (10.0f)                         //��
#define ENEMY_HEIGHT    (10.0f)                         //����
#define ENEMY_LIFE      (50)                            //�̗�
#define FRIST           (15)                            //�U�����蔭���J�n
#define FINISH          (25)                            //�U������I��
#define MAX_LIFE        (7)                             //�̗�
#define ENEMY001_TEXT   ("data\\TEXT\\yanki001.txt")    //�G�̃e�L�X�g�t�@�C��
#define ENEMY002_TEXT   ("data\\TEXT\\yanki002.txt")    //�G�̃e�L�X�g�t�@�C��
#define ENEMY003_TEXT   ("data\\TEXT\\yanki003.txt")    //�G�̃e�L�X�g�t�@�C��

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
CEnemyMedBoss *CEnemyMedBoss::m_EnemyMedBoss = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CEnemyMedBoss::CEnemyMedBoss()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_JumpPoint = { 0.0f,0.0f,0.0f };
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nIdxTexture = 0;
	m_nCntColli = 0;
	m_Tracking = false;
	m_bAction = false;
	m_ACKTYpe = ATTACKTYPE_NONE;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CEnemyMedBoss::CEnemyMedBoss(D3DXVECTOR3 pos, CEnemyMedBoss::TYPEENE type)
{
	SetPos(&pos);  //�ʒu�ݒ�
	SetPosOld(pos);
	m_typeEne = type;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_rot = { 0.0f, 0.0f, 0.0f };   //����
	m_JumpPoint = { 0.0f,0.0f,0.0f };
	m_nNumModel = 0;
	m_nNumPatrol = 0;
	m_nCurrentpos = 0;
	m_nCntAction = 0;
	m_nIdxTexture = 0;
	m_nCntColli = 0;
	m_Tracking = false;
	m_bAction = false;
	m_ACKTYpe = ATTACKTYPE_NONE;
}

//================================================================
//�f�X�g���N�^
//================================================================
CEnemyMedBoss::~CEnemyMedBoss()
{

}

//================================================================
//��������
//================================================================
CEnemyMedBoss *CEnemyMedBoss::Create(D3DXVECTOR3 pos, TYPEENE type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CEnemyMedBoss *pEnemy = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pEnemy == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pEnemy = new CEnemyMedBoss(pos, type);

			//����������
			pEnemy->Init();

			for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
			{
				if (m_Enemy[nCount] == NULL)
				{
					m_Enemy[nCount] = pEnemy;

					m_Enemy[nCount]->SetType(TYPE_BOSS);

					m_Enemy[nCount]->SetNumber(nCount);

					m_EnemyMedBoss = pEnemy;

					int nCountBoss = CEnemyManager::GetNumEneMedBoss();

					nCountBoss++;

					CEnemyManager::SetNumEneMedBoss(nCountBoss);

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
//�G�̏���������
//================================================================
HRESULT CEnemyMedBoss::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	//��ނ̐ݒ�
	m_type = TYPE_MEDBOSS;

	if (m_motion == NULL)
	{
		m_motion = new CMotion;

		//����������
		m_motion->Init();
	}

	//�̗�
	SetLife(MAX_LIFE);

	CEnemy::Init();

	//�e�L�X�g�t�@�C���ǂݍ���
	ReadText(m_typeEne);

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//�G�̏I������
//================================================================
void CEnemyMedBoss::Uninit(void)
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

	CEnemy::Uninit();

	m_EnemyMedBoss = NULL;
}

//================================================================
//�G�̍X�V����
//================================================================
void CEnemyMedBoss::Update(void)
{
	//�G�̑���
	Control();

	//�X�V����
	CEnemy::Update();
}

//================================================================
//�G�̕`�揈��
//================================================================
void CEnemyMedBoss::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&m_mtxTrans, Getpos().x, Getpos().y, Getpos().z);

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
void CEnemyMedBoss::Control(void)
{
	//�f�o�b�O�v���b�N�̏��擾
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�����蔻��̏��擾
	CCollision *pCollision = CGame::GetCollsion();

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	CSound *pSound = CManager::GetSound();

	CDISPDETECTION *pDispDetection = CDISPDETECTION::GetFrame();

	D3DXVECTOR3 pos = Getpos();

	D3DXVECTOR3 posOld = GetPosOld();

	D3DXVECTOR3 posplayer = pPlayer->Getpos();

	if (m_state != STATE_DEATH && m_state != STATE_END)
	{
		if ((pCollision->CollisionCircle(&pos, 300.0f, pPlayer) == true))
		{//�~�̒��Ƀv���C���[���������܂��́A��Ԃ��_���[�W�̂Ƃ�

			posOld = pos;

			D3DXVECTOR3 fDest;

			float fDiffmove, fDestmove;

			fDest = pos - posplayer;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - m_rot.y;

			//�p�x�̒l���C������--------------------------------------------------
			if (fDiffmove >= D3DX_PI)
			{
				fDiffmove = -D3DX_PI;
			}
			else if (fDiffmove <= -D3DX_PI)
			{
				fDiffmove = D3DX_PI;
			}

			m_rot.y += fDiffmove * 0.05f;

			//�p�x�̒l���C������--------------------------------------------------
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y = -D3DX_PI;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y = D3DX_PI;
			}

			//�ړ��ʂ��X�V(����������)
			m_move.x = sinf(m_rot.y + D3DX_PI) * ENEMYMOVE;
			m_move.z = cosf(m_rot.y + D3DX_PI) * ENEMYMOVE;

			if (fDest.x <= 100.0f && fDest.x >= -100.0f && fDest.z <= 100.0f && fDest.z >= -100.0f)
			{
				if (m_state == STATE_DAMEGE || m_state == STATE_STAGGER)
				{
					pos.x -= m_move.x * 0.5f;
					pos.z -= m_move.z * 0.5f;

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

						m_nCntColli = 0;
					}

					if (m_state == STATE_ACTIONNEUTRAL)
					{//��Ԃ��퓬�̐��̂Ƃ�

						m_nCntAction++;
					}

					if (m_motion->IsFinish() == true)
					{
						m_bAction = false;
					}

					if (m_nCntAction >= 40)
					{//�s���\�ɂȂ���

						m_nCntAction = 0;

						//�����̎��ݒ�
						srand((unsigned int)time(0));

						int AttackType = rand() % ATTACKTYPE_MAX;  //�U���̎�ޒ��I

						switch (AttackType)
						{
						case ATTACKTYPE_NONE:   //�ʏ�U��

							m_ACKTYpe = ATTACKTYPE_NONE;

							break;

						case ATTACKTYPE_JUMP:   //�W�����v�U��

							if (m_state != STATE_ACTION)
							{//��Ԃ��U���ȊO�̎�
								m_JumpPoint = posplayer;
								m_JumpPoint.y = m_JumpPoint.y + 50.0f;
								pDispDetection->Create({ pos.x, 1.0f, pos.z });
								m_state = STATE_ACTION;
								m_ACKTYpe = ATTACKTYPE_JUMP;
								m_motion->Set(MOTIONTYPE_JUMP);
								pSound->Play(CSound::SOUND_LABEL_SE08);
								m_bAction = true;
							}

							break;

						case ATTACKTYPE_AROUND:   //�͈͍U��

							if (m_state != STATE_ACTION)
							{//��Ԃ��U���ȊO�̎�

								//���[�V�������Z�b�g(�U��)
								m_motion->Set(MOTIONTYPE_ACTION);

								pSound->Play(CSound::SOUND_LABEL_SE00);

								m_state = STATE_ACTION;

								m_bAction = true;
							}

							m_ACKTYpe = ATTACKTYPE_AROUND;

							break;

						case ATTACKTYPE_BOM:

							if (m_state != STATE_ACTION)
							{//��Ԃ��U���ȊO�̎�

								//���[�V�������Z�b�g(�U��)
								m_motion->Set(MOTIONTYPE_BOM);

								m_state = STATE_ACTION;

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y + 0.25f, 0.0f), CBullet::TYPE_BOM);

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y, 0.0f), CBullet::TYPE_BOM);

								CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 60.0f, pos.z), D3DXVECTOR3(0.0f, m_rot.y - 0.25f, 0.0f), CBullet::TYPE_BOM);

								m_bAction = true;
							}

							m_ACKTYpe = ATTACKTYPE_BOM;

							break;
						}

						if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
						{
							//���[�V�������Z�b�g(�j���[�g����)
							m_motion->Set(MOTIONTYPE_DAMEGE);

							m_state = STATE_STAGGER;
						}

						if (m_state == STATE_STAGGER)
						{
							pos.x -= m_move.x;
							pos.z -= m_move.z;
						}
					}
				}
			}
			else
			{
				if (m_state != STATE_ACTION && m_ACKTYpe != ATTACKTYPE_JUMP && m_state != STATE_GETUP && m_state != STATE_DAMEGE && m_state != STATE_STAGGER && m_ACKTYpe != ATTACKTYPE_BOM)
				{//��Ԃ��U���ȊO���U���̎�ނ��W�����v�U���ȊO�̎�

					pos.x += m_move.x * 1.3f;
					pos.z += m_move.z * 1.3f;

					if (m_state != STATE_MOVE)
					{//��Ԃ��ړ��ȊO�̎�

						m_nFrame = 0;

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
			if (m_state != STATE_DAMEGE && m_state != STATE_STAGGER)
			{
				if (m_state != STATE_NONE && m_ACKTYpe != ATTACKTYPE_JUMP && m_bAction == false)
				{//��Ԃ�NONE�ȊO���U���̎�ނ��W�����v�U���ȊO�̎�

					m_nFrame = 0;

					//���[�V�������Z�b�g(�j���[�g����)
					m_motion->Set(MOTIONTYPE_NONE);

					m_state = STATE_NONE;
				}
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_AROUND)
		{
			m_nCntColli++;

			if (m_nCntColli >= FRIST && m_nCntColli <= FINISH)
			{
				if ((pCollision->CollisionCircle(&pos, 200.0f, pPlayer) == true))
				{//�~�̒��Ƀv���C���[��������

					pPlayer->Hit();
				}
			}
		}

		if (m_state == STATE_DAMEGE && m_state != STATE_STAGGER)
		{
			//���[�V�������Z�b�g(�j���[�g����)
			m_motion->Set(MOTIONTYPE_DAMEGE);

			m_state = STATE_STAGGER;
		}

		if (m_state == STATE_ACTION && m_ACKTYpe != ATTACKTYPE_JUMP && m_state != STATE_GETUP&& m_state != STATE_DAMEGE && m_state != STATE_STAGGER)
		{//��Ԃ��U���ȊO���U���̎�ނ��W�����v�U���ȊO�̎�

			m_nFrame++;

			if (m_nFrame == 15)
			{
				CEffectSword::Create({ pos.x, pos.y + 20.0f, pos.z }, { 0.0f, m_rot.y, 0.0f });
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_JUMP && m_state != STATE_JUMP && m_state != STATE_GETUP)
		{//�U���̎�ނ��W�����v�U������Ԃ��W�����v�ȊO�̂Ƃ�

			m_move.y += ENEMYMOVE * 0.1f;

			pos.y += m_move.y;

			if (pos.y >= 100.0f)
			{
				m_state = STATE_JUMP;
				m_move = { 0.0f, 0.0f, 0.0f };
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_JUMP  && m_state == STATE_JUMP)
		{//�U���̎�ނ��W�����v�U������Ԃ��W�����v�̎�

			m_move.y += ENEMYMOVE * 0.8f;

			pos.y -= m_move.y;

			if (pos.y <= 0.0f)
			{
				pos.y = 0.0f;

				CParticl::Create(pos, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 5.0f, TYPEPAR_GROUND);
				CImpact::Create({ pos.x, 15.0f, pos.z }, CImpact::TYPE_NONE);

				pSound->Play(CSound::SOUND_LABEL_SE06);

				m_ACKTYpe = ATTACKTYPE_NONE;
				m_state = STATE_GETUP;
				m_motion->Set(MOTIONTYPE_GETUP);

				if ((pCollision->CollisionCircle(&pos, 300.0f, pPlayer) == true))
				{//�~�̒��Ƀv���C���[��������

					pPlayer->Hit();
				}

				if (pDispDetection != NULL)
				{
					pDispDetection->Uninit();
					pDispDetection = NULL;
				}
			}
		}

		if (m_ACKTYpe == ATTACKTYPE_BOM)
		{//�U���̎�ނ����e�U��

			D3DXMATRIX Matrix = m_apModel[6]->GetMtxWorld();

			CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);
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

	if (m_motion->IsFinish() == true && m_state != STATE_DEATH)
	{//���[�V�������I������

		m_move = { 0.0f, 0.0f, 0.0f };
		m_nFrame = 0;
		m_nCntColli = 0;
		//m_state = TATE_NONE;
		m_ACKTYpe = ATTACKTYPE_NONE;
		m_bAction = false;
	}

	//�ʒu�ݒ�
	SetPos(&pos);
	SetPosOld(posOld);
}

//================================================================
//�O���t�@�C���ǂݍ���
//================================================================
void CEnemyMedBoss::ReadText(TYPEENE type)
{
	char aString[128] = {};
	char aComment[128] = {};
	const char *aText[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;
	int nCntPatrol = 0;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	switch (m_typeEne)
	{
	case TYPE_NONE:

		break;

	case TYPE_001:

		aText[0] = ENEMY001_TEXT;
		break;

	case TYPE_002:

		aText[0] = ENEMY002_TEXT;
		break;

	case TYPE_003:

		aText[0] = ENEMY003_TEXT;
		break;
	}

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(aText[0], "r");

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
		switch (m_typeEne)
		{
		case TYPE_NONE:

			break;

		case TYPE_001:

			//����������
			m_motion->ReadText(ENEMY001_TEXT);
			break;

		case TYPE_002:

			//����������
			m_motion->ReadText(ENEMY002_TEXT);
			break;

		case TYPE_003:

			//����������
			m_motion->ReadText(ENEMY003_TEXT);
			break;
		}
		
	}
}