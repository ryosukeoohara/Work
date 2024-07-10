//===========================================================
//
//プレイヤー処理[player.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PLAYER_H_             //このマクロ定義がされてなかったら
#define _PLAYER_H_             //2重インクルード防止のマクロ定義をする

//*==========================================================
//インクルードファイル
//*==========================================================
#include "character.h"
#include "object.h"

//*==========================================================
//前方宣言
//*==========================================================
class CMotion;
class CEnemy;
class CChibi;
class CFoot;

//*==========================================================
//プレイヤークラス
//*==========================================================
class CPlayer : public CObject
{
public:
	CPlayer();  //コンストラクタ
	CPlayer(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CPlayer();  //デストラクタ

	HRESULT Init(void);        //プレイヤーの初期化処理    
	void Uninit(void);		   //プレイヤーの終了処理
	void Update(void);         //プレイヤーの更新処理
	void Draw(void);           //プレイヤーの描画処理

	static CPlayer *Create(D3DXVECTOR3 pos);  //生成
	//static CPlayer *GetPlayer(void) { return m_Player; };
	
	void ReadText(const char *fliename);       //外部ファイル読み込み
	void Hit(void);			//攻撃をくらった時の処理

	D3DXVECTOR3 GetMove(void) { return m_move; }       //移動量取得
	void SetMove(D3DXVECTOR3 move) { m_move = move; }  //移動量設定

	void SetBullet(int RestBullet) { m_RestBullet = RestBullet; }

	bool GetbAttack(void) { return m_bAttack; }

	int GetRestBullet(void) { return m_RestBullet; }

protected:
	//CMotion *m_motion;                   //モーションへのポインタ
	//CCharacter *m_apModel[MAX_PRATS];   //モデル(パーツ)へのポインタ
	int m_ApprCharcter;
	
private:

	void ControlPlayer(void);    //プレイヤーの制御
	void Appear(void);           //出現処理
	D3DXVECTOR3 m_posOld;  //前回の位置
	D3DXVECTOR3 m_move;    //移動
	D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
	
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
	float m_fDiff;			             
	float m_fDest;			             
	bool m_bDash;                        //走っているかどうか
	bool m_bJump;                        //ジャンプしているかどうか
	bool m_bAction;		                 //攻撃したかどうか
	bool m_bAppr;                        //出現しているかどうか
	bool m_bEncounter;                   //戦闘しているかどうか
	bool m_bIconDisp;                    //アイコンを作ったか
	bool m_bAcFir;                       //連撃中
	bool m_bAcSec;                       //連撃中
	bool m_bAcThr;                       //連劇中
	
	D3DXVECTOR3 m_posOrigin;             
	//CMotion *m_motion;                   //モーションへのポインタ

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

//*==========================================================
//チビデブ
//*==========================================================
class CChibi : public CPlayer
{
public:

	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,                //待機
		STATE_MOVE,                   //移動
		STATE_JUMP,                   //ジャンプ
		STATE_ATTACK,                 //攻撃
		STATE_APPR,                   //出現
		STATE_DAMAGE,                 //ダメージ
		STATE_DEATH,                  //死亡
		STATE_TITLE,                  //タイトル
		STATE_RELOAD,                 //リロード
		STATE_MAX
	} STATE;

	//タイトルの状態
	enum TITLE_STATE
	{
		TITLE_STATE_NONE = 0,          //なんもない
		TITLE_STATE_NEUTRAL,           //待機
		TITLE_STATE_MOVE,              //移動
		TITLE_STATE_MAX
	};

	//モーション
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,              //ニュートラル
		MOTIONTYPE_MOVE,                     //移動
		MOTIONTYPE_JUMP,                     //ジャンプ
		MOTIONTYPE_ATTACK,                   //攻撃
		MOTIONTYPE_APPR,                     //出現
		MOTIONTYPE_TITLE,                    //タイトル
		MOTIONTYPE_RELOAD,                   //リロード
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	CChibi();  //コンストラクタ
	CChibi(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CChibi();  //デストラクタ

	HRESULT Init(void);        //プレイヤーの初期化処理    
	void Uninit(void);		   //プレイヤーの終了処理
	void Update(void);         //プレイヤーの更新処理
	void Draw(void);           //プレイヤーの描画処理

	static CChibi *Create(D3DXVECTOR3 pos);  //生成

	void SetState(STATE state) { m_State = state; };
	STATE GetState(void) { return m_State; };

	void SetTState(TITLE_STATE state) { m_TitleState = state; };

	bool GetbDisp(void) { return m_bDisp; }
	void SetbDisp(bool disp) { m_bDisp = disp; }

	bool GetbAppr(void) { return m_bAppr; }
	void SetbAppr(bool appr) { m_bAppr = appr; }

	void SetMoveY(float move) { m_move.y = move; }
	float GetMoveY(void) { return m_move.y; }

	void SetbJump(bool bjump) { m_bJump = bjump; }

	void SetbRand(bool brand) { m_bRand = brand; }
	bool GetbRand(void) { return m_bRand; }

	void SetLife(int nLife) { m_nLife = nLife; }  //体力の設定
	int GetLife(void) { return m_nLife; }		  //体力を取得

	void Hit(void);

	int GetRestBullet(void) { return m_RestBullet; }

	void Control(void);    //プレイヤーの制御

protected:
	
private:
	void ReadText(const char *fliename);       //外部ファイル読み込み
	STATE m_State;                             //状態
	TITLE_STATE m_TitleState;                  //タイトルの状態
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_posOld;  //前回の位置
						   //D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_move;   //移動
	D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
	CCharacter *m_apModel[MAX_PRATS];   //モデル(パーツ)へのポインタ
	CMotion *m_motion;                  //モーションへのポインタ
	int m_nLife;                        //体力
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
	int m_nCntBullet;                    //弾の出る間隔
	int m_nCntDamage;                    //ダメージ状態になっているカウント
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
	bool m_WaitApper;                    //出現待ち状態
	bool m_bRand;                        //地面に着地しているかどうか
	bool m_bDamage;                      //ダメージを受けた
	D3DXVECTOR3 m_posOrigin;

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

//*==========================================================
//クソデブ
//*==========================================================
class CFoot : public CPlayer
{
public:

	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,                //待機
		STATE_MOVE,                   //移動
		STATE_JUMP,                   //ジャンプ
		STATE_ATTACK,                 //攻撃
		STATE_APPR,                   //出現
		STATE_DAMAGE,                 //ダメージ
		STATE_DEATH,                  //死亡
		STATE_TITLE,                  //タイトル
		STATE_MAX
	} STATE;

	//タイトルの状態
	enum TITLE_STATE
	{
		TITLE_STATE_NONE = 0,          //なんもない
		TITLE_STATE_NEUTRAL,           //待機
		TITLE_STATE_MOVE,              //移動
		TITLE_STATE_MAX
	};

	//モーション
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,              //ニュートラル
		MOTIONTYPE_MOVE,                     //移動
		MOTIONTYPE_JUMP,                     //ジャンプ
		MOTIONTYPE_ATTACK,                   //攻撃
		MOTIONTYPE_APPR,                     //出現
		MOTIONTYPE_TITLE,                    //タイトル
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	CFoot();  //コンストラクタ
	CFoot(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CFoot();  //デストラクタ

	HRESULT Init(void);        //プレイヤーの初期化処理    
	void Uninit(void);		   //プレイヤーの終了処理
	void Update(void);         //プレイヤーの更新処理
	void Draw(void);           //プレイヤーの描画処理

	static CFoot *Create(D3DXVECTOR3 pos);  //生成

	void SetState(STATE state) { m_State = state; };
	STATE GetState(void) { return m_State; };

	void SetTState(TITLE_STATE state) { m_TitleState = state; };
	//TITLE_STATE GetState(void) { return m_TitleState; };

	bool GetbDisp(void) { return m_bDisp; }
	void SetbDisp(bool disp) { m_bDisp = disp; }

	bool GetbAppr(void) { return m_bAppr; }
	void SetbAppr(bool appr) { m_bAppr = appr; }

	void SetMoveY(float move) { m_move.y = move; }
	float GetMoveY(void) { return m_move.y; }

	void SetbJump(bool bjump) { m_bJump = bjump; }

	void SetbRand(bool brand) { m_bRand = brand; }
	bool GetbRand(void) { return m_bRand; }

	void SetLife(int nLife) { m_nLife = nLife; }  //体力の設定
	int GetLife(void) { return m_nLife; }		  //体力を取得

	void Hit(void);

	void Control(void);    //プレイヤーの制御

protected:
	
private:
	void ReadText(const char *fliename);       //外部ファイル読み込み
	STATE m_State;
	TITLE_STATE m_TitleState;                  //タイトルの状態
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_posOld;  //前回の位置
						   //D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_move;   //移動
	D3DXMATRIX m_mtxWorld;              //ワールドマトリックス
	CCharacter *m_apModel[MAX_PRATS];   //モデル(パーツ)へのポインタ
	CMotion *m_motion;                  //モーションへのポインタ
	int m_nLife;                        //体力
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
	int m_nCntEff;                        //エフェクトをだすカウント
	int m_nCntDuration;                  //連撃できる時間
	int m_nCntDie;                       //倒れるまでの時間
	int m_nCntSound;                     //サウンドが鳴って再度鳴るまでの時間
	int m_nNumMotion;
	int m_nCntMotion;
	int m_nCnterMotion;
	int m_nNumkey;
	int m_nCntDamage;                    //ダメージ状態になっているカウント
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
	bool m_WaitApper;                    //出現待ち状態
	bool m_bRand;                        //地面に着地しているかどうか
	bool m_bDamage;                      //ダメージを受けた
	D3DXVECTOR3 m_posOrigin;
	//CMotion *m_motion;                   //モーションへのポインタ

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