//===========================================================
//
// モーション処理[motion.cpp]
// Author 大原怜将
//
//===========================================================
#include "motion.h"
#include "character.h"
#include<stdio.h>
#include<time.h>
#include<string.h>

//===========================================================
// 静的メンバ変数
//===========================================================
int CMotion::m_nObj = 0;

//===========================================================
// コンストラクタ
//===========================================================
CMotion::CMotion()
{
	m_nNumAll = 0;
	m_nType = 0;
	m_nTypeold = 0;
	m_nNumKey = 0;
	m_nKey = 0;
	m_nCounter = 0;
	m_nCntkeySet = 0;
	m_nNumFrame = 0;
	m_nNowFrame = 0;
	m_bLoop = false;
	m_bFinish = false;
}

//===========================================================
// デストラクタ
//===========================================================
CMotion::~CMotion()
{
	
}

//===========================================================
// 初期化処理
//===========================================================
void CMotion::Init(void)
{
	
}

//===========================================================
// 終了処理
//===========================================================
void CMotion::Uninit(void)
{

}

//===========================================================
// 更新処理
//===========================================================
void CMotion::Update(void)
{
	D3DXVECTOR3 fDiffpos, fDiffrot;  //位置、向きの差分
	D3DXVECTOR3 fDestpos, fDestrot;  //位置、向きの目標

	//m_nType = GetType();

	if (m_nCounter >= m_aInfo[m_nType].m_KeySet[m_nKey].m_nFrame)
	{
		m_nKey = (m_nKey + 1) % m_aInfo[m_nType].m_nNumKey;

		m_nCounter = 0;
	}

	int Next = (m_nKey + 1) % m_aInfo[m_nType].m_nNumKey;

	if (m_aInfo[m_nType].m_bFinish == false)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			D3DXVECTOR3 posOrigin = m_ppModel[nCount]->GetPositionOri();
			D3DXVECTOR3 rotOrigin = m_ppModel[nCount]->GetRotOrigin();

			fDiffpos = posOrigin + m_aInfo[m_nType].m_KeySet[Next].m_aKey[nCount].m_pos - m_aOldInfo[nCount].m_pos;
			fDiffrot = rotOrigin + m_aInfo[m_nType].m_KeySet[Next].m_aKey[nCount].m_rot - m_aOldInfo[nCount].m_rot;

			// 補正
			if (fDiffrot.x > D3DX_PI)
			{
				fDiffrot.x -= D3DX_PI * 2.0f;
			}
			else if (fDiffrot.x < -D3DX_PI)
			{
				fDiffrot.x += D3DX_PI * 2.0f;
			}

			if (fDiffrot.y > D3DX_PI)
			{
				fDiffrot.y -= D3DX_PI * 2.0f;
			}
			else if (fDiffrot.y < -D3DX_PI)
			{
				fDiffrot.y += D3DX_PI * 2.0f;
			}

			if (fDiffrot.z > D3DX_PI)
			{
				fDiffrot.z -= D3DX_PI * 2.0f;
			}
			else if (fDiffrot.z < -D3DX_PI)
			{
				fDiffrot.z += D3DX_PI * 2.0f;
			}

			fDestpos = m_aOldInfo[nCount].m_pos + fDiffpos * ((float)m_nCounter / (float)m_aInfo[m_nType].m_KeySet[m_nKey].m_nFrame);
			fDestrot = m_aOldInfo[nCount].m_rot + fDiffrot * ((float)m_nCounter / (float)m_aInfo[m_nType].m_KeySet[m_nKey].m_nFrame);

			// 補正
			if (fDestrot.x > D3DX_PI)
			{
				fDestrot.x -= D3DX_PI * 2.0f;
			}
			else if (fDestrot.x < -D3DX_PI)
			{
				fDestrot.x += D3DX_PI * 2.0f;
			}

			if (fDestrot.y > D3DX_PI)
			{
				fDestrot.y -= D3DX_PI * 2.0f;
			}
			else if (fDestrot.y < -D3DX_PI)
			{
				fDestrot.y += D3DX_PI * 2.0f;
			}

			if (fDestrot.z > D3DX_PI)
			{
				fDestrot.z -= D3DX_PI * 2.0f;
			}
			else if (fDestrot.z < -D3DX_PI)
			{
				fDestrot.z += D3DX_PI * 2.0f;
			}

			m_ppModel[nCount]->SetPosition(fDestpos);
			m_ppModel[nCount]->SetRot(fDestrot);
		}

		m_nCounter++;
		m_nNowFrame++;

		if (m_aInfo[m_nType].m_nLoop == 0 && m_nKey + 1 >= m_aInfo[m_nType].m_nNumKey)
		{
			m_aInfo[m_nType].m_bFinish = true;
			m_nNowFrame = 0;
		}

		if (m_nCounter >= m_aInfo[m_nType].m_KeySet[m_nKey].m_nFrame)
		{
			SetInfo();
		}
	}
}

//===========================================================
// 設定処理
//===========================================================
void CMotion::Set(int nType)
{	
	SetInfo();

	m_nTypeold = m_nType;

	m_nType = nType;

	m_aInfo[nType].m_bFinish = false;

	m_nCounter = 0;
	m_nKey = 0;
	m_nNowFrame = 0;
}

//===========================================================
// 種類取得処理
//===========================================================
int CMotion::GetType(void)
{
	return m_nType;
}

//===========================================================
// 現在のフレーム取得
//===========================================================
int CMotion::GetNowFrame(void)
{
	return m_nNowFrame;
}

//===========================================================
// 攻撃判定発生フレーム取得
//===========================================================
int CMotion::GetAttackOccurs(void)
{
	return m_aInfo[m_nType].m_nAttackOccurs;
}

//===========================================================
// 攻撃判定終了フレーム取得
//===========================================================
int CMotion::GetAttackEnd(void)
{
	return m_aInfo[m_nType].m_nAttackEnd;
}

//===========================================================
// 攻撃力
//===========================================================
int CMotion::GetAttackDamege(void)
{
	return m_aInfo[m_nType].m_nAttackDamege;
}

//===========================================================
// 無敵開始フレーム
//===========================================================
int CMotion::GetInvincibleStrat(void)
{
	return m_aInfo[m_nType].m_nInvincibleStart;
}

//===========================================================
// 無敵終了フレーム
//===========================================================
int CMotion::GetInvincibleEnd(void)
{
	return m_aInfo[m_nType].m_nInvincibleEnd;
}

//===========================================================
// キャンセル可能フレーム取得
//===========================================================
int CMotion::GetCancellFrame(void)
{
	return m_aInfo[m_nType].nCancellFrame;
}

//===========================================================
// キャンセル可能終了フレーム取得
//===========================================================
int CMotion::GetCancellFrameEnd(void)
{
	return m_aInfo[m_nType].nCancellFrameEnd;
}

//===========================================================
// 吹っ飛び
//===========================================================
float CMotion::GetKnockBack(void)
{
	return m_aInfo[m_nType].m_nKnockBack;
}

//===========================================================
// 設定処理
//===========================================================
CMotion::INFO CMotion::GetInfo(void)
{
	return m_aInfo[m_nType];
}

//===========================================================
// 終了したかどうか
//===========================================================
bool CMotion::IsFinish(void)
{
	return m_aInfo[m_nType].m_bFinish;
}

//===========================================================
// 情報設定処理
//===========================================================
void CMotion::SetInfo(void)
{
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_aOldInfo[nCount].m_pos = m_ppModel[nCount]->GetPosition();
		m_aOldInfo[nCount].m_rot = m_ppModel[nCount]->GetRot();
	}
}

//===========================================================
// 情報設定処理
//===========================================================
void CMotion::SetModel(CCharacter **ppModel, int nNumModel)
{
	m_ppModel = ppModel;
	m_nNumModel = nNumModel;
}

//===========================================================
// 外部ファイル読み込み
//===========================================================
void CMotion::ReadText(const char *TextFilename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(TextFilename, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("MOTIONSET", aString) == 0)
				{
					while (strcmp("END_MOTIONSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("LOOP", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nLoop);
						}

						if (strcmp("NUM_KEY", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nNumKey);
						}

						if (strcmp("NUM_FRAME", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nNumFrame);
						}

						if (strcmp("STRAT_COLLI", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nAttackOccurs);
						}

						if (strcmp("END_COLLI", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nAttackEnd);
						}

						if (strcmp("ATTACK", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nAttackDamege);
						}

						if (strcmp("STRAT_CANCEL", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].nCancellFrame);
						}

						if (strcmp("END_CANCEL", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].nCancellFrameEnd);
						}

						if (strcmp("KNOCKBACK", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_nKnockBack);
						}

						if (strcmp("STRAT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nInvincibleStart);
						}

						if (strcmp("END", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);
							fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_nInvincibleEnd);
						}

						if (strcmp("KEYSET", aString) == 0)
						{
							while (strcmp("END_KEYSET", aString) != 0)
							{
								fscanf(pFile, "%s", &aString);

								if (strcmp("FRAME", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);
									fscanf(pFile, "%d", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_nFrame);
								}

								if (m_aInfo[nCntMotion].m_nNumKey != nCntKeySet)
								{
									if (strcmp("PARTS", aString) == 0)
									{
										while (strcmp("END_PARTS", aString) != 0)
										{
											fscanf(pFile, "%s", &aString);

											if (strcmp("POS", aString) == 0)
											{
												fscanf(pFile, "%s", &aString);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_pos.x);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_pos.y);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_pos.z);
											}

											if (strcmp("ROT", aString) == 0)
											{
												fscanf(pFile, "%s", &aString);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_rot.x);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_rot.y);
												fscanf(pFile, "%f", &m_aInfo[nCntMotion].m_KeySet[nCntKeySet].m_aKey[nCntKey].m_rot.z);
											}
										}


										nCntKey++;
									}
								}
							}

							nCntKeySet++;
							nCntKey = 0;
						}
					}

					nCntMotion++;
					nCntKeySet = 0;
				}
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===========================================================
// 角度直す
//===========================================================
void CMotion::RotCorrect(float rot)
{
	if (rot > D3DX_PI)
	{
		rot -= D3DX_PI * 2.0f;
	}
	else if (rot < -D3DX_PI)
	{
		rot += D3DX_PI * 2.0f;
	}
}