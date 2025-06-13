#include "pch.h"
#include "CShield.h"

CShield::CShield()
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDistance = 100.f;
	m_fSpeed = 5.f;
}

int CShield::Update()
{
	__super::Update_Rect();

	m_fAngle += m_fSpeed;

	return NOEVENT;
}

void CShield::Late_Update()
{
	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sinf(m_fAngle * (PI / 180.f));


}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CShield::Release()
{
}
