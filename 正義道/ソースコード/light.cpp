//=============================================================================
//
// カメラ処理 [light.cpp]
// Author : 大原　怜将
//
//=============================================================================

#include "main.h"
#include "light.h"
#include "renderer.h"
#include "manager.h"

//================================================================
//コンストラクタ
//================================================================
CLight::CLight()
{
	
}

//================================================================
//デストラクタ
//================================================================
CLight::~CLight()
{

}

//================================================================
//カメラの初期化処理
//================================================================
void CLight::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ライトの情報をクリアする
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCntLight)
		{
		case 0:
			//ライトの拡散校を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			m_vecDir[nCntLight] = D3DXVECTOR3(-0.04f, -0.24f, 0.97f);
			break;

		case 1:
			//ライトの拡散校を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			m_vecDir[nCntLight] = D3DXVECTOR3(-0.34f, -0.85f, 0.41f);
			break;

		case 2:
			//ライトの拡散校を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			m_vecDir[nCntLight] = D3DXVECTOR3(0.44f, -0.60f, -0.66f);
			break;
		}

		//ベクトルを正規化する
		D3DXVec3Normalize(&m_vecDir[nCntLight], &m_vecDir[nCntLight]);

		m_light[nCntLight].Direction = m_vecDir[nCntLight];

		//ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//================================================================
//カメラの終了処理
//================================================================
void CLight::Uninit(void)
{

}

//================================================================
//カメラ更新処理
//================================================================
void CLight::Update(void)
{

}