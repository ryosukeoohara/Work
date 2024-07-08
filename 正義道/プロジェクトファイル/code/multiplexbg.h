//===========================================================
//
//�|���S�����o�����[multiplexbg.h]
//Author �匴�叫
//
//===========================================================
#ifndef _MULTIPLEXBG_H_             //���̃}�N����`������ĂȂ�������
#define _MULTIPLEXBG_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object.h"

//���d�w�i�N���X
class CMultiplexBg : public CObject
{
public:
	CMultiplexBg();  //�R���X�g���N�^
	~CMultiplexBg();  //�f�X�g���N�^

	typedef enum
	{
		TYPETEX_00 = 0,
		TYPETEX_01,
		TYPETEX_02,
		TYPETEX_MAX
	}TYPETEX;

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	static void UnLoad(void);   //�e�N�X�`���̔j��

	static CMultiplexBg *Create(void);  //����

	static float m_fTexV;
	static float m_fTexU;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPETEX_MAX];  //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    //���_�����i�[
	static CObject2D *m_apObject2D[TYPETEX_MAX];

};


#endif