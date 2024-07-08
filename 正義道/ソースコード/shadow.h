//=============================================================================
//
// �V���h�E���� [shadow.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _SHADOW_H_             //���̃}�N����`������ĂȂ�������
#define _SHADOW_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object3D.h"

//�}�N����`
#define MAX_SHADOW   (128)   //�e�̍ő吔

class CShadow : public CObject3D
{
public:

	CShadow();
	CShadow(D3DXVECTOR3 pos);
	~CShadow();

	typedef enum
	{
		SHADOWTYPE_PLAYER = 0,
		SHADOWTYPE_BULLET,
		SHADOWTYPE_MAX
	}SHADOWTYPE;

	//�v���g�^�C�v�錾
	HRESULT Init(void);       //�e�̏���������    
	void Uninit(void);        //�e�̏I������
	void Update(void);        //�e�̍X�V����
	void Draw(void);          //�e�̕`�揈��
	static CShadow *Create(D3DXVECTOR3 pos);

	CShadow *GetShadow(void);

	int Set(D3DXVECTOR3 pos);
	void SetPosition(int nIdxShadow, D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;
	static CObject3D *m_Shadow[MAX_SHADOW];

	CShadow *m_shadow;

};

#endif