#pragma once
#include "BaseObj.h"
class Bullet : public BaseObj
{
public:
	Bullet();
	virtual ~Bullet();

public:
	// BaseObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Get_List(list<BaseObj*>* pList) override;
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect) override;

public:
	void Set_Direct(BULLETDIRECTION _dType) { m_Bdriect = _dType; }
	void Set_AnglePlus() { m_fAngle += 45.f; }


private:
	BULLETDIRECTION m_Bdriect;

	float m_fWidth;
	float m_fHeight;
	float m_fDiagonal;
	float m_fRadian;

	float m_Centerx;
	float m_Centery;
};

