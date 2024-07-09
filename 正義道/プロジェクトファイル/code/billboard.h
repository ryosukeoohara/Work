//===========================================================
//
// �r���{�[�h���� [billboard.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _BILLBOARD_H_             // ���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_             // 2�d�C���N���[�h�h�~�̃}�N����`������

#include "object3D.h"

//===========================================================
// �N���X��`
//===========================================================
class CBillBoard : public CObject3D
{
public:
	CBillBoard();
	~CBillBoard();

	HRESULT Init(void);  // ����������    
	void Uninit(void);   // �I������
	void Update(void);   // �X�V����
	void Draw(void);     // �`�揈��

	static CBillBoard *Create(void);  // ����

private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;       // �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxView;
};


#endif