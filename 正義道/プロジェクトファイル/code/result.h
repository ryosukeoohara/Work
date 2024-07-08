//===========================================================
//
//�|���S�����o�����[title.h]
//Author �匴�叫
//
//===========================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "manager.h"
#include "object2D.h"

//���U���g�N���X
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult *Create(void);

private:
	int m_nIdxTexture;                          //�e�N�X�`���̃C���f�b�N�X�ԍ�
	CObject2D *m_apObject2D;

};
#endif // !_TITLE_H_