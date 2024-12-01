#pragma once
#include "BaseObj.h"
class ScrewBullet : public BaseObj
{
public:
	ScrewBullet();
	virtual ~ScrewBullet();

public:
	// BaseObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Get_List(list<BaseObj*>* pList) override;
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect) override;

	void Set_Mydirection(BULLETMYDIRECTION _mDriect) { m_Mdirection = _mDriect; }

private:
	float	m_fRotAngle;
	float	m_fRotSpeed;

	bool	m_bStart;

	POINT	m_tCenter;
	BULLETMYDIRECTION m_Mdirection;
};

