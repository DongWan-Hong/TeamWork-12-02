#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() : m_fWidth(0.f), m_fHeight(0.f), m_fDiagonal(0.f), m_fRadian(0.f), m_Centerx(300.f), m_Centery(400.f)
{

}

Bullet::~Bullet()
{
	Release();
}

void Bullet::Initialize()
{
	//초기 위치(플레이어 위치) Set_Pos를 통해 설정
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 2.f;   // 불릿 속도

	m_bDead = false;
}

int Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_Bdriect) //{ DL_UP, DL_LUP, DL_RUP, DL_POSIN, DL_ROTATE, DL_END };
	{
	case DL_UP:
	{
		m_tInfo.fY -= m_fSpeed;
	}
	break;

	case DL_LUP:
	{
		m_fAngle = 45.f;
		m_tInfo.fX -= m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	case DL_RUP:
	{
		m_fAngle = 45.f;
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	case DL_MY:
	{
		/*m_tInfo.fX = 0.f;
		m_tInfo.fY = 0.f;*/


		m_Centerx += 1.f;
		m_Centery -= 1.f;

		m_fSpeed = 20.f;

		m_tInfo.fX = m_Centerx + m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_Centery - m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	case DL_CHARSE:
	{
		m_fSpeed = 6.f;
		m_fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		m_fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		m_fDiagonal = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight));

		m_fRadian = acosf(m_fWidth / m_fDiagonal);

		m_fAngle = m_fRadian * float(180.f / PI);

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	case DL_POSIN:
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	case DL_ROTATE:
	{
		m_fAngle += 2.f;
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	}
	break;

	default:
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Bullet::Late_Update()
{
	if (m_wWall.Lleft >= m_tRect.left ||
		m_wWall.Lright <= m_tRect.right ||
		m_wWall.Ltop >= m_tRect.top ||
		m_wWall.Lbottom <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Bullet::Release()
{
}

void Bullet::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* Bullet::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}
