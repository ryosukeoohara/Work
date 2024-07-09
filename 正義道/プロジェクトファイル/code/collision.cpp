//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "enemyweak.h"
#include "enemymanager.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "object.h"
#include "objectX.h"
#include "particl.h"
#include "slot.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCollision::Uninit(void)
{
	
}

//=============================================================================
// �e�ƃI�u�W�F�N�g�̓����蔻�菈��
//=============================================================================
bool CCollision::CollisionBulletEnemy(D3DXVECTOR3 *pos, float fWidthX, float fWidthZ, CEnemy **pEnemy)
{
	int MessCount = 0;
	int nNumEnemy = CEnemyManager::GetNumAll();
	float c = 0.0f;

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		float EnemyfRadius = 50.0f;

		if (pEnemy[nCount] != NULL)
		{
			D3DXVECTOR3 Enepos = pEnemy[nCount]->Getpos();

			if (pos->x <= Enepos.x + fWidthX
			 && pos->x >= Enepos.x - fWidthX
			 && pos->z <= Enepos.z + fWidthZ
			 && pos->z >= Enepos.z - fWidthZ)
			{
				if (pEnemy[nCount]->GetState() != CEnemy::STATE_DEATH || pEnemy[nCount]->GetState() != CEnemy::STATE_END)
				{
					int nLife = pEnemy[nCount]->GetLife();

					nLife--;

					pEnemy[nCount]->SetLife(nLife);

					pEnemy[nCount]->SetState(CEnemy::STATE_DAMEGE);
				}

				D3DXVECTOR3 rot = pEnemy[nCount]->GetRot();

				//�p�[�e�B�N���𐶐�
				CParticl::Create({ Enepos.x, Enepos.y + 50.0f, Enepos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, TYPEPAR_BLOOD);

				return true; 
			} 
			else
			{
				MessCount++;
			}
		}
	}

	return false;
}

//=============================================================================
// �e�ƃI�u�W�F�N�g�̓����蔻�菈��
//=============================================================================
bool CCollision::CollisionBulletPlayer(D3DXVECTOR3 *pPos, float fWidthX, float fWidthZ, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{//�g�p����Ă���Ƃ�

	    //�G�̈ʒu�擾
		D3DXVECTOR3 pos = pPlayer->Getpos();

		if (pPos->x <= pos.x + fWidthX
		 && pPos->x >= pos.x - fWidthX
		 && pPos->z <= pos.z + fWidthZ
		 && pPos->z >= pos.z - fWidthZ)
		{
			D3DXVECTOR3 rot = pPlayer->GetRot();

			pPlayer->Hit();

			//�p�[�e�B�N���𐶐�
			CParticl::Create({ pos.x, pos.y + 50.0f, pos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, TYPEPAR_BLOOD);

			return true;
		}
	}


	return false;
}

//=============================================================================
// �~�̓����蔻�菈��
//=============================================================================
bool CCollision::CollisionCircle(D3DXVECTOR3 *pPos, float fRadius, CPlayer *pPlayer)
{
	D3DXVECTOR3 pos = pPlayer->Getpos();

	float PlayerfRadius = 50.0f;

	float circleX = pPos->x - pos.x;
	float circleZ = pPos->z - pos.z;
	float c = 0.0f;

	c = (float)sqrt(circleX * circleX + circleZ * circleZ);

	if (c <= fRadius + PlayerfRadius)
	{
		return true;
	}

	return false;
}

//=============================================================================
// ���̂̓����蔻�菈��
//=============================================================================
bool CCollision::Knife(D3DXVECTOR3 *pPos, D3DXVECTOR3 rot, float fRadius, CEnemy **pEnemy)
{
	int MessCount = 0;
	int nNumEnemy = CEnemyManager::GetNumAll();
	float c = 0.0f;

	for (int nCount = 0; nCount < nNumEnemy; nCount++)
	{
		float EnemyfRadius = 50.0f;

		if (pEnemy[nCount] != NULL)
		{
			D3DXVECTOR3 pos = pEnemy[nCount]->Getpos();

			c = (pos.x - pPos->x) * (pos.x - pPos->x) + (pos.y - pPos->y) * (pos.y - pPos->y) + (pos.z - pPos->z) * (pos.z - pPos->z);

			if (c <= (fRadius + EnemyfRadius) * (fRadius + EnemyfRadius))
			{
				pEnemy[nCount]->Hit();

				//�p�[�e�B�N���𐶐�
				CParticl::Create({ pos.x, pos.y + 50.0f, pos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, TYPEPAR_BLOOD);

				return true;
			}
			else
			{
				MessCount++;
			}
		}
	}
	
	return false;
}

//=============================================================================
// �~�̓����蔻�菈��
//=============================================================================
bool CCollision::CollisionItem(D3DXVECTOR3 *pPos, float fWidthX, float fWidthZ, CItem::TYPE type, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{//�g�p����Ă���Ƃ�

		//�G�̈ʒu�擾
		D3DXVECTOR3 pos = pPlayer->Getpos();

		if (pPos->x <= pos.x + fWidthX
		 && pPos->x >= pos.x - fWidthX
		 && pPos->z <= pos.z + fWidthZ
		 && pPos->z >= pos.z - fWidthZ)
		{
			CSlot::Set(type);

			return true;
		}
	}


	return false;
}

//=============================================================================
// �G�ƃI�u�W�F�N�g�̓����蔻�菈��
//=============================================================================
bool CCollision::Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{
		//�G�̈ʒu�擾
		D3DXVECTOR3 Playerpos = pPlayer->Getpos();

		if (pos->x + fWidthX >= Playerpos.x - 10.0f
		 && pos->x - fWidthX <= Playerpos.x + 10.0f
		 && pos->z + fWidthZ >= Playerpos.z - 10.0f
		 && pos->z - fWidthZ <= Playerpos.z + 10.0f)
		{
			////����======================================
			//if (pos->z >= Playerpos.z - 10.0f
			// && posOld->z <= Playerpos.z - 10.0f)
			//{
			//	return true;
			//}

			////�w��======================================
			//else if (pos->z  <= Playerpos.z + 10.0f
			//	  && posOld->z >= Playerpos.z + 10.0f)
			//{
			//	return true;
			//}

			////������߂荞��
			//else if (pos->x >= Playerpos.x - 10.0f
			//	  && pos->x <= Playerpos.x + 10.0f)
			//{
			//	//��==================================
			//	if (pos->x >= Playerpos.x - 10.0f
			//     && posOld->x <= Playerpos.x - 10.0f)
			//	{
			//		return true;
			//	}

			//	//�E==================================
			//	else if (pos->x <= Playerpos.x + 10.0f
			//		  && posOld->x >= Playerpos.x + 10.0f)
			//	{
			//		return true;
			//	}
			//}

			return true;
		}
	}

	return false;
}

//=============================================================================
// �~�̓����蔻�菈��
//=============================================================================
bool CCollision::kugibat(D3DXVECTOR3 *pPos, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{//�g�p����Ă���Ƃ�

		//�G�̈ʒu�擾
		D3DXVECTOR3 pos = pPlayer->Getpos();

		if (pPos->x - 30.0f <= pos.x
		 && pPos->x + 30.0f >= pos.x
		 && pPos->z - 30.0f <= pos.z
		 && pPos->z + 30.0f >= pos.z )
		{
			pPlayer->Hit();

			return true;
		}
	}

	return false;
}

//=============================================================================
// �}�b�v�ɂ��錚���Ƃ̓����蔻��
//=============================================================================
bool CCollision::Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX)
{
	int nNumAll = CObjectX::GetNumAll();

	for (int nCount = 0; nCount < nNumAll; nCount++)
	{
		if (pObjectX[nCount] != NULL)
		{
			D3DXVECTOR3 Mappos = pObjectX[nCount]->Getpos();

			D3DXVECTOR3 vtxMin = pObjectX[nCount]->GetVtxMin();

			D3DXVECTOR3 vtxMax = pObjectX[nCount]->GetVtxMax();

			if (pos->x + 10.0f > Mappos.x + vtxMin.x
			 && pos->x + 10.0f < Mappos.x + vtxMax.x
			 && pos->z + 10.0f > Mappos.z + vtxMin.z
			 && pos->z + 10.0f < Mappos.z + vtxMax.z)
			{
				//�u���b�N�̏�======================================
				if (pos->z + 10.0f <= Mappos.z + vtxMax.z
				 && posOld->z + 10.0f >= Mappos.z + vtxMax.z)
				{
					pos->z = Mappos.z + vtxMax.z - 10.0f;

					return true;
				}

				//�u���b�N�̉�======================================
				else if (pos->z + 10.0f >= Mappos.z + vtxMin.z
					&& posOld->z + 10.0f <= Mappos.z + vtxMin.z)
				{
					pos->z = Mappos.z + vtxMin.z - 10.0f;

					return true;
				}

				//������߂荞��
				else if (pos->x + 10.0f > Mappos.x + vtxMin.x
					&& pos->x + 10.0f < Mappos.x + vtxMax.x)
				{
					//�u���b�N�̍�����==================================
					if (pos->x + 10.0f >= Mappos.x + vtxMin.x
						&& posOld->x + 10.0f <= Mappos.x + vtxMin.x)
					{
						pos->x = Mappos.x + vtxMin.x - 10.0f;

						return true;
					}

					//�u���b�N�̉E����==================================
					else if (pos->x - 10.0f <= Mappos.x + vtxMax.x
						&& posOld->x - 10.0f >= Mappos.x - vtxMax.x)
					{
						pos->x = Mappos.x + vtxMax.x - 10.0f;

						return true;
					}
				}
			}
		}
	}
	
	return false;
}