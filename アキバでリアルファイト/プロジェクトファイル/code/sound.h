//===========================================================
//
// �T�E���h���� [sound.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "main.h"

//===========================================================
// �T�E���h���̍\���̒�`
//===========================================================
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDINFO;

//===========================================================
// �T�E���h�N���X��`
//===========================================================
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_GAME,
		SOUND_LABEL_BGM_RESULT,
		SOUND_LABEL_SE_PUNCH,
		SOUND_LABEL_SE_MOVE,
		SOUND_LABEL_SE_IMPACT,
		SOUND_LABEL_SE_GRASS,
		SOUND_LABEL_SE_FIRE,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },
		{ "data/SOUND/BGM/tutorial.wav", -1 },
		{ "data/SOUND/BGM/game.wav", -1 },
		{ "data/SOUND/BGM/result.wav", -1 },
		{ "data/SOUND/SE/punch.wav", 0 },
		{ "data/SOUND/SE/asioto.wav", 0 },
		{ "data/SOUND/SE/impact.wav", 0 },
		{ "data/SOUND/SE/grass.wav", 0 },
		{ "data/SOUND/SE/fire1.wav", 0 },
	}; 

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif