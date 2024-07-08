//===========================================================
//
//�|���S�����o�����[item.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ITEM_H_             //���̃}�N����`������ĂȂ�������
#define _ITEM_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "objectX.h"



//�A�C�e���N���X
class CItem : public CObject
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NEAR,      //�ߋ���
		TYPE_FAR,       //������
		TYPE_NAILBAT,   //�B�o�b�g
		TYPE_BOM,       //���e
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		STATE_NONE = 0,
		STATE_FALL,
		STATE_LAND,
		STATE_MAX
	} STATE;

	CItem();  //�R���X�g���N�^
	CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CItem();  //�f�X�g���N�^

	HRESULT Init(void);      //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����
	void Draw(void);      //�|���S���̕`�揈��

	static CItem *Create(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //����
	//static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	//static void UnLoad(void);   //�e�N�X�`���̔j��
	static CItem *GetItem(void) { return m_Item; };  //�e���擾
	void SetState(STATE state) { m_state = state; }

private:
	//static LPDIRECT3DTEXTURE9 m_pTexture[ITEMTYPE_MAX];        //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_move; //�ړ�
	int m_nLife;  //����
	const char *m_aFilename;  //X�t�@�C���̖��O
	CObjectX *m_apModel[128];  //���f��(�p�[�c)�ւ̃|�C���^
	TYPE m_ItemType;
	static CItem *m_Item;
	int m_Indx;
	STATE m_state;

	bool CollisionItem(D3DXVECTOR3 pos);  //�G�Ƃ̓����蔻��
};

#endif