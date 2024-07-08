//===========================================================
//
// ���C�g���� [light.cpp]
// Author : �匴�@�叫
//
//===========================================================
#include "main.h"
#include "light.h"
#include "renderer.h"
#include "manager.h"

//===========================================================
// �萔��`
//===========================================================
namespace
{
	const int NUMLIGHT = 3;  // ���C�g�̑���
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CLight::CLight()
{
	
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CLight::~CLight()
{

}

//===========================================================
// ����������
//===========================================================
void CLight::Init(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (pRenderer == nullptr)
		return;

	if (pDevice == nullptr)
		return;

	// ���C�g�̏����N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < NUMLIGHT; nCntLight++)
	{
		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCntLight)
		{
		case 0:
			// ���C�g�̊g�U�Z��ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			m_vecDir[nCntLight] = D3DXVECTOR3(-0.05f, -0.87f, 0.05f);
			break;

		case 1:
			// ���C�g�̊g�U�Z��ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			m_vecDir[nCntLight] = D3DXVECTOR3(0.46f, 0.88f, -0.44f);
			break;

		case 2:
			// ���C�g�̊g�U�Z��ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			m_vecDir[nCntLight] = D3DXVECTOR3(-0.60f, -0.82f, 0.42f);
			break;
		}

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&m_vecDir[nCntLight], &m_vecDir[nCntLight]);

		m_light[nCntLight].Direction = m_vecDir[nCntLight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//===========================================================
// �I������
//===========================================================
void CLight::Uninit(void)
{

}

//===========================================================
// �X�V����
//===========================================================
void CLight::Update(void)
{

}