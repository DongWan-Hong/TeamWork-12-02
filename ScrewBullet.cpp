#include "pch.h"
#include "ScrewBullet.h"

ScrewBullet::ScrewBullet() : m_bStart(false), m_fRotAngle(0.f), m_fRotSpeed(0.f)
{
    ZeroMemory(&m_tCenter, sizeof(POINT));
}

ScrewBullet::~ScrewBullet()
{
    Release();
}

void ScrewBullet::Initialize()
{
    m_tInfo.fCX = 10.f;
    m_tInfo.fCY = 10.f;

    m_fSpeed = 2.f;

    m_bStart = true;
    m_bDead = false;
}

int ScrewBullet::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
    m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));




    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void ScrewBullet::Late_Update()
{
    if (m_wWall.Lleft >= m_tRect.left ||
        m_wWall.Lright <= m_tRect.right ||
        m_wWall.Ltop >= m_tRect.top ||
        m_wWall.Lbottom <= m_tRect.bottom)
    {
        m_bDead = true;
    }
}

void ScrewBullet::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void ScrewBullet::Release()
{
}

void ScrewBullet::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* ScrewBullet::CreateBullet(BULLETDIRECTION _eDriect)
{
    return nullptr;
}
