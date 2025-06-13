#pragma once

#include "CObj.h"

class CScrewBullet : public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	POINT		m_tCenter;

	float		m_fRotAngle;	// 자전 각도
	float		m_fRotSpeed;	// 회전 속도

	bool		m_bStart;
};

