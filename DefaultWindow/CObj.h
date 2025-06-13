#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_PosX(float _fX)
	{
		m_tInfo.fX += _fX;
	}
	void		Set_PosY(float _fY)
	{
		m_tInfo.fY += _fY;
	}



	void		Set_Dir(DIRECTION eDir)
	{
		m_eDir = eDir;
	}
	
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle;  }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void		Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }


	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }

	bool		Get_Dead() const { return m_bDead; }

	RENDERID	Get_RenderID() const { return m_eRender;  }

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

protected:
	void		Update_Rect();
	void		Update_Frame();

protected:

	CObj*		m_pTarget;

	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	FRAME		m_tFrame;
	RENDERID	m_eRender;

	float		m_fSpeed;
	float		m_fDistance;
	float		m_fAngle;
	bool		m_bDead;

	const TCHAR* m_pFrameKey;

};

