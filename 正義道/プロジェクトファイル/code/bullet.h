//===========================================================
//
// �o���b�g����[bullet.h]
// Author �匴�叫
//
//===========================================================
#ifndef _BULLET_H_             //���̃}�N����`������ĂȂ�������
#define _BULLET_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "billboard.h"

//===========================================================
// �N���X��`
//===========================================================
class CBullet : public CBillBoard
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,  // �����Ȃ�
		TYPE_PLAYER,    // �v���C���[
		TYPE_ENEMY,     // �G
		TYPE_BOM,       // ���e
		TYPE_MAX
	};

	CBullet();                                             // �R���X�g���N�^
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);  // �R���X�g���N�^(�I�[�o�[���[�h)
	~CBullet();                                            // �f�X�g���N�^

	HRESULT Init(void);                                    // ����������    
	void Uninit(void);                                     // �I������
	void Update(void);                                     // �X�V����
	void Draw(void);                                       // �`�揈��

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);  // ����
	static CBullet *GetBullet(void) { return m_Bullet; };                 // �e���擾
	void SetLife(int nLife) { m_nLife = nLife; }                          // �����擾
	int GetLife(void) { return m_nLife; }                                 // �����ݒ�

private:
	D3DXVECTOR3 m_move;                                                   // �ړ�
	D3DXVECTOR3 m_posOld;                                                 // �O��̈ʒu
	int m_nLife;                                                          // ����
	int m_nIdxTexture;                                                    // �e�N�X�`���̔ԍ�
	TYPE m_type;                                                          // ���
	static CBullet *m_Bullet;
};

#endif