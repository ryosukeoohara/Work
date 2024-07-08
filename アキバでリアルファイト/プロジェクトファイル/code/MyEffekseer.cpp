//===========================================================
//
// �G�t�F�N�V�A[MyEffekseer.cpp]
// Author �匴�叫
//
//===========================================================
#include <stdio.h>
#include <string>
#include <windows.h>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "MyEffekseer.h"
#include "camera.h"

// �G�t�F�N�g�̖��O
const char* CMyEffekseer::m_apEfkName[CMyEffekseer::TYPE_MAX] =
{
	"",                                                // �Ȃ���Ȃ�
	"data\\EFFEKSEER\\Effect\\impact.efkefc",          // �Ռ��g
	"data\\EFFEKSEER\\Effect\\hit.efkefc",             // �q�b�g
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CMyEffekseer::CMyEffekseer()
{
	// �l��������
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CMyEffekseer::~CMyEffekseer()
{

}

//===========================================================
// ����������
//===========================================================
void CMyEffekseer::Init(void)
{
	// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
	m_EfkManager = ::Effekseer::Manager::Create(8000);

	// Specify a position of view
	// ���_�ʒu���m��
	m_ViewerPosition = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);

	// ���W�n��ݒ肷��B�A�v���P�[�V�����ƈ�v������K�v������B
	m_EfkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// Setup effekseer modules
	// Effekseer�̃��W���[�����Z�b�g�A�b�v����
	SetupEffekseerModules(m_EfkManager);

	// Specify a projection matrix
	// ���e�s���ݒ�
	m_ProjectionMatrix.PerspectiveFovLH(90.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 500.0f);

	// Specify a camera matrix
		// �J�����s���ݒ�
	m_CameraMatrix.LookAtLH(m_ViewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
}

//===========================================================
// �I������
//===========================================================
void CMyEffekseer::Uninit(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		m_Info[i].pos = {};
		m_Info[i].rot = {};
		m_Info[i].effect = nullptr;
		m_Info[i].efkHandle = NULL;
		m_Info[i].EfkName = {};
		m_Info[i].time = 0;
	}

	m_nNum = 0;
}

//===========================================================
// �X�V����
//===========================================================
void CMyEffekseer::Update(void)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect != nullptr)
		{
			m_Info[i].pos = m_EfkManager->GetLocation(m_Info[i].efkHandle);

			// Move the effect
			// �G�t�F�N�g�̈ړ�
			m_EfkManager->AddLocation(m_Info[i].efkHandle, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f));

			// Set layer parameters
			// ���C���[�p�����[�^�̐ݒ�
			Effekseer::Manager::LayerParameter layerParameter;
			layerParameter.ViewerPosition = m_ViewerPosition;
			m_EfkManager->SetLayerParameter(0, layerParameter);

			// Update the manager
			// �}�l�[�W���[�̍X�V
			Effekseer::Manager::UpdateParameter updateParameter;
			m_EfkManager->Update(updateParameter);

			// Update a time
			// ���Ԃ��X�V����
			m_EfkRenderer->SetTime(m_Info[i].time / 60.0f);
			m_Info[i].time++;

			// ���t���[���A�G�t�F�N�g���Đ��I�����Ă��邩�m�F����
			if (m_EfkManager->Exists(m_Info[i].efkHandle) == false)
			{
				// �V���ɃG�t�F�N�g���Đ��������B���W�̓G�t�F�N�g��\���������ꏊ��ݒ肷��
				// (�ʒu���]�A�g��k�����ݒ肵�Ȃ����K�v������)
				m_EfkManager->StopEffect(m_Info[i].efkHandle);
				Release(i);
			}
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CMyEffekseer::Draw(void)
{
	if (m_EfkRenderer != nullptr)
	{
		// Specify a projection matrix
		// ���e�s���ݒ�
		m_EfkRenderer->SetProjectionMatrix(m_ProjectionMatrix);

		CCamera* pCamera = CManager::Getinstance()->GetCamera();

		auto ViewMatrix = pCamera->GetView();
		auto Projection = pCamera->GetProjection();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_ProjectionMatrix.Values[i][j] = Projection.m[i][j];
				m_CameraMatrix.Values[i][j] = ViewMatrix.m[i][j];
			}
		}

		// Specify a camera matrix
		// �J�����s���ݒ�
		m_EfkRenderer->SetCameraMatrix(m_CameraMatrix);

		// Begin to rendering effects
		// �G�t�F�N�g�̕`��J�n�������s���B
		m_EfkRenderer->BeginRendering();

		// Render effects
		// �G�t�F�N�g�̕`����s���B
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix = m_EfkRenderer->GetCameraProjectionMatrix();
		m_EfkManager->Draw(drawParameter);

		// Finish to rendering effects
		// �G�t�F�N�g�̕`��I���������s���B
		m_EfkRenderer->EndRendering();
	}
}

//===========================================================
// �ݒ�
//===========================================================
void CMyEffekseer::Set(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale)
{
	for (int i = 0; i < MAX_EFK; i++)
	{
		if (m_Info[i].effect == nullptr)
		{
			// char16_t�ɕϊ�
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
			std::u16string string16t = converter.from_bytes(FileName);

			m_Info[i].pos = pos;
			m_Info[i].rot = rot;
			m_Info[i].scale = scale;
			m_Info[i].time = 0;

			//std::char_16
			// Load an effect
			// �G�t�F�N�g�̓Ǎ�
			m_Info[i].effect = Effekseer::Effect::Create(m_EfkManager, string16t.c_str());

			// Play an effect
			// �G�t�F�N�g�̍Đ�
			m_Info[i].efkHandle = m_EfkManager->Play(m_Info[i].effect, 0, 0, 0);

			m_Info[i].EfkName = FileName;

			// �ʒu�A�����A�傫���ݒ�
			m_EfkManager->SetLocation(m_Info[i].efkHandle, m_Info[i].pos);
			m_EfkManager->SetRotation(m_Info[i].efkHandle, {0.0f, 1.0f, 0.0f}, m_Info[i].rot.Y);
			m_EfkManager->SetScale(m_Info[i].efkHandle, m_Info[i].scale.X, m_Info[i].scale.Y, m_Info[i].scale.Z);

			break;
		}
	}
}

//===========================================================
// ���W���[���ݒ�
//===========================================================
void CMyEffekseer::SetupEffekseerModules(::Effekseer::ManagerRef efkManager)
{
	// Create a  graphics device
	// �`��f�o�C�X�̍쐬
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice;
	graphicsDevice = ::EffekseerRendererDX9::CreateGraphicsDevice(CManager::Getinstance()->GetRenderer()->GetDevice());

	// Create a renderer of effects
	// �G�t�F�N�g�̃����_���[�̍쐬
	m_EfkRenderer = ::EffekseerRendererDX9::Renderer::Create(graphicsDevice, 8000);

	// Sprcify rendering modules
	// �`�惂�W���[���̐ݒ�
	efkManager->SetSpriteRenderer(m_EfkRenderer->CreateSpriteRenderer());
	efkManager->SetRibbonRenderer(m_EfkRenderer->CreateRibbonRenderer());
	efkManager->SetRingRenderer(m_EfkRenderer->CreateRingRenderer());
	efkManager->SetTrackRenderer(m_EfkRenderer->CreateTrackRenderer());
	efkManager->SetModelRenderer(m_EfkRenderer->CreateModelRenderer());

	// Specify a texture, model, curve and material loader
	// It can be extended by yourself. It is loaded from a file on now.
	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	efkManager->SetTextureLoader(m_EfkRenderer->CreateTextureLoader());
	efkManager->SetModelLoader(m_EfkRenderer->CreateModelLoader());
	efkManager->SetMaterialLoader(m_EfkRenderer->CreateMaterialLoader());
	efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

//===========================================================
// �w�肵���z����
//===========================================================
void CMyEffekseer::Release(int idx)
{
	if (m_Info[idx].effect != nullptr)
	{
		// �l��������
		m_Info[idx].pos = {};
		m_Info[idx].rot = {};
		m_Info[idx].scale = {};
		m_Info[idx].effect = nullptr;
		m_Info[idx].efkHandle = NULL;
		m_Info[idx].EfkName = {};
		m_Info[idx].time = 0;
	}
}