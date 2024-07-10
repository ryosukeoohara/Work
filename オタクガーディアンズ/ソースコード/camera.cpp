//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "game.h"
#include "player.h"

//マクロ定義
#define CAMERA_DISTNCE    (1000.0f)
#define CAMERA_ROTY       (0.03f)
#define CAMERA_MOVE       (2.0f)
#define CAMERA_LOWMOVE    (0.1f)

//================================================================
//コンストラクタ
//================================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nCounter = 0;
}

//================================================================
//デストラクタ
//================================================================
CCamera::~CCamera()
{

}

//================================================================
//カメラの初期化処理
//================================================================
void CCamera::Init(void)
{
	CScene *pScene = CManager::Getinstance()->GetScene();

	//if (pScene->GetMode() == CScene::MODE_TITLE)
	//{
	//	m_posV = D3DXVECTOR3(0.0f, 150.0f, -30.0f);
	//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	//}
}

//================================================================
//カメラの終了処理
//================================================================
void CCamera::Uninit(void)
{

}

//================================================================
//カメラ更新処理
//================================================================
void CCamera::Update(void)
{
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//シーンの情報を寿徳
	CScene *pScene = CManager::Getinstance()->GetScene();

	////プレイヤー(クソデブ)の情報を取得
	//CFoot *pFoot = CGame::GetPlayerFoot();

	////プレイヤー(チビデブ)の情報を取得
	//CChibi *pChibi = CGame::GetPlayerChibi();

	if (pScene->GetMode() == CScene::MODE_TITLE || pScene->GetMode() == CScene::MODE_RESULT)
	{
		Title();
	}

	if (pScene->GetMode() == CScene::MODE_GAME)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		CameraV();

		D3DXVECTOR3 pos = pPlayer->Getpos();

		//目標の注視点を設定
		m_posRDest.x = pos.x;
		m_posRDest.z = pos.z;

		//カメラの移動量
		m_move.x = m_posRDest.x - m_posR.x;
		m_move.z = m_posRDest.z - m_posR.z;

		//位置に移動量を保存
		m_posR.x += m_move.x;
		m_posR.z += m_move.z;
	}

	if (pScene->GetMode() == CScene::MODE_GAME && m_type == TYPE_EDIT)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		D3DXVECTOR3 pos = pPlayer->Getpos();

		Edit();

		////目標の注視点を設定
		//m_posRDest.x = pos.x;
		//m_posRDest.z = pos.z;

		////カメラの移動量
		//m_move.x = m_posRDest.x - m_posR.x;
		//m_move.z = m_posRDest.z - m_posR.z;

		////位置に移動量を保存
		//m_posR.x += m_move.x;
		//m_posR.z += m_move.z;
	}

	//向きを設定
	SetRot(m_rot);
	
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n---カメラの情報---");
	pDebugProc->Print("\nカメラの位置視点：X軸<%f>,Y軸<%f>,Z軸<%f>", m_posV.x, m_posV.y, m_posV.z);
	pDebugProc->Print("\nカメラの位置注視点：X軸<%f>,Y軸<%f>,Z軸<%f>", m_posR.x, m_posR.y, m_posR.z);
	pDebugProc->Print("\nカメラの向き ：X軸<%f>,Y軸<%f>,Z軸<%f>", m_rot.x , m_rot.y , m_rot.z);
} 

//================================================================
//カメラの設定処理
//================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		100000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//================================================================
//視点の移動
//================================================================
void CCamera::CameraV(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスの情報を取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//マウスの位置を取得
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	////プレイヤー(クソデブ)の情報を取得
	//CFoot *pFoot = CGame::GetPlayerFoot();

	////プレイヤー(チビデブ)の情報を取得
	//CChibi *pChibi = CGame::GetPlayerChibi(); 

	//m_rot.y += MousePos.x * 0.005f;

	CPlayer *pPlayer = CGame::GetPlayer();

	m_posV.x = m_posR.x - sinf(m_rot.y) * -CAMERA_DISTNCE;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -CAMERA_DISTNCE;

	D3DXVECTOR3 pos = pPlayer->Getpos();

	m_posV = D3DXVECTOR3(0.0f + pos.x, 150.0f + pos.y, 30.0f - m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, pos.y, 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

//================================================================
//視点の移動
//================================================================
void CCamera::CameraR(void)
{
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	CPlayer *pPlayer = CGame::GetPlayer();

	m_rot.z += MousePos.y * 0.005f;

	m_posR.x = m_posV.x - sinf(m_rot.y) * CAMERA_DISTNCE;
	m_posR.z = m_posV.z - cosf(m_rot.y) * CAMERA_DISTNCE;
}

//================================================================
//視点の移動
//================================================================
void CCamera::Title(void)
{
	m_posV = D3DXVECTOR3(-500.0f, 80.0f, -200.0f);
	m_posR = D3DXVECTOR3(-875.0f, 70.0f, 50.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

//================================================================
//ボスが登場するときのカメラ
//================================================================
void CCamera::Edit(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = pPlayer->Getpos();

	if (InputKeyboard->GetPress(DIK_F) == true)
	{
		m_move.x += sinf(m_rot.y) * 1.1f;
	}

	if (InputKeyboard->GetPress(DIK_H) == true)
	{
		m_move.x -= sinf(m_rot.y) * 1.1f;
	}

	if (InputKeyboard->GetPress(DIK_T) == true)
	{
		m_move.y += 1.0f;
	}

	if (InputKeyboard->GetPress(DIK_G) == true)
	{
		m_move.y -= 1.0f;
	}

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * -2300.0f;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -2300.0f;

	m_posR.x = m_posV.x - sinf(m_rot.y) * 2300.0f;
	m_posR.z = m_posV.z - cosf(m_rot.y) * 2300.0f;

	m_posR.x += m_move.x;
	m_posV.x += m_move.x;

	m_posR.y += m_move.y;
	m_posV.y += m_move.y;

	//m_posV += m_move;
	//m_posR += m_move;

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f + m_posV.y, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(100.0f + m_posR.x, 50.0f + m_posR.y, m_posR.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

//================================================================
//遠距離武器を使っているときのカメラ
//================================================================
void CCamera::Scope(void)
{
	/*CInputMouse *pInputMouse = CManager::GetInputMouse();

	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	CPlayer *pPlayer = CGame::GetPlayer();

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posR.x = m_posV.x - sinf(m_rot.y) * 50.0f;
	m_posR.z = m_posV.z - cosf(m_rot.y) * 50.0f;

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 pos = pPlayer->Getpos();

		m_posV = D3DXVECTOR3(pos.x , 70.0f, pos.z);
		m_posR = D3DXVECTOR3(m_posR.x, 70.0f, m_posR.z);
		m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}*/
}