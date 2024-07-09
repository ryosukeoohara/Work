//===========================================================
//
// �o���b�g����[bullet.cpp]
// Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "enemyBoss.h"
#include "enemyweak.h"
#include "effect.h"
#include "particl.h"
#include "number.h"
#include "score.h"
#include "debugproc.h"
#include "texture.h"
#include "collision.h"
#include "game.h"
#include "impact.h"
#include "sound.h"

//================================================================
// �萔��`
//================================================================
namespace
{
	const int LIFE = 120;        // ����
	const float WIDTH = 10.0f;   // ��
	const float HEIGHT = 20.0f;  // ����
	const float MOVE = -10.0f;   // �ړ���
	const float POS = 50.0f;     // �ʒu
}

//================================================================
// �ÓI�����o�ϐ��錾
//================================================================
CBullet *CBullet::m_Bullet = NULL;

//================================================================
// �R���X�g���N�^
//================================================================
CBullet::CBullet()
{
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_type = TYPE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	SetPos(&pos);
	SetRot(&rot);
	m_type = type;
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_move = { 0.0f, 0.0f, 0.0f };  //�ړ���
}

//================================================================
// �f�X�g���N�^
//================================================================
CBullet::~CBullet()
{

}

//================================================================
// ��������
//================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CBullet *pBullet = NULL;

	CTexture *pTexture = CManager::GetTexture();

	if (GetNumAll() < MAX_OBJECT)
	{
		if (pBullet == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pBullet = new CBullet(pos, rot, type);

			//����������
			pBullet->Init();
		}
	}

	return pBullet;
}

//================================================================
// ����������
//================================================================
HRESULT CBullet::Init(void)
{
	//��ސݒ�
	SetType(TYPE_BULLET);

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\bom.png");

	//����������
	CBillBoard::Init();

	//�e�̎���
	m_nLife = LIFE;

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CBullet::Uninit(void)
{
	//�I������
	CBillBoard::Uninit();
}

//================================================================
// �X�V����
//================================================================
void CBullet::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//�����蔻��̏��擾
	CCollision *pCollision = CManager::GetCollsion();

	//�G�̏��擾
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//�G�̏��擾
	CEnemyBoss *pEnemyBoss = CEnemyBoss::GetEnemy();

	//�G�̏��擾
	CEnemyWeak **pEnemyWeak = CEnemyWeak::GetEnemy();
	
	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	//�T�E���h�̏����擾
	CSound *pSound = CManager::GetSound();

	//�ʒu����
	D3DXVECTOR3 pos = Getpos();

	D3DXVECTOR3 rot = GetRot();

	//�O��̈ʒu���L�^
	m_posOld = pos;

	SetVtxBullet(pos, WIDTH, HEIGHT);

	//�ʒu���X�V
	pos.x += sinf(rot.y) * MOVE;
	pos.z += cosf(rot.y) * MOVE;

	//�X�V����
	CBillBoard::Update();

	//���������炷
	m_nLife--;

	switch (m_type)
	{
	case TYPE_PLAYER:

		//�G�Ƃ̓����蔻��
		if (pCollision->CollisionBulletEnemy(&pos, 40.0f, 10.0f, &*pEnemy) == true)
		{
			//�������Ȃ���
			m_nLife = 0;

			pDebugProc->Print("\n<<(߁��)����!!>>\n");
		}

		break;

	case TYPE_ENEMY:
		
			//�G�Ƃ̓����蔻��
			if (pCollision->CollisionBulletPlayer(&pos, 40.0f, 10.0f, pPlayer) == true && pPlayer != nullptr)
			{
				//�������Ȃ���
				m_nLife = 0;

				pDebugProc->Print("\n<<�ɂ�������>>\n");
			}

		break;

	case TYPE_BOM:

		if (pos.y <= 0.0f)
		{
			m_nLife = 0;

			CParticl::Create(pos, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 10.0f, TYPEPAR_GROUND);
			CParticl::Create(pos, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, 10.0f, TYPEPAR_SMOOK);
			CImpact::Create({ pos.x, 15.0f, pos.z }, CImpact::TYPE_NONE);

			pSound->Play(CSound::SOUND_LABEL_SE06);

			if ((pCollision->CollisionCircle(&pos, 300.0f, pPlayer) == true))
				 pPlayer->Hit();
		}
		else
		{
			pos.y -= 0.98f;
		}
			
		//�G�Ƃ̓����蔻��
		if (pCollision->CollisionBulletPlayer(&pos, 40.0f, 10.0f, pPlayer) == true && pPlayer != NULL)
		{
			//�������Ȃ���
			m_nLife = 0;

			pDebugProc->Print("\n<<�ɂ�������>>\n");
		}
		
		break;
	}
		
	if (m_nLife <= 0)
	{
		CBullet::Uninit();

		return;
	}
	else
	{
		CEffect::Create({ pos.x, pos.y, pos.z }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 5.0f, 15, CEffect::TYPEEFF_NONE);
	}
	
	// �ʒu��ݒ�
	CBillBoard::SetPos(&pos);
}

//================================================================
// �`�揈��
//================================================================
void CBullet::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �`�揈��
	CBillBoard::Draw();
}