//===========================================================
//
//インプット処理[input.cpp]
//Author 大原怜将
//
//===========================================================
#include "input.h"
#include "manager.h"
#include "debugproc.h"

//================================================================
//静的メンバ変数
//================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//================================================================
//コンストラクタ
//================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//================================================================
//デストラクタ
//================================================================
CInput::~CInput()
{

}

//================================================================
//初期化処理
//================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//directオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//================================================================
//キーボードの終了処理
//================================================================
void CInput::Uninit(void)
{
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//================================================================================
//キーボード
//================================================================================

//================================================================
//コンストラクタ
//================================================================
CInputKeyboard::CInputKeyboard()
{
	m_pDevice = NULL;
	/*m_aKeyState[0] = {};
	m_aKeyStateTrigger[0] = {};
	m_aKeyStateRelease[0] = {};
	m_aKeyStateRepeat[0] = {};*/
}

//================================================================
//デストラクタ
//================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//================================================================
//初期化処理
//================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != NULL)
	{
		//入力デバイス（キーボード）の生成
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//データフォーマット
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//調教モードを設定
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			return E_FAIL;
		}
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//================================================================
//キーボードの終了処理
//================================================================
void CInputKeyboard::Uninit(void)
{
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//================================================================
//キーボードの更新処理
//================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];       //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] | aKeyState[nCntKey]) ^ aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];     //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();     //キーボードのアクセス権を獲得
	}
}

//================================================================
//キーボードのプレス情報を所得
//================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//================================================================
//キーボードのトリガー情報を所得
//================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//================================================================
//キーボードのリリース情報を所得
//================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//********************************************************************************
//マウス
//********************************************************************************

//================================================================
//コンストラクタ
//================================================================
CInputMouse::CInputMouse()
{
	m_pDevice = NULL;
	/*m_aKeyState[0] = {};
	m_aKeyStateTrigger[0] = {};
	m_aKeyStateRelease[0] = {};
	m_aKeyStateRepeat[0] = {};*/
}

//================================================================
//デストラクタ
//================================================================
CInputMouse::~CInputMouse()
{

}

//================================================================
//マウスの初期化処理
//================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != NULL)
	{
		//入力デバイス（マウス）の生成
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//データフォーマット
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
		{
			return E_FAIL;
		}

		//調教モードを設定
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			return E_FAIL;
		}
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//================================================================
//マウスの終了処理
//================================================================
void CInputMouse::Uninit(void)
{
	//入力デバイス（マウス）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//================================================================
//マウスの更新処理
//================================================================
void CInputMouse::Update(void)
{
	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	//BYTE aKeyState[NUM_KEY_MAX];       //マウス入力情報
	//int nCntKey;

	//マウス座標を取得する
	POINT pos;
	GetCursorPos(&pos);

	//ShowCursor(FALSE);

	//スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &pos);

	int posX = 0, posY = 0;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
	{

	}
	else
	{
		m_pDevice->Acquire();     //マウスアクセス権を獲得
	}

	pDebugProc->Print("\n---マウスの情報---");
	pDebugProc->Print("\n<<位置 : X:%d Y:%d>>", pos, pos);
	pDebugProc->Print("\n<<[X] : %f, [Y] : %f>>", (float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
	pDebugProc->Print("\n<<ホイールの回転量 : %f>>", (float)m_CurrentMouseState.lZ);
}

//================================================================
//マウスの右クリック
//================================================================
bool CInputMouse::GetLButton(void)
{
	return (m_CurrentMouseState.rgbButtons[0] & 0x80) ? true : false;
}

//================================================================
//マウスの左クリック
//================================================================
bool CInputMouse::GetRButton(void)
{
	return (m_CurrentMouseState.rgbButtons[1] & 0x80) ? true : false;
}

//================================================================
//マウスのホイール
//================================================================
bool CInputMouse::GetWheel(void)
{
	return (m_CurrentMouseState.rgbButtons[2] & 0x80) ? true : false;
}

//================================================================
//移動量の取得
//================================================================
D3DXVECTOR2 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

//================================================================
//ホイールの回転量取得
//================================================================
float CInputMouse::GetMouseWheel(void)
{
	return (float)m_CurrentMouseState.lZ;
}

//********************************************************************************
//ゲームパッド
//********************************************************************************

//================================================================
//コンストラクタ
//================================================================
CInputJoyPad::CInputJoyPad()
{
	ZeroMemory(&m_State, sizeof(m_State));
	ZeroMemory(&m_StateRelease, sizeof(m_StateRelease));
	ZeroMemory(&m_StateTrigger, sizeof(m_StateTrigger));
	ZeroMemory(&m_StateRepeat, sizeof(m_StateRepeat));
}

//================================================================
//デストラクタ
//================================================================
CInputJoyPad::~CInputJoyPad()
{

}

//================================================================
//初期化処理
//================================================================
HRESULT CInputJoyPad::Init(void)
{
	XInputEnable(true);

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		memset(&m_State[nCount], 0, sizeof(XINPUT_STATE));
		memset(&m_StateTrigger[nCount], 0, sizeof(XINPUT_STATE));
		memset(&m_StateRelease[nCount], 0, sizeof(XINPUT_STATE));
		memset(&m_StateRepeat[nCount], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}

//================================================================
//終了処理
//================================================================
void CInputJoyPad::Uninit(void)
{
	XInputEnable(false);
}

//================================================================
//更新処理
//================================================================
void CInputJoyPad::Update(void)
{
	XINPUT_STATE aState[MAX_PLAYER];

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (XInputGetState(nCount, &aState[nCount]) == ERROR_SUCCESS)
		{
			//とりがー
			m_StateTrigger[nCount].Gamepad.wButtons =
				(m_State[nCount].Gamepad.wButtons ^ aState[nCount].Gamepad.wButtons)
				& aState[nCount].Gamepad.wButtons;

			//りりーす
			m_StateRelease[nCount].Gamepad.wButtons =
				(m_State[nCount].Gamepad.wButtons | aState[nCount].Gamepad.wButtons)
				^ aState[nCount].Gamepad.wButtons;

			//ぷれす
			m_State[nCount] = aState[nCount];
		}
		else
		{
			return;
			//m_pDevice->Acquire();     //マウスアクセス権を獲得
		}
	}
}

bool CInputJoyPad::GetPress(PADBUTTON nKey, int nCntPlayer)
{
	return (m_State[nCntPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

bool CInputJoyPad::GetTrigger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger[nCntPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

bool CInputJoyPad::GetRelease(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateRelease[nCntPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

bool CInputJoyPad::GetLeftTirgger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger[nCntPlayer].Gamepad.bLeftTrigger & (0x01 << nKey)) ? true : false;
}

bool CInputJoyPad::GetRightTirgger(PADBUTTON nKey, int nCntPlayer)
{
	return (m_StateTrigger[nCntPlayer].Gamepad.bRightTrigger & (0x01 << nKey)) ? true : false;
}

float CInputJoyPad::GetXStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State[nCntPlayer].Gamepad.sThumbLX > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 3))
	{
		return m_State[nCntPlayer].Gamepad.sThumbLX;
	}

	if (m_State[nCntPlayer].Gamepad.sThumbLX < -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * 2))
	{
		return m_State[nCntPlayer].Gamepad.sThumbLX;
	}

	return 0.0f;
}

float CInputJoyPad::GetYStick(PADBUTTON nKey, int nCntPlayer)
{
	if (m_State[nCntPlayer].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return m_State[nCntPlayer].Gamepad.sThumbLY;
	}

	return 0.0f;
}