#include "pch.h"
#include "CLineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float _fX, float* _pY)
{

	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& pLine : m_LineList)
	{
		if (_fX >= pLine->Get_Info().tLeft.fX &&
			_fX <= pLine->Get_Info().tRight.fX)
		{
			pTargetLine = pLine;
		}	
	}

	if (!pTargetLine)
		return false;

	
	float x1 = pTargetLine->Get_Info().tLeft.fX;
	float y1 = pTargetLine->Get_Info().tLeft.fY;
	float x2 = pTargetLine->Get_Info().tRight.fX;
	float y2 = pTargetLine->Get_Info().tRight.fY;	
	
	
	*_pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Load_Data()
{
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일 이름이 명시된 경로
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려있는 상태에서 다른 프로세스에서 접근할 때 허용할 것인가)
		NULL,				// 보안 속성(NULL 기본 보안 속성)
		OPEN_EXISTING,		// 생성 방식(쓰기 전용 : 파일이 없다면 생성, 있으면 덮어 쓰기, 읽기 전용(OPEN_EXISTING : 파일이 있는 경우면 불러오기))
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성 : 아무런 속성이 없는 일반 파일 형식
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일(NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	Release();

	DWORD		dwByte(0);
	LINE		tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (dwByte == 0)
			break;

		m_LineList.push_back(new CLine(tLine.tLeft, tLine.tRight));
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Initialize()
{
	/*LINEPOINT tPoint[4] =
	{
		{100.f, 450.f},
		{300.f, 450.f},
		{500.f, 250.f},
		{700.f, 250.f},
	};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));
	m_LineList.push_back(new CLine(tPoint[1], tPoint[2]));
	m_LineList.push_back(new CLine(tPoint[2], tPoint[3]));*/

	Load_Data();

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);

}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), DeleteObj());
	m_LineList.clear();
}
