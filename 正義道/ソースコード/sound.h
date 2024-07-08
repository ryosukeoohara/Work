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
		SOUND_LABEL_SE00,
		SOUND_LABEL_SE01,
		SOUND_LABEL_SE02,
		SOUND_LABEL_SE03,
		SOUND_LABEL_SE04,
		SOUND_LABEL_SE05,
		SOUND_LABEL_SE06,
		SOUND_LABEL_SE07,
		SOUND_LABEL_SE08,
		SOUND_LABEL_SE09,
		SOUND_LABEL_SE10,
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
		{ "data/SOUND/SE/sword00.wav", 0 },    //刀で切る音
		{ "data/SOUND/SE/sword01.wav", 0 },    //撃つ音
		{ "data/SOUND/SE/shot00.wav", 0 },     //
		{ "data/SOUND/SE/shot01.wav", 0 },     //撃つ音
		{ "data/SOUND/SE/nobullet.wav", 0 },   //玉切れ
		{ "data/SOUND/SE/looser.wav", 0 },     //倒れる音
		{ "data/SOUND/SE/bom.wav", 0 },        //爆発音
		{ "data/SOUND/SE/swing.wav", 0 },      //バットを振る音
		{ "data/SOUND/SE/jump.wav", 0 },       //ジャンプ
		{ "data/SOUND/SE/asioto.wav", 0 },     //足音
		{ "data/SOUND/SE/avoi.wav", 0 },       //回避
	}; 

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};

#endif
