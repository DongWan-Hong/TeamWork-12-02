#pragma once
#include "BaseObj.h"
#include "Bullet.h"

class Monster : public BaseObj
{
public:
	Monster();
	Monster(float _fCX, float _fCY, float _fX, float _fY, float _fSpeed);
	virtual ~Monster();

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
	void Set_Bullet();

private:
	float	m_fXspeed;
};

