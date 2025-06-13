#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 3.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return DEAD;


	__super::Update_Rect();

	/*switch (m_eDir)
	{
	case LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case UP:
		m_tInfo.fY -= m_fSpeed;
		break;

	case DOWN:
		m_tInfo.fY += m_fSpeed;
		break;

	case LUP:
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;

	case RUP:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;

	}*/

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	return NOEVENT;
}
void CBullet::Late_Update()
{	

}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBullet::Release()
{
}


