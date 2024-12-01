#include "pch.h"
#include "Player.h"
#include "AbstractFactory.h"

Player::Player() : m_pBulletList(nullptr), m_pShieldList(nullptr), m_pPet(nullptr), m_pMonsterList(nullptr),m_pBullet(nullptr)// , m_pScrewBulletList(nullptr)
{
    ZeroMemory(&m_tPosin, sizeof(POINT));
    ZeroMemory(&Bullet_Di, sizeof(Bullet_Di));
    ZeroMemory(&m_tOrbitP_Ob, sizeof(m_tOrbitP_Ob));
    m_ullLast_Fire = 0;
}

Player::~Player()
{
    Release();
}

void Player::Initialize()
{
    m_tInfo = { 30.f, 30.f, 20.f, 20.f };
    m_fSpeed = 5.f;
    m_fDistance = 50.f;

    m_fOrbitSpeed = 2.f;
    m_fOrbitAngle = 0;

}

int Player::Update()
{
    Update_Rect();
    Key_Input();

    __super::Update_Rect();

    //

    m_fOrbitAngle += m_fOrbitSpeed; //  ���ǵ� 360 ���� �Ǹ� �ٽ� 0����
    m_tOrbitP_Ob.x = long(m_tInfo.fX + m_fDistance * cosf(m_fOrbitAngle * (PI / 180.f)));
    // ������ �߽ɰ��� x ���ٰ� ( �÷��̾� �߽ɰ�x + �Ÿ� * ( �ǽð� ���� ���� )
    m_tOrbitP_Ob.y = long(m_tInfo.fY - m_fDistance * sinf(m_fOrbitAngle * (PI / 180.f)));

    if (m_tInfo.fX > WINCX - 225)  //������ ���浹
    {
        m_tInfo.fX = WINCX - 225;
    }

    if (m_tInfo.fX < 50) // ����
    {
        m_tInfo.fX = 50;
    }

    if (m_tInfo.fY > WINCY - 50)
    {
        m_tInfo.fY = WINCY - 50;
    }

    if (m_tInfo.fY < 40)
    {
        m_tInfo.fY = 40;
    }

    return OBJ_NOEVENT;
}

void Player::Late_Update()
{
    m_tPosin.x = LONG(m_tInfo.fX + m_fDistance * cosf(m_fAngle * (PI / 180.f)));
    m_tPosin.y = LONG(m_tInfo.fY - m_fDistance * sinf(m_fAngle * (PI / 180.f)));
}

void Player::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
    MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
    LineTo(hDC, m_tPosin.x, m_tPosin.y);

    //���� �׷��ֱ�
    Ellipse(hDC,
        m_tOrbitP_Ob.x - 10, m_tOrbitP_Ob.y - 10,
        m_tOrbitP_Ob.x + 10, m_tOrbitP_Ob.y + 10);
}

void Player::Release()
{
}

void Player::Get_List(list<BaseObj*>* pList)
{
    m_pBulletList = pList;
}

BaseObj* Player::CreateBullet(BULLETDIRECTION _eDriect)
{
    BaseObj* pObj = new Bullet;
    //�ʱ� ��ġ(= �÷��̾��� ��ġ)

    if (DL_CHARSE == _eDriect)
    {
        pObj->Set_Pos(m_tPosin.x, m_tPosin.y);
        pObj->Set_Angle(m_fAngle);
        pObj->Set_Target(m_pMonsterList->front());
    }

    if (DL_MY == _eDriect)
    {
        pObj->Set_Angle(m_fAngle);
    }

    /*if (DL_STAR == _eDriect)
    {
        pObj->Set_Pos(m_tPosin.x, m_tPosin.y);
    }*/

    /*if (DL_CLOVER == _eDriect)
    {
        pObj->Set_Pos(m_tPosin.x, m_tPosin.y);
    }*/

    else
    {
        pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
    }

    //pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);	//�Ѿ��� �߻�Ǵ� ��ġ�� �÷��̾� �߽�
    //pObj->Set_Pos(m_tPosin.x, m_tPosin.y);	// �Ѿ��� �߻�Ǵ� ��ġ�� ��������
    //pObj->Set_Angle(m_fAngle);				// ������ ������� �߻�

    pObj->Initialize();
    dynamic_cast<Bullet*>(pObj)->Set_Direct(_eDriect);
    return pObj;
}

void Player::Get_ListShield(list<BaseObj*>* pListShield)
{
    m_pShieldList = pListShield;
}

//void Player::Get_ListScrewBullet(list<BaseObj*>* pListScrewBullet)
//{
//    m_pScrewBulletList = pListScrewBullet;
//}

void Player::Key_Input()
{
    if (GetAsyncKeyState(VK_UP))
    {
        if (GetAsyncKeyState(VK_LEFT))  //���ǵ尪�� ��ȭ�� �ش�
        {
            m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
            m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
        }

        else if (GetAsyncKeyState(VK_RIGHT))
        {
            m_tInfo.fX += m_fSpeed / sqrtf(2.f);
            m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
        }

        else
        {
            m_tInfo.fY -= m_fSpeed;
        }
    }

    if (GetAsyncKeyState(VK_DOWN))
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
            m_tInfo.fY += m_fSpeed / sqrtf(2.f);
        }

        else if (GetAsyncKeyState(VK_RIGHT))
        {
            m_tInfo.fX += m_fSpeed / sqrtf(2.f);
            m_tInfo.fY += m_fSpeed / sqrtf(2.f);
        }

        else
        {
            m_tInfo.fY += m_fSpeed;
        }
    }

    if (GetAsyncKeyState(VK_LEFT))
    {
        m_tInfo.fX -= m_fSpeed;
    }

    if (GetAsyncKeyState(VK_RIGHT))
    {
        m_tInfo.fX += m_fSpeed;
    }

    if (GetAsyncKeyState('T')) //���� ����
    {
        m_pShieldList->push_back(CreateShield());
    }

    if (GetAsyncKeyState(VK_SPACE))
    {
        m_pBulletList->push_back(CreateBullet(DL_UP));
        m_pBulletList->push_back(CreateBullet(DL_LUP));
        m_pBulletList->push_back(CreateBullet(DL_RUP));

        /*m_pBulletList->push_back(CAbstractFactory<Bullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));*/
    }

    if (GetAsyncKeyState('A'))
    {
        m_fAngle += 5.f;

        if (m_fAngle > 180.f) // 180�� �ʰ� ����
        {
            m_fAngle = 180.f;
        }
    }

    if (GetAsyncKeyState('D'))
    {
        m_fAngle -= 5.f;

        if (m_fAngle < 0.f) // 0�� �̸� ����
        {
            m_fAngle = 0.f;
        }
    }


}

BaseObj* Player::CreateShield()
{
    BaseObj* pShield = new Shield;

    pShield->Initialize();

    pShield->Set_Target(this);

    return pShield;
}

//BaseObj* Player::CreateScrewBullet(BULLETMYDIRECTION _eDriect)
//{
//    BaseObj* pScrewBullet = new ScrewBullet;
//
//    pScrewBullet->Initialize();
//
//    if (MY_UP == _eDriect)
//    {
//        pScrewBullet->Set_Pos(m_tPosin.x, LONG(m_tPosin.y - (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_LUP == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x - (m_tInfo.fCX * 0.3f)), LONG(m_tPosin.y - (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_RUP == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x + (m_tInfo.fCX * 0.3f)), LONG(m_tPosin.y - (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_DOWN == _eDriect)
//    {
//        pScrewBullet->Set_Pos(m_tPosin.x, LONG(m_tPosin.y + (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_LDOWN == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x - (m_tInfo.fCX * 0.3f)), LONG(m_tPosin.y + (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_RDOWN == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x + (m_tInfo.fCX * 0.3f)), LONG(m_tPosin.y + (m_tInfo.fCY * 0.3f)));
//    }
//
//    if (MY_LEFT == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x - (m_tInfo.fCX * 0.3f)), m_tPosin.y);
//    }
//
//    if (MY_RIGHT == _eDriect)
//    {
//        pScrewBullet->Set_Pos(LONG(m_tPosin.x + (m_tInfo.fCX * 0.3f)), m_tPosin.y);
//    }
//
//    if (MY_CENTER == _eDriect)
//    {
//        pScrewBullet->Set_Pos(m_tPosin.x, m_tPosin.y);
//    }
//
//    if (MY_PRACTICE == _eDriect)
//    {
//        pScrewBullet->Set_Pos(m_tPosin.x, m_tPosin.y);
//    }
//    pScrewBullet->Set_Angle(m_fAngle);
//
//    return pScrewBullet;
//}
