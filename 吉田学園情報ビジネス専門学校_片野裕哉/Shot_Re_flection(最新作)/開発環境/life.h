//=============================================================================
//
//	残機 [life.h]
//	Author:Hiroya Katano
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "number.h"
#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEX					(2)

//-------------------------------------------------------------------------------
// 背景クラス(派生クラス)
//-------------------------------------------------------------------------------
class CLife : public CScene
{
public:
	CLife(int nPriority = 3);
	~CLife();

	static HRESULT Load(void);
	static void Unload(void);
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLife(int nLife);
	void AddLife(int nValue);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }
	static int GetLife(void) { return m_nLife; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX];			// テクスチャのポインタ
	CScene2D *m_apScene2D[MAX_TEX];							// 2Dポリゴンのポインタ
	CNumber *m_pNumber;										// ナンバーのポインタ
	static int m_nLife;											// 残機数

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
};

#endif
