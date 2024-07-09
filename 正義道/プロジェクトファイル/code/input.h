//===========================================================
//
// インプット処理[input.h]
// Author 大原怜将
//
//===========================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//マクロ定義
#define NUM_KEY_MAX     (256)     //キーの最大数

//===========================================================
// クラス定義
//===========================================================
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

#endif