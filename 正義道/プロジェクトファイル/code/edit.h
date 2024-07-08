//===========================================================
//
//�|���S�����o�����[edit.h]
//Author �匴�叫
//
//===========================================================
#ifndef _EDIT_H_
#define _EDIT_H_
#include "main.h"
#include "objectX.h"

//�}�N����`
#define MAX_MODELSET    (1028)

class CEdit
{
public:
	CEdit();
	~CEdit();

	typedef enum
	{
		MODELTYPE_BOSS = 0,
		MODELTYPE_KEN,
		MODELTYPE_MAX
	} MODELTYPE;

	typedef struct
	{
		char m_filename[128] = {};
	} MODEL;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);
	void Load(void);
	void ReadText(void);

private:
	LPDIRECT3DTEXTURE9  *m_pTexture;    //�e�N�X�`���ւ̃|�C���^
	CObjectX *m_apModel[MAX_MODELSET];  //���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;  //�ǂݍ��񂾃��f���̑���
	int m_nIdx;
	MODEL m_Model[1024];

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;

	D3DXVECTOR3 m_vtxMini;    //���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMax;     //���f���̍ő�l
	LPD3DXMESH   m_pMesh   ;       //�e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;  //���_�o�b�t�@�ւ̃|�C���^
	DWORD m_dwNumMat;         //�}�e���A���̐�
	D3DXMATRIX m_mtxWorld;    //���[���h�}�g���b�N�X

	char m_filename[128] = {};
};
#endif // !_EDIT_H_