#include "pch.h"
#include "CCollisionMgr.h"

void CCollisionMgr::Collision_Rect(list<CObj*> _pDst, list<CObj*> _pSrc)
{
	RECT	rcCollision{};

	for (auto& Dst : _pDst)
	{
		for (auto& Src : _pSrc)
		{
			if (IntersectRect(&rcCollision, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}


}

void CCollisionMgr::Collision_Circle(list<CObj*> _pDst, list<CObj*> _pSrc)
{
	for (auto& Dst : _pDst)
	{
		for (auto& Src : _pSrc)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDistance;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _pDst, list<CObj*> _pSrc)
{

	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _pDst)
	{
		for (auto& Src : _pSrc)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				//  상하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
					{
						Dst->Set_PosY(-fHeight);
					}
					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}

				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
					{
						Dst->Set_PosX(-fWidth);
					}
					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}

			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	float		fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);
		 
	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
