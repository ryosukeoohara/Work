//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
//インクルードファイル
//*============================================================================
#include "main.h"
#include "collision.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "object.h"
#include "objectX.h"
#include "particl.h"
#include "game.h"
#include "map.h"
#include "enemy.h"
#include "particl.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CCollision::Uninit(void)
{
	
}

//=============================================================================
//敵とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::Enemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy **pEnemy)
{
	for (int nCount = 0; nCount < 10; nCount++)
	{
		if (pEnemy[nCount] != nullptr)  //わすれてた
		{
			//敵の位置取得
			D3DXVECTOR3 Enepos = pEnemy[nCount]->Getpos();

			if (pos->x + fWidthX >= Enepos.x - 10.0f
				&& pos->x - fWidthX <= Enepos.x + 10.0f
				&& pos->y + fWidthZ >= Enepos.y
				&& pos->y - fWidthZ <= Enepos.y + 80.0f)
			{
				//正面======================================
				if (pos->y + fWidthZ >= Enepos.y
				 && posOld->y + fWidthZ <= Enepos.y)
				{
					return true;
				}

				//背面======================================
				else if (pos->y <= Enepos.y + 80.0f
					  && posOld->y >= Enepos.y + 80.0f)
				{
					return true;
				}

				//横からめり込んだ
				else if (pos->x + fWidthX >= Enepos.x - 10.0f
					  && pos->x - fWidthX <= Enepos.x + 10.0f)
				{
					//左==================================
					if (pos->x + fWidthX >= Enepos.x - 10.0f
					 /*&& posOld->x + fWidthX <= Enepos.x - 10.0f*/)
					{
						return true;
					}

					//右==================================
					else if (pos->x - fWidthX <= Enepos.x + 10.0f
						  /*&& posOld->x - fWidthX >= Enepos.x + 10.0f*/)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//=============================================================================
//弾とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::BulletEnemy(D3DXVECTOR3 *pos, float fWidthX, float fWidthY, CEnemy **pEnemy)
{
	//int nNumEnemy = CEnemyManager::GetNumAll();
	float c = 0.0f;

	for (int nCount = 0; nCount < 10; nCount++)
	{
		float EnemyfRadius = 50.0f;

		if (pEnemy[nCount] != NULL)
		{
			D3DXVECTOR3 Enepos = pEnemy[nCount]->Getpos();

			if (pos->x <= Enepos.x + fWidthX
			 && pos->x >= Enepos.x - fWidthX
			 && pos->y <= Enepos.y + fWidthY
			 && pos->y >= Enepos.y)
			{
				int nLife = pEnemy[nCount]->GetLife();

				nLife -= 10;

				pEnemy[nCount]->SetLife(nLife);

				D3DXVECTOR3 rot = pEnemy[nCount]->GetRot();

				//パーティクルを生成
				CParticl::Create({ Enepos.x, Enepos.y + 50.0f, Enepos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, CParticl::TYPEPAR_BULLET);

				return true; 
			} 
		}
	}

	return false;
}

//=============================================================================
//弾とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::BulletPlayer(D3DXVECTOR3 *pPos, float fWidthX, float fWidthZ, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{//使用されているとき

	    //敵の位置取得
		D3DXVECTOR3 pos = pPlayer->Getpos();

		if (pPos->x <= pos.x + fWidthX
		 && pPos->x >= pos.x - fWidthX
		 && pPos->y <= pos.y + fWidthZ
		 && pPos->y >= pos.y)
		{
			D3DXVECTOR3 rot = pPlayer->GetRot();

			pPlayer->Hit();

			//パーティクルを生成
			CParticl::Create({ pos.x, pos.y + 50.0f, pos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, CParticl::TYPEPAR_BULLET);

			return true;
		}
	}

	return false;
}

//=============================================================================
//弾とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::BulletMap(D3DXVECTOR3 * pos, CObjectX ** pObjectX)
{
	//マップの情報を取得
	CMap *pMap = CGame::GetMap();

	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(クソデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	int nNumAll = pMap->GetnNumAll();

	for (int nCount = 0; nCount < nNumAll; nCount++)
	{
		if (pObjectX[nCount] != NULL)
		{
			D3DXVECTOR3 Mappos = pObjectX[nCount]->Getpos();

			D3DXVECTOR3 vtxMin = pObjectX[nCount]->GetVtxMin();

			D3DXVECTOR3 vtxMax = pObjectX[nCount]->GetVtxMax();

			if (pos->x > Mappos.x + vtxMin.x
			 && pos->x < Mappos.x + vtxMax.x
			 && pos->y > Mappos.y + vtxMin.y
			 && pos->y < Mappos.y + vtxMax.y
			 && pos->z > Mappos.z + vtxMin.z
			 && pos->z < Mappos.z + vtxMax.z)
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
//円の当たり判定処理
//=============================================================================
bool CCollision::Circle(D3DXVECTOR3 *pPos, float fRadius, CPlayer *pPlayer)
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
//敵とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer)
{
	if (pPlayer != NULL)
	{
		//敵の位置取得
		D3DXVECTOR3 Playerpos = pPlayer->Getpos();

		if (pos->x + fWidthX >= Playerpos.x - 10.0f
		 && pos->x - fWidthX <= Playerpos.x + 10.0f
		 && pos->z + fWidthZ >= Playerpos.z - 10.0f
		 && pos->z - fWidthZ <= Playerpos.z + 10.0f)
		{
			////正面======================================
			//if (pos->z >= Playerpos.z - 10.0f
			// && posOld->z <= Playerpos.z - 10.0f)
			//{
			//	return true;
			//}

			////背面======================================
			//else if (pos->z  <= Playerpos.z + 10.0f
			//	  && posOld->z >= Playerpos.z + 10.0f)
			//{
			//	return true;
			//}

			////横からめり込んだ
			//else if (pos->x >= Playerpos.x - 10.0f
			//	  && pos->x <= Playerpos.x + 10.0f)
			//{
			//	//左==================================
			//	if (pos->x >= Playerpos.x - 10.0f
			//     && posOld->x <= Playerpos.x - 10.0f)
			//	{
			//		return true;
			//	}

			//	//右==================================
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
//マップにある建物との当たり判定
//=============================================================================
void CCollision::Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX)
{
	//マップの情報を取得
	CMap *pMap = CGame::GetMap();

	//プレイヤー(クソデブ)の情報を取得
	CFoot *pFoot = CGame::GetPlayerFoot();

	//プレイヤー(クソデブ)の情報を取得
	CChibi *pChibi = CGame::GetPlayerChibi();

	CPlayer *pPlayer = CGame::GetPlayer();

	int nNumAll = pMap->GetnNumAll();

	for (int nCount = 0; nCount < nNumAll; nCount++)
	{
		if (pObjectX[nCount] != NULL)
		{
		    D3DXVECTOR3 Mappos = pObjectX[nCount]->Getpos();

			D3DXVECTOR3 vtxMin = pObjectX[nCount]->GetVtxMin();

			D3DXVECTOR3 vtxMax = pObjectX[nCount]->GetVtxMax();

			if (pos->x + 20.0f > Mappos.x + vtxMin.x
			 && pos->x - 20.0f < Mappos.x + vtxMax.x
			 && pos->y + 60.0f > Mappos.y + vtxMin.y
			 && pos->y < Mappos.y + vtxMax.y
			 && pos->z + 20.0f > Mappos.z + vtxMin.z
			 && pos->z - 20.0f < Mappos.z + vtxMax.z)
			{
				//ブロックの上======================================
				if (pos->y <= Mappos.y + vtxMax.y
				 && posOld->y >= Mappos.y + vtxMax.y)
				{
					pos->y = Mappos.y + vtxMax.y;

					if (pFoot->GetbAppr() == true)
					{
						pFoot->SetPos(pos);
						pFoot->SetMoveY(0.0f);
						pFoot->SetbJump(false);
						pFoot->SetbRand(true);
					}
					
					if (pChibi->GetbAppr() == true)
					{
						pChibi->SetPos(pos);
						pChibi->SetMoveY(0.0f);
						pChibi->SetbJump(false);
						pChibi->SetbRand(true);
					}
				}
				/*else
				{
					if (pFoot->GetbAppr() == true)
					{
						pFoot->SetbRand(false);
					}

					if (pChibi->GetbAppr() == true)
					{
						pChibi->SetbRand(false);
					}
				}*/

				//ブロックの下======================================
				else if (pos->y + 60.0f >= Mappos.y + vtxMin.y
					&& posOld->y + 60.0f <= Mappos.y + vtxMin.y)
				{
					pos->y = Mappos.y + vtxMin.y - 60.0f;

					if (pFoot->GetbAppr() == true)
					{
						pFoot->SetPos(pos);
						pFoot->SetMoveY(0.0f);
					}

					if (pChibi->GetbAppr() == true)
					{
						pChibi->SetPos(pos);
						pChibi->SetMoveY(0.0f);
					}
				}

				//ブロックの左側面==================================
				if (pos->x + 20.0f >= Mappos.x + vtxMin.x
					&& posOld->x + 20.0f <= Mappos.x + vtxMin.x)
				{
					pos->x = Mappos.x + vtxMin.x - 20.0f;

					if (pFoot->GetbAppr() == true)
					{
						pFoot->SetPos(pos);
					}

					if (pChibi->GetbAppr() == true)
					{
						pChibi->SetPos(pos);
					}
				}

				//ブロックの右側面==================================
				if (pos->x - 20.0f <= Mappos.x + vtxMax.x
					&& posOld->x - 20.0f >= Mappos.x + vtxMax.x)
				{
					pos->x = Mappos.x + vtxMax.x + 20.0f;

					if (pFoot->GetbAppr() == true)
					{
						pFoot->SetPos(pos);
					}

					if (pChibi->GetbAppr() == true)
					{
						pChibi->SetPos(pos);
					}
				}
			}
		}
	}
}

bool CCollision::Block(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidthX, float fWidthZ)
{


	return false;
}

//=============================================================================
//剣の当たり判定
//=============================================================================
bool CCollision::Sword(D3DXMATRIX pos, D3DXMATRIX matrix, float flength, CEnemy **pEnemy)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX Matrix;
	D3DXVECTOR3 offPos = { 0.0f, 0.0f, -flength };
	D3DXVECTOR3 Pos = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 offRot = { 0.0f, 0.0f, 0.0f };

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Matrix);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, offRot.y, offRot.x, offRot.z);

	D3DXMatrixMultiply(&Matrix, &Matrix, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, offPos.x, offPos.y, offPos.z);

	D3DXMatrixMultiply(&Matrix, &Matrix, &m_mtxTrans);

	//算出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&Matrix, &Matrix, &matrix);

	Pos.x = Matrix._41;
	Pos.y = Matrix._42;
	Pos.z = Matrix._43;

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Matrix);

	for (int nCount = 0; nCount < 10; nCount++)
	{
		if (pEnemy[nCount] != NULL)
		{
			D3DXVECTOR3 Enepos = pEnemy[nCount]->Getpos();

			if ((pos._41 >= Enepos.x
			  && Pos.x <= Enepos.x
			  || pos._41 <= Enepos.x
			  && Pos.x >= Enepos.x)
			  && pos._42 >= Enepos.y
			  && Pos.y <= Enepos.y + 100.0f)
			{
				int nLife = pEnemy[nCount]->GetLife();

				nLife -= 20;

				pEnemy[nCount]->SetLife(nLife);

				D3DXVECTOR3 rot = pEnemy[nCount]->GetRot();

				//パーティクルを生成
				CParticl::Create({ Enepos.x, Enepos.y + 50.0f, Enepos.z }, { rot.x, rot.y, rot.z }, { 1.0f, 0.5f, 5.0f, 1.0f }, 5.0f, CParticl::TYPEPAR_BLOOD);

				return true;
			}
		}
	}

	return false;
}

//=============================================================================
//マップにある建物との当たり判定
//=============================================================================
void CCollision::MapEnemy(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, CObjectX ** pObjectX, CEnemy *penemy)
{
	//マップの情報を取得
	CMap *pMap = CGame::GetMap();

	int nNumAll = pMap->GetnNumAll();

	for (int nCount = 0; nCount < nNumAll; nCount++)
	{
		if (pObjectX[nCount] != NULL)
		{
			D3DXVECTOR3 Mappos = pObjectX[nCount]->Getpos();

			D3DXVECTOR3 vtxMin = pObjectX[nCount]->GetVtxMin();

			D3DXVECTOR3 vtxMax = pObjectX[nCount]->GetVtxMax();

			if (pos->x + 20.0f > Mappos.x + vtxMin.x
			 && pos->x - 20.0f < Mappos.x + vtxMax.x
			 && pos->y + 60.0f > Mappos.y + vtxMin.y
			 && pos->y < Mappos.y + vtxMax.y
			 && pos->z + 20.0f > Mappos.z + vtxMin.z
			 && pos->z - 20.0f < Mappos.z + vtxMax.z)
			{
				//ブロックの上======================================
				if (pos->y <= Mappos.y + vtxMax.y
					/*&& posOld->y >= Mappos.y + vtxMax.y*/)
				{
					pos->y = Mappos.y + vtxMax.y;

					penemy->SetPos(pos);
					penemy->SetMoveY(0.0f); 
				}
				//ブロックの下======================================
				else if (pos->y + 60.0f >= Mappos.y + vtxMin.y
					/*&& posOld->y + 60.0f <= Mappos.y + vtxMin.y*/)
				{
					pos->y = Mappos.y + vtxMin.y - 60.0f;

					penemy->SetPos(pos);
					penemy->SetMoveY(0.0f);
				}

				//ブロックの左側面==================================
				if (pos->x + 20.0f >= Mappos.x + vtxMin.x
					&& posOld->x + 20.0f <= Mappos.x + vtxMin.x)
				{
					pos->x = Mappos.x + vtxMin.x - 20.0f;

					penemy->SetPos(pos);
					penemy->SetMoveX(0.0f);
				}
				//ブロックの右側面==================================
				else if (pos->x - 20.0f <= Mappos.x + vtxMax.x
					&& posOld->x - 20.0f >= Mappos.x + vtxMax.x)
				{
					pos->x = Mappos.x + vtxMax.x + 20.0f;

					penemy->SetPos(pos);
					penemy->SetMoveX(0.0f);
				}
			}
		}
	}
}
