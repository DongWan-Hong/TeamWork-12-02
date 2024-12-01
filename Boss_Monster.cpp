#include "pch.h"
#include "Boss_Monster.h"
#include "Boss_Bullet.h"

Boss_Monster::Boss_Monster()
{
	ZeroMemory(&m_p_Boss_Bullet, sizeof(m_p_Boss_Bullet));
	ZeroMemory(&turretEnd, sizeof(turretEnd));
	m_ullLast_Fire = 0;
	m_fTurretAngle = 0.f; // 포신 각도 초기화
	m_fTurretSpeed = 2.f; // 포신 회전 속도
	Bullet_X = 40;
}

Boss_Monster::~Boss_Monster()
{
}

void Boss_Monster::Initialize()
{
	m_tInfo = { 300, -200, 200.f, 200.f };
	m_fSpeed = 3.f;
}

int Boss_Monster::Update()
{
	m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY > 150) // 멈추는 조건
	{
		m_fSpeed = 0;
	}

	if (m_fSpeed == 0)
	{
		Key_Input();
	}

	// 포신 회전 각도 갱신
	m_fTurretAngle += m_fTurretSpeed;


	if (bDead == true)
	{
		return OBJ_DEAD;
	}



	Update_Rect();
	return OBJ_NOEVENT;


}

void Boss_Monster::Late_Update()
{

}

void Boss_Monster::Render(HDC hDC)
{

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	TCHAR box[32] = L""; // 총알
	swprintf_s(box, L"보스");
	TextOut(hDC, (int)m_tInfo.fX - 17, (int)m_tInfo.fY - 10, box, lstrlen(box)); // x축 y축


	turretEnd.x = long(m_tInfo.fX + 100 * cosf(m_fTurretAngle * (PI / 180.f))); // 100은 선 길이
	turretEnd.y = long(m_tInfo.fY - 100 * sinf(m_fTurretAngle * (PI / 180.f)));

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, turretEnd.x, turretEnd.y);
}

int Boss_Monster::Crash()
{
	return 0;
}

void Boss_Monster::Release()
{
}

void Boss_Monster::Key_Input()
{
	if (GetAsyncKeyState('1')) // 기본 총알
	{
		if (m_ullLast_Fire + 100 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(1)); // 기본 총알
	}

	if (GetAsyncKeyState('2')) // 오른쪽 벽 몰기 패턴
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(2));

	}
	if (GetAsyncKeyState('3')) // 왼쪽 벽 몰기 패턴
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(3));

	}
	if (GetAsyncKeyState('4'))  // 5개 유도탄
	{
		if (m_ullLast_Fire + 500 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(4));
	}
}

BaseObj* Boss_Monster::Create_Boss_Bullet(int _type)
{
	BaseObj* pBullet = new Boss_Bullet;

	if (_type == 1) // 기본 총알
	{
		static_cast<Boss_Bullet*>(pBullet)->Default_Bullet();
		pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY); // 총알의 초기 위치를 포신 끝으로 설정
		pBullet->Set_Ang(m_fTurretAngle);        // 포신 각도로 초기 방향 설정

	}
	else if (_type == 2) // 레이저 총알 오른벽 몰기
	{
		static int direction_Left = 1; // 

		if (Bullet_X >= 490) // 오른쪽 끝에 닿았을 때
		{
			direction_Left = -1;
		}
		else if (Bullet_X <= 80) // 왼쪽 끝에 닿았을 때
		{
			direction_Left = 1;
		}
		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_1();
		pBullet->BSet_Pos(Bullet_X, -200); // 총알의 초기 위치를 포신 끝으로 설정
		Bullet_X += 50 * direction_Left; // 방향에 따라 이동
	}
	else if (_type == 3) //3번  레이저 총알 왼벽 몰기
	{
		static int direction_Right = 1; // 
		static float _Bullet_X = 550;

		if (_Bullet_X >= 550) // 오른쪽 끝에 닿았을 때
		{
			direction_Right = -1;
		}
		else if (_Bullet_X <= 130) // 왼쪽 끝에 닿았을 때
		{
			direction_Right = +1;
		}
		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_2();
		pBullet->Set_Pos(_Bullet_X, -200); // 총알의 초기 위치를 포신 끝으로 설정
		_Bullet_X += 50 * direction_Right; // 방향에 따라 이동   
	}
	else if (_type == 4) // 유도총알
	{
		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_3();
		pBullet->Set_Pos(turretEnd.x, turretEnd.y);
		pBullet->Set_Ang(m_fTurretAngle);
	}


	return pBullet;
}

void Boss_Monster::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* Boss_Monster::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}


