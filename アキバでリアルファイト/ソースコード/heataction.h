//===========================================================
//
// �q�[�g�A�N�V����[heataction.h]
// Author �匴�叫
//
//===========================================================
#ifndef _HIEATACTION_H_
#define _HIEATACTION_H_

//===========================================================
// �C���N���[�h�t�@�C��
//===========================================================
#include "player.h"

//===========================================================
// �O���錾
//===========================================================
class CEnemy;
class CItem;

//===========================================================
// �q�[�g�A�N�V�����N���X��`
//===========================================================
class CHeatAction
{
public:

	void Init(void);
	void Uninit(void);
	void Updata(void);

	void BikeCrash(CPlayer* pPlayer, CEnemy* pEnemy);                         // ���]�Ԃ��g�p�����A�N�V����
	void MicroWave(CPlayer* pPlayer, CEnemy* pEnemy, CItem *pItem);           // �d�q�����W���g�p�����A�N�V����
	void SetAction(CPlayer::HEAT heatact, CPlayer* pPlayer, CEnemy* pEnemy);  // �A�N�V������ݒ�

private:

	CPlayer::HEAT m_HeatAct;
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy;

	int m_nHeatActTime;

	bool m_bInMicroWave = false;;  // �q�[�g�A�N�V����:�d�q�����W�œG���d�q�����W�̒��ɓ��������ǂ���

};

#endif