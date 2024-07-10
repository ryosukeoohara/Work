//===========================================================
//
//出現演出処理[appear.h]
//Author 大原怜将
//
//===========================================================
#ifndef _APPEAR_H_             //このマクロ定義がされてなかったら
#define _APPEAR_H_             //2重インクルード防止のマクロ定義をする

#include "character.h"
#include "object.h"

//前方宣言
class CMotion;
class CEnemy;
class CChibi;
class CFoot;

//マクロ定義
#define PLAYERMOVE   (1.0f)

//プレイヤークラス
class CAppear : public CObject
{
public:
	CAppear();  //コンストラクタ
	CAppear(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CAppear();  //デストラクタ

				 //状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,                //待機
		STATE_MOVE,                   //移動
		STATE_JUMP,                   //ジャンプ
		STATE_ATTACK,                 //攻撃
		STATE_APPR,                   //出現
		STATE_MAX
	} STATE;

	//モーション
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,               //ニュートラル
		MOTIONTYPE_MOVE,                     //移動
		MOTIONTYPE_JUMP,                     //ジャンプ
		MOTIONTYPE_ATTACK,                   //攻撃
		MOTIONTYPE_APPR,                     //出現
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);        //プレイヤーの初期化処理    
	void Uninit(void);		   //プレイヤーの終了処理
	void Update(void);         //プレイヤーの更新処理
	void Draw(void);           //プレイヤーの描画処理

	static CAppear *Create(D3DXVECTOR3 pos);  //生成
											  //static CPlayer *GetPlayer(void) { return m_Player; };
	void SetState(STATE state) { m_State = state; };
	STATE GetState(void) { return m_State; };
	void ReadText(const char *fliename);       //外部ファイル読み込み
	void Hit(void);			//攻撃をくらった時の処理

	D3DXVECTOR3 GetMove(void) { return m_move; }      //移動量取得
	void SetMove(D3DXVECTOR3 move) { m_move = move; }  //移動量設定

	void SetBullet(int RestBullet) { m_RestBullet = RestBullet; }

	bool GetbAttack(void) { return m_bAttack; }

	int GetRestBullet(void) { return m_RestBullet; }

	bool GetbDisp(void) { return m_bDisp; }
	void SetbDisp(bool disp) { m_bDisp = disp; }

private:

	void Control(void);    //プレイヤーの制御
								 //D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_posOld;  //前回の位置
						   //D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_move;   //移動
	STATE m_State;
	D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
	CCharacter *m_apModel[MAX_PRATS];   //モデル(パーツ)へのポインタ
	int m_nNumModel;                    //モデル(パーツ)の総数
	int m_nIdxTexture;
	int m_nIdxShaadow;
	char m_filename[128] = {};

	CChibi *m_Chibi;
	CFoot *m_Foot;

	//PLAYER m_Player[2];

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	int m_nCntInvincible;                //無敵時間
	int m_nIdx;
	int m_nParent;
	int m_nLoop;
	int m_nFrame;                        //モーションのフレーム数
	int m_nCntColi;                       //攻撃判定が出ている時間
	int m_nCntEff;                        //エフェクトをだすカウント
	int m_nCntDuration;               //連撃できる時間
	int m_nCntDie;                       //倒れるまでの時間
	int m_nCntSound;                     //サウンドが鳴って再度鳴るまでの時間
	int m_nNumMotion;
	int m_nCntMotion;
	int m_nCnterMotion;
	int m_nNumkey;
	int m_nLifeGage;
	int m_RestBullet;                    //残弾数
	int m_ApprCharcter;
	float m_fDiff;
	float m_fDest;
	bool m_bDash;                        //走っているかどうか
	bool m_bJump;                        //ジャンプしているかどうか
	bool m_bAction;		                 //攻撃したかどうか
	bool m_bDisp;                        //描画するかどうか
	bool m_bAppr;                        //出現しているかどうか
	bool m_bEncounter;                   //戦闘しているかどうか
	bool m_bIconDisp;                    //アイコンを作ったか
	bool m_bAcFir;                       //連撃中
	bool m_bAcSec;                       //連撃中
	bool m_bAcThr;                       //連劇中
	D3DXVECTOR3 m_posOrigin;
	CMotion *m_motion;                   //モーションへのポインタ

										 //チュートリアルで使う関数,変数
	void ControlTutorial(void);          //チュートリアルのプレイヤーの制御
	bool m_bPushW;                       //Wキーを押した
	bool m_bPushA;                       //Aキーを押した
	bool m_bPushS;                       //Sキーを押した
	bool m_bPushD;                       //Dキーを押した
	bool m_bAttack;                      //攻撃をした
	bool m_bAvoi;                        //回避した
	bool m_bWhee;                        //ホイールを回転した
};

#endif