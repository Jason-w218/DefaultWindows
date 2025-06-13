#pragma once
#include "CObj.h"
class CMonster :  public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	
};

