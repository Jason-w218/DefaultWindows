#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public :
	void		Update();

	bool		Key_Pressing(int _iKey);

	// ������ ����(�� �� ���� ó��)
	bool		Key_Down(int _iKey);
	
	// �����ٰ� ���� ��
	bool		Key_Up(int _iKey);


public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr* m_pInstance;

	bool		m_bKeyState[VK_MAX];
};


