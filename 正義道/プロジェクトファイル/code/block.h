//===========================================================
//
//�|���S�����o�����[block.h]
//Author �匴�叫
//
//===========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "object2D.h"

//�}�N����`
#define MAX_BLOCK       (128)       //�u���b�N�̍ő吔
#define BLOCK_WIDTH     (50.0f)     //�u���b�N�̕�
#define BLOCK_HEIGHT    (50.0f)     //�u���b�N�̍���
#define BLOCK_MOVEY     (0.5f)      //�u���b�N�̈ړ���

//�u���b�N�̎��
typedef enum
{
	BLOCKTYPE_NORMAL = 0,  //�����Ȃ��u���b�N
	BLOCKTYPE_MOVE,        //�����u���b�N
} BLOCKSTATE;

//�u���b�N�N���X
class CBlock : public CObject2D
{
public:
	CBlock();
	CBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);
	~CBlock();

	HRESULT Init(void);       //�u���b�N�̏���������    
	void Uninit(void);        //�u���b�N�̏I������
	void Update(void);        //�u���b�N�̍X�V����
	void Draw(void);          //�u���b�N�̕`�揈��

	static CBlock *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);  //����
	static HRESULT Load(void);  //�e�N�X�`�������[�h
	static void UnLoad(void);   //�e�N�X�`����j��

	void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
	bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);
	bool CollisionBulletBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

	static CBlock *GetBlock(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	static CObject2D *m_apObject2D[MAX_BLOCK];
	static CBlock *m_aBlock[MAX_BLOCK];         //�u���b�N�̏��
};


#endif