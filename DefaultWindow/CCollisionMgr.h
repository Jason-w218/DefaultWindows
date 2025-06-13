#pragma once

#include "CObj.h"

class CCollisionMgr
{
public:
	static void		Collision_Rect(list<CObj*> _pDst, list<CObj*> _pSrc);
	static void		Collision_Circle(list<CObj*> _pDst, list<CObj*> _pSrc);
	static bool		Check_Sphere(CObj* pDst, CObj* pSrc);

	static void		Collision_RectEx(list<CObj*> _pDst, list<CObj*> _pSrc);
	static bool		Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);

};

