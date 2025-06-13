#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CShield.h"
#include "CScrewBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CGuideBullet.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"


CPlayer::CPlayer() : m_bJump(false), m_fVelocity(0.f), m_fTime(0.f)
, m_eCurState(IDLE), m_ePreState(END)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/maja2.bmp", L"Player");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	


	m_tInfo = { 100.f, WINCY >> 1, 200.f, 200.f };
	m_fSpeed = 4.f;
	m_fDistance = 100.f;	
	m_fVelocity = 20.f;

	m_pFrameKey = L"Player_DOWN";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;

	m_eRender = RENDER_GAMEOBJECT;

}

int CPlayer::Update()
{
	Key_Input();

	__super::Update_Rect();

	__super::Update_Frame();

	return NOEVENT;
}

void CPlayer::Late_Update()
{
	Jumping();
	Offset();
	Motion_Change();
}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	// 이미지 출력 함수

	//BitBlt(hDC,		// 복사 받을 DC
	//	m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X,Y
	//	m_tRect.top, 
	//	(int)m_tInfo.fCX, // 복사 받을 가로, 세로 사이즈
	//	(int)m_tInfo.fCY,
	//	hMemDC,		// 복사할 DC
	//	0,			// 비트맵 이미지 left, top
	//	0, 
	//	SRCCOPY);	// 출력 효과 설정 : 그대로 복사하여 출력

	// 원하는 픽셀 색상을 제거하여 출력하는 함수

	GdiTransparentBlt(hDC, 
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,	// 복사할 비트맵 가로 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));	// 제거할 픽셀 색상 값


}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
#pragma region 생략
	//if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	if(GetAsyncKeyState(VK_UP))
	//	{
	//		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
	//		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
	//	}
	//
	//	else if (GetAsyncKeyState(VK_DOWN))
	//	{
	//		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
	//		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
	//	}
	//
	//	else
	//		m_tInfo.fX += m_fSpeed;
	//}
	//
	//else if (GetAsyncKeyState(VK_LEFT))
	//{
	//	if (GetAsyncKeyState(VK_UP))
	//	{
	//		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
	//		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
	//	}
	//
	//	else if (GetAsyncKeyState(VK_DOWN))
	//	{
	//		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
	//		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
	//	}
	//
	//	else
	//		m_tInfo.fX -= m_fSpeed;
	//}
	//
	//else if (GetAsyncKeyState(VK_UP))
	//{
	//	m_tInfo.fY -= m_fSpeed;
	//}
	//
	//else if (GetAsyncKeyState(VK_DOWN))
	//{
	//	m_tInfo.fY += m_fSpeed;
	//}
	//
	//if (GetAsyncKeyState(VK_SPACE))
	//{
	//	m_pBullet->push_back(Create_Bullet(UP));
	//	m_pBullet->push_back(Create_Bullet(LUP));
	//	m_pBullet->push_back(Create_Bullet(RUP));
	//}
	//
	//if (GetAsyncKeyState('W'))
	//{
	//	m_pBullet->push_back(Create_Bullet(UP));
	//}
	//
	//if (GetAsyncKeyState('A'))
	//{
	//	m_pBullet->push_back(Create_Bullet(LEFT));
	//}
	//
	//if (GetAsyncKeyState('S'))
	//{
	//	m_pBullet->push_back(Create_Bullet(DOWN));
	//}
	//
	//if (GetAsyncKeyState('D'))
	//{
	//	m_pBullet->push_back(
	//		CAbstractFactory<CBullet>::Create_Obj
	//		(m_tInfo.fX, m_tInfo.fY, RIGHT));
	//}
#pragma endregion

#pragma region 삼각함수 이용 키값
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	m_fAngle += 5.f;
	//}
	//
	//if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	m_fAngle -= 5.f;
	//}
	//
	//if (GetAsyncKeyState(VK_UP))
	//{
	//	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	//	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	//}
	//
	//if (GetAsyncKeyState(VK_DOWN))
	//{
	//	m_tInfo.fX += -m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	//	m_tInfo.fY -= -m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	//}
	//
	//if (GetAsyncKeyState(VK_SPACE))
	//{
	//	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet<CGuideBullet>((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
	//}

	//if (GetAsyncKeyState('S'))
	//{

	//	CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, Create_Shield());
	//}

#pragma endregion

#pragma region 그냥


if (GetAsyncKeyState(VK_LEFT))
{
	m_tInfo.fX -= m_fSpeed;
	m_pFrameKey = L"Player_LEFT";
	m_eCurState = WALK;
}

else if (GetAsyncKeyState(VK_RIGHT))
{
	m_tInfo.fX += m_fSpeed;
	m_pFrameKey = L"Player_RIGHT";
	m_eCurState = WALK;
}


else if (GetAsyncKeyState(VK_UP))
{
	m_tInfo.fY -= m_fSpeed;
	m_pFrameKey = L"Player_UP";
	m_eCurState = WALK;
}

else if (GetAsyncKeyState(VK_DOWN))
{
	m_tInfo.fY += m_fSpeed;
	m_pFrameKey = L"Player_DOWN";
	m_eCurState = WALK;
}

else if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
{
	m_bJump = true;
}

else
m_eCurState = IDLE;

#pragma endregion

	

}

void CPlayer::Jumping()
{
	float	fY(0.f);

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fVelocity * m_fTime - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}

	
}

void CPlayer::Offset()
{
	/*int	iOffsetX = WINCX >> 1;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffsetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);*/

	int	iOffsetminX = 100;
	int	iOffsetmaxX = 700;

	int	iOffsetminY = 100;
	int	iOffsetmaxY = 500;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffsetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetminY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetmaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;

			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;

		case DEATH:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;
		}

		m_ePreState = m_eCurState;

	}


}

template<typename T>
CObj* CPlayer::Create_Bullet(float fX, float fY, float fAngle)
{	
	CObj* pBullet = CAbstractFactory<T>::Create_Obj(fX, fY);
	pBullet->Set_Angle(fAngle);	

	return pBullet;
}

CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create_Obj();
	pShield->Set_Target(this);

	return pShield;
}

