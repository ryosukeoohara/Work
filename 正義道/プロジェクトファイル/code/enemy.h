//===========================================================
//
//ポリゴンを出すやつ[enemy.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ENEMY_H_             //このマクロ定義がされてなかったら
#define _ENEMY_H_             //2重インクルード防止のマクロ定義をする

#include "motion.h"
#include "character.h"
#include "shadow.h"
#include "life.h"

//マクロ定義
#define MAX_ENEMY   (128)   //敵の最大数
#define MAX_RARTS   (128)   //パーツの最大数

//敵クラス
class CEnemy : public CObject
{
public:
	CEnemy();  //コンストラクタ
	~CEnemy();  //デストラクタ

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_NEAR,                 //近距離のザコ
		TYPE_FAR,                  //遠距離のザコ
		TYPE_MEDBOSS,              //中ボス
		TYPE_BOSS,                 //ボス
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,
		STATE_MOVE,                 //移動
		STATE_JUMP,                 //ジャンプ
		STATE_GETUP,                //起き上がり
		STATE_ACTION,               //攻撃
		STATE_RUSH,                 //突進攻撃
		STATE_ACTIONNEUTRAL,        //攻撃ニュートラル
		STATE_DAMEGE,               //ダメージ受け
		STATE_STAGGER,              //よろけ
		STATE_DEATH,                //死亡
		STATE_END,                  //終了
		STATE_MAX
	};

	HRESULT Init(void);   //初期化処理    
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	void ReadText(char *Filename);  //外部ファイル読み込み
	static CEnemy **GetEnemy(void) { return &m_Enemy[0]; }

	void SetPosOld(D3DXVECTOR3 posold) { m_posOld = posold; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	void SetState(STATE state) { m_state = state; }  //状態設定
	STATE GetState(void) { 
		return m_state; 
	}         //状態取得

	void SetNumber(int nNum) { m_nNumber = nNum; }

	void Hit(void);                                  //ヒット処理

	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }

protected:
	static CEnemy *m_Enemy[MAX_ENEMY];
	static int m_nNumAll;                        //ざこ敵の総数
	static LPDIRECT3DTEXTURE9 m_pTexture;        //テクスチャへのポインタ
	CCharacter *m_apModel[MAX_RARTS];            //モデル(パーツ)へのポインタ
	CMotion *m_motion;                           //モーションへのポインタ
	D3DXVECTOR3 m_pos;                           //位置
	D3DXVECTOR3 m_posOld;                        //前回の位置
	D3DXVECTOR3 m_move;                          //移動
	D3DXVECTOR3 m_rot;                           //向き

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;

	int m_nIdxTexture;
	int m_nIdxShaadow;

	D3DXMATRIX m_mtxWorld;    //ワールドマトリックス
	char m_filename[128] = {};

	int m_nNumModel;  //モデルの総数

	STATE m_state;  //状態

	CShadow *m_pShadow;   //影へのポインタ
	CLife *m_Life;        //ライフへのポインタ

private:
	TYPE m_type;

	int m_nIdx;
	int m_nParent;

	int m_nNumber;

	

};

#endif