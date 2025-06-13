#include "pch.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

CButton::CButton() : m_iDrawID(0)
{
}

CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_eRender = RENDER_UI;
}

int CButton::Update()
{
	__super::Update_Rect();

	return NOEVENT;
}

void CButton::Late_Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_STAGE);
			}
			else if (!lstrcmp(L"Edit", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_EDIT);
			}
			else if (!lstrcmp(L"Exit", m_pFrameKey))
			{
				DestroyWindow(g_hWnd);
			}

			return;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;



}

void CButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID,
		0,
		(int)m_tInfo.fCX,	// 복사할 비트맵 가로 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 픽셀 색상 값
}

void CButton::Release()
{
}
