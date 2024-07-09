//===========================================================
//
// マネージャ処理[manager.h]
// Author 大原怜将
//
//===========================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//#include "object.h"

//===========================================================
//前方宣言
//===========================================================
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CSound;
class CPlayer;
class CDebugProc;
class CCamera;
class CLight;
class CTexture;
class CModel;
class CObject3D;
class CEnemy;
class CCollision;
class CEdit;
class CMap;
class CGame;
class CTutorial;
class CTitle;
class CResult;
class CFade;
class CPause;

//===========================================================
// クラス定義
//===========================================================
class CScene
{
public:

	enum MODE
	{
		MODE_TITLE = 0,   //タイトル
		MODE_TUTORIAL,    //チュートリアル
		MODE_GAME,        //ゲーム
		MODE_RESULT,      //リザルト
		MODE_RANKING,     //ランキング
		MODE_MAX
	};

	CScene();  //コンストラクタ
	CScene(MODE mode);  //コンストラクタ
	~CScene(); //デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene *Create(MODE mode);
	static CScene::MODE GetMode(void);

private:
	static MODE m_mode;
	static CGame *m_Game;
	static CTutorial *m_Tutorial;
	static CTitle *m_Title;
	static CResult *m_Result;

};

//===========================================================
// クラス定義
//===========================================================
class CManager
{
public:		//誰でもアクセスできる

	CManager();  //コンストラクタ
	~CManager(); //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);       //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理
	void Draw(void);    //描画処理

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetKeyBoard(void);
	static CInputMouse *GetInputMouse(void);
	static CSound *GetSound(void);
	static CPlayer *GetPlayer(void);
	static CDebugProc *GetDebugProc(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CTexture *GetTexture(void);
	static CModel *GetModel(void);
	static CObject3D *GetObject3D(void);
	static CEnemy *GetEnemy(void);
	//static void *SetEnemy(CEnemy *enemy) { return m_Enemy = enemy; }
	static CCollision *GetCollsion(void);
	static CEdit *GetEdit(void);
	static CMap *GetMap(void);
	static CScene *GetScene(void);
	static CFade *GetFade(void);
	static CPause *GetPause(void);

	static void SetMode(CScene::MODE mode);

	static void SetbPause(bool bpause) { m_bPause = bpause; }
	static bool GetbPause(void) { return m_bPause; }

private:	//自分だけがアクセスできる

	static CRenderer *m_Renderer;
	static CInputKeyboard *m_InputKeyboard;
	static CInputMouse *m_InputMouse;
	static CSound *m_Sound;
	static CPlayer *m_Player;
	static CDebugProc *m_DebugProc;
	static CCamera *m_Camera;
	static CLight *m_Light;
	static CTexture *m_Texture;
	static CModel *m_Model;
	static CObject3D *m_Object3D;
	static CEnemy *m_Enemy;
	static CCollision *m_Collision;
	static CEdit *m_Edit;
	static CMap *m_Map;
	static CScene *m_pScene;
	static CFade *m_Fade;
	static CPause *m_Pause;

	int m_ResetCounter;  //リセットした回数
	static bool m_bPause;       //ポーズ中かどうか
	bool m_EditUse;   //エディットモードにするかどうか
};



#endif // !1