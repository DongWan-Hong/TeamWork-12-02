#include "pch.h"
#include "Pet.h"

Pet::Pet()
{
    ZeroMemory(&m_pCenter, sizeof(POINT));
}

Pet::~Pet()
{
    Release();
}

void Pet::Initialize()
{

}

void Pet::Initialize(float _fX, float _fY)
{
    m_pCenter.x = LONG(_fX);
    m_pCenter.y = LONG(_fY);
    m_tInfo.fCX = 20.f;
    m_tInfo.fCY = 20.f;
    m_fDistance = 70.f;
}

void Pet::Bullet_Update()
{
    if (GetAsyncKeyState('B')) // 유도탄 발사
    {
        if (0 != m_pMonsterList->size()) //몬스터가 없을 때는 발사되지 않음
        {
            if (m_Time + 100 > GetTickCount64())
            {
                return;
            }
            m_pBulletList->push_back(CreateBullet(DL_CHARSE));
            m_Time = GetTickCount64();
        }
    }
}

int Pet::Update()
{
    /*if (m_bDead)
        return OBJ_DEAD;*/

    Bullet_Update();

    m_fAngle += 2.f;
    m_tInfo.fX = m_pCenter.x + m_fDistance * cosf(m_fAngle * (PI / 180.f));
    m_tInfo.fY = m_pCenter.y - m_fDistance * sinf(m_fAngle * (PI / 180.f));
    /*POINT   ptMouse{};

    GetCursorPos(&ptMouse);

    ScreenToClient(g_hWnd, &ptMouse);

    m_tInfo.fX = float(ptMouse.x);
    m_tInfo.fY = float(ptMouse.y);*/

    __super::Update_Rect();

    /*ShowCursor(FALSE);*/

    return OBJ_NOEVENT;
}

void Pet::Late_Update()
{
}

void Pet::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Pet::Release()
{
}

void Pet::Get_List(list<BaseObj*>* pList)
{
    m_pBulletList = pList;
}

BaseObj* Pet::CreateBullet(BULLETDIRECTION _eDriect)
{
    BaseObj* pObj = new Bullet;

    pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);

    if (DL_CHARSE == _eDriect)
    {
        pObj->Set_Target(m_pMonsterList->back());
    }
    //이니셜라이즈와 셋 포즈는 각 Obj마다 다르게 설정되어야 함

    pObj->Initialize();

    dynamic_cast<Bullet*>(pObj)->Set_Direct(_eDriect);

    return pObj;
}


