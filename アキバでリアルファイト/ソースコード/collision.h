//===========================================================
//
// �����蔻�菈�� [collision.h]
// Author : �匴�@�叫
//
//===========================================================
#ifndef _CONLLISION_H_
#define _CONLLISION_H_

//===========================================================
// �O���錾
//===========================================================
class CEnemyManager;
class CPlayer;
class CEnemy;
class CBullet;
class CObjectX;
class CItem;

//===========================================================
// �R���W�����N���X��`
//===========================================================
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);

	static CCollision *Create(void);

	bool Enemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy **pEnemy);    // �G�Ƃ̓����蔻��(�v���C���[�)
	bool Circle(D3DXVECTOR3 *pMyPos, D3DXVECTOR3 *pTargetPos, float fMyRadius, float fTargetRadius);     // �~�̓����蔻��
	void AttackCircle(D3DXVECTOR3 *pMyPos, float fMyRadius, float fTargetRadius, float fHeight);         // �~�̓����蔻��
	bool Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer);  // �Ղꂢ��[�Ƃ̓����蔻��
	void Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fRadius);                                      // �}�b�v�ɂ��錚���Ƃ̓����蔻��
	bool Block(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ);                     // �u���b�N�Ƃ̔���
	bool Sword(D3DXMATRIX matrix1, D3DXMATRIX matrix2, float flength, CEnemy *pEnemy);
	void MapEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX, CEnemy *enemy);            // �}�b�v�ɂ��錚���Ƃ̓����蔻��
	bool Item(D3DXVECTOR3 *pos);
	void ItemAttack(CObjectX *pobj);
	bool ItemEnemy(CItem *pItem, CEnemy *pEnemy, float fMyRadius, float fTargetRadius, float fHeight);   // �A�C�e���ƓG�̔���
	D3DXVECTOR3 *CheckEnemy(D3DXVECTOR3 *pMyPos, D3DXVECTOR3 *pMyOldPos, D3DXVECTOR3 *pTargetPos, float fMyRadius);                      // �G�Ƃ̓����蔻��

	void SetbColli(bool bValue) { m_bColli = bValue; }
	bool GetbColli(void) { return m_bColli; }
	static CCollision *GetColl(void) { return m_pColli; }
	
private:
	static CCollision *m_pColli;
	bool m_bColli;

};

#endif // !_CONLLISION_H_