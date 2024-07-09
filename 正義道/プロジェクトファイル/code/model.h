//=============================================================================
//
// ���f������ [model.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "objectX.h"

//�}�N����`
#define MAX_MODEL   (1024)   //�e�N�X�`���̍ő吔

//===========================================================
// �N���X��`
//===========================================================
class CModel
{
public:
	CModel();
	~CModel();

	//�e�N�X�`���̎��
	typedef enum
	{
		TYPE_PLAYER = 0,  //�v���C���[
		TYPE_ENEMY,       //�G
		TYPE_BULLET,      //�e
		TYPE_MAX
	} TYPE;

	const char *c_apFilename[TYPE_MAX] =
	{
		"data\\TEXTURE\\niwatori.png",
		"data\\TEXTURE\\003.png",
		"data\\TEXTURE\\000.png"
	};

	struct MODEL
	{
		char aName[64] = "a";
		CObjectX *m_aModel;  //���f��(�p�[�c)�ւ̃|�C���^
	};

	//typedef struct
	//{
	//	D3DXVECTOR3 m_pos;
	//	D3DXVECTOR3 m_posOrigin;
	//	D3DXVECTOR3 m_rot;
	//	D3DXVECTOR3 m_rotOrigin;
	//	D3DXVECTOR3 m_vtxMini;    //���f���̍ŏ��l
	//	D3DXVECTOR3 m_vtxMax;     //���f���̍ő�l
	//	LPD3DXMESH m_pMesh;       //�e�N�X�`���ւ̃|�C���^
	//	LPD3DXBUFFER m_pBuffMat;  //���_�o�b�t�@�ւ̃|�C���^
	//	DWORD m_dwNumMat;         //�}�e���A���̐�
	//	D3DXMATRIX m_mtxWorld;    //���[���h�}�g���b�N�X

	//} MODEL;

	HRESULT Load(void);
	void UnLoad(void);

	int Regist(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);
	CObjectX GetAddress(int nIdx);

	int GetNumTexture(void) { return m_nNumAll; };

private:
	LPDIRECT3DTEXTURE9  *m_pTexture;     //�e�N�X�`���ւ̃|�C���^
	static int m_nNumAll;
	
	MODEL m_aModel[MAX_MODEL];
};

#endif // !_TEXTURE_H_