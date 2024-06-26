//===========================================================
//
// �t�F�[�h���� [fade.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _FADE_H_             //���̃}�N����`������ĂȂ�������
#define _FADE_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "object2D.h"
#include "manager.h"

//===========================================================
// �t�F�[�h�N���X��`
//===========================================================
class CFade
{
public:

	// ���
	enum FADE
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_BLACK,
		FADE_MAX
	};

	CFade();                                   // �R���X�g���N�^
	CFade(CScene::MODE modenext);              // �R���X�g���N�^
	~CFade();                                  // �f�X�g���N�^
												  
	HRESULT Init(void);                        // ����������
	void Uninit(void);                         // �I������
	void Update(void);                         // �X�V����
	void Draw(void);                           // �`�揈��
												  
	// �ݒ�n									   
	void Set(CScene::MODE modenext);           // �ݒ菈��
	void Set(void);

	// �擾�n
	FADE Get(void) { return m_fade; }          // �t�F�[�h�擾
	float GetCol(void) { return m_Color.a; }   // �F�擾

	static CFade *Create(CScene::MODE modenext);                // ����

private:
	LPDIRECT3DTEXTURE9 m_pTexture;              // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         // ���_�����i�[
	FADE m_fade;                                // �t�F�[�h�̏��
	CScene::MODE m_modeNext;                    // ���̉��
	CScene::MODE m_modeOld;                     // ���̉��
	D3DXCOLOR m_Color;                          // �|���S���̐F
	int m_nIdxTexture;                          // �e�N�X�`���̃C���f�b�N�X�ԍ�
	bool m_bFade;                               // �t�F�[�h�����ǂ���
};

#endif