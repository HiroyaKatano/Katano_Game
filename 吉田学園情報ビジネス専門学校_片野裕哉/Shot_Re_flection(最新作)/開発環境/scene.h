//=============================================================================
//
// シーン [scene.h]
// Author : Hiroya Katano
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLY2D		(8192)			// 2Dポリゴンクラスの最大数
#define MAX_PRIORITY_NUM (4)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	enum PRIORITY
	{
		PRIORITY_NONE,
		PRIORITY_BG,
		PRIORITY_BULLET,
		PRIORITY_EFFECT,
		PRIORITY_EXPLOSION,
		PRIORITY_ENEMY,
		PRIORITY_PLAYER,
		PRIORITY_UI,
		PRIORITY_MAX
	};

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_ENEMY,		// 敵
		OBJTYPE_BOSS,		// ボス
		OBJTYPE_EFFECT,		// エフェクト
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_MAX
	} OBJTYPE;

	CScene(int nPriority = 2);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	D3DXVECTOR3 SetPos(void);

	void SetObjType(OBJTYPE objType) { m_objType = objType; }
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority, int nCntScene) { return m_apScene[nPriority][nCntScene]; }
	virtual D3DXVECTOR3 GetPosition(void) = 0;
	virtual D3DXVECTOR3 GetScale(void) = 0;

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_PRIORITY_NUM][MAX_POLY2D];
	static int m_nNumAll;

	int m_nPriority;	// 優先順位の番号
	int m_nID;			// 格納先の番号

	OBJTYPE m_objType;	// オブジェクトの種類
};

#endif