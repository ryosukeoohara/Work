//===========================================================
//
// モーション処理[motion.h]
// Author 大原怜将
//
//===========================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//===========================================================
// インクルードファイル
//===========================================================
#include "objectX.h"

//マクロ定義
#define MAX_INFO   (64)

//===========================================================
// 前方宣言
//===========================================================
class CCharacter;

//===========================================================
// モーションクラス定義
//===========================================================
class CMotion
{
private:

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
		int m_nNumKey;    // キーの総数
		int m_nLoop;      // ループするかどうか
		int m_nNumFrame;  // フレームの総数
		int m_nAttackOccurs;  // 攻撃判定発生フレーム
		int m_nAttackEnd;  // 攻撃判定終了フレーム
		int m_nAttackDamege;  // 攻撃力
		int m_nInvincibleStart;  // 完全無敵状態開始
		int m_nInvincibleEnd;    // 完全無敵終了
		int nCancellFrame;   // キャンセル可能フレーム
		int nCancellFrameEnd;  // キャンセル可能フレーム
		float m_nKnockBack;      // 吹っ飛び
		bool m_bLoop;     // ループするかどうか
		bool m_bFinish;   // 終了したかどうか

		KEYINFO m_KeySet[MAX_INFO];

	} INFO;

public:
	CMotion();
	~CMotion();

	void Init(void);
	void Uninit(void);
	void Update(void);

	bool IsFinish(void);
	
	// 読み込み系
	void ReadText(const char *TextFilename);            // 外部ファイル読み込み
	
	// 設定系
	void Set(int nType);                                // モーション
	void SetInfo(void);                                 // 情報
	void SetModel(CCharacter **ppModel, int nNumModel); // キャラクターのモデル

	// 取得系
	int GetType(void);                                  // 種類
	int GetNumFrame(void) { return m_nNowFrame; }   // モーションの総フレーム
	int GetNowFrame(void);
	int GetAttackOccurs(void);
	int GetAttackEnd(void);
	int GetAttackDamege(void);
	int GetInvincibleStrat(void);
	int GetInvincibleEnd(void);
	int GetCancellFrame(void);
	int GetCancellFrameEnd(void);
	float GetKnockBack(void);
	INFO GetInfo(void);

private:

	void RotCorrect(float rot);

	INFO m_aInfo[MAX_INFO];
	KEY m_aOldInfo[MAX_INFO];
	int  m_nNumAll;              //モーションの総数
	int  m_nType;                //モーションの種類
	int m_nTypeold;              //前回のモーションの種類
	bool m_bLoop;                //ループするかどうか
	int  m_nNumKey;              //キーの総数
	int  m_nKey;                 //現在のキー
	int  m_nCounter;             //フレーム数に達したか
	int  m_nCntkeySet;
	int m_nNumFrame;             //モーションのフレーム数
	int m_nNowFrame;
	bool m_bFinish;              //終了したかどうか
	
	CCharacter **m_ppModel;  //モデルへのダブルポインタ
	int m_nNumModel;         //モデルの総数
	static int m_nObj;       //誰のモーションか
};

#endif