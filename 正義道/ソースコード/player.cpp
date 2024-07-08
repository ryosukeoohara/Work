//===========================================================
//
//�|���S�����o�����[player.cpp]
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
#include "enemyBoss.h"
#include "enemyweak.h"
#include "effect.h"
#include "debugproc.h"
#include "block.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "collision.h"
#include "particl.h"
#include "frame.h"
#include "game.h"
#include "effectsord.h"
#include "displife.h"
#include "map.h"
#include "shadow.h"
#include "fade.h"
#include "tutorial.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
//�}�N����`
//================================================================
#define MAX_LIFE    (10)                            //�v���C���[�̗̑�
#define REST_BULLET (6)                             //�ێ��ł���e�̐�
#define MUTEKITIME  (30)                            //���G����
#define PLAYER_X    (40.0f)                         //�v���C���[��X���̕�
#define PLAYER_Z    (10.0f)                         //�v���C���[��Z���̕�
#define FRIST       (21)                            //�U�����蔭���J�n
#define FINISH      (31)                            //�U������I��
#define PLAYER_TEXT ("data\\TEXT\\player.txt")      //�v���C���[�̃e�L�X�g�t�@�C��

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CPlayer::CPlayer()
{
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	//m_rot = { 0.0f, 0.0f, 0.0f };
	m_State = STATE_NONE;
	m_AcType = ACTIONTYPE_NEAR;
	m_nCnterMotion = 0;
	m_nCntMotion = 0;
	m_nCntEff = 0;
	m_nCntDuration = 0;
	m_nCntDie = 0;
	m_nCntSound = 0;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nLifeGage = -1;
	m_RestBullet = 0;
	m_motion = NULL;
	m_pShadow = NULL;
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
	m_bAction = false;
	m_bEncounter = false;
	m_bIconDisp = false;
	m_bAcFir = false;
	m_bAcSec = false;
	m_bAcThr = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CPlayer::CPlayer(D3DXVECTOR3 pos)
{
	SetPos(&pos);  //�ʒu
	SetRot(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_move = {0.0f, 0.0f, 0.0f};  //�ړ���
	m_Readpos = { 0.0f, 0.0f, 0.0f };
	m_Readrot = { 0.0f, 0.0f, 0.0f };
	m_State = STATE_NONE;
	m_AcType = ACTIONTYPE_NEAR;
	m_nCnterMotion = 0;
	m_nCntMotion = 0;
	m_nCntEff = 0;
	m_nCntDuration = 0;
	m_nCntDie = 0;
	m_nCntSound = 0;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nLifeGage = -1;
	m_RestBullet = 0;
	m_motion = NULL;
	m_pShadow = NULL;
	m_fDiff = 0.0f;
	m_fDest = 0.0f;
	m_bDash = false;
	m_bAction = false;
	m_bEncounter = false;
	m_bIconDisp = false;
	m_bAcFir = false;
	m_bAcSec = false;
	m_bAcThr = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CPlayer::~CPlayer()
{

}

//================================================================
//��������
//================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CPlayer *pPlayer = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pPlayer = new CPlayer(pos);

			//����������
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
//�v���C���[�̏���������
//================================================================
HRESULT CPlayer::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	//���C�t�\���̏��擾
	CDispLife *pDispLife = CGame::GetDispLife();

	//�V�[���̏����擾
	CScene *pScene = CManager::GetScene();

	if (pScene->GetMode() == CScene::MODE_TUTORIAL)
	{
		m_Tutostate = TUTOSTATE_MOVE;
	}

	//�e�̏����擾
	//CShadow *pShadow = CGame::GetShadow();

	D3DXVECTOR3 pos = Getpos();

	//��ސݒ�
	SetType(TYPE_PLAYER);

	if(m_motion == NULL)
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

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\yanki.jpg");

	ReadText();

	SetLife(MAX_LIFE);

	m_RestBullet = REST_BULLET;

	//���f���̐ݒ�
	m_motion->SetModel(&m_apModel[0], m_nNumModel);

	return S_OK;
}

//================================================================
//�v���C���[�̏I������
//================================================================
void CPlayer::Uninit(void)
{
	//�T�E���h�̏����擾
	CSound *pSound = CManager::GetSound();

	//�T�E���h�X�g�b�v
	pSound->Stop();

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

//================================================================
//�v���C���[�̍X�V����
//================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *InputKeyboard;

	InputKeyboard = CManager::GetKeyBoard();

	CSound *pSound;

	pSound = CManager::GetSound();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::GetFade();

	//�V�[���̏����擾
	CScene *pScene = CManager::GetScene();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Update();
	}

	if (m_motion != NULL)
	{
		//����������
		m_motion->Update();
	}

	int nLife = GetLife();

	if (pScene->GetMode() == CScene::MODE_GAME)
	{
		//�v���C���[�̐���
		ControlPlayer();
	}
	else if (pScene->GetMode() == CScene::MODE_TUTORIAL || pScene->GetMode() == CScene::MODE_TITLE)
	{
		//�`���[�g���A���̃v���C���[�̐���
		ControlTutorial();
	}
	
	SetLife(nLife);

	if (nLife <= 0 && m_State != STATE_DEATH && m_State != STATE_END)
	{
		m_State = STATE_DEATH;

		CEnemyWeak::UninitWeak();
	}

	if (m_State == STATE_END)
	{
		if (pFade->Get() != pFade->FADE_OUT)
		{
			pFade->Set(CScene::MODE_RESULT);
		}
	}
}

//================================================================
//�v���C���[�̕`�揈��
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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

	if (m_State != STATE_END)
	{
		if (m_AcType == ACTIONTYPE_NEAR)
		{
			for (int nCount = 0; nCount < m_nNumModel - 1; nCount++)
			{
				//�`�揈��
				m_apModel[nCount]->Draw();
			}
		}
		else if (m_AcType == ACTIONTYPE_BAT)
		{
			for (int nCount = 0; nCount < m_nNumModel; nCount++)
			{
				if (nCount != 15)
				{
					//�`�揈��
					m_apModel[nCount]->Draw();
				}
			}
		}
		else
		{
			for (int nCount = 0; nCount < m_nNumModel - 2; nCount++)
			{
				//�`�揈��
				m_apModel[nCount]->Draw();
			}
		}
	}
}

//================================================================
//�v���C���[�̐��䏈��
//================================================================
void CPlayer::ControlPlayer(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�J�����擾
	CCamera *pCamera = CManager::GetCamera();

	CObject3D *pObject3D = CManager::GetObject3D();

	//�J�����̌����擾
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//�G�̏��擾
	CEnemyBoss *pEnemyBoss = CEnemyBoss::GetEnemy();

	//�G�̏��擾
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//�����蔻��̏��擾
	CCollision *pCollision = CManager::GetCollsion();

	//�t���[���̏����擾
	CFrame *pFrame = CFrame::GetFrame();

	//�}�b�v���f���̏����擾
	CObjectX **pMap = CMap::GetX();

	//�e�̏����擾
	CShadow *pShadow = CGame::GetShadow();

	D3DXVECTOR3 Playerpos = Getpos();
	D3DXVECTOR3 PlayerRot = GetRot();

	m_posOld = Playerpos;  //�ʒu����
	m_move = GetMove();

	if (Playerpos.x >= 3000.0f)
	{
		Playerpos.x = 3000.0f;
	}

	if (Playerpos.x <= -3000.0f)
	{
		Playerpos.x = -3000.0f;
	}

	if (Playerpos.z >= 3000.0f)
	{
		Playerpos.z = 3000.0f;
	}

	if (Playerpos.z <= -3000.0f)
	{
		Playerpos.z = -3000.0f;
	}

	//�����Ă��Ȃ����
	m_bDash = false;

	//float fHeight;

	if (m_State != STATE_DEATH && m_State != STATE_END)
	{
		if (m_State != STATE_STAGGER && m_State != STATE_DAMEGE)
		{
			if (m_State != STATE_AVOI)
			{
				//��Ɉړ�----------------------------------------------
				if (InputKeyboard->GetPress(DIK_W) == true)
				{//W�L�[�������ꂽ

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//D�L�[�������� �E��Ɉړ�

					 //�ړ���
						m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
					}

					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//A�L�[�������� ����Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
					}

					else
					{//W�L�[����������	�^��Ɉړ�

					 //�ړ���
						m_move.x -= sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
					}

					//�����Ă����Ԃɂ���
					m_bDash = true;

					//�p�[�e�B�N���𐶐�
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}

				//���Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_S) == true)
				{//S�L�[�������ꂽ

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//D�L�[�������� �E���Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
					}
					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//A�L�[�������� �����Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
					}
					else
					{//S�L�[���������� �^���Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI));
					}

					//�����Ă����Ԃɂ���
					m_bDash = true;

					//�p�[�e�B�N���𐶐�
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}

				//�E�Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_D) == true)
				{//D�L�[����������

				 //�ړ���
					m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//����
					m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));

					//�����Ă����Ԃɂ���
					m_bDash = true;

					//�p�[�e�B�N���𐶐�
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}
				//���Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_A) == true)
				{//A�L�[����������

				 //�ړ���
					m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//����
					m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));

					//�����Ă����Ԃɂ���
					m_bDash = true;

					//�p�[�e�B�N���𐶐�
					//CParticl::Create(m_pos, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f);
				}
			}

			if (pCamera->GetType() == CCamera::TYPE_SCOPE || m_AcType == ACTIONTYPE_FAR)
			{
				PlayerRot.y = CameraRot.y;
			}
			else
			{
				m_fDiff = m_fDest - PlayerRot.y;

				//�p�x�̒l���C������
				if (m_fDiff >= D3DX_PI)
				{
					m_fDiff -= D3DX_PI * 2;
				}
				else if (m_fDiff <= -D3DX_PI)
				{
					m_fDiff += D3DX_PI * 2;
				}

				//�ړ�����(�p�x)�̕␳------------------------------------------------
				PlayerRot.y += m_fDiff * 0.15f;

				//�p�x�̒l���C������--------------------------------------------------
				if (PlayerRot.y > D3DX_PI)
				{
					PlayerRot.y = -D3DX_PI;
				}
				else if (PlayerRot.y < -D3DX_PI)
				{
					PlayerRot.y = D3DX_PI;
				}
			}
			
			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
			 && m_AcType == ACTIONTYPE_NEAR && m_State != STATE_AVOI)
			{
				//if (m_bAcFir == false)
				//{
				//	//���[�V�������Z�b�g(�ߐڍU��)
				//	m_motion->Set(MOTIONTYPE_ACFRIST);

				//	m_State = STATE_CONSECAC;

				//	m_bAcFir = true;

				//	m_nCntDuration = 0;
				//}
				//else if (m_bAcFir == true && m_bAcSec == false)
				//{
				//	//���[�V�������Z�b�g(�ߐڍU��)
				//	m_motion->Set(MOTIONTYPE_ACSECOND);

				//	m_State = STATE_CONSECACSEC;

				//	m_bAcSec = true;

				//	m_nCntDuration = 0;
				//}
				//else if (m_bAcSec == true && m_bAcThr == false)
				//{
				//	//���[�V�������Z�b�g(�ߐڍU��)
				//	m_motion->Set(MOTIONTYPE_ACTHIRD);

				//	m_State = STATE_CONSECACTHI;

				//	m_bAcThr = false;
				//}

				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_KNIFEAC);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE00);

				m_bAction = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_SNP && m_AcType == ACTIONTYPE_FAR && m_RestBullet >= 1 && m_State != STATE_AVOI)
			{
				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_SNP);

				m_State = STATE_SNP;

				CBullet::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y + 60.0f, Playerpos.z), D3DXVECTOR3(0.0f, CameraRot.y, 0.0f), CBullet::TYPE_PLAYER);

				m_RestBullet--;

				pSound->Play(CSound::SOUND_LABEL_SE03);

				m_bAction = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC && m_AcType == ACTIONTYPE_BAT)
			{
				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_BATACTION);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE07);

				m_bAction = true;
			}

			if (pInputMouse->GetRButton() == true && m_State != STATE_AVOI)
			{
				//���[�V�������Z�b�g(���)
				m_motion->Set(MOTIONTYPE_AVOI);

				m_State = STATE_AVOI;

				pSound->Play(CSound::SOUND_LABEL_SE10);
			}

			if (m_State == STATE_KNIFEAC)
			{
				m_nCntColi++;

				if (m_nCntColi >= FRIST && m_nCntColi <= FINISH)
				{
					if (m_apModel[m_nNumModel - 1] != NULL)
					{
						D3DXMATRIX Matrix = m_apModel[m_nNumModel - 1]->GetMtxWorld();

						CEffect::Create({ Matrix._41, Matrix._42, Matrix._43 }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 2.0f, 15, CEffect::TYPEEFF_NONE);
					}

					if (pCollision->Knife(&Playerpos, { PlayerRot.x, PlayerRot.y, PlayerRot.z }, 50.0f, pEnemy) == true)
					{
						pDebugProc->Print("\n�N�\�C���z���n����Yspecial�o�[�W����1.2���܂݂�`�`");
					}
				}
			}

			//fHeight = pObject3D->GetHeight(m_pos);

			//m_move.y -= 0.8f;

			Playerpos.x += m_move.x;
			Playerpos.y += m_move.y;
			//m_pos.y = fHeight + 18.0f;
			Playerpos.z += m_move.z;

			if (m_bDash == true && m_State != STATE_MOVE && m_State != STATE_AVOI)
			{
				//���[�V�������Z�b�g(�ړ�)
				m_motion->Set(MOTIONTYPE_MOVE);

				m_State = STATE_MOVE;

				m_nCntColi = 0;

				m_bAction = false;
			}

			if (m_bAcFir == true || m_bAcSec == true || m_bAcThr == true)
			{
				m_nCntDuration++;

				if (m_nCntDuration >= 120)
				{
					m_bAcFir = false;
					m_bAcSec = false;
					m_bAcThr = false;

					m_nCntDuration = 0;
				}
			}

			if (pFrame != NULL)
			{
				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_NEAR && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					//���[�V�������Z�b�g(�ړ�)
					m_motion->Set(MOTIONTYPE_KNIFESTAN);

					m_State = STATE_KNIFESTAN;
				}

				if (m_State != STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					m_motion->Set(MOTIONTYPE_SNPSTAN);

					m_State = STATE_SNPSTAN;
				}

				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_BAT && m_bDash == false && m_bAction == false && m_State != STATE_AVOI)
				{
					//���[�V�������Z�b�g(�ړ�)
					m_motion->Set(MOTIONTYPE_BATNEUTAL);

					m_State = STATE_KNIFESTAN;
				}
			}

			if (m_State == STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR)
			{
				if (InputKeyboard->GetTrigger(DIK_E) == true)
				{//E�L�[�������ꂽ

					if (pCamera->GetType() == CCamera::TYPE_GAME)
					{
						pCamera->SetType(CCamera::TYPE_SCOPE);
					}
					else if (pCamera->GetType() == CCamera::TYPE_SCOPE)
					{
						pCamera->SetType(CCamera::TYPE_GAME);
					}
				}
			}

			if (m_motion->IsFinish() == true)
			{
				m_nCntEff = 0;
				m_nCntColi = 0;
				m_bAction = false;

				m_State = STATE_NONE;
			}

			if (m_State == STATE_NEUTRAL)
			{
				Playerpos.y = -17.0f;
			}
			else
			{
				Playerpos.y = 0.0f;
			}

			//�ړ��ʂ��X�V(����������)--------------------------------------------
			m_move.x += (0.0f - m_move.x) * 0.1f;
			m_move.z += (0.0f - m_move.z) * 0.1f;

			if (pEnemy != NULL)
			{
				//�G�Ƃ̓����蔻��
				if (pCollision->CollsionEnemy(&Playerpos, &m_posOld, PLAYER_X, PLAYER_Z, *pEnemy) == true)
				{

				}
			}
		}
	}

	if (pFrame != NULL)
	{
		if (pFrame->GetACType() == CFrame::TYPE_NEAR)
		{
			m_AcType = ACTIONTYPE_NEAR;
		}

		if (pFrame->GetACType() == CFrame::TYPE_FAR)
		{
			m_AcType = ACTIONTYPE_FAR;
		}

		if (pFrame->GetACType() == CFrame::TYPE_BAT)
		{
			m_AcType = ACTIONTYPE_BAT;
		}
	}
	else
	{
		m_AcType = ACTIONTYPE_NEAR;
	}
	
	if (m_State == STATE_DAMEGE)
	{
		m_State = STATE_STAGGER;

		m_motion->Set(MOTIONTYPE_DAMEGE);

		m_nCntInvincible = MUTEKITIME;
	}

	if (m_State == STATE_STAGGER)
	{
		m_nCntInvincible--;

		Playerpos.x -= m_move.x * 0.5f;
		Playerpos.z -= m_move.z * 0.5f;

		if (m_nCntInvincible <= 0)
		{
			m_State = STATE_NONE;
		}
	}

	if (m_State == STATE_AVOI)
	{
		m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
		m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;

		Playerpos.x += m_move.x * 0.05f;
		Playerpos.z += m_move.z * 0.05f;
	}

	if (m_State == STATE_DEATH && m_State != STATE_END && m_motion->GetType() != MOTIONTYPE_DEATH)
	{
		//���[�V�������Z�b�g(���S)
		m_motion->Set(MOTIONTYPE_DEATH);
	}

	if (m_motion->GetType() == MOTIONTYPE_DEATH)
	{
		m_nCntDie++;

		if (m_nCntDie == 50)
		{
			pSound->Play(CSound::SOUND_LABEL_SE05);
		}
	}
	
	if (m_motion->IsFinish() == true && m_State == STATE_DEATH)
	{
		m_State = STATE_END;

		m_bAction = false;
	}

	if (m_bDash == true && m_nCntSound == 0)
	{
		m_nCntSound = 35;

		pSound->Play(CSound::SOUND_LABEL_SE09);
	}

	if (m_nCntSound > 0)
	{
		m_nCntSound--;
	}

	if (pCollision->Map(&Playerpos, &m_posOld, pMap) == true)
	{
		int n = 0;
	}

	if (m_bEncounter == true)
	{

	}

	SetPos(&Playerpos);
	SetRot(&PlayerRot);

	m_pShadow->SetPosition(m_nIdxShaadow, { Playerpos.x, 2.0f, Playerpos.z });

	pDebugProc->Print("�v���C���[�̈ʒu�F%f,%f,%f\n", Playerpos.x, Playerpos.y, Playerpos.z);
	pDebugProc->Print("�v���C���[�̌����F%f,%f,%f\n", PlayerRot.x, PlayerRot.y, PlayerRot.z);
	pDebugProc->Print("�v���C���[�̈ړ��ʁF%f,%f,%f", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("\n�e���ˁF���N���b�N");
}

//================================================================
//�`���[�g���A���̃v���C���[�̐��䏈��
//================================================================
void CPlayer::ControlTutorial(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::GetKeyBoard();

	//�J�����擾
	CCamera *pCamera = CManager::GetCamera();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	//�V�[���̏����擾
	CScene *pScene = CManager::GetScene();

	//�t���[���̏����擾
	CFrame *pFrame = CFrame::GetFrame();

	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�J�����̌����擾
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	D3DXVECTOR3 Playerpos = Getpos();
	D3DXVECTOR3 PlayerRot = GetRot();

	//�����Ă��Ȃ����
	m_bDash = false;

	if (pScene->GetMode() != CScene::MODE_TITLE)
	{
		if (Playerpos.z >= -1100.0f && m_Tutostate == TUTOSTATE_MOVE)
		{
			//�����Ă����Ԃɂ���
			m_bDash = true;

			m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
			m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
		}

		if (Playerpos.z < -1150.0f && m_Tutostate == TUTOSTATE_MOVE)
		{
			//m_State = PLAYERSTATE_KNIFESTAN;

			m_Tutostate = TUTOSTATE_STOP;
		}

		if (GetTutostate() == TUTOSTATE_NONE)
		{
			if (m_State != STATE_AVOI)
			{
				//��Ɉړ�----------------------------------------------
				if (InputKeyboard->GetPress(DIK_W) == true)
				{//W�L�[�������ꂽ

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//D�L�[�������� �E��Ɉړ�

					 //�ړ���
						m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
					}

					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//A�L�[�������� ����Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
					}

					else
					{//W�L�[����������	�^��Ɉړ�

					 //�ړ���
						m_move.x -= sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z -= cosf(CameraRot.y) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
					}

					//�����Ă����Ԃɂ���
					m_bDash = true;

					m_bPushW = true;
				}

				//���Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_S) == true)
				{//S�L�[�������ꂽ

					if (InputKeyboard->GetPress(DIK_D) == true)
					{//D�L�[�������� �E���Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
					}
					else if (InputKeyboard->GetPress(DIK_A) == true)
					{//A�L�[�������� �����Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
					}
					else
					{//S�L�[���������� �^���Ɉړ�

					 //�ړ���
						m_move.x += sinf(CameraRot.y) * PLAYERMOVE;
						m_move.z += cosf(CameraRot.y) * PLAYERMOVE;

						//����
						m_fDest = (CameraRot.y + (D3DX_PI));
					}

					//�����Ă����Ԃɂ���
					m_bDash = true;

					m_bPushS = true;
				}

				//�E�Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_D) == true)
				{//D�L�[����������

				 //�ړ���
					m_move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//����
					m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));

					//�����Ă����Ԃɂ���
					m_bDash = true;

					m_bPushD = true;
				}
				//���Ɉړ�----------------------------------------------
				else if (InputKeyboard->GetPress(DIK_A) == true)
				{//A�L�[����������

				 //�ړ���
					m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;
					m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * PLAYERMOVE;

					//����
					m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));

					//�����Ă����Ԃɂ���
					m_bDash = true;

					m_bPushA = true;
				}
			}

			m_fDiff = m_fDest - PlayerRot.y;

			//�p�x�̒l���C������
			if (m_fDiff >= D3DX_PI)
			{
				m_fDiff -= D3DX_PI * 2;
			}
			else if (m_fDiff <= -D3DX_PI)
			{
				m_fDiff += D3DX_PI * 2;
			}

			//�ړ�����(�p�x)�̕␳------------------------------------------------
			PlayerRot.y += m_fDiff * 0.15f;

			//�p�x�̒l���C������--------------------------------------------------
			if (PlayerRot.y > D3DX_PI)
			{
				PlayerRot.y = -D3DX_PI;
			}
			else if (PlayerRot.y < -D3DX_PI)
			{
				PlayerRot.y = D3DX_PI;
			}

			if (m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON01)
			{
				CTutorial::SetEndlesson(true);
			}

			if (pInputMouse->GetRButton() == true && m_State != STATE_AVOI
				&& m_bWhee == true)
			{
				//���[�V�������Z�b�g(���)
				m_motion->Set(MOTIONTYPE_AVOI);

				m_State = STATE_AVOI;

				pSound->Play(CSound::SOUND_LABEL_SE10);

				m_bAvoi = true;
			}

			if (m_bAvoi == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON05)
			{
				CTutorial::SetEndlesson(true);
			}

			//===============================================================================================================================
			//�U��
			//===============================================================================================================================
			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
				&& m_AcType == ACTIONTYPE_NEAR && m_State != STATE_AVOI && m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true)
			{
				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_KNIFEAC);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				pSound->Play(CSound::SOUND_LABEL_SE00);

				m_bAction = true;

				m_bAttack = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_SNP
				&& m_AcType == ACTIONTYPE_FAR && m_RestBullet >= 0 && m_State != STATE_AVOI  && m_bWhee == true)
			{
				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_SNP);

				CBullet::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y + 60.0f, Playerpos.z), D3DXVECTOR3(0.0f, m_fDest, 0.0f), CBullet::TYPE_PLAYER);

				m_State = STATE_SNP;

				pSound->Play(CSound::SOUND_LABEL_SE03);

				//m_RestBullet--;

				m_bAction = true;

				m_bAttack = true;
			}

			if (pInputMouse->GetLButton() == true && m_bDash == false && m_State != STATE_KNIFEAC
				&& m_AcType == ACTIONTYPE_BAT  && m_bPushW == true && m_bPushA == true && m_bPushS == true && m_bPushD == true)
			{
				//���[�V�������Z�b�g(�ߐڍU��)
				m_motion->Set(MOTIONTYPE_BATACTION);

				m_State = STATE_KNIFEAC;

				m_nFrame = m_motion->GetNumFrame();

				m_bAction = true;

				m_bAttack = true;
			}

			//===============================================================================================================================

			if (m_bAttack == true && (CTutorial::GetLesson() == CTutorial::TYPE_LESSON02 || CTutorial::GetLesson() == CTutorial::TYPE_LESSON04))
			{
				CTutorial::SetEndlesson(true);
			}

			if (pFrame != NULL)
			{
				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_NEAR
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI && m_bAvoi == true)
				{
					//���[�V�������Z�b�g(�ړ�)
					m_motion->Set(MOTIONTYPE_KNIFESTAN);

					m_State = STATE_KNIFESTAN;
				}

				if (m_State != STATE_SNPSTAN && pFrame->GetACType() == CFrame::TYPE_FAR
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI && m_bAvoi == true)
				{
					m_motion->Set(MOTIONTYPE_SNPSTAN);

					m_State = STATE_SNPSTAN;
				}

				if (m_State != STATE_KNIFESTAN && pFrame->GetACType() == CFrame::TYPE_BAT
					&& m_bDash == false && m_bAction == false && m_State != STATE_AVOI  && m_bAvoi == true)
				{
					//���[�V�������Z�b�g(�ړ�)
					m_motion->Set(MOTIONTYPE_BATNEUTAL);

					m_State = STATE_KNIFESTAN;
				}
			}

			if (pFrame != NULL)
			{
				if (pFrame->GetACType() == CFrame::TYPE_NEAR)
				{
					m_AcType = ACTIONTYPE_NEAR;
				}

				if (pFrame->GetACType() == CFrame::TYPE_FAR)
				{
					m_AcType = ACTIONTYPE_FAR;

					m_bWhee = true;
				}

				if (pFrame->GetACType() == CFrame::TYPE_BAT)
				{
					m_AcType = ACTIONTYPE_BAT;
				}
			}
			else
			{
				m_AcType = ACTIONTYPE_NEAR;
			}

			if (m_bWhee == true && CTutorial::GetLesson() == CTutorial::TYPE_LESSON03)
			{
				CTutorial::SetEndlesson(true);

				m_bAttack = false;
			}
		}

		Playerpos.x += m_move.x;
		Playerpos.y += m_move.y;
		//m_pos.y = fHeight + 18.0f;
		Playerpos.z += m_move.z;

		//�ړ��ʂ��X�V(����������)--------------------------------------------
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		//�ړ�---------------------------------------------------------------------------------------------
		if (m_bDash == true && m_State != STATE_MOVE && m_State != STATE_AVOI)
		{
			//���[�V�������Z�b�g(�ړ�)
			m_motion->Set(MOTIONTYPE_MOVE);

			m_State = STATE_MOVE;

			m_nCntColi = 0;

			m_bAction = false;
		}

		//�U���j���[�g����---------------------------------------------------------------------------------------------
		if (m_State != STATE_KNIFESTAN && m_bDash == false
			&& m_bAction == false && m_State != STATE_AVOI)
		{
			//���[�V�������Z�b�g(�ړ�)
			m_motion->Set(MOTIONTYPE_KNIFESTAN);

			m_State = STATE_KNIFESTAN;
		}

		//���---------------------------------------------------------------------------------------------
		if (m_State == STATE_AVOI)
		{
			m_move.x += sinf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;
			m_move.z += cosf(PlayerRot.y + D3DX_PI) * PLAYERMOVE;

			Playerpos.x += m_move.x * 0.05f;
			Playerpos.z += m_move.z * 0.05f;
		}

		if (m_bDash == true && m_nCntSound == 0)
		{
			m_nCntSound = 35;

			pSound->Play(CSound::SOUND_LABEL_SE09);
		}

		if (m_nCntSound > 0)
		{
			m_nCntSound--;
		}

		if (m_motion->IsFinish() == true)
		{
			m_nCntEff = 0;
			m_nCntColi = 0;
			m_bAction = false;
			m_State = STATE_NONE;
		}

		SetPos(&Playerpos);
		SetRot(&PlayerRot);
	}

	m_pShadow->SetPosition(m_nIdxShaadow, { Playerpos.x, 2.0f, Playerpos.z });
}

//================================================================
//�U������������̏���
//================================================================
void CPlayer::Hit(void)
{
	if (m_State != STATE_DAMEGE && m_State != STATE_STAGGER && m_State != STATE_AVOI)
	{
		int nLife = GetLife();

		nLife--;

		SetLife(nLife);

		m_State = STATE_DAMEGE;
	}
}

//================================================================
//�O���t�@�C���ǂݍ���
//================================================================
void CPlayer::ReadText(void)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

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