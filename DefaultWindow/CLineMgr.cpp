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
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// ���� �̸��� ��õ� ���
		GENERIC_READ,		// ���� ���� ���(GENERIC_WRITE : ����, GENERIC_READ : �б�)
		NULL,				// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ������� ������ �� ����� ���ΰ�)
		NULL,				// ���� �Ӽ�(NULL �⺻ ���� �Ӽ�)
		OPEN_EXISTING,		// ���� ���(���� ���� : ������ ���ٸ� ����, ������ ���� ����, �б� ����(OPEN_EXISTING : ������ �ִ� ���� �ҷ�����))
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ� : �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����(NULL)

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
	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
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
