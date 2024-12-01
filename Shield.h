#pragma once
#include "BaseObj.h"
class Shield : public BaseObj
{
public:
	Shield();
	virtual ~Shield();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Get_List(list<BaseObj*>* pList) override;
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect) override;
};