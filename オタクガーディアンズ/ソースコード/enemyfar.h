//=============================================================================
//
// 遠距離の敵の処理 [enemyfar.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMYFAR_H_
#define _ENEMYFAR_H_

//*=============================================================================
//インクルードファイル
//*=============================================================================
//#include "character.h"
//#include "object.h"
#include "enemy.h"

//*=============================================================================
//クラス定義
//*=============================================================================
class CMotion;

//*=============================================================================
//クラス定義
//*=============================================================================
class CEnemyFar : public CEnemy
{
public:

	enum STATE
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,
		STATE_ACTION,
		STATE_MAX
	};

	//モーション
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,              //ニュートラル
		MOTIONTYPE_ACTION,                   //攻撃
		MOTIONTYPE_MAX
	};

	CEnemyFar();                                  //コンストラクタ
	CEnemyFar(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //コンストラクタ
	~CEnemyFar();                                 //デストラクタ

	HRESULT Init(void);                        //初期化
	void Uninit(void);                         //終了
	void Update(void);                         //更新
	void Draw(void);                           //描画

	static CEnemyFar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //生成
	void ReadText(char *fliename);             //テキストファイル読み込み

	//static CEnemyFar **GetEnemy(void) { return &m_pEnemy[0]; }
	void SetMoveX(float move) { m_move.x = move; }
	void SetMoveY(float move) { m_move.y = move; }

	static int GetNumAll(void) { return m_nNumAll; }

private:
	void Controll(void);                       //制御処理
	CMotion *m_motion;                         //モーションへのポインタ
	CCharacter *m_apModel[MAX_PRATS];          //モデル(パーツ)へのポインタ
	STATE m_state;                             //状態
	//static CEnemyFar *m_pEnemy[64];            //敵のポインタ
	D3DXVECTOR3 m_posOld;                      //前回の位置
	D3DXVECTOR3 m_move;                        //移動
	D3DXMATRIX m_mtxWorld;                     //ワールドマトリックス
	//int m_nidxID;                              //インデックス番号
	int m_nActionCounter;                      //次に攻撃するまでのカウント
	int m_nLife;
	//static int m_nNumAll;                      //敵の総数

	//*=============================================================================
	//外部ファイル読み込み用
	//*=============================================================================
	D3DXVECTOR3 m_Readpos;                     //位置読み込み用
	D3DXVECTOR3 m_Readrot;                     //向き読み込み用
	int m_nIdx;                                //インデックス番号
	int m_nParent;                             //親のインデックス番号
	int m_nNumModel;                           //モデル(パーツ)の総数
	
	char m_filename[128] = {};                 //文字読み込み用

};

#endif // !_ENEMYFAR_H_