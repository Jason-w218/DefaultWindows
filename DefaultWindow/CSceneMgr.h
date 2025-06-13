#pragma once

#include "Define.h"
#include "CLogo.h"
#include "CMenu.h"
#include "CEdit.h"
#include "CStage.h"

class CSceneMgr
{
public:
	enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eID);

	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;

	CScene* m_pScene;

	SCENEID	m_eCurScene;
	SCENEID m_ePreScene;

};

