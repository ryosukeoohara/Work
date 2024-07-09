//===========================================================
//
// バレット処理[bullet.cpp]
// Author 大原怜将
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
// 定数定義
//================================================================
namespace
{
	const int LIFE = 120;        // 寿命
	const float WIDTH = 10.0f;   // 幅
	const float HEIGHT = 20.0f;  // 高さ
	const float MOVE = -10.0f;   // 移動量
	const float POS = 50.0f;     // 位置
}

//================================================================
// 静的メンバ変数宣言
//================================================================
CBullet *CBullet::m_Bullet = NULL;

//================================================================
// コンストラクタ
//================================================================
CBullet::CBullet()
{
	m_nLife = 0;
	m_nIdxTexture = -1;
	m_type = TYPE_NONE;
	m_move = { 0.0f, 0.0f, 0.0f };  //移動量
}

//================================================================
// コンストラクタ(オーバーロード)
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
// デストラクタ
//================================================================
CBullet::~CBullet()
{

}

//================================================================
// 生成処理
//================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	//オブジェクト2Dのポインタ
	CBullet *pBullet = NULL;

	CTexture *pTexture = CManager::GetTexture();

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
// 初期化処理
//================================================================
HRESULT CBullet::Init(void)
{
	//種類設定
	SetType(TYPE_BULLET);

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\bom.png");

	//初期化処理
	CBillBoard::Init();

	//弾の寿命
	m_nLife = LIFE;

	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CBullet::Uninit(void)
{
	//終了処理
	CBillBoard::Uninit();
}

//================================================================
// 更新処理
//================================================================
void CBullet::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//当たり判定の情報取得
	CCollision *pCollision = CManager::GetCollsion();

	//敵の情報取得
	CEnemy **pEnemy = CEnemy::GetEnemy();

	//敵の情報取得
	CEnemyBoss *pEnemyBoss = CEnemyBoss::GetEnemy();

	//敵の情報取得
	CEnemyWeak **pEnemyWeak = CEnemyWeak::GetEnemy();
	
	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	//サウンドの情報を取得
	CSound *pSound = CManager::GetSound();

	//位置を代入
	D3DXVECTOR3 pos = Getpos();

	D3DXVECTOR3 rot = GetRot();

	//前回の位置を記録
	m_posOld = pos;

	SetVtxBullet(pos, WIDTH, HEIGHT);

	//位置を更新
	pos.x += sinf(rot.y) * MOVE;
	pos.z += cosf(rot.y) * MOVE;

	//更新処理
	CBillBoard::Update();

	//寿命を減らす
	m_nLife--;

	switch (m_type)
	{
	case TYPE_PLAYER:

		//敵との当たり判定
		if (pCollision->CollisionBulletEnemy(&pos, 40.0f, 10.0f, &*pEnemy) == true)
		{
			//寿命をなくす
			m_nLife = 0;

			pDebugProc->Print("\n<<(ﾟ∀ﾟ)ｷﾀｺﾚ!!>>\n");
		}

		break;

	case TYPE_ENEMY:
		
			//敵との当たり判定
			if (pCollision->CollisionBulletPlayer(&pos, 40.0f, 10.0f, pPlayer) == true && pPlayer != nullptr)
			{
				//寿命をなくす
				m_nLife = 0;

				pDebugProc->Print("\n<<痛すぎぃぃ>>\n");
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
			
		//敵との当たり判定
		if (pCollision->CollisionBulletPlayer(&pos, 40.0f, 10.0f, pPlayer) == true && pPlayer != NULL)
		{
			//寿命をなくす
			m_nLife = 0;

			pDebugProc->Print("\n<<痛すぎぃぃ>>\n");
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
	
	// 位置を設定
	CBillBoard::SetPos(&pos);
}

//================================================================
// 描画処理
//================================================================
void CBullet::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 描画処理
	CBillBoard::Draw();
}