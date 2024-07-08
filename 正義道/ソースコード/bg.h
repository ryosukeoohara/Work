//===========================================================
//
//�|���S�����o�����[bg.h]
//Author �匴�叫
//
//===========================================================
#ifndef _BG_H_             //���̃}�N����`������ĂȂ�������
#define _BG_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//�w�i�N���X
class CBg : public CObject2D
{
public:
	CBg();  //�R���X�g���N�^
	~CBg();  //�f�X�g���N�^

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	static void UnLoad(void);   //�e�N�X�`���̔j��

	static CBg *Create(void);  //����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    //���_�����i�[
};

#endif