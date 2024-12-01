#include "pch.h"
#include "CollisionMgr.h"

void CollisionMgr::Collision_Rect(list<BaseObj*>* _Dst, list<BaseObj*>* _Src)
{
	RECT rc{};

	for (list<BaseObj*>::iterator iter = _Dst->begin();
		iter != _Dst->end(); ++iter)
	{
		for (list<BaseObj*>::iterator iter2 = _Src->begin();
			iter2 != _Src->end(); ++iter2)
		{
			if (IntersectRect(&rc, (*iter)->Get_Rect(), (*iter2)->Get_Rect()))
			{
				(*iter)->Set_Dead();
				(*iter2)->Set_Dead();
			}
		}
	}
}

void CollisionMgr::Collision_Circle(list<BaseObj*> _Dst, list<BaseObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CollisionMgr::Check_Circle(BaseObj* _Dst, BaseObj* _Src)
{
	float fRadius = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;

	float fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

	return fRadius > fDiagonal;
}


