//===========================================================
//
//ポリゴンを出すやつ[enemy.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ENEMYMEDBOSS_H_             //このマクロ定義がされてなかったら
#define _ENEMYMEDBOSS_H_             //2重インクルード防止のマクロ定義をする

#include "object2D.h"
#include "objectX.h"
#include "character.h"
#include "enemy.h"

//前方宣言
class CMotion;
class CEnemy;

//マクロ定義
#define ENEMYMOVE   (2.0f)
#define MAX_PATROL   (16)  //巡回できる地点の最大数

//敵クラス
class CEnemyMedBoss : public CEnemy
{
public:

	enum TYPEENE
	{
		TYPE_NONE = 0,
		TYPE_001,
		TYPE_002,
		TYPE_003,
		TYPE_MAX
	};

	CEnemyMedBoss();  //コンストラクタ
	CEnemyMedBoss(D3DXVECTOR3 pos, TYPEENE type);  //コンストラクタ(オーバーロード)
	~CEnemyMedBoss();  //デストラクタ

	enum ATTACKTYPE
	{
		ATTACKTYPE_NONE = 0,    //通常攻撃
		ATTACKTYPE_JUMP,        //ジャンプ攻撃
		ATTACKTYPE_AROUND,      //範囲攻撃
		ATTACKTYPE_BOM,         //爆発攻撃
		ATTACKTYPE_MAX
	};

	//モーション
	typedef enum
	{
		MOTIONTYPE_NONE = 0,         //ニュートラル
		MOTIONTYPE_MOVE,             //移動
		MOTIONTYPE_GETUP,            //起き上がり
		MOTIONTYPE_ACTION,           //攻撃
		MOTIONTYPE_JUMP,             //ジャンプ攻撃
		MOTIONTYPE_BOM,              //爆弾攻撃
		MOTIONTYPE_ACTIONNEUTRAL,    //攻撃待機
		MOTIONTYPE_DAMEGE,           //くらいモーション
		MOTIONTYPE_DEATH,            //死亡
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CEnemyMedBoss *Create(D3DXVECTOR3 pos, TYPEENE type);  //生成
												
	void ReadText(TYPEENE type);  //外部ファイル読み込み
	static CEnemyMedBoss *GetEnemy(void) { return m_EnemyMedBoss; };

	void Control(void);  //敵の動き

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	static CEnemyMedBoss *m_EnemyMedBoss;

	//STATE m_state;  //状態
	TYPE m_type;
	TYPEENE m_typeEne;
	ATTACKTYPE m_ACKTYpe;

	int m_nNumModel;  //モデルの総数
	int m_nIdxTexture;
	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	char m_filename[128] = {};
	int m_nIdx;
	int m_nParent;
	int m_nLoop;
	int m_nFrame;   //モーションのフレーム数
	int m_nCntColli;   //当たり判定が発生している時間
	int m_nNumMotion;
	int m_nCntMotion;
	int m_nCnterMotion;
	int m_nNumkey;
	int m_nNumPatrol;   //巡回する地点の数
	int m_nCurrentpos;  //現在どこの巡回地点にいるか
	int m_nCntAction;   //攻撃してから再び攻撃するまでの時間
	float m_fDiff;
	float m_fDest;
	bool m_Tracking;  //プレイヤーを追尾するかどうか
	bool m_bAction;
	D3DXVECTOR3 m_posOrigin;
	D3DXVECTOR3 m_JumpPoint;
};

#endif