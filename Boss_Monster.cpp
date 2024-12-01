#include "pch.h"
#include "Boss_Monster.h"
#include "Boss_Bullet.h"

Boss_Monster::Boss_Monster()
{
	ZeroMemory(&m_p_Boss_Bullet, sizeof(m_p_Boss_Bullet));
	ZeroMemory(&turretEnd, sizeof(turretEnd));
	m_ullLast_Fire = 0;
	m_fTurretAngle = 0.f; // ���� ���� �ʱ�ȭ
	m_fTurretSpeed = 2.f; // ���� ȸ�� �ӵ�
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

	if (m_tInfo.fY > 150) // ���ߴ� ����
	{
		m_fSpeed = 0;
	}

	if (m_fSpeed == 0)
	{
		Key_Input();
	}

	// ���� ȸ�� ���� ����
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

	TCHAR box[32] = L""; // �Ѿ�
	swprintf_s(box, L"����");
	TextOut(hDC, (int)m_tInfo.fX - 17, (int)m_tInfo.fY - 10, box, lstrlen(box)); // x�� y��


	turretEnd.x = long(m_tInfo.fX + 100 * cosf(m_fTurretAngle * (PI / 180.f))); // 100�� �� ����
	turretEnd.y = long(m_tInfo.fY - 100 * sinf(m_fTurretAngle * (PI / 180.f)));

	// ���� �׸���
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
	if (GetAsyncKeyState('1')) // �⺻ �Ѿ�
	{
		if (m_ullLast_Fire + 100 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(1)); // �⺻ �Ѿ�
	}

	if (GetAsyncKeyState('2')) // ������ �� ���� ����
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(2));

	}
	if (GetAsyncKeyState('3')) // ���� �� ���� ����
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(3));

	}
	if (GetAsyncKeyState('4'))  // 5�� ����ź
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

	if (_type == 1) // �⺻ �Ѿ�
	{
		static_cast<Boss_Bullet*>(pBullet)->Default_Bullet();
		pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY); // �Ѿ��� �ʱ� ��ġ�� ���� ������ ����
		pBullet->Set_Ang(m_fTurretAngle);        // ���� ������ �ʱ� ���� ����

	}
	else if (_type == 2) // ������ �Ѿ� ������ ����
	{
		static int direction_Left = 1; // 

		if (Bullet_X >= 490) // ������ ���� ����� ��
		{
			direction_Left = -1;
		}
		else if (Bullet_X <= 80) // ���� ���� ����� ��
		{
			direction_Left = 1;
		}
		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_1();
		pBullet->BSet_Pos(Bullet_X, -200); // �Ѿ��� �ʱ� ��ġ�� ���� ������ ����
		Bullet_X += 50 * direction_Left; // ���⿡ ���� �̵�
	}
	else if (_type == 3) //3��  ������ �Ѿ� �޺� ����
	{
		static int direction_Right = 1; // 
		static float _Bullet_X = 550;

		if (_Bullet_X >= 550) // ������ ���� ����� ��
		{
			direction_Right = -1;
		}
		else if (_Bullet_X <= 130) // ���� ���� ����� ��
		{
			direction_Right = +1;
		}
		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_2();
		pBullet->Set_Pos(_Bullet_X, -200); // �Ѿ��� �ʱ� ��ġ�� ���� ������ ����
		_Bullet_X += 50 * direction_Right; // ���⿡ ���� �̵�   
	}
	else if (_type == 4) // �����Ѿ�
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


