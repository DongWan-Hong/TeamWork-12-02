#pragma once

#include "BaseObj.h"

template<typename T>
class CAbstractFactory // 
{
public:
	CAbstractFactory() {};
	~CAbstractFactory() {};

public:
	static BaseObj* Create()
	{
		BaseObj* pObj = new T; // COBJ타입의 객체 선언 
		pObj->Initialize();
		return pObj;

	}

	//static BaseObj* Create(Obj* _Tmp)
	//{
	//	BaseObj* pObj = new T;
	//	pObj->Initialize();
	//	pObj->Set_Target(_Tmp);
	//	return pObj;
	//}

	static BaseObj* Create(float _fX, float _fY, float _fAngle)
	{
		BaseObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		//pObj->Set_Direction(eDIR);

		return pObj;
	}

	static BaseObj* Create(float _fx, float _fY, float _fCX, float _fCY, float _fAngle)
	{
		BaseObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fx, _fY, _fCX, _fCY);
		pObj->Set_Ang(_fAngle);
		return pObj;
	}

};


