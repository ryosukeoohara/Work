//===========================================================
//
// �v���R���p�C��[precompile.h]
// Author �匴�叫
//
//===========================================================
#ifndef _PRECOMPILE_H_
#define _PRECOMPILE_H_

#define DIRECTINPUT_VERSION (0x0800)               //�r���g���̌x���Ώ��p�}�N��

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "d3dx9.h"
#include "dinput.h"  //���͏����ɕK�v
#include "xaudio2.h" //�T�E���h�����ɕK�v   

//===========================================================
// ���C�u���������N
//===========================================================
#pragma comment(lib,"d3d9.lib")                    // �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")                   // [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")                  // Direct�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")                   // �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")                 // ���͏����ɕK�v

#endif