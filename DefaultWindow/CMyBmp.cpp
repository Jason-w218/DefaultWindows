#include "pch.h"
#include "CMyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : �Ű� ������ ���޵� dc�� ȣȯ�Ǵ� dc�� �Ҵ�

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,	// ���α׷��� �ν��Ͻ� �ڵ�	
							pFilePath,		// ������ ��θ� ����
							IMAGE_BITMAP,	// � ������ ����
							0,				// �̹��� ����, ���� ũ��
							0, 
							LR_LOADFROMFILE | LR_CREATEDIBSECTION);
							//	LR_LOADFROMFILE :  ���Ϸκ��� �̹����� �о����
							//	LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ

	// SelectObject : �غ��� dc�� �ҷ��� gdi ������Ʈ�� ����, 
	// �� �Լ��� gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ

	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
