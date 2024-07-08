//===========================================================
//
//�|���S�����o�����[effextsord.h]
//Author �匴�叫
//
//===========================================================
#ifndef _EFFECTSORD_H_
#define _EFFECTSORD_H_

#include "object3D.h"

class CEffectSword : public CObject3D
{
public:
	CEffectSword();
	CEffectSword(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~CEffectSword();

	HRESULT Init(void);   //�a���G�t�F�N�g�̏���������    
	void Uninit(void);    //�a���G�t�F�N�g�̏I������
	void Update(void);    //�a���G�t�F�N�g�̍X�V����
	void Draw(void);      //�a���G�t�F�N�g�̕`�揈��

	static CEffectSword *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //����

private:
	int m_nIdxTexture;  //�e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_DispCounter;  //�`�悵�Ă��鎞��
	D3DXCOLOR m_col;    //�F

};

#endif // !_FIELD_H_