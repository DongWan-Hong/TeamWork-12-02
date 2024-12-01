#include "pch.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(float _fCX, float _fCY, float _fX, float _fY, float _fSpeed)
	:BaseObj(_fCX, _fCY, _fX, _fY, _fSpeed), m_fXspeed(0.f)
{
}

Monster::~Monster()
{
	Release();
}

void Monster::Initialize()
{
	m_fXspeed = 6.f;

	int i = (rand() % 2) + 1;

	if (1 == i)
		m_fXspeed *= -1.f;

	m_bDead = false;
}

int Monster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_Bullet();

	m_tInfo.fY += m_fSpeed;
	m_tInfo.fX += m_fXspeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Monster::Late_Update()
{
	if (m_wWall.Lbottom <= m_tRect.bottom ||
		m_wWall.Lleft >= m_tRect.left ||
		m_wWall.Lright <= m_tRect.right ||
		m_wWall.Ltop >= m_tRect.top)
	{
		m_fSpeed *= -1.f;
		m_fXspeed *= -1.f;
	}

	/*if (m_wWall.Lbottom <= m_tRect.bottom ||
		m_wWall.Lleft >= m_tRect.left ||
		m_wWall.Lright <= m_tRect.right)
	{
		m_bDead = true;
	}*/
}

void Monster::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Monster::Release()
{
}

void Monster::Get_List(list<BaseObj*>* pList)
{
	m_pBulletList = pList;
}

void Monster::Set_Bullet()
{
	//m_pBulletList->push_back(CreateBullet(DL_UP));
}

BaseObj* Monster::CreateBullet(BULLETDIRECTION _eDriect)
{
	BaseObj* pObj = new Bullet;

	//이니셜라이즈와 셋 포즈는 각 Obj마다 다르게 설정되어야 함
	pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pObj->Initialize();

	dynamic_cast<Bullet*>(pObj)->Set_Direct(_eDriect);

	return pObj;
}

