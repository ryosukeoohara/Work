//===========================================================
//
//ポリゴンを出すやつ[enemy.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ENEMYWEAK_H_             //このマクロ定義がされてなかったら
#define _ENEMYWEAK_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"
#include "objectX.h"
#include "character.h"
#include "enemy.h"

//前方宣言
class CMotion;
class CEnemy;

//マクロ定義
#define ENEMYMOVE    (2.0f)
#define MAX_PATROL   (16)  //巡回できる地点の最大数

//敵クラス
class CEnemyWeak : public CEnemy
{
public:
	CEnemyWeak();  //コンストラクタ
	CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //コンストラクタ(オーバーロード)
	~CEnemyWeak();  //デストラクタ

	//モーション
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //ニュートラル
		MOTIONTYPE_MOVE,             //移動
		MOTIONTYPE_ACTION,           //攻撃
		MOTIONTYPE_ACTIONNEUTRAL,    //攻撃待機
		MOTIONTYPE_DAMEGE,           //ダメージ
		MOTIONTYPE_DEATH,            //死亡
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CEnemyWeak *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //生成
												 
	void ReadText(char *Filename);  //外部ファイル読み込み
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);
	//static void SetType(TYPE type) { m_type = type; }

	void Control(void);  //敵の動き
	void Death(int nCntEnemy);    //死んだとき

	void SetState(STATE state) { m_state = state; }  //状態設定
	STATE GetState(void) { return m_state; }  //状態取得

protected:
	static CEnemyWeak *m_EnemyWeak[128];
	

private:

	static TYPE m_type;

	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //巡回する地点の数
	int m_nCurrentpos;     //現在どこの巡回地点にいるか
	int m_nCntAction;      //攻撃してから再び攻撃するまでの時間
	int m_nCntDeath;       //死亡してから消滅するまでの時間
	int m_DeathEnemyIdx;   //死亡した敵の番号
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //プレイヤーを追尾するかどうか
	bool m_bAction;        //攻撃したかどうか
};

//敵クラス(近距離)
class CEnemyNear : public CEnemyWeak
{
public:
	CEnemyNear();                 //コンストラクタ
	CEnemyNear(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //コンストラクタ(オーバーロード)
	~CEnemyNear();                //デストラクタ

	////状態
	//enum STATE
	//{
	//	TATE_NONE = 0,             //ニュートラル
	//	TATE_MOVE,                 //移動
	//	TATE_ACTION,               //攻撃
	//	TATE_ACTIONNEUTRAL,        //攻撃ニュートラル
	//	TATE_DAMEGE,               //ダメージ受け
	//	TATE_STAGGER,              //よろけ
	//	TATE_DEATH,                //死亡
	//	TATE_MAX
	//};

	//モーション
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //ニュートラル
		MOTIONTYPE_MOVE,             //移動
		MOTIONTYPE_ACTION,           //攻撃
		MOTIONTYPE_RUSH,             //突撃攻撃
		MOTIONTYPE_ACTIONNEUTRAL,    //攻撃待機
		MOTIONTYPE_DAMEGE,           //ダメージ
		MOTIONTYPE_DEATH,            //死亡
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CEnemyNear *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //生成

	void ReadText(char *Filename);  //外部ファイル読み込み
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);

	void Control(void);           //敵の動き
	void Death(int nCntEnemy);    //死んだとき

	void SetState(STATE state) { m_state = state; }  //状態設定
	STATE GetState(void) { return m_state; }  //状態取得



private:

	//static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	//CCharacter *m_apModel[128];                  //モデル(パーツ)へのポインタ
	//CMotion *m_motion;                           //モーションへのポインタ
	//D3DXVECTOR3 m_pos;                           //位置
	//D3DXVECTOR3 m_move;                          //移動
	//D3DXVECTOR3 m_rot;                           //向き

	//D3DXVECTOR3 m_Readpos;
	//D3DXVECTOR3 m_Readrot;
	//static CEnemyWeak *m_EnemyWeak[128];
	//static int m_nNumAll;  //ざこ敵の総数

	//STATE m_state;  //状態

	//int m_nNumModel;  //モデルの総数
	//int m_nIdxTexture;
	//D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	//char m_filename[128] = {};

	TYPE m_type;
	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //巡回する地点の数
	int m_nCurrentpos;     //現在どこの巡回地点にいるか
	int m_nCntAction;      //攻撃してから再び攻撃するまでの時間
	int m_nCntDeath;       //死亡してから消滅するまでの時間
	int m_DeathEnemyIdx;   //死亡した敵の番号
	int m_nCntRush;          //突進攻撃をしてくるまでのカウント
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //プレイヤーを追尾するかどうか
	bool m_bAction;        //攻撃したかどうか
};

//敵クラス(近距離)
class CEnemyFar : public CEnemyWeak
{
public:
	CEnemyFar();                 //コンストラクタ
	CEnemyFar(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //コンストラクタ(オーバーロード)
	~CEnemyFar();                //デストラクタ

	////状態------------------------------------------------------------------
	//enum STATE
	//{
	//	TATE_NONE = 0,             //ニュートラル
	//	TATE_MOVE,                 //移動
	//	TATE_ACTION,               //攻撃
	//	TATE_ACTIONNEUTRAL,        //攻撃ニュートラル
	//	TATE_DAMEGE,               //ダメージ受け
	//	TATE_STAGGER,              //よろけ
	//	TATE_DEATH,                //死亡
	//	TATE_MAX
	//};

	//モーション-------------------------------------------------------------
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //ニュートラル
		MOTIONTYPE_MOVE,             //移動
		MOTIONTYPE_ACTION,           //攻撃
		MOTIONTYPE_ACTIONNEUTRAL,    //攻撃待機
		MOTIONTYPE_REROAD,           //爆弾をポッケから取り出す
		MOTIONTYPE_DAMEGE,           //ダメージ
		MOTIONTYPE_DEATH,            //死亡
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CEnemyFar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //生成

	void ReadText(char *Filename);  //外部ファイル読み込み
	static CEnemyWeak **GetEnemy(void) { return &m_EnemyWeak[0]; };
	static CEnemyWeak *SetEnemy(CEnemyWeak *pEnemy) {  };
	static void UninitWeak(void);

	void Control(void);  //敵の動き
	void Death(int nCntEnemy);    //死んだとき

	void SetState(STATE state) { m_state = state; }  //状態設定
	STATE GetState(void) { return m_state; }  //状態取得

private:

	TYPE m_type;
	int m_nIdx;
	int m_nParent;
	int m_nNumPatrol;      //巡回する地点の数
	int m_nCurrentpos;     //現在どこの巡回地点にいるか
	int m_nCntAction;      //攻撃してから再び攻撃するまでの時間
	int m_nCntDeath;       //死亡してから消滅するまでの時間
	int m_DeathEnemyIdx;   //死亡した敵の番号
	int m_nCntReload;      //リロードするまでのカウント
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;       //プレイヤーを追尾するかどうか
	bool m_bAction;        //攻撃したかどうか
	bool m_bBom;           //爆弾をポッケから取り出す
};

#endif