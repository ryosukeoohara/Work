//===============================================================
//
// �^�C�g��UI����[titleUI.h]
// Author �匴�叫
//
//===============================================================
#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "object2D.h"

#define MAX_TUTOOBJ     (8)

//===========================================================
// �N���X��`
//===========================================================
class CTitleUI : public CObject2D
{
public:
	CTitleUI();
	~CTitleUI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleUI *Create(D3DXVECTOR3 pos);

private:
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCntMove;                             //�Ăшړ����n�߂�܂ł̃J�E���g
	float m_colA;                               //�����x
	TYPE m_type;                                //���
	D3DXCOLOR m_col;                            //�F
};

#endif