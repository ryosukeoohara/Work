//===============================================================
//
//�`���[�g���A��AI����[tutorialAI.h]
// Author �匴�叫
//
//===============================================================
#ifndef _TUTORIALAI_H
#define _TUTORIALAI_H_

#include "object.h"

class CMotion;
class CShadow;
class CCharacter;

class CTutorialAI : public CObject
{
public:
	CTutorialAI();
	CTutorialAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CTutorialAI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialAI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //����
	void ReadText(void);                          //�O���t�@�C���ǂݍ���

private:

	CMotion *m_motion;                   //���[�V�����ւ̃|�C���^
	CShadow *m_pShadow;                  //�e�ւ̃|�C���^
	CCharacter *m_apModel[64];           //���f��(�p�[�c)�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;               //���[���h�}�g���b�N�X

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;

	int m_nNumModel;                     //���f��(�p�[�c)�̑���
	int m_nIdx;
	int m_nParent;
	char m_filename[128] = {};
};

#endif // !_TUTORIALAI_H