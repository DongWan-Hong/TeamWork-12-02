#include "pch.h"
#include "BaseObj.h"

BaseObj::BaseObj() : m_fSpeed(0.f), m_fAngle(0.f), m_fDistance(0.f), m_fAngleAccel(0.f), m_bDead(false), m_pTarget(nullptr), m_Time(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

BaseObj::BaseObj(float _fCX, float _fCY, float _fX, float _fY, float _fSpeed)
{
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_fSpeed = _fSpeed;
	m_bDead = false;
}

BaseObj::~BaseObj()
{
}

void BaseObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
