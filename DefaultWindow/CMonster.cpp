#include "pch.h"
#include "CMonster.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_fSpeed = 3.f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CMonster::Update()
{
	if (m_bDead)
		return DEAD;


	__super::Update_Rect();		 

	//float		fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);
	//
	//fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	//fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	//
	//fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	//
	//fRadian = acosf(fWidth / fDiagonal);
	//
	//// if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	//// 	fRadian = 2.f * PI - fRadian;
	//
	//
	//// radian to degree
	//m_fAngle = fRadian * (180.f / PI);
	//
	//if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	//	m_fAngle *= -1.f;

    return NOEVENT;
}

void CMonster::Late_Update()
{
	//m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
}

void CMonster::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX,	// 복사할 비트맵 가로 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 픽셀 색상 값
}

void CMonster::Release()
{
}

