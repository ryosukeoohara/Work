////===========================================================
////
////�|���S�����o�����[block.cpp]
////Author �匴�叫
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
////�ÓI�����o�ϐ��錾
////================================================================
//LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;
//CObject2D *CBlock::m_apObject2D[MAX_BLOCK] = {};
//CBlock *CBlock::m_aBlock[MAX_BLOCK] = {};                       //�u���b�N�̏��
//
////================================================================
////�R���X�g���N�^
////================================================================
//CBlock::CBlock()
//{
//	
//}
//
////================================================================
////�R���X�g���N�^(�I�[�o�[���[�h)
////================================================================
//CBlock::CBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
//{
//	//m_pos = pos;  //�ʒu
//	//m_fWidth = fWidth;
//	//m_fHeight = fHeight;
//	SetPosition(pos);
//	//SetType(type);
//}
//
////================================================================
////�f�X�g���N�^
////================================================================
//CBlock::~CBlock()
//{
//
//}
//
////================================================================
////��������
////================================================================
//CBlock *CBlock::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
//{
//	//�I�u�W�F�N�g2D�̃|�C���^
//	CBlock *pBlock = NULL;
//
//	if (pBlock == NULL)
//	{
//		//�I�u�W�F�N�g2D�̐���
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
//		//�e�N�X�`�����o�C���h
//		pBlock->BindTexture(m_pTexture);
//
//		//����������
//		pBlock->Init();
//	}
//
//	return pBlock;
//}
//
////================================================================
////�e�̏���������
////================================================================											 
//HRESULT CBlock::Init(void)
//{
//	//�I�u�W�F�N�g�𐶐�
//	CObject2D::Create({ 0.0f,0.0f,0.0f });
//
//	//����������
//	CObject2D::Init();
//
//	return S_OK;
//}
//
////================================================================
////�|���S���̏I������
////================================================================
//void CBlock::Uninit(void)
//{
//	//�I������
//	CObject2D::Uninit();
//}
//
////================================================================
////�e�̍X�V����
////================================================================
//void CBlock::Update(void)
//{
//	//�ݒ菈��
//	SetVtxBlock(m_pos, m_fWidth, m_fHeight);
//}
//
////================================================================
////�e�̕`�揈��
////================================================================
//void CBlock::Draw(void)
//{
//	//�`�揈��
//	CObject2D::Draw();
//}
//
////================================================================
////�����蔻��
////================================================================
//bool CBlock::CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
//{
//	bool bLand = false;   //���n�������ǂ���
//
//	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
//	{
//		if (m_aBlock[nCount] != NULL)
//		{
//			if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//			{
//				//�u���b�N�̏�======================================
//				if (m_aBlock[nCount]->m_pos.y >= pPosOld->y && m_aBlock[nCount]->m_pos.y <= pPos->y)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y;   //�u���b�N�̏�ɗ�������
//					pMove->y = 0.0f;     //�ړ��ʂ�0�ɂ���
//				}
//
//				//�u���b�N�̂���====================================
//				else if (m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPosOld->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					bLand = false;
//					pPos->y = m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight + fHeight;   //�u���b�N�̉��ɗ�������
//					pMove->y = 0.0f;       //�ړ��ʂ�0�ɂ���
//				}
//
//				if (m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y
//				 || m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y
//				 && m_aBlock[nCount]->m_pos.y <= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					//�u���b�N�̍�����==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //�u���b�N�̍��ɗ�������
//						pMove->x = 0.0f;
//					}
//
//					//�u���b�N�̉E����==================================
//					else if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //�u���b�N�̉E�ɗ�������
//						pMove->x = 0.0f;
//					}
//
//					//�E�΂�==================================
//					if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//						&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y
//						/*|| m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//						&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight < pPos->y*/
//						/*&& m_aBlock[nCount]->m_pos.y >= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y*/)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //�u���b�N�̉E�ɗ�������
//						//pMove->x = 0.0f;
//					}
//
//					//���΂�==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth
//				     && m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y)
//					{
//						bLand = false;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //�u���b�N�̍��ɗ�������
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
////�����蔻��
////================================================================
//bool CBlock::CollisionBulletBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
//{
//	bool bLand = false;   //���n�������ǂ���
//
//	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
//	{
//		if (m_aBlock[nCount] != NULL)
//		{
//			if (m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth && m_aBlock[nCount]->m_pos.x >= pPos->x
//			 || m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x && m_aBlock[nCount]->m_pos.x <= pPos->x)
//			{
//				//�u���b�N�̏�======================================
//				if (m_aBlock[nCount]->m_pos.y >= pPosOld->y && m_aBlock[nCount]->m_pos.y <= pPos->y + fHeight)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y - fWidth;   //�u���b�N�̍��ɗ�������
//					pMove->y = 0.0f;
//				}
//
//				//�u���b�N�̂���====================================
//				else if (m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y - fHeight)
//				{
//					bLand = true;
//					pPos->y = m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight + fHeight;   //�u���b�N�̉��ɗ�������
//					pMove->y = 0.0f;       //�ړ��ʂ�0�ɂ���
//				}
//
//				if (m_aBlock[nCount]->m_pos.y <= pPos->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight >= pPos->y)
//				{
//					//�u���b�N�̍�����==================================
//					if (m_aBlock[nCount]->m_pos.x >= pPosOld->x && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth)
//					{
//						bLand = true;
//						pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //�u���b�N�̍��ɗ�������
//						pMove->x = 0.0f;
//					}
//
//					//�u���b�N�̉E����==================================
//					else if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPosOld->x && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPos->x - fWidth)
//					{
//						bLand = true;
//						pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //�u���b�N�̉E�ɗ�������
//						pMove->x = 0.0f;
//					}
//
//				//	//�E�΂�==================================
//				//	if (m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y
//				//		/*|| m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth >= pPosOld->x - fWidth && m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth <= pPos->x
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight < pPos->y*/
//				//		/*&& m_aBlock[nCount]->m_pos.y >= pPos->y - fHeight && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight <= pPos->y*/)
//				//	{
//				//		bLand = false;
//				//		pPos->x = m_aBlock[nCount]->m_pos.x + m_aBlock[nCount]->m_fWidth + fWidth;   //�u���b�N�̉E�ɗ�������
//				//																					 //pMove->x = 0.0f;
//				//	}
//
//				//	//���΂�==================================
//				//	if (m_aBlock[nCount]->m_pos.x >= pPosOld->x + fWidth && m_aBlock[nCount]->m_pos.x <= pPos->x + fWidth
//				//		&& m_aBlock[nCount]->m_pos.y < pPosOld->y && m_aBlock[nCount]->m_pos.y + m_aBlock[nCount]->m_fHeight > pPos->y)
//				//	{
//				//		bLand = false;
//				//		pPos->x = m_aBlock[nCount]->m_pos.x - fWidth;   //�u���b�N�̍��ɗ�������
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
////�e�N�X�`���̐���(�ǂݍ���)
////================================================================
//HRESULT CBlock::Load(void)
//{
//	CRenderer *pRenderer;
//	pRenderer = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\runningman000.png",
//		&m_pTexture
//	);
//
//	return S_OK;
//}
//
////================================================================
////�e�N�X�`���̔j��
////================================================================
//void CBlock::UnLoad(void)
//{
//	//�e�N�X�`���̏���
//	if (m_pTexture != NULL)
//	{//�g�p����Ă�����
//
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}
//
////================================================================
////�u���b�N�̎擾����
////================================================================
//CBlock *CBlock::GetBlock(void)
//{
//	return m_aBlock[0];
//}