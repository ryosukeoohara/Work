//=============================================================================
//
// �V���h�E���� [shadow.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _LIFE_H_             //���̃}�N����`������ĂȂ�������
#define _LIFE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "billboard.h"

//�}�N����`
#define MAX_SHADOW   (128)   //�e�̍ő吔

class CLife : public CBillBoard
{
public:

	CLife();
	CLife(D3DXVECTOR3 pos);
	~CLife();

	typedef enum
	{
		SHADOWTYPE_PLAYER = 0,
		SHADOWTYPE_BULLET,
		SHADOWTYPE_MAX
	}SHADOWTYPE;

	//�v���g�^�C�v�錾
	HRESULT Init(void);          //�e�̏���������    
	void Uninit(void);        //�e�̏I������
	void Update(void);        //�e�̍X�V����
	void Draw(void);          //�e�̕`�揈��
	static CLife *Create(D3DXVECTOR3 pos);

	CLife *Get(void);

	static int Set(D3DXVECTOR3 pos);
	void SetPosition(int nIdxShadow, D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;
	static CBillBoard *m_Life[MAX_SHADOW];

	CLife *m_shadow;

};

#endif