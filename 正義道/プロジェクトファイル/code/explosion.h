//===========================================================
//
// �|���S�����o�����[explosion.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EXPLOSION_H_             //���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"

//�}�N����`
#define EXPLOSIONPOS   (80.0f)   //�����̈ʒu
#define EXPLOSIONLIFE  (50)      //�����̎���

//===========================================================
// �N���X��`
//===========================================================
class CExplosion : public CObject2D
{
public:
	CExplosion();  //�R���X�g���N�^
	CExplosion(D3DXVECTOR3 pos);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CExplosion();  //�f�X�g���N�^

	HRESULT Init();      //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����
	void Draw(void);      //�|���S���̕`�揈��

	static CExplosion *Create(D3DXVECTOR3 pos);  //����
	static HRESULT Load(void);  //�e�N�X�`���𐶐�(�ǂݍ���)
	static void UnLoad(void);   //�e�N�X�`����j��
	static CExplosion *GetExplosion(void) { return m_Explosion; };  //�����̎擾

private:
	//void ControlPlayer(void);  //�v���C���[�̐���
	static LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move; //�ړ�
	int m_nLife;  //����
	static CExplosion *m_Explosion;
};

#endif