//===========================================================
//
//バレット処理[bullet.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "effect.h"
#include "debugproc.h"
#include "texture.h"
#include "game.h"
#include "sound.h"
#include "collision.h"
#include "enemy.h"
#include "map.h"

//================================================================
//マクロ定義
//================================================================
#define BULLETMOVE       (-10.0f)    //弾の移動量
#define BULLETPOS        (50.0f)     //弾の位置
#define BULLETLIFE       (120)       //弾の寿命
#define BULLET_WIDTH     (10.0f)     //弾の幅
#define BULLET_HEIGHT    (20.0f)     //弾の高さ

//================================================================
//静的メンバ変数宣言
//================================================================
//LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
CBullet *CBullet::m_Bullet = NULL;

//================================================================
//コンストラクタ
//================================================================
CBullet::CBullet()
{
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_type = TYPE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
}

//================================================================
//コンストラクタ(オーバーロード)
//================================================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	SetPos(&pos);
	SetRot(&rot);
	m_type = type;
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
}

//================================================================
//デストラクタ
//================================================================
CBullet::~CBullet()
{

}

//================================================================
//生成処理
//================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	//オブジェクト2Dのポインタ
	CBullet *pBullet = NULL;

	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	if (GetNumAll() < MAX_OBJECT)
	{
		if (pBullet == NULL)
		{
			//オブジェクト2Dの生成
			pBullet = new CBullet(pos, rot, type);

			//初期化処理
			pBullet->Init();
		}
	}

	return pBullet;
}

//================================================================
//バレットの初期化処理
//================================================================
HRESULT CBullet::Init(void)
{
	//種類設定
	SetType(TYPE_BULLET);

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\bom.png");

	//初期化処理
	CBillBoard::Init();

	//弾の寿命
	m_nLife = BULLETLIFE;

	return S_OK;
}

//================================================================
//バレットの終了処理
//================================================================
void CBullet::Uninit(void)
{
	//終了処理
	CBillBoard::Uninit();
}

//================================================================
//バレットの更新処理
//================================================================
void CBullet::Update(void)
{
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	CMap *pmap = CGame::GetMap();

	//当たり判定の情報取得
	CCollision *pCollision = CGame::GetCollsion();

	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	CFoot *pPlayerFoot = CGame::GetPlayerFoot();
	CChibi *pPlayerChibi = CGame::GetPlayerChibi();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//位置を代入
	D3DXVECTOR3 pos = Getpos();

	//向きを代入
	D3DXVECTOR3 rot = GetRot();

	//前回の位置を記録
	m_posOld = pos;

	SetVtxBullet(pos, BULLET_WIDTH, BULLET_HEIGHT);

	if (pPlayerFoot->GetState() != CFoot::STATE_APPR && pPlayerChibi->GetState() != CChibi::STATE_APPR)
	{
		//位置を更新
		pos.x += sinf(rot.y) * BULLETMOVE;
	}

	//更新処理
	CBillBoard::Update();

	//寿命を減らす
	m_nLife--;

	switch (m_type)
	{
	case CBullet::TYPE_NONE:
		break;

	case CBullet::TYPE_PLAYER:

		if (pmap != NULL)
		{
			//マップモデルの情報を取得
			//CObjectX **pMap = CMap::GetX();

			if (pCollision != NULL && pmap->GetX() != NULL)
			{
				if (pCollision->BulletEnemy(&pos, 20.0f, 100.0f, pEnemy) == true)
				{
					m_nLife = 0;
				}
				else if (pCollision->BulletMap(&pos, pmap->GetX()) == true)
				{
					m_nLife = 0;
				}
			}
		}
		
		
		break;

	case CBullet::TYPE_ENEMY:

		if (pCollision != NULL && pmap->GetX() != NULL)
		{
			if (pPlayerFoot->GetbAppr() == true)
			{
				if (pCollision->BulletPlayer(&pos, 20.0f, 100.0f, pPlayer) == true)
				{
					m_nLife = 0;
				}
			}

			if (pPlayerChibi->GetbAppr() == true)
			{
				if (pCollision->BulletPlayer(&pos, 20.0f, 80.0f, pPlayer) == true)
				{
					m_nLife = 0;
				}
			}

			if (pCollision->BulletMap(&pos, pmap->GetX()) == true)
			{
				m_nLife = 0;
			}
		}
		break;

	case CBullet::TYPE_BOM:
		break;

	case CBullet::TYPE_MAX:
		break;

	default:
		break;
	}

	if (m_nLife <= 0)
	{//寿命がなくなったら

		//爆発を生成
		//CExplosion::Create(pos);

		//パーティクルを生成
		//CParticl::Create(pos, {0.0f, 0.0f, 0.0f}, { 0.6f, 1.0f, 5.0f, 1.0f }, 5.0f, TYPEPAR_BULLET);

		//終了処理
		CBullet::Uninit();
	}
	else
	{
		CEffect::Create({ pos.x, pos.y, pos.z }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.8f, 0.7f }, 5.0f, 15, CEffect::TYPEEFF_NONE);

		//位置を設定
		CBillBoard::SetPos(&pos);
	}
}

//================================================================
//バレットの描画処理
//================================================================
void CBullet::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//描画処理
	CBillBoard::Draw();
}

//================================================================
//敵との当たり判定
//================================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	//{
	//	CObject *pObj;

	//	//オブジェクトを取得
	//	pObj = Getobject(nCount);

	//	if (pObj != NULL)  //わすれてた
	//	{
	//		//種類を取得
	//		TYPE type = pObj->GetType();
	//		
	//		if (type == TYPE_ENEMY)
	//		{//種類が敵の場合

	//			//キャストして代入
	//			CEnemy *pEnemy = (CEnemy*)pObj;

	//			D3DXVECTOR3 Enemypos = pEnemy->Getpos();

	//			if (pos.x >= Enemypos.x - 50.0f
	//			 && pos.x <= Enemypos.x + 50.0f
	//			 && pos.y >= Enemypos.y - 50.0f
	//			 && pos.y <= Enemypos.y + 50.0f)
	//			{
	//				//爆発を生成
	//				//CExplosion::Create(pEnemy->GetPosition());

	//				CParticl::Create(pos, {0.6f, 1.0f, 5.0f, 1.0f}, 15.0f);

	//				CScore::AddScore(100);

	//				pObj->Uninit();

	//				//終了処理
	//				Uninit();

	//				return true;
	//			}
	//			
	//		}
	//	}
	//}

	return false;
}