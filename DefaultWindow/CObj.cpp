#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_eDir(END), m_bDead(false), m_fAngle(0.f), m_fDistance(0.f)
, m_pTarget(nullptr), m_pFrameKey(L""), m_eRender(RENDER_END)

{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
  
}

void CObj::Update_Rect()
{
	m_tRect.left    = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top     = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right   = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom  = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));

}

void CObj::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}


