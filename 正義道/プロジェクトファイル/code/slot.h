//===========================================================
//
// �X���b�g����[slot.h]
// Author �匴�叫
//
//===========================================================
#ifndef _SLOT_H_             //���̃}�N����`������ĂȂ�������
#define _SLOT_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "itemslot.h"
#include "item.h"
#include "frame.h"

//�}�N����`
#define MAX_SLOT   (2)  //�X���b�g�̍ő吔

//===========================================================
// �N���X��`
//===========================================================
class CSlot : public CItemSlot
{
public:

	CSlot();                                //�R���X�g���N�^
	CSlot(D3DXVECTOR3 pos);                 //�R���X�g���N�^(�I�[�o�[���[�h)
	~CSlot();                               //�f�X�g���N�^

	HRESULT Init(void);                     //�|���S���̏���������    
	void Uninit(void);                      //�|���S���̏I������
	void Update(void);                      //�|���S���̍X�V����
	void Draw(void);                        //�|���S���̕`�揈��

	static CSlot *Create(void);             //����

	void Collision(void);
	static void Set(CItem::TYPE type);

	//CItemSlot::TYPE GetAttackType(void) { return m_type; }

private:
	struct SLOT
	{
		bool m_bUse;
		CFrame::TYPE m_type;
	};

	static LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	//static bool m_bUse[MAX_SLOT];

	static SLOT m_aSlot[MAX_SLOT];

	static CItemSlot *m_apItemSlot[MAX_SLOT];
};

#endif