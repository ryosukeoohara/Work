//===============================================================
//
//チュートリアルAI処理[tutorialAI.h]
// Author 大原怜将
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

	static CTutorialAI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);  //生成
	void ReadText(void);                          //外部ファイル読み込み

private:

	CMotion *m_motion;                   //モーションへのポインタ
	CShadow *m_pShadow;                  //影へのポインタ
	CCharacter *m_apModel[64];           //モデル(パーツ)へのポインタ
	D3DXMATRIX m_mtxWorld;               //ワールドマトリックス

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;

	int m_nNumModel;                     //モデル(パーツ)の総数
	int m_nIdx;
	int m_nParent;
	char m_filename[128] = {};
};

#endif // !_TUTORIALAI_H