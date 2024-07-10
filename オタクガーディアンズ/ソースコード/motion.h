//===========================================================
//
//モーション処理[motion.h]
//Author 大原怜将
//
//===========================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "objectX.h"
#include "character.h"

//マクロ定義
#define MAX_INFO   (64)

//モーションクラス
class CMotion
{
public:
	CMotion();
	~CMotion();

	//モデル---------------------------------------------------------------
	typedef struct
	{
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_rot;

	} KEY;

	//モデル---------------------------------------------------------------
	typedef struct
	{
		KEY m_aKey[MAX_INFO];  //現在のキー
		int m_nFrame;   //モーションのフレーム数

	} KEYINFO;

	//モーション---------------------------------------------------------------
	typedef struct
	{
		int m_nNumKey;  //キーの総数
		int m_nLoop;    //ループするかどうか
		bool m_bLoop;   //ループするかどうか
		bool m_bFinish; //終了したかどうか

		KEYINFO m_KeySet[MAX_INFO];
		
	} INFO;

	//モデル---------------------------------------------------------------
	typedef struct
	{
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_rot;

	} OLDKEY;

	//モデル---------------------------------------------------------------
	typedef struct
	{
		OLDKEY m_aKey[MAX_INFO];  //現在のキー
		int m_nFrame;   //モーションのフレーム数

	} OLDKEYINFO;

	//モーション---------------------------------------------------------------
	typedef struct
	{
		int m_nNumKey;  //キーの総数
		int m_nLoop;    //ループするかどうか
		bool m_bLoop;   //ループするかどうか
		bool m_bFinish; //終了したかどうか

		OLDKEYINFO m_KeySet[MAX_INFO];

	} OLDINFO;

	//モーション---------------------------------------------------------------
	/*typedef struct
	{
		INFO m_aInfo[9];

	} Obj;*/

	void Init(void);
	void Uninit(void);
	void Update(void);

	void Set(int nType);
	int GetType(void);
	bool IsFinish(void);
	void SetInfo(INFO info);
	void SetModel(CCharacter **ppModel, int nNumModel);
	CCharacter **GetModel(void) { return m_ppModel; }
	void ReadText(const char *TextFilename);        //外部ファイル読み込み
	int GetNumFrame(void) { return m_nNumFrame; }   //モーションの総フレーム

private:
	//Obj m_aObj[9];
	INFO m_aInfo[MAX_INFO];
	INFO m_aOldInfo;
	int  m_nNumAll;              //モーションの総数
	int  m_nType;                //モーションの種類
	int m_nTypeold;              //前回のモーションの種類
	bool m_bLoop;                //ループするかどうか
	int  m_nNumKey;              //キーの総数
	int  m_nKey;                 //現在のキー
	int  m_nCounter;             //フレーム数に達したか
	int  m_nCntkeySet;
	int m_nNumFrame;             //モーションのフレーム数
	bool m_bFinish;              //終了したかどうか
	
	CCharacter **m_ppModel;  //モデルへのダブルポインタ
	int m_nNumModel;         //モデルの総数
	static int m_nObj;       //誰のモーションか
};

#endif // !_MOTION_H_

