#pragma once

#include "CObj.h"

class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rhs) = delete;
	CObjMgr operator = (const CObj& rObj) = delete;
	~CObjMgr();


public:
	CObj* Get_Target(OBJID eID, CObj* pObj);
	void	Delete_Object(OBJID eID);

public:
	void	Add_Object(OBJID eID, CObj* pObj);
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();




public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr* m_pInstance;
private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderList[RENDER_END];


};

