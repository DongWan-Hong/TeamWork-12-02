#pragma once
#include "BaseObj.h"

class CollisionMgr
{

public:

	static void	Collision_Rect(list<BaseObj*>* _Dst, list<BaseObj*>* _Src);
	static void	Collision_Circle(list<BaseObj*> _Dst, list<BaseObj*> _Src);
	static bool	Check_Circle(BaseObj* _Dst, BaseObj* _Src);

};

