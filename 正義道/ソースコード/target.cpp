//===========================================================
//
//ポリゴンを出すやつ[title.cpp]
//Author 大原怜将
//
//===========================================================
#include "target.h"
#include "texture.h"
#include "game.h"
#include "field.h"
#include "debugproc.h"
#include "renderer.h"
#include "titlelogo.h"
#include "camera.h"
#include "player.h"

//===========================================================
//静的メンバ変数
//===========================================================
CNumber *CTarget::m_apNumber[MAX_NUMBER] = {};
CNumber *CTarget::m_apNumCount[MAX_NUMBER] = {};
CTarget::TYPE CTarget::m_type = TYPE_NONE;

//===========================================================
//コンストラクタ
//===========================================================
CTarget::CTarget()
{
	m_nIdxTexture = -1;
}

//===========================================================
//コンストラクタ(オーバーロード)
//===========================================================
CTarget::CTarget(TYPE type, D3DXVECTOR3 pos)
{
	m_nIdxTexture = -1;
	m_type = type;
	SetPos(&pos);
}

//===========================================================
//デストラクタ
//===========================================================
CTarget::~CTarget()
{

}

//===========================================================
//生成
//===========================================================
CTarget *CTarget::Create(TYPE type, D3DXVECTOR3 pos)
{
	CTarget *Target = NULL;

	if (Target == NULL)
	{
		Target = new CTarget(type, pos);

		Target->Init();
	}

	return Target;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CTarget::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//初期化処理
	CObject2D::Init();

	switch (m_type)
	{
	case CTarget::TYPE_NONE:    //なし
		break;

	case CTarget::TYPE_FIRST:   //最初の目標

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim000.png"));
		break;

	case CTarget::TYPE_SECOND:  //二つ目の目標

		SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim001.png"));
		break;

	case CTarget::TYPE_MAX:
		break;

	default:
		break;
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			m_apNumber[nCount] = CNumber::Create({ 1090.0f + 50.0f * nCount, 235.0f, 0.0f });

			m_apNumber[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			//初期化処理
			m_apNumber[nCount]->Init();

			m_apNumber[nCount]->m_Number = 0;
		}
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumCount[nCount] == NULL)
		{
			m_apNumCount[nCount] = CNumber::Create({ 1220.0f + 50.0f * nCount, 235.0f, 0.0f });

			m_apNumCount[nCount]->SetNumberType(CNumber::TYPENUMBER_DESTROYCOUNTER);

			m_apNumCount[nCount]->m_Number = 0;
		}
	}
	
	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTarget::Uninit(void)
{
	//終了処理
	CObject2D::Uninit();

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//終了処理
			m_apNumber[nCount]->Uninit();

			m_apNumber[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumCount[nCount] != NULL)
		{
			//終了処理
			m_apNumCount[nCount]->Uninit();

			m_apNumCount[nCount] = NULL;
		}
	}
}

//===========================================================
//更新処理
//===========================================================
void CTarget::Update(void)
{
	//敵の死んだ数を取得
	int EnemyDieCount = CEnemyManager::GetCounter();

	//ざこ敵の総数を取得
	int nNumEnemyWeak = CEnemyManager::GetNumEneWeak();

	//幹部の総数を取得
	int nNumBoss = CEnemyManager::GetNumEneMedBoss();

	//テクスチャの情報取得
	CTexture *pTexture = CManager::GetTexture();

	//プレイヤーの情報を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	//位置代入
	D3DXVECTOR3 pos = Getpos();

	//更新処理
	CObject2D::Update();

	CObject2D::SetVtxTarget(pos, 180.0f, 70.0f);

	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
		{
			if (m_apNumber[nCount] != NULL)
			{
				m_apNumber[0]->m_Number = 0;
				m_apNumber[1]->m_Number = EnemyDieCount;

				//更新処理
				m_apNumber[nCount]->SetVtxCounter({ 260.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
			}
		}

		switch (m_type)
		{
		case CTarget::TYPE_NONE:    //なし
			break;

		case CTarget::TYPE_FIRST:   //最初の目標

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					m_apNumCount[0]->m_Number = 0;
					m_apNumCount[1]->m_Number = nNumEnemyWeak;

					//更新処理
					m_apNumCount[nCount]->SetVtxCounter({ 350.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
				}
			}

			break;

		case CTarget::TYPE_SECOND:  //二つ目の目標

			SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim001.png"));

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					m_apNumCount[0]->m_Number = 0;
					m_apNumCount[1]->m_Number = nNumBoss;

					//更新処理
					m_apNumCount[nCount]->SetVtxCounter({ 350.0f + 30.0f * nCount, 235.0f, 0.0f }, 15.0f, 20.0f);
				}
			}

			break;

		case CTarget::TYPE_FINAL:  //最後の目標

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumber[nCount] != NULL)
				{
					//終了処理
					m_apNumber[nCount]->Uninit();

					m_apNumber[nCount] = NULL;
				}
			}

			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumCount[nCount] != NULL)
				{
					//終了処理
					m_apNumCount[nCount]->Uninit();

					m_apNumCount[nCount] = NULL;
				}
			}

			SetIdxTex(pTexture->Regist("data\\TEXTURE\\aim002.png"));

			break;

		case CTarget::TYPE_MAX:
			break;

		default:
			break;
		}
	}
}

//===========================================================
//描画処理
//===========================================================
void CTarget::Draw(void)
{
	CTexture *pTexture = CManager::GetTexture();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	CCamera *pCamera = CManager::GetCamera();

	//プレイヤーの情報を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		//描画処理
		CObject2D::Draw();

		if (m_type != TYPE_FINAL)
		{
			for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
			{
				if (m_apNumber[nCount] != NULL)
				{
					//描画処理
					//m_apNumber[nCount]->Draw();
				}
			}
		}
	}
}