//=============================================================================
//
// シーン [scene2D.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点処理
	float rhw;			// 1.0で固定
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャの座標
} VERTEX_2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	D3DXVECTOR3 GetPosition(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetExplosionTex(int nCnt);
	void SetBgTex(float fTexU, float fTexV);

	D3DXVECTOR3 GetScale(void) { return m_Polygon.scale; }

	void CScene2D::SetEffect(D3DXCOLOR col, float nData);

	void CScene2D::SetPlayerCol(float nData);
	//D3DXCOLOR GetColor(void) { return m_col; }

	void SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 scale);


	typedef struct
	{
		D3DXVECTOR3 pos;	// ポリゴンの位置
		D3DXVECTOR3 scale;	// ポリゴンの拡縮倍率
		float fLength;		// ポリゴンの対角線の長さ
		float fAngle;		// ポリゴンの対角線の角度
		D3DXCOLOR col;		// ポリゴンのカラー
	} POLYGON;


private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	
	POLYGON m_Polygon;
};

#endif
