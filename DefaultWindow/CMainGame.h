#pragma once

#include "Define.h"
#include "CPlayer.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

private:
	HDC		m_DC;

	TCHAR	m_szFPS[32];
	int		m_iFPS;
	DWORD	m_dwTime;

};

// 숙제 1. 삼각 함수가 무엇인지 공부하라
// 숙제 2. 플레이어를 중심으로 회전하는 포신을 구현하라
// 숙제 3. 포신이 바라보는 방향으로 이동하고, 총알이 나가도록 만들어라.


/////////////////////////////////////////////////////////////////////

// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 패턴
// https://refactoring.guru/ko/design-patterns

// 1. 추상 팩토리 패턴 : 객체를 생성하는 방법을 추상화시킨 패턴
// 2. 반복자 패턴 : 내부 표현 방식은 공개하지 않고, 순차적인 방법을 제공하는 패턴
// 3. 메디에디이터 패턴(중재자 패턴) : 상호작용하는 객체들이 서로 복잡한 관계를 맺고 있을 경우, 별도의 형식으로 정의하여 중재하는 객체를 두는 패턴
// 4. 상태 패턴 : FSM(Finite state machine : 자신이 취할 수 있는 유한한 개수의 상태를 가진다) 기반으로 객체의 상태를 표현하기 위한 패턴