#pragma once

#define	WINCX 800
#define	WINCY 600

#define TILECX 64
#define TILECY 64

#define TILEX 30
#define TILEY 20


#define PURE = 0

#define NOEVENT 0
#define DEAD    1 

#define PI		3.141592f

#define VK_MAX		0xff

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LUP,
	RUP,
	END
};

enum OBJID
{
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_MONSTER,
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_BUTTON,
	OBJ_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_GAMEOBJECT,
	RENDER_EFFECT,
	RENDER_UI,
	RENDER_END

};

typedef struct tagInfo
{
	float	fX;		// 중점 X,Y
	float	fY;
	float	fCX;	// 가로, 세로 길이
	float	fCY;	

}INFO;

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() 
	{
		ZeroMemory(this, sizeof(tagPoint));
	}
	tagPoint(float _fX ,float _fY) : fX(_fX), fY(_fY){}


}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;


	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOINT _tLeft, LINEPOINT _tRight) : tLeft(_tLeft), tRight(_tRight) {}


}LINE;


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}


struct tagFinder
{
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(MyPair.first, m_pString);
	}

	const TCHAR* m_pString;
};



struct DeleteObj
{	
	template<typename T>
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

struct DeleteMap
{
	template<typename T>
	void operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;



extern HWND g_hWnd;