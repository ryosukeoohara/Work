////===========================================================
////
////ポリゴンを出すやつ[block.cpp]
////Author 大原怜将
////
////===========================================================
//#include "main.h"
//#include "block.h"
//#include "player.h"
//#include "input.h"
//#include "manager.h"
//#include "renderer.h"
//
////================================================================
////静的メンバ変数宣言
////================================================================
//LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;
//CObject2D *CBlock::m_apObject2D[MAX_BLOCK] = {};
//CBlock *CBlock::m_aBlock[MAX_BLOCK] = {};                       //ブロックの情報
//
////================================================================
////コンストラクタ
////================================================================
//CBlock::CBlock()
//{
//	
//}
//
////================================================================
////コンストラクタ(オーバーロード)
////================================================================
//CBlock::CBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
//{
//	//m_pos = pos;  //位置
//	//m_fWidth = fWidth;
//	//m_fHeight = fHeight;
//	SetPosition(pos);
//	//SetType(type);
//}
//
////================================================================
////デストラクタ
////================================================================
//CBlock::~CBlock()
//{
//
//}
//
////================================================================
////生成処理
////================================================================
//CBlock *CBlock::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
//{
//	//オブジェクト2Dのポインタ
//	CBlock *pBlock = NULL;
//
//	if (pBlock == NULL)
//	{
//		//オブジェクト2Dの生成
//		pBlock = new CBlock(pos, fWidth, fHeight);
//
//		for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
//		{
//			if (m_aBlock[nCount] == NULL)
//			{
//				m_aBlock[nCount] = pBlock;
//
//				break;
//			}
//		}
//		
//		//テクスチャをバインド
//		pBlock->BindTexture(m_pTexture);
//
//		//初期化処理
//		pBlock->Init();
//	}
//
//	return pBlock;
//}
//
////================================================================
////弾の初期化処理
////================================================================											 
//HRESULT CBlock::Init(void)
//{
//	//オブジェクトを生成
//	CObject2D::Create({ 0.0f,0.0f,0.0f });
//
//	//初期化処理
//	CObject2D::Init();
//
//	return S_OK;
//}
//
////================================================================
////ポリゴンの終了処理
////================================================================
//void CBlock::Uninit(void)
//{
//	//終了処理
//	CObject2D::Uninit();
//}
//
////================================================================
////弾の更新処理
////================================================================
//void CBlock::Update(void)
//{
//	//設定処理
//	SetVtxBlock(m_pos, m_fWidth, m_fHeight);
//}
//
////================================================================
////弾の描画処理
////================================================================
//void CBlock::Draw(void)
//{
//	//描画処理
//	CObject2D::Draw();
//}
//
////================================================================
////当たり判定
////================================================================
//bool CBlock::CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
//{
//	bool bLand = false;   //着地したかどうか
//
//	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
//	{
//		if (m_aBlock[nCount] != NULL)
//		{
//			if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//			{
//				//ブロックの上======================================
//				if (m_aBlock[nCount]->m_pos.y >= pPosOld->y && m_aBlock[nCount]->m_pos.y <= pPos->y)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y;   //ブロックの上に立たせる
//					pMove->y = 0.0f;     //移動量を0にする
//				}
//
//				//ブロックのした====================================
//				else if (m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPosOld->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					bLand = false;
//					pPos->y = m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight + fHeight;   //ブロックの下に立たせる
//					pMove->y = 0.0f;       //移動量を0にする
//				}
//
//				if (m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y
//				 || m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y
//				 && m_aBlock[nCount]->m_pos.y <= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					//ブロックの左側面==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //ブロックの左に立たせる
//						pMove->x = 0.0f;
//					}
//
//					//ブロックの右側面==================================
//					else if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //ブロックの右に立たせる
//						pMove->x = 0.0f;
//					}
//
//					//右斜め==================================
//					if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//						&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y
//						/*|| m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//						&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight < pPos->y*/
//						/*&& m_aBlock[nCount]->m_pos.y >= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y*/)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //ブロックの右に立たせる
//						//pMove->x = 0.0f;
//					}
//
//					//左斜め==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth
//				     && m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //ブロックの左に立たせる
//						//pMove->x = 0.0f;
//					}
//				}
//
//				
//			}
//		}
//	}
//
//	return bLand;
//}
//
////================================================================
////当たり判定
////================================================================
//bool CBlock::CollisionBulletBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
//{
//	bool bLand = false;   //着地したかどうか
//
//	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
//	{
//		if (m_aBlock[nCount] != NULL)
//		{
//			if (m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth && m_aBlock[nCount]->m_pos.x >= pPos->x
//			 || m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x && m_aBlock[nCount]->m_pos.x <= pPos->x)
//			{
//				//ブロックの上======================================
//				if (m_aBlock[nCount]->m_pos.y >= pPosOld->y && m_aBlock[nCount]->m_pos.y <= pPos->y + fHeight)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y - fWidth;   //ブロックの左に立たせる
//					pMove->y = 0.0f;
//				}
//
//				//ブロックのした====================================
//				else if (m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight + fHeight;   //ブロックの下に立たせる
//					pMove->y = 0.0f;       //移動量を0にする
//				}
//
//				if (m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y)
//				{
//					//ブロックの左側面==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//					{
//						bLand = true;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //ブロックの左に立たせる
//						pMove->x = 0.0f;
//					}
//
//					//ブロックの右側面==================================
//					else if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPosOld->x && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth)
//					{
//						bLand = true;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //ブロックの右に立たせる
//						pMove->x = 0.0f;
//					}
//
//				//	//右斜め==================================
//				//	if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y
//				//		/*|| m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight < pPos->y*/
//				//		/*&& m_aBlock[nCount]->m_pos.y >= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y*/)
//				//	{
//				//		bLand = false;
//				//		pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //ブロックの右に立たせる
//				//																					 //pMove->x = 0.0f;
//				//	}
//
//				//	//左斜め==================================
//				//	if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y)
//				//	{
//				//		bLand = false;
//				//		pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //ブロックの左に立たせる
//				//														//pMove->x = 0.0f;
//				//	}
//				}
//
//
//			}
//		}
//	}
//
//	return bLand;
//}
//
////================================================================
////テクスチャの生成(読み込み)
////================================================================
//HRESULT CBlock::Load(void)
//{
//	CRenderer *pRenderer;
//	pRenderer = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\runningman000.png",
//		&m_pTexture
//	);
//
//	return S_OK;
//}
//
////================================================================
////テクスチャの破棄
////================================================================
//void CBlock::UnLoad(void)
//{
//	//テクスチャの処理
//	if (m_pTexture != NULL)
//	{//使用されていたら
//
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}
//
////================================================================
////ブロックの取得処理
////================================================================
//CBlock *CBlock::GetBlock(void)
//{
//	return m_aBlock[0];
//}