//===========================================================
//
//ポリゴンを出すやつ[enemy.h]
//Author 大原怜将
//
//===========================================================
#ifndef _POLICE_H_             //このマクロ定義がされてなかったら
#define _POLICE_H_             //2重インクルード防止のマクロ定義をする

#include "motion.h"
#include "character.h"
#include "shadow.h"
#include "life.h"

//マクロ定義
#define MAX_ENEMY   (128)   //敵の最大数
#define MAX_RARTS   (128)   //パーツの最大数
#define MAX_PATROL   (16)   //巡回できる地点の最大数

//敵クラス
class CPolice : public CObject
{
public:
	CPolice();                                                                          //コンストラクタ
	CPolice(D3DXVECTOR3 pos);                                                           //コンストラクタ
	~CPolice();                                                                         //デストラクタ
								                                                        
	enum TYPE					                                                        
	{							                                                        
		TYPE_NONE = 0,			                                                        
		TYPE_NEAR,                                                                      //近距離のザコ
		TYPE_FAR,                                                                       //遠距離のザコ
		TYPE_MEDBOSS,                                                                   //中ボス
		TYPE_BOSS,                                                                      //ボス
		TYPE_MAX				                                                        
	}; 							                                                        
								                                                        
	enum STATE					                                                        
	{							                                                        
		TATE_NONE = 0,			                                                        
		TATE_MOVE,                                                                       //移動
		TATE_JUMP,                                                                       //ジャンプ
		TATE_GETUP,                                                                      //起き上がり
		TATE_ACTION,                                                                     //攻撃
		TATE_RUSH,                                                                       //突進攻撃
		TATE_ACTIONNEUTRAL,                                                              //攻撃ニュートラル
		TATE_DAMEGE,                                                                     //ダメージ受け
		TATE_STAGGER,                                                                    //よろけ
		TATE_DEATH,                                                                      //死亡
		TATE_MAX				                                                        
	};							                                                        
								                                                        
	HRESULT Init(void);                                                                  //初期化処理    
	void Uninit(void);                                                                   //終了処理
	void Update(void);                                                                   //更新処理
	void Draw(void);                                                                     //描画処理

	void ReadText(char *Filename);                                                       //外部ファイル読み込み
	static CPolice **GetPolice(void) { return &m_Police[0]; }                             //警察取得処理

	void Controll(void);                                                                 //動き制御処理

	void SetPosOld(D3DXVECTOR3 posold) { m_posOld = posold; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	void SetState(STATE state) { m_state = state; }                                       //状態設定
	STATE GetState(void) { return m_state; }                                              //状態取得
													                                      
	void SetNumber(int nNum) { m_nNumber = nNum; }	                                      
													                                      
	void Hit(void);                                                                       //ヒット処理

	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }

	typedef struct
	{
		D3DXVECTOR3 m_PatrolPos;                                                          //巡回地点

	}PATROL;

private:

	static CPolice *m_Police[MAX_ENEMY];
	static int m_nNumAll;                                                                 //警察の総数
	static LPDIRECT3DTEXTURE9 m_pTexture;                                                 //テクスチャへのポインタ
	CCharacter *m_apModel[MAX_RARTS];                                                     //モデル(パーツ)へのポインタ
	CMotion *m_motion;                                                                    //モーションへのポインタ
	PATROL m_Vigi[MAX_PATROL];					                                          
	D3DXVECTOR3 m_posOld;                                                                 //前回の位置
	D3DXVECTOR3 m_Readpos;                                                                //読み込むときの位置
	D3DXVECTOR3 m_Readrot;                                                                //読み込むときの向き
	//D3DXVECTOR3 m_posOld;                                                                 //前回の位置
	D3DXVECTOR3 m_move;                                                                   //移動
	D3DXMATRIX m_mtxWorld;                                                                //ワールドマトリックス
	char m_filename[128] = {};					                                          
												                                          
	CShadow *m_pShadow;                                                                   //影へのポインタ
	CLife *m_Life;                                                                        //ライフへのポインタ
	TYPE m_type;                                                                          //種類
	STATE m_state;                                                                        //状態
	int m_nIdxTexture;                                                                    //テクスチャのインデックス番号
	int m_nIdxShaadow;                                                                    //影のインデックス番号
	int m_nNumModel;                                                                      //モデルの総数
	int m_nNumPatrol;                                                                     //パトロールする地点の数
	int m_nCurrentpos;                                                                    //現在どこの巡回地点にいるか
	int m_nIdx;             
	int m_nParent;
	int m_nNumber;
};

#endif