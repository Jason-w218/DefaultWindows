#pragma once

#include "CLine.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();


public:
	bool	Collision_Line(float _fX, float* _pY);
	void		Load_Data();

public:
	void	Initialize();
	void	Render(HDC hDC);
	void	Release();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	static CLineMgr*	m_pInstance;

	list<CLine*>		m_LineList;
};

