#pragma once

#include "CObj.h"

class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

	int			Get_DrawID() const { return m_iDrawID;  }
	int			Get_Option() const { return m_iOption; }
		
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int		m_iDrawID;
	int		m_iOption;

};

