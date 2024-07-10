//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド情報の構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDINFO;

//サウンドクラス
class CSound
{
public:
	CSound();
	~CSound();

	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,
		SOUND_LABEL_BGM001,
		SOUND_LABEL_BGM002,
		SOUND_LABEL_BGM003,
		SOUND_LABEL_SESWORD,
		SOUND_LABEL_SELOOSER,
		SOUND_LABEL_SEJUMP00,
		SOUND_LABEL_SEJUMP01,
		SOUND_LABEL_SEASIOTO,
		SOUND_LABEL_SEMAGIC,
		SOUND_LABEL_SEMAGICPOWER,
		SOUND_LABEL_CHANGE,
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
	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{ "data/SOUND/BGM/game.wav", -1 },     //ゲームのBGM
		{ "data/SOUND/BGM/result.wav", -1 },   //リザルトのBGM
		{ "data/SOUND/BGM/title.wav", -1 },    //タイトルのBGM
		{ "data/SOUND/BGM/tutorial.wav", -1 }, //チュートリアルのBGM
		{ "data/SOUND/SE/swing.wav", 0 },    //刀で切る音
		{ "data/SOUND/SE/looser.wav", 0 },     //倒れる音
		{ "data/SOUND/SE/jump000.wav", 0 },       //ジャンプ
		{ "data/SOUND/SE/jump001.wav", 0 },       //ジャンプ
		{ "data/SOUND/SE/asioto.wav", 0 },     //足音
		{ "data/SOUND/SE/magic.wav", 0 },     //魔法
		{ "data/SOUND/SE/magicpower.wav", 0 },     //魔力をためる
		{ "data/SOUND/SE/change.wav", 0 },     //キャラチェン
	}; 

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};

#endif