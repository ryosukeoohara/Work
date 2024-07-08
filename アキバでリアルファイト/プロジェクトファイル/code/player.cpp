//===========================================================
//
// �v���C���[����[player.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyBoard.h"
#include "InputJoyPad.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"
#include "camera.h"
#include "object.h"
#include "gage.h"
#include "billboard.h"
#include "enemymanager.h"
#include "utility.h"
#include "item.h"
#include "itemmanager.h"
#include "particle.h"
#include "effect2D.h"
#include "animation.h"
#include "heataction.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//===========================================================
// �ÓI�����o�ϐ�
//===========================================================
CPlayer *CPlayer::m_pPlayer = nullptr;

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int DAMAGE_COUNT = 15;                               // �_���[�W��Ԃł��鎞��
	const int MICROWAVE = 3600;                                // �d�q�����W���g�p�����q�[�g�A�N�V�������Ăюg�p�\�ɂȂ�܂ł̎���
	const float GRAP_MOVE_SPEED = 0.7f;                        // �͂ݏ�Ԃ̈ړ��̑���
	const float MOVE_SPEED = 1.0f;                             // �ʏ��Ԃ̈ړ��̑���
	const float MAX_STAMINA = 40.0f;                           // �X�^�~�i�̍ő�l
	const float BOOST_STAMINA = 0.1f;                          // �X�^�~�i�̉񕜒l
	const float LOST_STMINA = 10.0f;                           // ����̃X�^�~�i�����
	const float GRAP_LOST_STMINA = 0.1f;                       // �G��͂�ł��鎞�̃X�^�~�i�����
	const char* PLAYER_TEXT = "data\\TEXT\\motion_player.txt"; // �v���C���[�̃e�L�X�g�t�@�C��

	const D3DXVECTOR3 CAMERA_ROT[CPlayer::HEAT_MAX] = 
	{ 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI * -0.38f),

	};  // �q�[�g�A�N�V�������̃J�����ʒu

	const float CAMERA_DISTNCE[CPlayer::HEAT_MAX] =
	{
		300.0f,
		300.0f,
		200.0f,

	};  // �q�[�g�A�N�V�������̃J�����̋���

	const D3DXVECTOR3 ENEMY_GRAP_POS[CEnemy::MAX] =
	{
		D3DXVECTOR3(-10.0f, -10.0f, 60.0f),  // �G���G
		D3DXVECTOR3(-15.0f, -10.0f, 80.0f),  // �{�X�G
	};

	const D3DXVECTOR3 MAP_LIMIT_MAX = D3DXVECTOR3(800.0f, 0.0f, 1000.0f);   // �}�b�v�̐���
	const D3DXVECTOR3 MAP_LIMIT_MIN = D3DXVECTOR3(-850.0f, 0.0f, -670.0f);  // �}�b�v�̐���
	const float TUTORIAL_MAP_LIMITZ = 30.0f;                                // �`���[�g���A���}�b�v��Z���̐���

	const D3DXVECTOR3 STICK_ENEMY = D3DXVECTOR3(100.0f, 0.0f, 100.0f);      // 
	const D3DXVECTOR2 HEATACT_BUTTON_SIZE = D3DXVECTOR2(25.0f, 25.0f);      // �q�[�g�A�N�V�����\���ɏo��e�N�X�`���̃T�C�Y
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CPlayer::CPlayer()
{
	// ������
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_Grap.pItem = nullptr;
	m_Grap.pEnemy = nullptr;

	m_HeatAct = HEAT_NONE;
	m_Mobility = Immobile;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_nUseCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItemMicro = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pItem = nullptr;
	m_pBotton = nullptr;
	m_pGekiatu = nullptr;
	m_pHeatAct = nullptr;
	m_nIdxEne = -1;
	m_nIdxItem = -1;
	m_nDefeat = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nCntSound = 0;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	m_bInvi = false;
	m_bHeatActFlag = false;
	
	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;

	m_pPlayer = this;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, int nPriority) : CObject(nPriority)
{
	// ������
	m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_HeatAct = HEAT_NONE;
	m_Mobility = Immobile;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_nUseCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItemMicro = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pItem = nullptr;
	m_pBotton = nullptr;
	m_pGekiatu = nullptr;
	m_pHeatAct = nullptr;
	m_nIdxEne = -1;
	m_nIdxItem = -1;
	m_nDefeat = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nCntSound = 0;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	m_bInvi = false;
	m_bHeatActFlag = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;

	m_pPlayer = this;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CPlayer::~CPlayer()
{

}

//===========================================================
// ��������
//===========================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nPriority)
{
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		// ����
		pPlayer = new CPlayer(pos, nPriority);

		// ����������
		pPlayer->Init();
	}
	
	return pPlayer;
}

//===========================================================
// ��������
//===========================================================
CPlayer * CPlayer::Create(void)
{
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		// ����
		pPlayer = new CPlayer();

		// ����������
		pPlayer->Init();
	}
	
	return pPlayer;
}

//===========================================================
// �_���[�W
//===========================================================
void CPlayer::Damage(int nDamage, float fKnockBack)
{
	if (m_Info.state != STATE_DAMEGE && m_bInvi == false)
	{
		m_Info.state = STATE_DAMEGE;
		m_pMotion->Set(TYPE_DAMAGE);
		CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
		CAnimation::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 60.0f, m_Info.pos.z), 30.0f, CBillBoard::TYPE_HIT);
		m_Info.nLife -= nDamage;
		m_Info.move = D3DXVECTOR3(sinf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack, fKnockBack, cosf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack);
	}
}

//===========================================================
// �^�C�g���ŕ���
//===========================================================
void CPlayer::TitleWalk(void)
{
	// �p�[�c���Ƃ̍X�V
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// ���[�V�����̍X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	if (m_Info.state != STATE_OTA)
	{
		m_Info.state = STATE_OTA;
		m_pMotion->Set(TYPE_OTA);
	}

	//�ʒu�Ɉړ��ʉ��Z----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//m_pos.y = fHeight + 18.0f;

	//�ړ��ʂ��X�V(����������)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	CManager::Getinstance()->GetDebugProc()->Print("\n�v���C���[�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("�v���C���[�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
}

//===========================================================
// ����������
//===========================================================
HRESULT CPlayer::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//�V�[���̏����擾
	CScene *pScene = CManager::Getinstance()->GetScene();

	//��ސݒ�
	SetType(TYPE_PLAYER);

	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;

		//����������
		m_pMotion->Init();

		m_pMotion->Set(TYPE_NEUTRAL);
	}

	m_fGrapRot = 1.0f;
	m_fStamina = 40.0f;
	m_Info.nLife = 200;
	m_Info.fRadius = 20.0f;
	m_nCntSound = 35;
	m_nDamegeCounter = DAMAGE_COUNT;

	ReadText(PLAYER_TEXT);

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME || CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		m_pLife = CGage2D::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 42.0f, (float)((m_Info.nLife * 0.01f) * 20.0f), CGage2D::TYPE_LIFE);
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.01f) * 20));
		m_pStamina = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, m_fStamina, CGage3D::TYPE_STAMINA);
		m_pStamina->SetPos(&m_Info.pos);
		m_pStamina->GetBill()->SetTex(m_fStamina);
	}
	
	return S_OK;
}

//================================================================
// �I������
//================================================================
void CPlayer::Uninit(void)
{
	//�T�E���h�̏����擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�T�E���h�X�g�b�v
	pSound->Stop();

	if (m_pMotion != nullptr)
	{
		//�I������
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppCharacter != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_ppCharacter[nCount] != nullptr)
			{
				m_ppCharacter[nCount]->Uninit();
				m_ppCharacter[nCount] = nullptr;
			}
		}

		delete m_ppCharacter;
		m_ppCharacter = nullptr;
	}

	if (m_pStamina != nullptr)
	{
		m_pStamina->Uninit();
		m_pStamina = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	CObject::Release();
}

//================================================================
// �X�V����
//================================================================
void CPlayer::Update(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	//�V�[���̏����擾
	CScene *pScene = CManager::Getinstance()->GetScene();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMAGE_COUNT;
		}
	}
	else
	{
		if (m_Mobility == Mobile)
		{
			// ���䏈��
			Control();
		}
	}
	
	// �p�[�c���Ƃ̍X�V
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// ���[�V�����̍X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	// �X�^�~�i
	if (m_fStamina < MAX_STAMINA && m_bGrap == false)
	{
		m_fStamina += BOOST_STAMINA;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	if (m_nUseCounter > 0)
	{
		m_nUseCounter--;

		if (m_nUseCounter % 20 == 0)
		{
			if (m_pItemMicro != nullptr)
			{
				CParticle::Create(m_pItemMicro->GetPosition(), CParticle::TYPE_SMOOK);
			}
		}
	}

	// �̗�
	if (m_pLife != nullptr)
	{
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.1f) * 20.0f));
	}

	if (m_Info.nLife <= 0)
	{
		Uninit();

		//�t�F�[�h�̏����擾
		CFade *pFade = CManager::Getinstance()->GetFade();

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_RESULT);
		}
	}

	if (m_pHeatAct != nullptr)
	{
		m_pHeatAct->Updata();

		if (m_bHeatActFlag == false)
			m_pHeatAct = nullptr;
	}

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// �}�b�v�̐���
		if (m_Info.pos.x >= MAP_LIMIT_MAX.x)
		{
			m_Info.pos.x = MAP_LIMIT_MAX.x;
		}
		if (m_Info.pos.x <= MAP_LIMIT_MIN.x)
		{
			m_Info.pos.x = MAP_LIMIT_MIN.x;
		}
		if (m_Info.pos.z >= MAP_LIMIT_MAX.z)
		{
			m_Info.pos.z = MAP_LIMIT_MAX.z;
		}
		if (m_Info.pos.z <= TUTORIAL_MAP_LIMITZ)
		{
			m_Info.pos.z = TUTORIAL_MAP_LIMITZ;
		}
	}

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		// �}�b�v�̐���
		if (m_Info.pos.x >= MAP_LIMIT_MAX.x)
		{
			m_Info.pos.x = MAP_LIMIT_MAX.x;
		}
		if (m_Info.pos.x <= MAP_LIMIT_MIN.x)
		{
			m_Info.pos.x = MAP_LIMIT_MIN.x;
		}
		if (m_Info.pos.z >= MAP_LIMIT_MAX.z)
		{
			m_Info.pos.z = MAP_LIMIT_MAX.z;
		}
		if (m_Info.pos.z <= MAP_LIMIT_MIN.z)
		{
			m_Info.pos.z = MAP_LIMIT_MIN.z;
		}
	}
}

//================================================================
// �`�揈��
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Draw();
		}
	}
}

//================================================================
// ���䏈��
//================================================================
void CPlayer::Control(void)
{
	if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME || CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_TUTORIAL)
	{
		Move();     // �ړ�
	}

	// �G�Ƃ̓����蔻��
	CEnemy *pEnemy = CEnemy::GetTop();
	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();
		if (m_nIdxEne != pEnemy->GetIdxID())
		{
			m_Info.pos = *CGame::GetCollision()->CheckEnemy(&m_Info.pos, &m_Info.posOld, &pEnemy->GetPosition(), m_Info.fRadius);
		}
		pEnemy = pEnemyNext;
	}

	// �A�C�e���Ƃ̓����蔻��
	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		CItem* pItem = CItem::GetTop();

		while (pItem != nullptr)
		{
			CItem* pItemNext = pItem->GetNext();

			pItem->Collision(&m_Info.pos, &m_Info.posOld, 20.0f);

			pItem = pItemNext;
		}
	}
	
	//�}�E�X���擾
	CInputMouse* pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad* pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	if (pInputMouse == nullptr)
		return;

	if (pInputJoyPad == nullptr)
		return;

	// �ʏ�U��
	if (pInputMouse->GetLButton() == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_B, 0) == true)
	{
		if (m_Info.state != STATE_GRAP && m_Info.state != STATE_HEAT && m_bGrap == false)
		{
			// �U��
			Attack();
		}
	}

	// ����
	Grap();

	// ���
	Avoid();

	// �q�[�g�A�N�V����
	Heat();

	// ���
	State();   

	CManager::Getinstance()->GetDebugProc()->Print("\n�v���C���[�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("�v���C���[�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	CManager::Getinstance()->GetDebugProc()->Print("�͂�ł���G�̔ԍ�:%d", m_nIdxEne);
	CManager::Getinstance()->GetDebugProc()->Print("�|�������F%d\n", m_nDefeat);
}

//================================================================
// �ړ�����
//================================================================
void CPlayer::Move(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�J�����擾
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_bDesh = false;

	m_Info.posOld = m_Info.pos;
	
	float fSpeed = 0.0f;

	if (m_bGrap == true)
	{
		fSpeed = GRAP_MOVE_SPEED;
	}
	else
	{
		fSpeed = MOVE_SPEED;
	}

	if (m_Info.state != STATE_GRAP && m_Info.state != STATE_AVOID && m_Info.state != STATE_ATTACK && m_Info.state != STATE_HEAT && m_Info.state != STATE_DAMEGE)
	{
		//��Ɉړ�----------------------------------------------
		if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
		{//W�L�[�������ꂽ

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//D�L�[�������� �E��Ɉړ�

				// �ړ���
				m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				//����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//A�L�[�������� ����Ɉړ�

				// �ړ���
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;

				//����
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
			}
			else
			{//W�L�[����������	�^��Ɉړ�

				// �ړ���
				m_Info.move.x -= sinf(CameraRot.y) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y) * fSpeed;

				//����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
			}

			m_bDesh = true;

			// �`���[�g���A������
			m_bPushW = true;
		}
		//���Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_S) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
		{//S�L�[�������ꂽ

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//D�L�[�������� �E���Ɉړ�

				// �ړ���
				m_Info.move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;

				// ����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//A�L�[�������� �����Ɉړ�

				// �ړ���
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				// ����
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
			}
			else
			{//S�L�[���������� �^���Ɉړ�

				// �ړ���
				m_Info.move.x += sinf(CameraRot.y) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y) * fSpeed;

				// ����
				m_fDest = (CameraRot.y + (D3DX_PI));
			}

			m_bDesh = true;

			// �`���[�g���A������
			m_bPushS = true;
		}
		//�E�Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[����������

			// �ړ���
			m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// �`���[�g���A������
			m_bPushD = true;

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
		}
		//���Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[����������

			// �ړ���
			m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// �`���[�g���A������
			m_bPushA = true;

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
		}

		m_fDiff = m_fDest - m_Info.rot.y;

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
		m_Info.rot.y += m_fDiff * 0.15f;

		//�p�x�̒l���C������--------------------------------------------------
		if (m_Info.rot.y > D3DX_PI)
		{
			m_Info.rot.y = -D3DX_PI;
		}
		else if (m_Info.rot.y < -D3DX_PI)
		{
			m_Info.rot.y = D3DX_PI;
		}
	}
	else if(m_Info.state == STATE_GRAP)
	{
		GrapRotition();
	}
	
	//�ʒu�Ɉړ��ʉ��Z----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//�ړ��ʂ��X�V(����������)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	if(CCollision::GetColl() != nullptr)
	CCollision::GetColl()->Map(&m_Info.pos, &m_Info.posOld, 40.0f);
}

//================================================================
// �A�N�V����
//================================================================
void CPlayer::Attack(void)
{
	// �U����i��
	if (m_Info.state != STATE_ATTACK)
	{
		m_Info.state = STATE_ATTACK;
		m_Info.Atc = TYPE_ATTACK1;
		m_pMotion->Set(TYPE_ATTACK01);
	}

	// �U����i��
	if (m_Info.Atc == TYPE_ATTACK1 
	&& (m_pMotion->GetCancellFrame() <= m_pMotion->GetNumFrame() 
	&&  m_pMotion->GetCancellFrameEnd() >= m_pMotion->GetNumFrame()))
	{// �U������i�ڂ����݂̃t���[�����L�����Z���\�t���[��

		m_Info.Atc = TYPE_ATTACK2;
		m_pMotion->Set(TYPE_ATTACK02);
	}

	// �U���O�i��
	if (m_Info.Atc == TYPE_ATTACK2 
	&& (m_pMotion->GetCancellFrame() <= m_pMotion->GetNumFrame()
	&&  m_pMotion->GetCancellFrameEnd() >= m_pMotion->GetNumFrame()))
	{// �U������i�ڂ����݂̃t���[�����L�����Z���\�t���[��

		m_Info.Atc = TYPE_ATTACK3;
		m_pMotion->Set(TYPE_ATTACK03);
	}

	float fLenght = EnemyDistance();

	if (fLenght <= 100.0f)
	{
		float fDiffmove = 0.0f;

		// �ǔ�
		fDiffmove = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, m_pEnemy->GetPosition(), m_Info.rot.y);

		// �p�x�␳
		m_fDest = fDiffmove;
		m_Info.rot.y += fDiffmove;

		// �p�x�␳
		m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

		//�ړ��ʂ��X�V(����������)
		m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * MOVE_SPEED;
		m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * MOVE_SPEED;
	}
}

//================================================================
// �����鎞�̊p�x����
//================================================================
void CPlayer::GrapRotition(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�J�����擾
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_fDestOld = m_fDest;

	//��Ɉړ�----------------------------------------------
	if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
	{//W�L�[�������ꂽ

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[�������� �E��Ɉړ�

			//����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[�������� ����Ɉړ�

			//����
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
		}
		else
		{//W�L�[����������	�^��Ɉړ�

			//����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
		}

	}
	//���Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
	{//S�L�[�������ꂽ

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[�������� �E���Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[�������� �����Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
		}
		else
		{//S�L�[���������� �^���Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * m_fGrapRot));
		}

	}
	//�E�Ɉړ�----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//D�L�[����������

		// ����
		m_fDest += (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//���Ɉړ�----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//A�L�[����������

		// ����
		m_fDest -= (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//�E�Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
	{//D�L�[����������

		// ����
		m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
	}
	//���Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
	{//A�L�[����������

		// ����
		m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
	}

	if (m_fDest > 0.0f && m_fDestOld < 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}
	else if (m_fDest < 0.0f && m_fDestOld > 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}

	m_fDiff = m_fDest - m_Info.rot.y;

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
	m_Info.rot.y += m_fDiff * (0.15f * m_fGrapRot);

	//�p�x�̒l���C������--------------------------------------------------
	if (m_Info.rot.y > D3DX_PI)
	{
		m_Info.rot.y = -D3DX_PI;
	}
	else if (m_Info.rot.y < -D3DX_PI)
	{
		m_Info.rot.y = D3DX_PI;
	}
}

//================================================================
// �����鏈��
//================================================================
void CPlayer::Grap(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	// �G��͂�
	if (InputKeyboard->GetTrigger(DIK_E) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
	{
		if (m_Info.state != STATE_THROW && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_AVOID && m_Info.state != STATE_HEAT)
		{
			if (m_Grap.pEnemy == nullptr && m_Grap.pItem == nullptr)
			{
				m_Info.state = STATE_GRAP;
				m_pMotion->Set(TYPE_GRAP);
			}
			else
			{
				if (m_Grap.pEnemy != nullptr)
				{
					m_Grap.pEnemy->SetCurrent(nullptr);
					m_Grap.pEnemy->SetPosition(m_Info.pos);
					m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_Grap.pEnemy->SetState(CEnemy::STATE_NEUTRAL);
					m_Grap.pEnemy->SetChase(CEnemy::CHASE_ON);
					m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_NEUTRAL);
					m_Grap.pEnemy = nullptr;
					m_nIdxEne = -1;
					m_Info.state = STATE_NEUTRAL;
					m_pMotion->Set(TYPE_NEUTRAL);
					m_bGrap = false;
				}

				if (m_Grap.pItem != nullptr)
				{
					m_Grap.pItem->SetCurrent(nullptr);
					m_Grap.pItem->SetPosition(m_Info.pos);
					m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_Grap.pItem = nullptr;
					m_Info.state = STATE_NEUTRAL;
					m_pMotion->Set(TYPE_NEUTRAL);
					m_bLift = false;
				}
			}
		}
	}

	if (m_fStamina > 0.0f && m_bGrap == true && m_Info.state != STATE_HEAT)
	{// �G��͂�ł�����X�^�~�i�����炷

		m_fStamina -= GRAP_LOST_STMINA;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	if (m_fStamina < 0.0f && m_bGrap == true)
	{// �X�^�~�i���Ȃ��Ȃ������G��͂�ł�����

		// �G�𗣂�
		if (m_Grap.pEnemy != nullptr)
		{
			m_Grap.pEnemy->SetCurrent(nullptr);
			m_Grap.pEnemy->SetPosition(m_Info.pos);
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_Grap.pEnemy->SetState(CEnemy::STATE_NEUTRAL);
			m_Grap.pEnemy->SetChase(CEnemy::CHASE_ON);
			m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_NEUTRAL);
			m_Grap.pEnemy = nullptr;
			m_nIdxEne = -1;
			m_Info.state = STATE_NEUTRAL;
			m_pMotion->Set(TYPE_NEUTRAL);
			m_bGrap = false;
		}
	}

	// �G�܂��̓A�C�e����͂�
	{
		if (m_Info.state == STATE_GRAP && m_bGrap == false && m_bLift == false)
		{
			float f = EnemyDistance();
			float g = ItemDistance();
			if (f >= g)
			{// �͈͓�

				if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
				{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

					if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pItem->GetPosition(), 40.0f, 40.0f) == true)
					{// �͈͓�

						m_Grap.pItem = m_pItem;

						// �e�A�ʒu�A�����A��ԁA�ǔ��A���[�V������ݒ肵�A�͂�ł��邱�Ƃɂ���
						m_Grap.pItem->SetCurrent(m_ppCharacter[9]->GetMtxWorld());
						m_Grap.pItem->SetPosition(D3DXVECTOR3(50.0f, 5.0f, -15.0f));
						m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
						m_Grap.pEnemy = nullptr;
						m_nIdxEne = -1;
						m_bLift = true;
					}
				}
			}
			else
			{
				if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
				{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

					if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pEnemy->GetPosition(), 40.0f, 40.0f) == true
						/*&& m_pEnemy->GetState() == CEnemy::STATE_PAINFULDAMAGE || m_pEnemy->GetState() == CEnemy::STATE_GETUP*/)
					{// �͈͓����G���R�P�Ă���

						m_Grap.pEnemy = m_pEnemy; 

						// �e�A�ʒu�A�����A��ԁA�ǔ��A���[�V������ݒ肵�A�͂�ł��邱�Ƃɂ���
						m_Grap.pEnemy->SetCurrent(m_ppCharacter[9]->GetMtxWorld());
						m_Grap.pEnemy->SetPosition(ENEMY_GRAP_POS[m_Grap.pEnemy->GetType()]);
						m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
						m_Grap.pEnemy->SetState(CEnemy::STATE_GRAP);
						m_Grap.pEnemy->SetChase(CEnemy::CHASE_OFF);
						m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_GRAP);
						m_nIdxEne = m_Grap.pEnemy->GetIdxID();
						m_Grap.pItem = nullptr;
						m_bGrap = true;
					}
				}
			}
		}
	}
	
}

//================================================================
// �������
//================================================================
void CPlayer::Avoid(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	if ((InputKeyboard->GetTrigger(DIK_LSHIFT) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true))
	{
		if (m_Info.state != STATE_AVOID && m_Info.state != STATE_LIFT &&
			m_Info.state != STATE_THROW && m_Info.state != STATE_GRAP && 
			m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_GRAPWALK && 
			m_Info.state != STATE_HEAT)
		{
			if (m_fStamina >= LOST_STMINA)
			{// ����ʂ�葽��������

				// �X�^�~�i���炵�ĉ����Ԃ�
				m_bAvoid = true;
				m_fStamina -= LOST_STMINA;
				m_Info.state = STATE_AVOID;
				m_pMotion->Set(TYPE_AVOID);

				if (m_pStamina != nullptr)
				{
					m_pStamina->GetBill()->SetTex(m_fStamina);
				}
			}
		}
	}
}

//================================================================
// ��ԏ���
//================================================================
void CPlayer::State(void)
{
	// �G��͂�
	if (m_bLift == true && m_bDesh == true && m_Info.state != STATE_HEAT)
	{
		if (m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_THROW)
		{
			m_Info.state = STATE_GRAPDASH;
			m_pMotion->Set(TYPE_GRAPDASH);
		}
	}

	if (m_bGrap == true && m_bDesh == true && m_Info.state != STATE_HEAT)
	{
		if (m_Info.state != STATE_GRAPWALK)
		{
			m_Info.state = STATE_GRAPWALK;
			m_pMotion->Set(TYPE_GRAPWALK);
		}
	}

	// �ʏ�U���E���Ԃ�or�A�C�e��
	if (m_Info.state == STATE_ATTACK && m_Info.state != STATE_HEAT)
	{
		// �A�C�e��
		if (m_Grap.pItem != nullptr)
		{
			D3DXMATRIX *mtx = m_Grap.pItem->GetMtxWorld();

			D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Objpos.x = mtx->_41;
			Objpos.y = mtx->_42;
			Objpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

				CGame::GetCollision()->AttackCircle(&Objpos, 50.0f, 50.0f, 100.0f);
			}
		}
		else // ���Ԃ�
		{
			D3DXMATRIX *mtx = m_ppCharacter[9]->GetMtxWorld();

			D3DXVECTOR3 Handpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Handpos.x = mtx->_41;
			Handpos.y = mtx->_42;
			Handpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

				CGame::GetCollision()->AttackCircle(&Handpos, 25.0f, 50.0f, 100.0f);
			}
		}
	}

	// �A�C�e����������
	if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW &&m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_HEAT && m_bLift == true)
	{
		m_Info.state = STATE_LIFT;
		m_pMotion->Set(TYPE_LIFT);
	}

	// ���
	if (m_Info.state == STATE_AVOID)
	{
		m_bDesh = false;
		m_Info.move.x += sinf(m_Info.rot.y + D3DX_PI) * 0.5f;
		m_Info.move.z += cosf(m_Info.rot.y + D3DX_PI) * 0.5f;

		if (m_pMotion->GetInvincibleStrat() <= m_pMotion->GetNowFrame() && m_pMotion->GetInvincibleEnd() >= m_pMotion->GetNowFrame())
		{// ���ԓ��������犮�S���G�ɂ���

			m_bInvi = true;
		}
		else
		{// ���S���G�I��

			m_bInvi = false;
		}
	}

	// �����Ă���A�C�e���ōU������
	if (m_Info.state == STATE_THROW && m_Grap.pItem != nullptr)
	{
		m_Grap.pItem->SetPosition(D3DXVECTOR3(50.0f, -30.0f, -15.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI, -D3DX_PI * 0.5f));
		CGame::GetCollision()->ItemAttack(m_Grap.pItem);
	}

	// �����Ă���A�C�e���Ƃ̐e�q�֌W��؂�
	if (m_pMotion->GetNumFrame() >= m_pMotion->GetAttackEnd() && m_Grap.pItem != nullptr && (m_Info.state == STATE_THROW || m_Info.state == STATE_HEAT))
	{
		m_Grap.pItem->SetCurrent(nullptr);
		m_Grap.pItem->SetPosition(D3DXVECTOR3(m_Info.pos.x + sinf(m_Info.rot.y) * -60.0f, m_Info.pos.y, m_Info.pos.z + cosf(m_Info.rot.y) * -60.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
		m_Grap.pItem = nullptr;
	}
	
	// ���[�V�������ړ����[�V�����ɂ���
	if (m_Info.state != STATE_MOVE && m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH 
		&& m_Info.state != STATE_GRAPWALK && m_Info.state != STATE_THROW && m_Info.state != STATE_HEAT
		&& m_bDesh == true && m_bAttack == false && m_bAvoi == false)
	{
		m_Info.state = STATE_MOVE;

		//���[�V�������Z�b�g(�ړ�)
		m_pMotion->Set(TYPE_MOVE);
	}

	// ���[�V�������I�����q�[�g�A�N�V������
	if (m_pMotion->IsFinish() == true && m_Info.state == STATE_HEAT)
	{
		// �J���������Ƃ̈ʒu�ɖ߂�
		CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
	}

	// ���[�V�������I�����G�𓊂��郂�[�V����
	if (m_pMotion->IsFinish() == false && m_pMotion->GetType() == STATE_ENEMYGRAP)
	{
		if (m_Grap.pEnemy != nullptr)
		{
			m_Grap.pEnemy->SetCurrent(m_ppCharacter[6]->GetMtxWorld());
			m_Grap.pEnemy->SetPosition(D3DXVECTOR3(-15.0f, 0.0f, 80.0f));
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
		}
	}

	// �ҋ@���[�V�����ɂ���
	if (m_pMotion->IsFinish() == true || (m_bDesh == false && m_bLift == true && m_Info.state == STATE_GRAPDASH)
		|| (m_bDesh == false && m_bGrap == true && m_Info.state == STATE_GRAPWALK)
		|| (m_bDesh == false && m_bGrap == false && m_bLift == false 
		 && m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_AVOID
		 && m_Info.state != STATE_LIFT && m_Info.state != STATE_HEAT && m_Info.state != STATE_THROW
		 && m_Info.state != STATE_AVOID && m_Info.state != STATE_GRAP))
	{
		//���[�V�������Z�b�g(�ҋ@)
		m_pMotion->Set(TYPE_NEUTRAL);
		m_Info.state = STATE_NEUTRAL;
		m_bLift = false;
		m_bAttack = false;
		m_nCntColi = 0;

		if (CGame::GetCollision() != nullptr)
		{
			CGame::GetCollision()->SetbColli(false);
		}
		
		if (m_Grap.pItem != nullptr)
		{
			m_Info.state = STATE_LIFT;
			m_pMotion->Set(TYPE_LIFT);
			m_bLift = true;
		}

		if (m_Grap.pEnemy != nullptr)
		{
			m_Info.state = STATE_GRAPNEUTRAL;
			m_pMotion->Set(TYPE_GRAPNEUTRAL);
			m_bGrap = true;
		}
	}
}

//================================================================
// �_���[�W
//================================================================
void CPlayer::Damege(void)
{
	if (m_Info.state == STATE_HEAT)
	{
		if (m_Info.state != STATE_DAMEGE)
		{
			m_Info.state = STATE_DAMEGE;
			m_nDamegeCounter = 10;
		}

		m_Info.nLife--;

		m_nDamegeCounter--;
	}
}

//================================================================
// �q�[�g�A�N�V����
//================================================================
void CPlayer::Heat(void)
{
	// �A�C�e���������Ă���Ƃ��܂��̓A�C�e���������đ����Ă���Ƃ�
	if (m_Info.state == STATE_LIFT || m_Info.state == STATE_GRAPDASH)
	{
		// �����𑪂��Ĉ�ԋ߂��̓G���o����
		EnemyDistance();
			
		if (m_pEnemy != nullptr)
		{
			if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pEnemy->GetPosition(), 50.0f, 50.0f) == true)
			{// �͈͓��ɓ�������Y�{�^�����o�Ă���

				m_HeatAct = HEAT_SMASH;

				// X�{�^�����o�Ă���
				{
					if (m_pBotton == nullptr)
					{
						m_pBotton = CObject2D::Create();
						m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
						m_pBotton->SetSize(HEATACT_BUTTON_SIZE.x, HEATACT_BUTTON_SIZE.y);
						m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Xbutton.png"));
						m_pBotton->SetDraw(true);
					}

					if (m_pBotton != nullptr)
					{
						//CEffect2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.7f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30.0f, 30, CEffect2D::TYPE_SMOOK);
					}
				}

				if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true)
				{// �q�[�g�A�N�V��������

					m_pHeatAct = new CHeatAction;
					if (m_pHeatAct != nullptr)
					{
						m_pHeatAct->SetAction(m_HeatAct, this, m_pEnemy);
					}

					if(CGame::GetEnemyManager() != nullptr)
					CGame::GetEnemyManager()->SetTarget(m_pEnemy->GetIdxID());

					m_Info.state = STATE_HEAT;

					// �q�[�g�A�N�V�������Ă���
					m_bHeatActFlag = true;

					if (m_pBotton != nullptr)
					{
						m_pBotton->Uninit();
						m_pBotton = nullptr;
					}
				}
			}
			else
			{
				if (m_pBotton != nullptr)
				{
					m_pBotton->Uninit();
					m_pBotton = nullptr;
				}
			}
		}
	}

	// �d�q�����W
	if (m_bGrap == true && m_nUseCounter == 0)
	{// �G��͂�ł���

		CItem *pItem = CItem::GetTop();

		while (pItem != nullptr)
		{
			CItem *pItemNext = pItem->GetNext();

			if (pItem->GetType() == CItem::TYPE_MICROWAVE)
			{
				m_pItemMicro = pItem;
			}

			pItem = pItemNext;
		}

		if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pItemMicro->GetPosition(), 30.0f, 40.0f))
		{// �͈͓�

			m_HeatAct = HEAT_FIRE;

			// X�{�^�����o�Ă���
			{
				if (m_pBotton == nullptr)
				{
					m_pBotton = CObject2D::Create();
					m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
					m_pBotton->SetSize(HEATACT_BUTTON_SIZE.x, HEATACT_BUTTON_SIZE.y);
					m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Xbutton.png"));
					m_pBotton->SetDraw(true);
				}
			}

			if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true)
			{// �q�[�g�A�N�V��������

				m_pHeatAct = new CHeatAction;
				if (m_pHeatAct != nullptr)
				{
					m_pHeatAct->SetAction(m_HeatAct, this, m_pEnemy);
				}

				if (CGame::GetEnemyManager() != nullptr)
					CGame::GetEnemyManager()->SetTarget(m_pEnemy->GetIdxID());

				m_pMotion->Set(TYPE_ENEMYGRAP);

				m_Info.state = STATE_HEAT;

				// �q�[�g�A�N�V�������Ă���
				m_bHeatActFlag = true;

				// �G�𗣂�
				m_bGrap = false;

				if (m_pBotton != nullptr)
				{
					m_pBotton->Uninit();
					m_pBotton = nullptr;
				}
			}
		}
		else
		{
			if (m_pBotton != nullptr)
			{
				m_pBotton->Uninit();
				m_pBotton = nullptr;
			}
		}
	}
}

//================================================================
// �O���t�@�C���ǂݍ���
//================================================================
void CPlayer::ReadText(const char *fliename)
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
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(fliename, "r");

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

					m_ppCharacter = new CCharacter*[m_nNumModel];

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //���f���̖��O

					m_ppCharacter[nCntModel] = CCharacter::Create(m_filename);
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
										m_ppCharacter[nCntParts2]->SetParent(m_ppCharacter[m_nParent]);
									}
									else
									{
										m_ppCharacter[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.z);  //���f���̑���

									m_ppCharacter[nCntParts2]->SetPositionOri(m_Readpos);

									m_ppCharacter[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.z);  //���f���̑���

									m_ppCharacter[nCntParts2]->SetRotOrigin(m_Readrot);

									m_ppCharacter[nCntParts2]->SetRot(m_Readrot);
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

	if (m_pMotion != nullptr)
	{
		// ���f���̐ݒ�
		m_pMotion->SetModel(m_ppCharacter, m_nNumModel);

		// ����������
		m_pMotion->ReadText(fliename);

		// �Z�b�g(�ҋ@)
		m_pMotion->Set(TYPE_NEUTRAL);
	}
}

//================================================================
// �G�Ƃ̋����Z�o
//================================================================
float CPlayer::EnemyDistance(void)
{
	float fLenght = 10000.0f;
	float fLenghtDiff = 0.0f;  // ��r�p

	CEnemy *pEnemy = CEnemy::GetTop();

	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();

		// �����ƓG�̋������擾
		if (CManager::Getinstance()->GetUtility() != nullptr)
			fLenghtDiff = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, pEnemy->GetPosition());

		// �������r
		if (fLenght >= fLenghtDiff)
		{
			fLenght = fLenghtDiff;
			
			// ��ԋ߂��̓G���o����
			m_pEnemy = pEnemy;
		}
			
		pEnemy = pEnemyNext;
	}

	return fLenght;
}

//================================================================
// �A�C�e���Ƃ̋����Z�o
//================================================================
float CPlayer::ItemDistance(void)
{
	float fLenght = 10000.0f;
	float fLenghtDiff = 0.0f;  // ��r�p

	CItem *pItem = CItem::GetTop();

	while (pItem != nullptr)
	{
		CItem *pItemNext = pItem->GetNext();

		if (pItem->GetType() == CItem::TYPE_BIKE)
		{
			// �����ƃA�C�e���̋������擾
			if (CManager::Getinstance()->GetUtility() != nullptr)
				fLenghtDiff = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, pItem->GetPosition());

			// �������r
			if (fLenght >= fLenghtDiff)
			{
				fLenght = fLenghtDiff;

				// ��ԋ߂��̓G���o����
				m_pItem = pItem;
			}
		}
		
		pItem = pItemNext;
	}

	return fLenght;
}