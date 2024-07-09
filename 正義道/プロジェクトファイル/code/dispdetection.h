//===========================================================
//
// �|���S�����o�����[dispdetection.h]
// Author �匴�叫
//
//===========================================================
#ifndef _DISPDETECTION_H_             //���̃}�N����`������ĂȂ�������
#define _DISPDETECTION_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "object3D.h"

//===========================================================
// �N���X��`
//===========================================================
class CDISPDETECTION : public CObject3D
{
public:

	enum TYPE
	{
		TYPE_NEAR = 0,
		TYPE_FAR,
		TYPE_MAX
	};

	CDISPDETECTION();  //�R���X�g���N�^
	CDISPDETECTION(D3DXVECTOR3 pos);  //�R���X�g���N�^
	~CDISPDETECTION();  //�f�X�g���N�^

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static CDISPDETECTION *Create(D3DXVECTOR3 pos);  //����

	static CDISPDETECTION *GetFrame(void) { return m_DispDetection; }
	CDISPDETECTION::TYPE GetACType(void) { return m_type; }

private:
	static CDISPDETECTION *m_DispDetection;
	int m_nIdxTexture;

	CDISPDETECTION::TYPE m_type;
	D3DXCOLOR m_col;    //�F

};

#endif