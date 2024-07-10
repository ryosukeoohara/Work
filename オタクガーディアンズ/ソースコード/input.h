//===========================================================
//
//インプット処理[input.h]
//Author 大原怜将
//
//===========================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#pragma comment(lib, "xinput.lib")

//マクロ定義
#define NUM_KEY_MAX     (256)     //キーの最大数
#define MAX_PLAYER      (1)

//入力クラス------------------------------------------------------
class CInput
{
public:
	CInput();  //コンストラクタ
	virtual ~CInput();  //デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);  //初期化処理
	virtual void Uninit(void);      //終了処理
	virtual void Update(void) = 0;  //更新処理
	
protected:
	static LPDIRECTINPUT8 m_pInput;     //directInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;     //入力デバイス（キーボード）へのポインタ
};

//キーボードの入力クラス-------------------------------------------
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();   //コンストラクタ
	~CInputKeyboard();  //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];
};

//マウスの入力クラス------------------------------------------------
class CInputMouse : public CInput
{
public:
	CInputMouse();   //コンストラクタ
	~CInputMouse();  //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理

	bool GetLButton(void);  //左クリック
	bool GetRButton(void);  //右クリック
	bool GetWheel(void);    //ホイール

	D3DXVECTOR2 GetMouseMove(void);  //移動量取得
	float GetMouseWheel(void);       //マウスホイールの回転量取得

private:
	DIMOUSESTATE  m_CurrentMouseState;
	//BYTE rgbButtons[4];
};

//ゲームパットのクラス----------------------------------------------
class CInputJoyPad : public CInput
{
public:
	/*XINPUT_GAMEPAD_DPAD_UP
	XINPUT_GAMEPAD_DPAD_DOWN
	XINPUT_GAMEPAD_DPAD_LEFT
	XINPUT_GAMEPAD_DPAD_RIGHT
	XINPUT_GAMEPAD_START
	XINPUT_GAMEPAD_BACK
	XINPUT_GAMEPAD_LEFT_THUMB
	XINPUT_GAMEPAD_RIGHT_THUMB
	XINPUT_GAMEPAD_LEFT_SHOULDER
	XINPUT_GAMEPAD_RIGHT_SHOULDER
	XINPUT_GAMEPAD_A
	XINPUT_GAMEPAD_B
	XINPUT_GAMEPAD_X
	XINPUT_GAMEPAD_Y*/

	//PAD_UP,		//	十字キーの上
	//	PAD_DOWN,	//	十字キーの下
	//	PAD_LEFT,	//	十字キーの左
	//	PAD_RIGHT,	//	十字キーの右
	//	PAD_START,	//	Start
	//	PAD_BACK,	//	Back
	//	PAD_LEFT_THUMB,		//	左スティック
	//	PAD_RIGHT_THUMB,	//	右スティック
	//	PAD_LB,  //	LB
	//	PAD_RB,	//	RB
	//	PAD_A,	//	Aボタン
	//	PAD_B,	//	Bボタン
	//	PAD_X,	//	Xボタン
	//	PAD_Y,	//	Yボタン
	//			// アナログ
	//	PAD_LEFT_U_STICK,	//	左スティックの上
	//	PAD_LEFT_D_STICK,	//	左スティックの下
	//	PAD_LEFT_L_STICK,	//	左スティックの左
	//	PAD_LEFT_R_STICK,	//	左スティックの右
	//	PAD_RIGHT_U_STICK,	//	右スティックの上
	//	PAD_RIGHT_D_STICK,	//	右スティックの下
	//	PAD_RIGHT_L_STICK,	//	右スティックの左
	//	PAD_RIGHT_R_STICK,	//	右スティックの右
	//	PAD_LT,	//	左トリガー
	//	PAD_RT,	//	右トリガー

	enum PADBUTTON
	{
		BUTTON_UP = 0,
		BUTTON_DOWN,
		BOTTON_LEFt,
		BUTTON_RIGHT,
		BUTTON_START,
		BUTTON_BACK,
		BUTTON_LTHUMB,
		BUTTON_RTHUMB,
		BUTTON_LB,
		BUTTON_RB,
		BUTTON_LT,
		BUTTON_RT,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		STICK_LX,
		STICK_LY,
		BUTTON_MAX
	};

	CInputJoyPad();   //コンストラクタ
	~CInputJoyPad();  //デストラクタ

	HRESULT Init(void);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理

	bool GetPress(PADBUTTON nKey, int nCntPlayer);
	bool GetTrigger(PADBUTTON nKey, int nCntPlayer);
	bool GetRelease(PADBUTTON nKey, int nCntPlayer);

	bool GetLeftTirgger(PADBUTTON nKey, int nCntPlayer);
	bool GetRightTirgger(PADBUTTON nKey, int nCntPlayer);

	float GetXStick(PADBUTTON nKey, int nCntPlayer);
	float GetYStick(PADBUTTON nKey, int nCntPlayer);

	

private:
	XINPUT_STATE m_State[MAX_PLAYER];
	XINPUT_STATE m_StateTrigger[MAX_PLAYER];
	XINPUT_STATE m_StateRelease[MAX_PLAYER];
	XINPUT_STATE m_StateRepeat[MAX_PLAYER];
};

#endif