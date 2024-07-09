//===========================================================
//
// ���ڐ��̏���[effectline.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFECTLINE_H_             //���̃}�N����`������ĂȂ�������
#define _EFFECTLINE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//===============================================================
// �N���X��`
//===============================================================
class CEffectLine : public CObject2D
{
public:
	CEffectLine();  //�R���X�g���N�^
	~CEffectLine();  //�f�X�g���N�^

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	static void UnLoad(void);   //�e�N�X�`���̔j��

	static CEffectLine *Create(void);  //����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    //���_�����i�[

	int m_nIdxTexture;   //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCounter;      //�W������������܂ł̎���
};

#endif