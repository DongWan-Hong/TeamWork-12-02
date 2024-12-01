#include "pch.h"
#include "Boss_Bullet.h"


Boss_Bullet::Boss_Bullet()
{
	ZeroMemory(&Check_Boss_Bul, sizeof(Check_Boss_Bul));
	m_fAngleSpeed = 0;
	f_Bullet_Ang = 0;
	skill_3_Count = 0;
	bMoving = true;
}

Boss_Bullet::~Boss_Bullet()
{
	Release();
}

void Boss_Bullet::Initialize()
{
}
//m_tInfo.fX += cosf(f_Bullet_Ang * PI / 180.f) * m_fSpeed; //����
//m_tInfo.fY += sinf(f_Bullet_Ang * PI / 180.f) * m_fSpeed;
int Boss_Bullet::Update()
{


	if (Check_Boss_Bul == Boss_Level_1) // ���� 1
	{
		m_tInfo.fY += m_fSpeed; // �Ʒ��� �̵�
	}
	if (Check_Boss_Bul == Boss_Level_2) // ���� 2
	{
		m_tInfo.fCY = 500;
		m_tInfo.fY += m_fSpeed; // �Ʒ��� �̵�
	}
	if (Check_Boss_Bul == Boss_Level_3) // ���� 3
	{
		m_tInfo.fCY = 500;
		m_tInfo.fY += m_fSpeed; // �Ʒ��� �̵�
	}
	if (Check_Boss_Bul == Boss_Level_4)
	{
		m_tInfo.fY += m_fSpeed; // �Ʒ��� �̵�
	}
	if (m_tInfo.fX < 50 || m_tInfo.fX > 600 ||
		m_tInfo.fY > 540)
	{
		return OBJ_DEAD;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void Boss_Bullet::Late_Update()
{

}

void Boss_Bullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	if (Check_Boss_Bul == 2 || Check_Boss_Bul == 3)
	{

		HBRUSH MyBrush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
		HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		HPEN OldPen = (HPEN)SelectObject(hDC, MyPen);
		Rectangle(hDC,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
		SelectObject(hDC, OldBrush);
		SelectObject(hDC, OldPen);
		DeleteObject(MyPen);
		DeleteObject(MyBrush);
	}
}

int Boss_Bullet::Crash()
{
	return 0;
}

void Boss_Bullet::Release()
{
}

void Boss_Bullet::Default_Bullet() // ���� 1
{
	m_tInfo.fCX = 20.f; // �Ѿ� ũ��
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f;

	Check_Boss_Bul = Boss_Level_1;
}

void Boss_Bullet::Boss_Bullet_1()  //  ���� 2
{
	m_tInfo.fCX = 20.f; // �Ѿ� ũ��
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f;
	Check_Boss_Bul = Boss_Level_2;
}

void Boss_Bullet::Boss_Bullet_2() // ���� 3
{
	m_tInfo.fCX = 20.f; // �Ѿ� ũ��
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f;
	Check_Boss_Bul = Boss_Level_3;
}
void Boss_Bullet::Boss_Bullet_3() // ���� 3
{
	m_tInfo.fCX = 20.f; // �Ѿ� ũ��
	m_tInfo.fCY = 20.f;
	m_fSpeed = 0.000000000001f;

	Check_Boss_Bul = Boss_Level_4;
}

void Boss_Bullet::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* Boss_Bullet::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}


//if (m_ObjList[OBJ_BULLET].empty() == false) // �浹 ó�� �Լ�
   //{
   //    for (auto iter = m_ObjList[OBJ_BULLET].begin(); iter != m_ObjList[OBJ_BULLET].end();)
   //    {
   //        auto pBullet = (*iter)->Get_Info(); // �Ѿ� ����
   //        auto pMonster = m_ObjList[OBJ_MONSTER].front()->Get_Info(); // ���� ����


   //        float fMonsterRadius = pMonster.fCX / 2.0f; // fCX�� ���� ũ��
   //        float fBulletRadius = pBullet.fCX / 2.0f;


   //        float fDistance = sqrt    // �߽ɰŸ� �����س���
   //        (
   //            (pBullet.fX - pMonster.fX) * (pBullet.fX - pMonster.fX)
   //            +
   //            (pBullet.fY - pMonster.fY) * (pBullet.fY - pMonster.fY)
   //        );


   //        if (fDistance <= (fMonsterRadius + fBulletRadius))// �浹 ����: �߽� �Ÿ� <= �������� ��
   //        {

   //            m_ObjList[OBJ_BULLET].front()->Set_Dead();
   //            m_ObjList[OBJ_MONSTER].front()->Set_Dead();
   //            iCount++;
   //            break;
   //        }
   //        else
   //        {
   //            ++iter; // ��� ����
   //        }
   //    }
   //}