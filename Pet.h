#pragma once
#include "BaseObj.h"
#include "Bullet.h"
#include "Monster.h"

class Pet : public BaseObj
{
public:
	Pet();
	virtual ~Pet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void Get_List(list<BaseObj*>* pList) override;
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect) override;

public:
	void Initialize(float _fX, float _fY);
	void Get_Monster(list<BaseObj*>* pMonster) { m_pMonsterList = pMonster; }
	void Bullet_Update();

private:
	POINT	m_pCenter;
	list<BaseObj*>* m_pMonsterList;
	BaseObj* m_Target;
};

