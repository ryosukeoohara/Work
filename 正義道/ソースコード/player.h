//===========================================================
//
//ポリゴンを出すやつ[player.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PLAYER_H_             //このマクロ定義がされてなかったら
#define _PLAYER_H_             //2重インクルード防止のマクロ定義をする

#include "object3D.h"
#include "objectX.h"
#include "character.h"
#include "shadow.h"

//前方宣言
class CMotion;
class CEnemy;

//マクロ定義
#define PLAYERMOVE   (1.0f)



//プレイヤークラス
class CPlayer : public CObject
{
public:
	CPlayer();  //コンストラクタ
	CPlayer(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CPlayer();  //デストラクタ

	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,                //待機
		STATE_DAMEGE,                 //ダメージ
		STATE_MOVE,                   //移動
		STATE_STAGGER,                //くらい
		STATE_AVOI,                   //回避
		STATE_ACTION,                 //攻撃(近距離)
		STATE_ACTIONNEUTAL,           //攻撃待機(近距離)
		STATE_SNPSTAN,                //攻撃回避(遠距離) 
		STATE_SNP,                    //攻撃(遠距離)
		STATE_KNIFESTAN,              //攻撃待機(ナイフ)
		STATE_KNIFEAC,                //攻撃(ナイフ)
		STATE_CONSECAC,               //連撃
		STATE_CONSECACSEC,            //連撃二撃
		STATE_CONSECACTHI,            //連撃三撃
		STATE_DEATH,                  //死んだ
		STATE_END,                    //終了
		STATE_TUTOMOVE,               //チュートリアルの移動
		STATE_MAX
	} STATE;

	//モーション
	typedef enum
	{
		MOTIONTYPE_NONE = 0,                 //なし
		MOTIONTYPE_MOVE,                     //移動
		MOTIONTYPE_ACTION,                   //攻撃
		MOTIONTYPE_ACTIONNEUTAL,             //ニュートラル
		MOTIONTYPE_SNPSTAN,                  //射撃待ち
		MOTIONTYPE_SNP,                      //射撃
		MOTIONTYPE_KNIFESTAN,                //ナイフ構え
		MOTIONTYPE_KNIFEAC,                  //ナイフで攻撃
		MOTIONTYPE_ACFRIST,                  //攻撃の一段目
		MOTIONTYPE_ACSECOND,                 //攻撃の二段目
		MOTIONTYPE_ACTHIRD,                  //攻撃の三段目
		MOTIONTYPE_DAMEGE,                   //くらいモーション
		MOTIONTYPE_AVOI,                     //回避
		MOTIONTYPE_BATNEUTAL,                //バットを持っているときのニュートラル
		MOTIONTYPE_BATMOVE,                  //バットを持っているときの移動
		MOTIONTYPE_BATACTION,                //バットを持っているときの攻撃
		MOTIONTYPE_DEATH,                    //死亡
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	//攻撃方法
	enum ACTIONTYPE
	{ 
		ACTIONTYPE_NEAR = 0,     //ナイフ
		ACTIONTYPE_FAR,          //銃    
		ACTIONTYPE_BAT,          //バット
		ACTIONTYPE_MAX
	};

	//チュートリアルの状態
	enum TUTOSTATE
	{
		TUTOSTATE_NONE = 0,
		TUTOSTATE_MOVE,
		TUTOSTATE_STOP,
		TUTOSTATE_MAX
	};


	HRESULT Init(void);      //プレイヤーの初期化処理    
	void Uninit(void);       //プレイヤーの終了処理
	void Update(void);       //プレイヤーの更新処理
	void Draw(void);         //プレイヤーの描画処理

	static CPlayer *Create(D3DXVECTOR3 pos);  //生成
	//static CPlayer *GetPlayer(void) { return m_Player; };
	void SetState(STATE state) { m_State = state; };
	STATE GetState(void) { return m_State; };
	void ReadText(void);  //外部ファイル読み込み
	void Hit(void);       //攻撃をくらった時の処理
	void CollsionENEMY(CEnemy *pEnemy);  //敵との当たり判定

	D3DXVECTOR3 GetMove(void) { return m_move; }      //移動量取得
	void SetMove(D3DXVECTOR3 move) {m_move = move; }  //移動量設定

	void SetBullet(int RestBullet) { m_RestBullet = RestBullet; }

	TUTOSTATE GetTutostate(void) { return m_Tutostate; }
	void SetTutostate(TUTOSTATE state) { m_Tutostate = state; }

	bool GetbAttack(void) { return m_bAttack; }

	int GetRestBullet(void) { return m_RestBullet; }
	
private:

	void ControlPlayer(void);    //プレイヤーの制御
	//D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_posOld;  //前回の位置
	//D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_move;   //移動
	STATE m_State;
	TUTOSTATE m_Tutostate;
	ACTIONTYPE m_AcType;
	D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
	CCharacter *m_apModel[MAX_PRATS];   //モデル(パーツ)へのポインタ
	int m_nNumModel;                    //モデル(パーツ)の総数
	int m_nIdxTexture;
	int m_nIdxShaadow;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	int m_nCntInvincible;                //無敵時間
	int m_nIdx;				             
	int m_nParent;			             
	int m_nLoop;			             
	int m_nFrame;                        //モーションのフレーム数
	int m_nCntColi;                      //攻撃判定が出ている時間
	int m_nCntEff;                       //エフェクトをだすカウント
	int m_nCntDuration;                  //連撃できる時間
	int m_nCntDie;                       //倒れるまでの時間
	int m_nCntSound;                     //サウンドが鳴って再度鳴るまでの時間
	int m_nNumMotion;		             
	int m_nCntMotion;		             
	int m_nCnterMotion;		             
	int m_nNumkey;			             
	int m_nLifeGage;		             
	int m_RestBullet;                    //残弾数
	float m_fDiff;			             
	float m_fDest;			             
	bool m_bDash;                        //走っているかどうか
	bool m_bAction;		                 
	bool m_bEncounter;                   //戦闘しているかどうか
	bool m_bIconDisp;                    //アイコンを作ったか
	bool m_bAcFir;                       //連撃中
	bool m_bAcSec;                       //連撃中
	bool m_bAcThr;                       //連劇中
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_motion;                   //モーションへのポインタ
	CShadow *m_pShadow;                  //影へのポインタ

	//チュートリアルで使う関数,変数
	void ControlTutorial(void);          //チュートリアルのプレイヤーの制御
	bool m_bPushW;                       //Wキーを押した
	bool m_bPushA;                       //Aキーを押した
	bool m_bPushS;                       //Sキーを押した
	bool m_bPushD;                       //Dキーを押した
	bool m_bAttack;                      //攻撃をした
	bool m_bAvoi;                        //回避した
	bool m_bWhee;                       //ホイールを回転した
};

#endif