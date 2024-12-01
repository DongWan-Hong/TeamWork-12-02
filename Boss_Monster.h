#pragma once

#include "BaseObj.h"

class Boss_Monster : public BaseObj
{
public:
    Boss_Monster();
    ~Boss_Monster();

public:
    void        Set_Bullet(list<BaseObj*>* pBullet) { m_p_Boss_Bullet = pBullet; }

    virtual void		Initialize();
    virtual int		    Update();
    virtual void		Late_Update();
    virtual void		Render(HDC hDC);
    virtual int         Crash();
    virtual void		Release();

    void     Key_Input();

    BaseObj* Create_Boss_Bullet(int _type);

    
    virtual void Get_List(list<BaseObj*>* pList);
    virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect);


private:
    list<BaseObj*>* m_p_Boss_Bullet;
    unsigned long long m_ullLast_Fire;
private:
    int Bullet_X;
    float m_fTurretAngle; // 포신의 현재 회전각도
    float m_fTurretSpeed; // 포신의 회전 속도
    bool Check_Y;
    POINT turretEnd;

};



