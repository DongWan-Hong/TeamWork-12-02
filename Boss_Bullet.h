#pragma once
#include "BaseObj.h"

enum Check_Boss_Bullet
{
	Boss_Level_1 = 1, Boss_Level_2, Boss_Level_3, Boss_Level_4
};

class Boss_Bullet : public BaseObj
{
public:
	Boss_Bullet();
	virtual ~Boss_Bullet();

public:

	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual int			Crash();
	virtual void		Release();


	void Default_Bullet();
	void Boss_Bullet_1();
	void Boss_Bullet_2();
	void Boss_Bullet_3();

	bool GetMoving() const { return bMoving; }

	int GetCount() { return skill_3_Count; }

	void SetMoving(bool _moving) { bMoving = _moving; }

	void SetSpeed(float speed) { m_fSpeed = speed; }

	void SetCount(int _type) { skill_3_Count = _type; }

	virtual void Get_List(list<BaseObj*>* pList);
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect);

private:

	struct BulletInfo
	{
		float fX, fY;
		float fAngle;
		bool bStopped; // ¸ØÃè´ÂÁö«n
	};

	Check_Boss_Bullet Check_Boss_Bul;
	float m_fAngleSpeed;
	float f_Bullet_Ang;
	bool bMoving;
	int skill_3_Count;

};

