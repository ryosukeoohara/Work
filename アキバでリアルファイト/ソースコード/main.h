//===========================================================
//
//�|���S�����o�����[main.h]
//Author �匴�叫
//
//===========================================================
#ifndef _MAIN_H_     //���̃}�N������`����ĂȂ�������
#define _MAIN_H_     //2�d�C���N���[�h��h�~�̃}�N�����`����

namespace
{
	const char *CLASS_NAME = "windowclass";  // �E�C���h�E�N���X�̖��O
	const int SCREEN_WIDTH = 1280;                   //�E�C���h�E�ɕ�
	const int SCREEN_HEIGHT = 720;                   //�E�C���h�E�̍���
	const int FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	const int FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
}

// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;   // �ʒu
	float rhw;
	D3DCOLOR col;      // �F
	D3DXVECTOR2 tex;   // �e�N�X�`���̍��W
} VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;    // �ʒu
	D3DXVECTOR3 nor;    // �@���x�N�g��
	D3DCOLOR col;       // �F
	D3DXVECTOR2 tex;    // �e�N�X�`�����W
} VERTEX_3D;


#ifndef _DEBUG
#pragma comment(lib, "Effekseer.lib")
#else
#pragma comment(lib, "Effekseerd.lib")
#endif
#include <Effekseer.h>

#ifndef _DEBUG
#pragma comment(lib, "EffekseerRendererDX9.lib")
#else
#pragma comment(lib, "EffekseerRendererDX9d.lib")
#endif
#include <EffekseerRendererDX9.h>

#endif