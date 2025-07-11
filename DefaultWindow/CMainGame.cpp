#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CMonster.h"
#include "CMouse.h"
#include "CCollisionMgr.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"

CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);	
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_LOGO);
}


void CMainGame::Update()
{	
	CSceneMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CKeyMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Late_Update();

	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	// 플레이어 렌더 호출
	CSceneMgr::Get_Instance()->Render(hBackDC);
	
	BitBlt(m_DC, 0, 0, WINCX, WINCY,hBackDC,0,0,SRCCOPY);		
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_DC);
	
	CTileMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();

	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
}
