#include "pch.h"
#include "Shield.h"

Shield::Shield()
{
}

Shield::~Shield()
{
	Release();
}

void Shield::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fDistance = 50.f;
	m_fSpeed = 3.f;
	m_bDead = false;
}

int Shield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;
	m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Shield::Late_Update()
{
}

void Shield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Shield::Release()
{
}

void Shield::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* Shield::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}
